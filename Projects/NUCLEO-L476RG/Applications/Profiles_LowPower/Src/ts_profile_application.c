/**
  ******************************************************************************
  * @file    ts_profile_application.c
  * @author  AAS / CL
  * @brief   This file implements the main function executing the Time Server
  *          profile
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
#include "bluenrg_types.h"
#include "bluenrg_def.h"
#include <debug.h>
#include <ble_list.h>
#include <hci_const.h>
#include <ble_profile.h>
#include <ble_events.h>
#include <timer.h>
#include "stm32xx_timerserver.h"
#include "profile_application.h"
#include "low_power_conf.h"
#include <time_server.h>
#include <time_profile_types.h>

#include "hci_tl_interface.h"

#if (BLE_CURRENT_PROFILE_ROLES & TIME_SERVER)
/*******************************************************************************
 * Macros
*******************************************************************************/
#define TS_TIMER_VALUE	1000000 /**< Value in us */

/******************************************************************************
 * Local Variable Declarations
******************************************************************************/
tCurrentTime time;
int TS_Start_Timer = 0;

/******************************************************************************
 * Global Variable Declarations
******************************************************************************/
extern tProfileApplContext profileApplContext; /* Profile Application Context */
extern volatile uint8_t send_measurement;

/******************************************************************************
 * Function Declarations
******************************************************************************/
void TSProfileGetAddress(uint8_t* addr);
void Init_Current_Time(void);
void Profile_Appl_Evt_Notify(tNotificationEvent event,uint8_t evtLen,uint8_t* evtData);
void Init_Profile(void);
void Advertize(void);
static int TS_Application_Process(void);

/******************************************************************************
 * Function Definitions 
******************************************************************************/

/**
 * @brief  Initialize the Application Context for using the Time Server
 *         profile methods
 * @param  None
 * @retval None
 */
void TS_Appl_Context_Init(void)
{
  if (profileApplContext.profileGetAddressFunc == NULL)
  {
    profileApplContext.profileGetAddressFunc = TSProfileGetAddress;
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
    profileApplContext.profileStateMachineFunc = TimeServer_StateMachine;
  }
  
  if (profileApplContext.profileApplicationProcessFunc == NULL)
  {
    profileApplContext.profileApplicationProcessFunc = TS_Application_Process;
  }
  
  Init_Current_Time();
}

/**
 * @brief This function sets TS specific address
 * @param The profile address
* @retval None
 */
void TSProfileGetAddress(uint8_t* addr)
{
  uint8_t PROFILE_ADDR[] = {0x12, 0x34, 0x10, 0xE1, 0x80, 0x02};
  
  BLUENRG_memcpy(addr, PROFILE_ADDR, sizeof(PROFILE_ADDR));
}

/** 
* @brief  Initialize the current time.
* @param  None
* @retval None
*/
void Init_Current_Time(void)
{
  time.date = 14;
  time.day_of_week = WEDNESDAY;
  time.hours = 1;
  time.minutes = 1;
  time.seconds = 4;
  
  /* NOTES: Values to be set for running PTS tests CTS, CSP */
  time.adjustReason = 0x01; /* ADJUST_REASON_MANUAL_TIME_UPDATE: TP/CSP/BV-02-C */
  //time.adjustReason = 0x04; /* ADJUST_REASON_CHANGE_OF_TIME_ZONE: TP/CSP/BV-03-C */
  //time.adjustReason = 0x08; /* ADJUST_REASON_CHANGE_OF_DST:     TP/CSP/BV-04-C */
  //time.adjustReason = 0x02; /* ADJUST_REASON_EXTERNAL_REFERENCE_TIME_UPDATE: TP/CSP/BV-05-C, TP/CSP/BV-06-C*/
  
  time.fractions256 = 0x00;
  time.month = 10;
  time.year = 2015;

}

/**
 * @brief  Update time before sending.
 * @param  Update interval (in sec)
 * @retval None
 */
void Update_Current_Time(uint8_t time_interval)
{
  time.seconds += time_interval;
  if (time.seconds >= 60)
  {
    time.seconds = time.seconds % 60;
    time.minutes++;
  }
  if (time.minutes == 60)
  {
    time.minutes = 0;
    time.hours++;
  }  
}

