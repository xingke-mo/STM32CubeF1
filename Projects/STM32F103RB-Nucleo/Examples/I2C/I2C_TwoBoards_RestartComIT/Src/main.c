/**
  ******************************************************************************
  * @file    I2C/I2C_TwoBoards_RestartComIT/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use STM32F1xx I2C HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          IT transfer and with a repeated start condition between the transmit
  *          and receive process.
  *          The communication is done using 2 Boards.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
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

/** @addtogroup I2C_TwoBoards_RestartComIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Uncomment this line to use the board as master, if not it is used as slave */
//#define MASTER_BOARD
#define I2C_ADDRESS        0x30F

/* I2C SPEEDCLOCK define to max value: 400 KHz on STM32F1xx*/
#define I2C_SPEEDCLOCK   400000
#define I2C_DUTYCYCLE    I2C_DUTYCYCLE_2
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
I2C_HandleTypeDef I2cHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****I2C_TwoBoards advanced communication based on IT****  ****I2C_TwoBoards advanced communication based on IT****  ****I2C_TwoBoards advanced communication based on IT**** ";

/* Buffer used for reception */
uint8_t aRxBuffer[RXBUFFERSIZE];

#ifndef MASTER_BOARD
    /* Variable used to trig an address match code event */
    __IO uint32_t     uwTransferReadRequested = 0;
    __IO uint32_t     uwTransferWriteRequested = 0;
