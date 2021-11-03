/**
  ******************************************************************************
  * @file    pr_profile_application.c
  * @author  AAS / CL
  * @brief   This file implements the main function executing the Proximity
  *          Reporter profile
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/*******************************************************************************
 * Include Files
*******************************************************************************/
#include <host_config.h>
#if (PLATFORM_WINDOWS == 1)
#include <Windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <bluenrg_types.h>
#include <bluenrg_def.h>
#include <debug.h>
#include <ble_list.h>
#include <hci_const.h>
#include <ble_profile.h>
#include <ble_events.h>
#include <timer.h>
#include "low_power_conf.h"
#include "stm32xx_timerserver.h"
#include "profile_application.h"
#include <proximity_reporter.h>

#include "hci_tl_interface.h"

#if (BLE_CURRENT_PROFILE_ROLES & PROXIMITY_REPORTER)
/*******************************************************************************
 * Macros
*******************************************************************************/
#define PR_TIMER_VALUE	1000000 /**< Value in us */
#define MILD_ALERT_BLINK 6
#define HIGH_ALERT_BLINK 2
#define REPEAT_BLINK     9

/******************************************************************************
 * Local Variable Declarations
******************************************************************************/
int PR_Start_Timer = 0;
uint8_t  blinkTimer_Id;
uint32_t blink_delay;

/******************************************************************************
 * Global Variable Declarations
******************************************************************************/
extern tProfileApplContext profileApplContext; /* Profile Application Context */

/******************************************************************************
 * Function Declarations
******************************************************************************/
void PRProfileGetAddress(uint8_t* addr);
void PR_Set_Alert_Level(uint8_t level);
void Blink_Handler(void);
tBleStatus Blink_Timer_Start(uint32_t expiryTime,
                             TIMER_TIMEOUT_NOTIFY_CALLBACK_TYPE timercb,
                             tTimerID *timerID);
void Init_Current_Time(void);
void Profile_Appl_Evt_Notify(tNotificationEvent event,uint8_t evtLen,uint8_t* evtData);
void Init_Profile(void);
void Advertize(void);
static void PR_Application_Process(void);
static void PR_Process_Reporting(void);

/******************************************************************************
 * Function Definitions 
******************************************************************************/

/**
 * @brief  Initialize the Application Context for using the Proximity Reporter
 *         profile methods
 * @param  The profile application context
 * @retval None
 */
void PR_Appl_Context_Init(void)
{
  if (profileApplContext.profileGetAddressFunc == NULL)
  {
    profileApplContext.profileGetAddressFunc = PRProfileGetAddress;
  }
  
  if (profileApplContext.profileApplNotifyFunc == NULL)
  {
    profileApplContext.profileApplNotifyFunc = Profile_Appl_Evt_Notify;
  }
  
  if (profileApplContext.initProfileFunc == NULL)
  {
    profileApplContext.initProfileFunc = Init_Profile;
  }
  
  if (profileApplContext.advertizeFunc == NULL)
  {
    profileApplContext.advertizeFunc = Advertize;
  }

  if (profileApplContext.profileStateMachineFunc == NULL)
  {
    profileApplContext.profileStateMachineFunc = ProximityReporterProfile_StateMachine;
  }
  
  if (profileApplContext.profileApplicationProcessFunc == NULL)
  {
    profileApplContext.profileApplicationProcessFunc = PR_Application_Process;
  }
  
  if (profileApplContext.profileProcessMeasurementFunc == NULL)
  {
    profileApplContext.profileProcessMeasurementFunc = PR_Process_Reporting;
  }
    
}

/**
 * @brief This function sets PR specific address
 * @param The profile address
 * @retval None
 */
void PRProfileGetAddress(uint8_t* addr)
{
  uint8_t PROFILE_ADDR[] = {0x12, 0x34, 0x12, 0xE1, 0x80, 0x02};
  
  BLUENRG_memcpy(addr, PROFILE_ADDR, sizeof(PROFILE_ADDR));
}

/**
 * @brief  Profile Application Event Notify
 * @param  Event
 * @param  Event length
 * @param  Event data
 * @retval None
 */
