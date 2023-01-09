/*******************************************************************************
* File Name: SysClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SysClk_H)
#define CY_CLOCK_SysClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void SysClk_Start(void) ;
void SysClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SysClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SysClk_StandbyPower(uint8 state) ;
void SysClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SysClk_GetDividerRegister(void) ;
void SysClk_SetModeRegister(uint8 modeBitMask) ;
void SysClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 SysClk_GetModeRegister(void) ;
void SysClk_SetSourceRegister(uint8 clkSource) ;
uint8 SysClk_GetSourceRegister(void) ;
#if defined(SysClk__CFG3)
void SysClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 SysClk_GetPhaseRegister(void) ;
#endif /* defined(SysClk__CFG3) */

#define SysClk_Enable()                       SysClk_Start()
#define SysClk_Disable()                      SysClk_Stop()
#define SysClk_SetDivider(clkDivider)         SysClk_SetDividerRegister(clkDivider, 1u)
#define SysClk_SetDividerValue(clkDivider)    SysClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define SysClk_SetMode(clkMode)               SysClk_SetModeRegister(clkMode)
#define SysClk_SetSource(clkSource)           SysClk_SetSourceRegister(clkSource)
#if defined(SysClk__CFG3)
#define SysClk_SetPhase(clkPhase)             SysClk_SetPhaseRegister(clkPhase)
#define SysClk_SetPhaseValue(clkPhase)        SysClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(SysClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SysClk_CLKEN              (* (reg8 *) SysClk__PM_ACT_CFG)
#define SysClk_CLKEN_PTR          ((reg8 *) SysClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SysClk_CLKSTBY            (* (reg8 *) SysClk__PM_STBY_CFG)
#define SysClk_CLKSTBY_PTR        ((reg8 *) SysClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SysClk_DIV_LSB            (* (reg8 *) SysClk__CFG0)
#define SysClk_DIV_LSB_PTR        ((reg8 *) SysClk__CFG0)
#define SysClk_DIV_PTR            ((reg16 *) SysClk__CFG0)

/* Clock MSB divider configuration register. */
#define SysClk_DIV_MSB            (* (reg8 *) SysClk__CFG1)
#define SysClk_DIV_MSB_PTR        ((reg8 *) SysClk__CFG1)

/* Mode and source configuration register */
#define SysClk_MOD_SRC            (* (reg8 *) SysClk__CFG2)
#define SysClk_MOD_SRC_PTR        ((reg8 *) SysClk__CFG2)

#if defined(SysClk__CFG3)
/* Analog clock phase configuration register */
#define SysClk_PHASE              (* (reg8 *) SysClk__CFG3)
#define SysClk_PHASE_PTR          ((reg8 *) SysClk__CFG3)
#endif /* defined(SysClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SysClk_CLKEN_MASK         SysClk__PM_ACT_MSK
#define SysClk_CLKSTBY_MASK       SysClk__PM_STBY_MSK

/* CFG2 field masks */
#define SysClk_SRC_SEL_MSK        SysClk__CFG2_SRC_SEL_MASK
#define SysClk_MODE_MASK          (~(SysClk_SRC_SEL_MSK))

#if defined(SysClk__CFG3)
/* CFG3 phase mask */
#define SysClk_PHASE_MASK         SysClk__CFG3_PHASE_DLY_MASK
#endif /* defined(SysClk__CFG3) */

#endif /* CY_CLOCK_SysClk_H */


/* [] END OF FILE */
