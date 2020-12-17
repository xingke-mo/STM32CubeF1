/**
  ******************************************************************************
  * @file    SPI/SPI_FullDuplex_ComPolling/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use STM32F1xx SPI HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          Polling transfer.
  *          The communication is done using 2 Boards.
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

/** @addtogroup SPI_FullDuplex_ComPolling
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Uncomment this line to use the board as master, if not it is used as slave */
//#define MASTER_BOARD

/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SPI_HandleTypeDef SpiHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = "****SPI - Two Boards communication based on Polling **** SPI Message ******** SPI Message ******** SPI Message ****";

/* Buffer used for reception */
uint8_t aRxBuffer[BUFFERSIZE];

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config( void );
static void Error_Handler( void );
static void Timeout_Error_Handler( void );
static uint16_t Buffercmp( uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength );

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
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

    /* Configure the system clock to 24 MHz */
    SystemClock_Config();

    /* Configure LED3 and LED4 */
    BSP_LED_Init( LED3 );
    BSP_LED_Init( LED4 );

    /*##-1- Configure the SPI peripheral #######################################*/
    /* Set the SPI parameters */
    SpiHandle.Instance               = SPIx;
    SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
    SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
    SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
    SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
    SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
    SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
    SpiHandle.Init.CRCPolynomial     = 7;
    SpiHandle.Init.NSS               = SPI_NSS_SOFT;

#ifdef MASTER_BOARD
    SpiHandle.Init.Mode = SPI_MODE_MASTER;
#else
    SpiHandle.Init.Mode = SPI_MODE_SLAVE;
#endif /* MASTER_BOARD */

    if( HAL_SPI_Init( &SpiHandle ) != HAL_OK )
    {
        /* Initialization Error */
        Error_Handler();
    }

#ifdef MASTER_BOARD
    /* SPI block is enabled prior calling SPI transmit/receive functions, in order to get CLK signal properly pulled down.
       Otherwise, SPI CLK signal is not clean on this board and leads to errors during transfer */
    __HAL_SPI_ENABLE( &SpiHandle );

    /* Configure User push-button */
    BSP_PB_Init( BUTTON_USER, BUTTON_MODE_GPIO );

    /* Wait for User push-button press before starting the Communication */
    while( BSP_PB_GetState( BUTTON_USER ) != GPIO_PIN_SET )
    {
        BSP_LED_Toggle( LED3 );
        HAL_Delay( 100 );
    }

    BSP_LED_Off( LED3 );
#endif /* MASTER_BOARD */

    /*##-2- Start the Full Duplex Communication process ########################*/
    /* While the SPI in TransmitReceive process, user can transmit data through
       "aTxBuffer" buffer & receive data through "aRxBuffer" */
    /* Timeout is set to 5S */

    switch( HAL_SPI_TransmitReceive( &SpiHandle, ( uint8_t * )aTxBuffer, ( uint8_t * )aRxBuffer, BUFFERSIZE, 5000 ) )
    {
    case HAL_OK:

        /* Communication is completed ___________________________________________ */
        /* Compare the sent and received buffers */
        if( Buffercmp( ( uint8_t * )aTxBuffer, ( uint8_t * )aRxBuffer, BUFFERSIZE ) )
        {
            /* Transfer error in transmission process */
            Error_Handler();
        }

        /* Turn LED2 on: Transfer in transmission/Reception process is correct */
        BSP_LED_On( LED3 );
        break;

    case HAL_TIMEOUT:
        /* A Timeout Occur ______________________________________________________*/
        /* Call Timeout Handler */
        Timeout_Error_Handler();
        break;

    /* An Error Occur ______________________________________________________ */
    case HAL_ERROR:
        /* Call Timeout Handler */
        Error_Handler();
        break;

    default:
        break;
    }

    /* Infinite loop */
    while( 1 )
    {
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler( void )
{
    /* Turn LED4 on */
    BSP_LED_On( LED4 );

    while( 1 )
    {
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Timeout_Error_Handler( void )
{
    /* Toggle LED4 on */
    while( 1 )
    {
        BSP_LED_On( LED4 );
        HAL_Delay( 500 );
        BSP_LED_Off( LED4 );
        HAL_Delay( 500 );
    }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 24000000
  *            HCLK(Hz)                       = 24000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 2
  *            PLLMUL                         = 6
  *            Flash Latency(WS)              = 0
  * @param  None
  * @retval None
  */
void SystemClock_Config( void )
{
    RCC_ClkInitTypeDef clkinitstruct = {0};
    RCC_OscInitTypeDef oscinitstruct = {0};

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
    oscinitstruct.HSEState        = RCC_HSE_ON;
    oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV2;
    oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
    oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL6;

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
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if( HAL_RCC_ClockConfig( &clkinitstruct, FLASH_LATENCY_0 ) != HAL_OK )
    {
        /* Initialization Error */
        while( 1 );
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