void Profile_Appl_Evt_Notify (tNotificationEvent event,uint8_t evtLen,uint8_t* evtData)
{  
  switch(event)
  {
  case EVT_MP_CONNECTION_COMPLETE:
    {
      BSP_LED_Off(LED2);
    }
    break;    
  case EVT_PR_INITIALIZED:
    {
      APPL_MESG_DBG(profiledbgfile,"EVT_PR_INITIALIZED\n");
      BLE_Profile_Write_DeviceState(APPL_INIT_DONE);
    }
    break;
  case EVT_PR_PATH_LOSS_ALERT:
    {
      APPL_MESG_DBG(profiledbgfile,"EVT_PR_PATH_LOSS_ALERT %d\n",evtData[0]);
      BLE_Profile_Write_DeviceState(APPL_INIT_DONE);
      switch(evtData[0])
      {
      case 0:
        BSP_LED_Off(LED2);
        break;
      case 1:
      case 2:
        PR_Set_Alert_Level(evtData[0]);
        break;
      }
    }
    break;
  case EVT_PR_LINK_LOSS_ALERT:
    {
      APPL_MESG_DBG(profiledbgfile,"EVT_PR_LINK_LOSS_ALERT %d\n",evtData[0]);
      BLE_Profile_Write_DeviceState(APPL_INIT_DONE);
      switch(evtData[0])
      {
      case 0:
        BSP_LED_Off(LED2);
        break;
      case 1:
      case 2:
        PR_Set_Alert_Level(evtData[0]);
        break;
      }
    }
    break;
  }
  
}/* end Profile_Appl_Evt_Notify() */


/**
 * @brief  This function initializes the Proximity Reporter Profile by calling the
 *         function ProximityReporter_Init().
 * @param  None
 * @retval None
 */
void Init_Profile(void)
{
  PRINTF ("Test Application: Initializing Proximity Reporter profile\n");
  
  /* LED2 is used for signaling the presence of the target */
  BSP_LED_Init(LED2);
  
  if (ProximityReporter_Init(0xff,BLE_Profiles_Evt_Notify_Cb) == 
      BLE_STATUS_SUCCESS)
  {
    APPL_MESG_DBG(profiledbgfile,"Initialized Proximity Reporter Profile \n" );
  }
  else
  {
    APPL_MESG_DBG(profiledbgfile,"Proximity Reporter Profile init failure\n" );
  }
  
}/* end Init_Profile() */


/**
 * @brief  This function enables advertising.
 * @param  None
 * @retval None
 */
void Advertize(void)
{  
  APPL_MESG_DBG(profiledbgfile,"enable advertising\n");
  ProximityReporter_Make_Discoverable(0x00);
}/* end Advertize() */


/**
 * @brief  Application specific processing
 * @param  None
 * @retval None
 */
static void PR_Application_Process(void)
{
  switch(BLE_Profile_Read_DeviceState())
  { 
  case APPL_INIT_DONE:
    {
      if(PR_Start_Timer == 1)
      {
        /**
    	 * Make sure to stop the timer only when it has been started at least once
    	 * The Timer ID must be existing to call TIMER_Stop();
    	 */
    	TIMER_Stop(profileApplContext.profileTimer_Id);
    	PR_Start_Timer = 0;
      }
      Advertize();
      BLE_Profile_Write_DeviceState(APPL_ADVERTISING);
    }
    break;
  case APPL_TERMINATE_LINK:
    {
      /* on disconnection complete, the state will be changed to INIT_DONE
      */ 
      BLE_Profile_Disconnect();
      BLE_Profile_Write_DeviceState(APPL_UNINITIALIZED);
    }
    break;
  case APPL_CONNECTED:
    {
      if (PR_Start_Timer == 0)
      {
        TIMER_Start(profileApplContext.profileTimer_Id, (uint16_t)(PR_TIMER_VALUE/TIMERSERVER_TICK_VALUE));
        PR_Start_Timer = 1;
      }
    }
    break;
  default:
    break;
  }
  return;
}

void PR_Set_Alert_Level(uint8_t level) {
  
  if (level == MILD_ALERT) blink_delay = MILD_ALERT_BLINK;
  if (level == HIGH_ALERT) blink_delay = HIGH_ALERT_BLINK;
  
  BSP_LED_Off(LED2);
  Blink_Timer_Start(blink_delay, Blink_Handler, &blinkTimer_Id);

}

void Blink_Handler(void)
{
  static uint8_t repeat = REPEAT_BLINK;
  
  Blue_NRG_Timer_Stop(blinkTimer_Id);
  
  if (repeat > 0) {
    BSP_LED_Toggle(LED2);
    Blink_Timer_Start(blink_delay, Blink_Handler, &blinkTimer_Id);    
    repeat--;
  }
  else {    
    repeat = REPEAT_BLINK;
  }
  return;
}

tBleStatus Blink_Timer_Start(uint32_t expiryTime,
                                TIMER_TIMEOUT_NOTIFY_CALLBACK_TYPE timercb,
                                tTimerID *timerID)
{
  TIMER_Create(eTimerModuleID_BlueNRG_Profile, timerID, eTimerMode_SingleShot, (pf_TIMER_TimerCallBack_t) timercb);
  TIMER_Start(*timerID, expiryTime*100000/TIMERSERVER_TICK_VALUE);
  return (BLE_STATUS_SUCCESS);
}

static void PR_Process_Reporting(void)
{
  return;  
}

#endif  /* (BLE_CURRENT_PROFILE_ROLES & PROXIMITY_REPORTER) */