#endif

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config( void );
static uint16_t Buffercmp( uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength );
static void Error_Handler( void );

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main( void )
{
    /* STM32F1xx HAL library initialization:
         - Configure the Flash prefetch
         - Systick timer is configured by default as source of time base, but user
           can eventually implement his proper time base source (a general purpose
           timer for example or other time source), keeping in mind that Time base
           duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
           handled in milliseconds basis.
         - Set NVIC Group Priority to 4
         - Low Level Initialization
       */
    HAL_Init();

    /* Configure the system clock to 64 MHz */
    SystemClock_Config();

    /* Configure LED2 */
    BSP_LED_Init( LED2 );


    /*##-1- Configure the I2C peripheral ######################################*/
    I2cHandle.Instance              = I2Cx;
    I2cHandle.Init.ClockSpeed       = I2C_SPEEDCLOCK;
    I2cHandle.Init.DutyCycle        = I2C_DUTYCYCLE;
    I2cHandle.Init.AddressingMode   = I2C_ADDRESSINGMODE_10BIT;
    I2cHandle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
    I2cHandle.Init.OwnAddress1      = I2C_ADDRESS;
    I2cHandle.Init.OwnAddress2      = 0xFF;

    if( HAL_I2C_Init( &I2cHandle ) != HAL_OK )
    {
        /* Initialization Error */
        Error_Handler();
    }


#ifdef MASTER_BOARD

    /* Configure Key push-button */
    BSP_PB_Init( BUTTON_KEY, BUTTON_MODE_GPIO );

    /* Wait for Key push-button press before starting the Communication */
    while( BSP_PB_GetState( BUTTON_KEY ) != GPIO_PIN_RESET )
    {
    }

    /* Wait for Key push-button release before starting the Communication */
    while( BSP_PB_GetState( BUTTON_KEY ) != GPIO_PIN_SET )
    {
    }

    /* The board sends the message and expects to receive it back */

    /*##-2- Start the transmission process #####################################*/
    /* While the I2C in reception process, user can transmit data through
       "aTxBuffer" buffer */
    do
    {
        if( HAL_I2C_Master_Seq_Transmit_IT( &I2cHandle, ( uint16_t )I2C_ADDRESS, ( uint8_t * )aTxBuffer, TXBUFFERSIZE, I2C_FIRST_FRAME ) != HAL_OK )
        {
            /* Error_Handler() function is called when error occurs. */
            Error_Handler();
        }

        /*##-3- Wait for the end of the transfer #################################*/
        /*  Before starting a new communication transfer, you need to check the current
            state of the peripheral; if it�s busy you need to wait for the end of current
            transfer before starting a new one.
            For simplicity reasons, this example is just waiting till the end of the
            transfer, but application may perform other tasks while transfer operation
            is ongoing. */
        while( HAL_I2C_GetState( &I2cHandle ) != HAL_I2C_STATE_READY )
        {
        }

        /* When Acknowledge failure occurs (Slave don't acknowledge it's address)
           Master restarts communication */
    } while( HAL_I2C_GetError( &I2cHandle ) == HAL_I2C_ERROR_AF );

    /* Wait for Key push-button press before starting the Communication */
    while( BSP_PB_GetState( BUTTON_KEY ) != GPIO_PIN_RESET )
    {
    }

    /* Wait for Key push-button release before starting the Communication */
    while( BSP_PB_GetState( BUTTON_KEY ) != GPIO_PIN_SET )
    {
    }

    /*##-4- Put I2C peripheral in reception process ############################*/
    do
    {
        if( HAL_I2C_Master_Seq_Receive_IT( &I2cHandle, ( uint16_t )I2C_ADDRESS, ( uint8_t * )aRxBuffer, RXBUFFERSIZE, I2C_LAST_FRAME ) != HAL_OK )
        {
            /* Error_Handler() function is called when error occurs. */
            Error_Handler();
        }

        /*##-5- Wait for the end of the transfer #################################*/
        /*  Before starting a new communication transfer, you need to check the current
            state of the peripheral; if it�s busy you need to wait for the end of current
            transfer before starting a new one.
            For simplicity reasons, this example is just waiting till the end of the
            transfer, but application may perform other tasks while transfer operation
            is ongoing. */
        while( HAL_I2C_GetState( &I2cHandle ) != HAL_I2C_STATE_READY )
        {
        }

        /* When Acknowledge failure occurs (Slave don't acknowledge it's address)
           Master restarts communication */
    } while( HAL_I2C_GetError( &I2cHandle ) == HAL_I2C_ERROR_AF );

#else

    /* The board receives the message and sends it back */

    /*##-3- Put I2C peripheral in listen mode process ###########################*/
    if( HAL_I2C_EnableListen_IT( &I2cHandle ) != HAL_OK )
    {
        /* Transfer error in reception process */
        Error_Handler();
    }

    /*##-4- Wait Address Match Code event ######################################*/
    /*  Before starting a transfer, you need to wait a Master request event.
        For simplicity reasons, this example is just waiting till an Address callback event,
        but application may perform other tasks while transfer operation is ongoing. */
    while( uwTransferReadRequested != 1 )
    {
    }

    /*##-5- Put I2C peripheral in reception process ############################*/
    if( HAL_I2C_Slave_Seq_Receive_IT( &I2cHandle, ( uint8_t * )aRxBuffer, RXBUFFERSIZE, I2C_FIRST_FRAME ) != HAL_OK )
    {
        /* Transfer error in reception process */
        Error_Handler();
    }

    /*##-6- Wait for the end of the transfer ###################################*/
    /*  Before starting a new communication transfer, you need to check the current
        state of the peripheral; if it�s busy you need to wait for the end of current
        transfer before starting a new one.
        For simplicity reasons, this example is just waiting till the end of the
        transfer, but application may perform other tasks while transfer operation
        is ongoing. */
    while( HAL_I2C_GetState( &I2cHandle ) != HAL_I2C_STATE_LISTEN )
    {
    }

    /*##-7- Wait Address Match Code event ######################################*/
    /*  Before starting a transfer, you need to wait a Master request event.
        For simplicity reasons, this example is just waiting till an Address callback event,
        but application may perform other tasks while transfer operation is ongoing. */
    while( uwTransferWriteRequested != 1 )
    {
    }

    /*##-8- Start the transmission process #####################################*/
    /* While the I2C in reception process, user can transmit data through
       "aTxBuffer" buffer */
    if( HAL_I2C_Slave_Seq_Transmit_IT( &I2cHandle, ( uint8_t * )aTxBuffer, TXBUFFERSIZE, I2C_LAST_FRAME ) != HAL_OK )
    {
        /* Transfer error in transmission process */
        Error_Handler();
    }

#endif /* MASTER_BOARD */

    /*##-5- Wait for the end of the transfer ###################################*/
    /*  Before starting a new communication transfer, you need to check the current
        state of the peripheral; if it�s busy you need to wait for the end of current
        transfer before starting a new one.
        For simplicity reasons, this example is just waiting till the end of the
        transfer, but application may perform other tasks while transfer operation
        is ongoing. */
    while( HAL_I2C_GetState( &I2cHandle ) != HAL_I2C_STATE_READY )
    {
    }

    /*##-6- Compare the sent and received buffers ##############################*/
    if( Buffercmp( ( uint8_t * )aTxBuffer, ( uint8_t * )aRxBuffer, RXBUFFERSIZE ) )
    {
        /* Processing Error */
        Error_Handler();
    }

    /* Infinite loop */
    while( 1 )
    {
    }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLLMUL                         = 16
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config( void )
{
    RCC_ClkInitTypeDef clkinitstruct = {0};
    RCC_OscInitTypeDef oscinitstruct = {0};

    /* Configure PLL ------------------------------------------------------*/
    /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
    /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
    /* Enable HSI and activate PLL with HSi_DIV2 as source */
    oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
    oscinitstruct.HSEState        = RCC_HSE_OFF;
    oscinitstruct.LSEState        = RCC_LSE_OFF;
    oscinitstruct.HSIState        = RCC_HSI_ON;
    oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    oscinitstruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
    oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
    oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;

    if( HAL_RCC_OscConfig( &oscinitstruct ) != HAL_OK )
    {
        /* Initialization Error */
        while( 1 );
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
       clocks dividers */
    clkinitstruct.ClockType = ( RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 );
    clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;

    if( HAL_RCC_ClockConfig( &clkinitstruct, FLASH_LATENCY_2 ) != HAL_OK )
    {
        /* Initialization Error */
        while( 1 );
    }
}

/**
  * @brief  Tx Transfer completed callback.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report end of IT Tx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
#ifdef MASTER_BOARD
void HAL_I2C_MasterTxCpltCallback( I2C_HandleTypeDef *I2cHandle )
{
    /* Turn LED2 on: Transfer in transmission process is correct */
    BSP_LED_On( LED2 );
}
#else
void HAL_I2C_SlaveTxCpltCallback( I2C_HandleTypeDef *I2cHandle )
{
    /* Reset address match code event */
    uwTransferWriteRequested = 0;

    /* Turn LED2 off: Transfer in transmission process is correct */
    BSP_LED_Off( LED2 );
}
#endif /* MASTER_BOARD */

/**
  * @brief  Rx Transfer completed callback.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report end of IT Rx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
#ifdef MASTER_BOARD
void HAL_I2C_MasterRxCpltCallback( I2C_HandleTypeDef *I2cHandle )
{
    /* Turn LED2 off: Transfer in reception process is correct */
    BSP_LED_Off( LED2 );
}
#else
void HAL_I2C_SlaveRxCpltCallback( I2C_HandleTypeDef *I2cHandle )
{
    /* Reset address match code event */
    uwTransferReadRequested = 0;

    /* Turn LED2 on: Transfer in reception process is correct */
    BSP_LED_On( LED2 );
}
#endif /* MASTER_BOARD */