/**
 * @brief  Profile Application Event Notify.
 * @param  Event
 * @param  Event length
 * @param  Event data
 * @retval None
 */
void Profile_Appl_Evt_Notify (tNotificationEvent event,uint8_t evtLen,uint8_t* evtData)
{  
  switch(event)
  {
  case EVT_TS_INITIALIZED:
    {
      APPL_MESG_DBG(profiledbgfile,"EVT_TS_INITIALIZED\n");
      BLE_Profile_Write_DeviceState(APPL_INIT_DONE);
    }
    break;
  case EVT_TS_START_REFTIME_UPDATE:
    {
      APPL_MESG_DBG(profiledbgfile,"EVT_TS_START_REFTIME_UPDATE\n");
      TimeServer_Update_Current_Time_Value(time);
    }
    break;
  case EVT_TS_CHAR_UPDATE_CMPLT:
    {
      APPL_MESG_DBG(profiledbgfile,"EVT_TS_CHAR_UPDATE_CMPLT\n");
      BLE_Profile_Write_DeviceState(APPL_CONNECTED);
    }
    break;
  case EVT_TS_CURTIME_READ_REQ:
    {
      APPL_MESG_DBG(profiledbgfile,"EVT_TS_CURTIME_READ_REQ\n");
      Allow_Curtime_Char_Read();
    }
    break;
  }
  
}/* end Profile_Appl_Evt_Notify() */


/**
 * @brief  This function initializes the Time Server Profile by calling the
 *         function TimeServer_Init().
 * @param  None
 * @retval None
 */
void Init_Profile(void)
{
  PRINTF ("Test Application: Initializing Find me profile\n");
  if (TimeServer_Init (NEXT_DST_CHANGE_SERVICE_BITMASK|REFERENCE_TIME_UPDATE_SERVICE_BITMASK, 
                       BLE_Profiles_Evt_Notify_Cb) == BLE_STATUS_SUCCESS)
  {
    APPL_MESG_DBG(profiledbgfile,"Initialized Time Server Profile \n" );
  }
  else
  {
    APPL_MESG_DBG(profiledbgfile,"Failed Time Server Profile \n" );
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
  TimeServer_Make_Discoverable(0x00);
}/* end Advertize() */


/**
 * @brief  Application specific processing
 * @param  None
 * @retval int
 */
static int TS_Application_Process(void)
{
  uint8_t status;
  int ret_val = 1;
  int32_t uwPRIMASK_Bit = __get_PRIMASK();	/**< backup PRIMASK bit */

  switch(BLE_Profile_Read_DeviceState())
  { 
  case APPL_UNINITIALIZED:
    break;
  case APPL_INIT_DONE:
    {
      if(TS_Start_Timer == 1)
      {
        /**
    	 * Make sure to stop the timer only when it has been started at least once
    	 * The Timer ID must be existing to call TIMER_Stop();
    	 */
    	TIMER_Stop(profileApplContext.profileTimer_Id);
    	TS_Start_Timer = 0;
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
      if (TS_Start_Timer == 0)
      {
        TIMER_Start(profileApplContext.profileTimer_Id, (uint16_t)(TS_TIMER_VALUE/TIMERSERVER_TICK_VALUE));
        TS_Start_Timer = 1;
      }
      BLE_Profile_Write_DeviceState(APPL_WAIT);
    }
    break;
  default:
      if (send_measurement != 0) {
        
        __disable_irq();  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/
        send_measurement = 0;
        __set_PRIMASK(uwPRIMASK_Bit);  /**< Restore PRIMASK bit*/
        BLE_Profile_Write_DeviceState(APPL_WAIT);
        
        Update_Current_Time((uint8_t)(UPDATE_INTERVAL/1000));
        
        status = TimeServer_Update_Current_Time_Value(time);
        APPL_MESG_DBG(profiledbgfile,"updating current time status is %d\n", status);
        
      }else{
        ret_val = 0;
      }

    break;
  }
  return ret_val;
}

#endif  /* (BLE_CURRENT_PROFILE_ROLES & TIME_SERVER) */
