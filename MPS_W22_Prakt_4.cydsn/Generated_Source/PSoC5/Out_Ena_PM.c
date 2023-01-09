/*******************************************************************************
* File Name: Out_Ena_PM.c
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

#include "Out_Ena.h"

/* Check for removal by optimization */
#if !defined(Out_Ena_Sync_ctrl_reg__REMOVED)

static Out_Ena_BACKUP_STRUCT  Out_Ena_backup = {0u};

    
/*******************************************************************************
* Function Name: Out_Ena_SaveConfig
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
void Out_Ena_SaveConfig(void) 
{
    Out_Ena_backup.controlState = Out_Ena_Control;
}


/*******************************************************************************
* Function Name: Out_Ena_RestoreConfig
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
void Out_Ena_RestoreConfig(void) 
{
     Out_Ena_Control = Out_Ena_backup.controlState;
}


/*******************************************************************************
* Function Name: Out_Ena_Sleep
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
void Out_Ena_Sleep(void) 
{
    Out_Ena_SaveConfig();
}


/*******************************************************************************
* Function Name: Out_Ena_Wakeup
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
void Out_Ena_Wakeup(void)  
{
    Out_Ena_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