#ifndef MASTER_BOARD
/**
  * @brief  Slave Address Match callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  TransferDirection: Master request Transfer Direction (Write/Read), value of @ref I2C_XferDirection_definition
  * @param  AddrMatchCode: Address Match Code
  * @retval None
  */
void HAL_I2C_AddrCallback( I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode )
{
    if( TransferDirection == I2C_DIRECTION_TRANSMIT )
    {
        uwTransferReadRequested = 1;
    }
    else if( TransferDirection == I2C_DIRECTION_RECEIVE )
    {
        uwTransferWriteRequested = 1;
    }

    /* A new communication with a Master is initiated */
    /* Turn LED2 On: A Communication is initiated */
    BSP_LED_On( LED2 );
}

/**
  * @brief  Listen Complete callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_ListenCpltCallback( I2C_HandleTypeDef *hi2c )
{
    /* Turn LED2 off: Communication is completed */
    BSP_LED_Off( LED2 );
}
#endif

/**
  * @brief  I2C error callbacks.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_I2C_ErrorCallback( I2C_HandleTypeDef *I2cHandle )
{
    /** Error_Handler() function is called when error occurs.
      * 1- When Slave doesn't acknowledge its address, Master restarts communication.
      * 2- When Master doesn't acknowledge the last data transferred, Slave doesn't care in this example.
      */
    if( HAL_I2C_GetError( I2cHandle ) != HAL_I2C_ERROR_AF )
    {
        Error_Handler();
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler( void )
{
    /* Error if LED2 is slowly blinking (1 sec. period) */
    while( 1 )
    {
        BSP_LED_Toggle( LED2 );
        HAL_Delay( 1000 );
    }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 0  : pBuffer1 identical to pBuffer2
  *         >0 : pBuffer1 differs from pBuffer2
  */
static uint16_t Buffercmp( uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength )
{
    while( BufferLength-- )
    {
        if( ( *pBuffer1 ) != *pBuffer2 )
        {
            return BufferLength;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed( uint8_t *file, uint32_t line )
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while( 1 )
    {
    }
}
#endif


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
