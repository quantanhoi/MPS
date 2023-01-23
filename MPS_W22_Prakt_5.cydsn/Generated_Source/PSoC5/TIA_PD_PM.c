/*******************************************************************************
* File Name: TIA_PD_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power management source code to the API for the 
*  TIA component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TIA_PD.h"

static TIA_PD_BACKUP_STRUCT  TIA_PD_backup;


/*******************************************************************************  
* Function Name: TIA_PD_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
*
* Parameters:
*  TIA_PD_backup - global structure, where configuration registers are
*  stored.
*
* Return:
*  None
*
*******************************************************************************/
void TIA_PD_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: TIA_PD_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None
*
* Return:
*  void
*
*******************************************************************************/
void TIA_PD_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: TIA_PD_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TIA_PD_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void TIA_PD_Sleep(void) 
{
    /* Save TIA enable state */
    if((TIA_PD_PM_ACT_CFG_REG & TIA_PD_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        TIA_PD_backup.enableState = 1u;
        /* Stop the configuration */
        TIA_PD_Stop();
    }
    else
    {
        /* Component is disabled */
        TIA_PD_backup.enableState = 0u;
    }
    /* Save the configuration */
    TIA_PD_SaveConfig();
}


/*******************************************************************************  
* Function Name: TIA_PD_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  void
*
* Global variables:
*  TIA_PD_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void TIA_PD_Wakeup(void) 
{
    /* Restore the configuration */
    TIA_PD_RestoreConfig();

    /* Enable's the component operation */
    if(TIA_PD_backup.enableState == 1u)
    {
        TIA_PD_Enable();
    } /* Do nothing if component was disabled before */
}


/* [] END OF FILE */
