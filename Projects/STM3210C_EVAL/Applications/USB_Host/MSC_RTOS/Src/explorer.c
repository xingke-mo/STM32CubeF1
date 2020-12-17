/**
  ******************************************************************************
  * @file    USB_Host/MSC_RTOS/Src/explorer.c
  * @author  MCD Application Team
  * @brief   Explore the USB flash disk content
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

/* Includes ------------------------------------------------------------------ */
#include "main.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
/* Private function prototypes ----------------------------------------------- */
/* Private functions --------------------------------------------------------- */

/**
  * @brief  Displays disk content.
  * @param  path: Pointer to root path
  * @param  recu_level: Disk content level
  * @retval Operation result
  */
FRESULT Explore_Disk( char *path, uint8_t recu_level )
{
    FRESULT res = FR_OK;
    FILINFO fno;
    DIR dir;
    char *fn;
    char tmp[14];
    uint8_t line_idx = 0;

#if _USE_LFN
    static char lfn[_MAX_LFN + 1];  /* Buffer to store the LFN */
    fno.lfname = lfn;
    fno.lfsize = sizeof lfn;
#endif

    res = f_opendir( &dir, path );

    if( res == FR_OK )
    {
        while( USBH_MSC_IsReady( &hUSBHost ) )
        {
            res = f_readdir( &dir, &fno );

            if( res != FR_OK || fno.fname[0] == 0 )
            {
                break;
            }

            if( fno.fname[0] == '.' )
            {
                continue;
            }

#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            strcpy( tmp, fn );

            line_idx++;

            if( line_idx > 9 )
            {
                line_idx = 0;
                LCD_UsrLog( "> Press [Key] To Continue.\n" );

                /* KEY Button in polling */
                while( BSP_PB_GetState( BUTTON_KEY ) != RESET )
                {
                    /* Wait for User Input */
                }
            }

            if( recu_level == 1 )
            {
                LCD_DbgLog( "   |__" );
            }
            else if( recu_level == 2 )
            {
                LCD_DbgLog( "   |   |__" );
            }

            if( ( fno.fattrib & AM_MASK ) == AM_DIR )
            {
                strcat( tmp, "\n" );
                LCD_UsrLog( ( void * )tmp );
            }
            else
            {
                strcat( tmp, "\n" );
                LCD_DbgLog( ( void * )tmp );
            }

            if( ( ( fno.fattrib & AM_MASK ) == AM_DIR ) && ( recu_level == 2 ) )
            {
                Explore_Disk( fn, 2 );
            }
        }

        f_closedir( &dir );
        LCD_UsrLog( "> Select an operation to Continue.\n" );
    }

    return res;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
