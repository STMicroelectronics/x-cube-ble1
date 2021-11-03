/**
  ******************************************************************************
  * @file    user_timer.c
  * @author  AMS VMA RF Application team
  * @brief   User timer management
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

/* Includes ------------------------------------------------------------------*/
    
#include "user_timer.h"

tClockTime user_timer_expired = FALSE;

/**
  * @brief  Initialize a timer for application usage.
  * @retval None
  */
void Init_User_Timer(void)
{ 
  /* TIMx Peripheral clock enable */
  TIMx_CLK_ENABLE();
  
  /* Set TIMx instance */
  TimHandle.Instance = TIMx;
  TimHandle.Init.Period            = USER_TIMER_PERIOD;
  TimHandle.Init.Prescaler         = USER_TIMER_PRESCALER;
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_DOWN;
  
  /* Configure the NVIC for TIMx */  
  HAL_NVIC_SetPriority(TIMx_IRQn, 4, 0); 
  /* Enable the TIMx global Interrupt */
  HAL_NVIC_EnableIRQ(TIMx_IRQn);
  
  HAL_TIM_Base_Init(&TimHandle);
  __HAL_TIM_CLEAR_FLAG(&TimHandle,TIM_FLAG_UPDATE);

}

/**
  * @brief  Start the user timer
  * @retval None
  */
void Start_User_Timer(void)
{
  __HAL_TIM_SET_COUNTER(&TimHandle,0);
  
  HAL_TIM_Base_Start_IT(&TimHandle);
  
}

/**
  * @brief   Stop the user timer
  * @retval None
  */
void Stop_User_Timer(void)
{
  HAL_TIM_Base_Stop_IT(&TimHandle);
}

/**
  * @brief  Adjust user  timer prescaler when entering sleep mode
  * @retval None
  */
void User_Timer_Enter_Sleep(void)
{
  uint16_t cnt;
  
  if((&TimHandle)->Instance->CR1 & TIM_CR1_CEN)
  {
    __HAL_TIM_DISABLE_IT(&TimHandle, TIM_IT_UPDATE);
    __HAL_TIM_SET_PRESCALER(&TimHandle,USER_TIMER_PRESCALER_SLEEP);
    cnt = __HAL_TIM_GET_COUNTER(&TimHandle);
    (&TimHandle)->Instance->EGR = TIM_EVENTSOURCE_UPDATE; //TBR
    __HAL_TIM_SET_COUNTER(&TimHandle,cnt);
    __HAL_TIM_CLEAR_FLAG(&TimHandle,TIM_FLAG_UPDATE);
    __HAL_TIM_ENABLE_IT(&TimHandle, TIM_IT_UPDATE);
  }
}


/**
  * @brief  Adjust user timer prescaler when exiting sleep mode
  * @retval None
  */
void User_Timer_Exit_Sleep(void)
{  
  uint16_t cnt;
  
  if((&TimHandle)->Instance->CR1 & TIM_CR1_CEN)
  {
    __HAL_TIM_DISABLE_IT(&TimHandle, TIM_IT_UPDATE);  
    __HAL_TIM_SET_PRESCALER(&TimHandle,USER_TIMER_PRESCALER);
    cnt = __HAL_TIM_GET_COUNTER(&TimHandle);
    (&TimHandle)->Instance->EGR = TIM_EVENTSOURCE_UPDATE; //TBR
    __HAL_TIM_SET_COUNTER(&TimHandle,cnt);
    __HAL_TIM_CLEAR_FLAG(&TimHandle,TIM_FLAG_UPDATE);
    __HAL_TIM_ENABLE_IT(&TimHandle, TIM_IT_UPDATE);
  }    
}
