/**
  ******************************************************************************
  * @file    BSP/Src/joystick.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the joystick feature in the
  *          STM3210C_EVAL driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F1xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static JOYState_TypeDef JoyState = JOY_NONE;
/* Private function prototypes -----------------------------------------------*/
static void Joystick_SetHint( void );
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Joystick demo
  * @param  None
  * @retval None
  */
void Joystick_demo( void )
{
    static uint16_t xPtr = 12;
    static uint16_t yPtr = 92;
    static uint16_t old_xPtr = 12;
    static uint16_t old_yPtr = 92;

    Joystick_SetHint();

    if( BSP_JOY_Init( JOY_MODE_GPIO ) != IO_OK )
    {
        BSP_LCD_SetBackColor( LCD_COLOR_WHITE );
        BSP_LCD_SetTextColor( LCD_COLOR_RED );
        BSP_LCD_DisplayStringAt( 0, BSP_LCD_GetYSize() - 95, ( uint8_t * )"ERROR", CENTER_MODE );
        BSP_LCD_DisplayStringAt( 0, BSP_LCD_GetYSize() - 80, ( uint8_t * )"Joystick cannot be initialized", CENTER_MODE );

        if( CheckForUserInput() > 0 )
        {
            return;
        }
    }

    while( 1 )
    {
        /* Get the Joystick State */
        JoyState = BSP_JOY_GetState();

        switch( JoyState )
        {
        case JOY_UP:
            if( yPtr > 92 )
            {
                yPtr--;
            }

            break;

        case JOY_DOWN:
            if( yPtr < ( BSP_LCD_GetYSize() - 12 - 11 ) )
            {
                yPtr++;
            }

            break;

        case JOY_LEFT:
            if( xPtr > 12 )
            {
                xPtr--;
            }

            break;

        case JOY_RIGHT:
            if( xPtr < ( BSP_LCD_GetXSize() - 8 - 11 ) )
            {
                xPtr++;
            }

            break;

        default:
            break;
        }

        BSP_LCD_SetBackColor( LCD_COLOR_WHITE );
        BSP_LCD_SetTextColor( LCD_COLOR_BLUE );

        if( JoyState == JOY_SEL )
        {
            BSP_LCD_SetTextColor( LCD_COLOR_RED );
            BSP_LCD_DisplayChar( xPtr, yPtr, 'X' );

        }
        else if( JoyState == JOY_NONE )
        {
            BSP_LCD_SetTextColor( LCD_COLOR_BLUE );
            BSP_LCD_DisplayChar( xPtr, yPtr, 'X' );
        }
        else
        {
            BSP_LCD_SetTextColor( LCD_COLOR_WHITE );
            BSP_LCD_DisplayChar( old_xPtr, old_yPtr, 'X' );
            BSP_LCD_SetTextColor( LCD_COLOR_BLUE );
            BSP_LCD_DisplayChar( xPtr, yPtr, 'X' );

            old_xPtr = xPtr;
            old_yPtr = yPtr;
        }

        if( CheckForUserInput() > 0 )
        {
            return;
        }

        HAL_Delay( 5 );
    }
}

/**
  * @brief  Display joystick demo hint
  * @param  None
  * @retval None
  */
static void Joystick_SetHint( void )
{
    /* Clear the LCD */
    BSP_LCD_Clear( LCD_COLOR_WHITE );

    /* Set Joystick Demo description */
    BSP_LCD_SetTextColor( LCD_COLOR_BLUE );
    BSP_LCD_FillRect( 0, 0, BSP_LCD_GetXSize(), 80 );
    BSP_LCD_SetTextColor( LCD_COLOR_WHITE );
    BSP_LCD_SetBackColor( LCD_COLOR_BLUE );
    BSP_LCD_SetFont( &Font24 );
    BSP_LCD_DisplayStringAt( 0, 0, ( uint8_t * )"Joystick", CENTER_MODE );
    BSP_LCD_SetFont( &Font12 );
    BSP_LCD_DisplayStringAt( 0, 30, ( uint8_t * )"Please use the joystick to move the pointer", CENTER_MODE );
    BSP_LCD_DisplayStringAt( 0, 45, ( uint8_t * )"inside the rectangle, to switch to next menu", CENTER_MODE );
    BSP_LCD_DisplayStringAt( 0, 60, ( uint8_t * )"press Key push-button.", CENTER_MODE );

    /* Set the LCD Text Color */
    BSP_LCD_SetTextColor( LCD_COLOR_BLUE );
    BSP_LCD_DrawRect( 10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 100 );
    BSP_LCD_DrawRect( 11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize() - 102 );
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
