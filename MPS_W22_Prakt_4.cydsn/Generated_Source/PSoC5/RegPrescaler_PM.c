/*******************************************************************************
* File Name: RegPrescaler_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "RegPrescaler.h"

/* Check for removal by optimization */
#if !defined(RegPrescaler_Sync_ctrl_reg__REMOVED)

static RegPrescaler_BACKUP_STRUCT  RegPrescaler_backup = {0u};

    
/*******************************************************************************
* Function Name: RegPrescaler_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RegPrescaler_SaveConfig(void) 
{
    RegPrescaler_backup.controlState = RegPrescaler_Control;
}


/*******************************************************************************
* Function Name: RegPrescaler_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void RegPrescaler_RestoreConfig(void) 
{
     RegPrescaler_Control = RegPrescaler_backup.controlState;
}


/*******************************************************************************
* Function Name: RegPrescaler_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RegPrescaler_Sleep(void) 
{
    RegPrescaler_SaveConfig();
}


/*******************************************************************************
* Function Name: RegPrescaler_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RegPrescaler_Wakeup(void)  
{
    RegPrescaler_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
