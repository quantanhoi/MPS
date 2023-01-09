/*******************************************************************************
* File Name: Cpwm.h
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

#if !defined(CY_CLOCK_Cpwm_H)
#define CY_CLOCK_Cpwm_H

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

void Cpwm_Start(void) ;
void Cpwm_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Cpwm_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Cpwm_StandbyPower(uint8 state) ;
void Cpwm_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Cpwm_GetDividerRegister(void) ;
void Cpwm_SetModeRegister(uint8 modeBitMask) ;
void Cpwm_ClearModeRegister(uint8 modeBitMask) ;
uint8 Cpwm_GetModeRegister(void) ;
void Cpwm_SetSourceRegister(uint8 clkSource) ;
uint8 Cpwm_GetSourceRegister(void) ;
#if defined(Cpwm__CFG3)
void Cpwm_SetPhaseRegister(uint8 clkPhase) ;
uint8 Cpwm_GetPhaseRegister(void) ;
#endif /* defined(Cpwm__CFG3) */

#define Cpwm_Enable()                       Cpwm_Start()
#define Cpwm_Disable()                      Cpwm_Stop()
#define Cpwm_SetDivider(clkDivider)         Cpwm_SetDividerRegister(clkDivider, 1u)
#define Cpwm_SetDividerValue(clkDivider)    Cpwm_SetDividerRegister((clkDivider) - 1u, 1u)
#define Cpwm_SetMode(clkMode)               Cpwm_SetModeRegister(clkMode)
#define Cpwm_SetSource(clkSource)           Cpwm_SetSourceRegister(clkSource)
#if defined(Cpwm__CFG3)
#define Cpwm_SetPhase(clkPhase)             Cpwm_SetPhaseRegister(clkPhase)
#define Cpwm_SetPhaseValue(clkPhase)        Cpwm_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Cpwm__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Cpwm_CLKEN              (* (reg8 *) Cpwm__PM_ACT_CFG)
#define Cpwm_CLKEN_PTR          ((reg8 *) Cpwm__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Cpwm_CLKSTBY            (* (reg8 *) Cpwm__PM_STBY_CFG)
#define Cpwm_CLKSTBY_PTR        ((reg8 *) Cpwm__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Cpwm_DIV_LSB            (* (reg8 *) Cpwm__CFG0)
#define Cpwm_DIV_LSB_PTR        ((reg8 *) Cpwm__CFG0)
#define Cpwm_DIV_PTR            ((reg16 *) Cpwm__CFG0)

/* Clock MSB divider configuration register. */
#define Cpwm_DIV_MSB            (* (reg8 *) Cpwm__CFG1)
#define Cpwm_DIV_MSB_PTR        ((reg8 *) Cpwm__CFG1)

/* Mode and source configuration register */
#define Cpwm_MOD_SRC            (* (reg8 *) Cpwm__CFG2)
#define Cpwm_MOD_SRC_PTR        ((reg8 *) Cpwm__CFG2)

#if defined(Cpwm__CFG3)
/* Analog clock phase configuration register */
#define Cpwm_PHASE              (* (reg8 *) Cpwm__CFG3)
#define Cpwm_PHASE_PTR          ((reg8 *) Cpwm__CFG3)
#endif /* defined(Cpwm__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Cpwm_CLKEN_MASK         Cpwm__PM_ACT_MSK
#define Cpwm_CLKSTBY_MASK       Cpwm__PM_STBY_MSK

/* CFG2 field masks */
#define Cpwm_SRC_SEL_MSK        Cpwm__CFG2_SRC_SEL_MASK
#define Cpwm_MODE_MASK          (~(Cpwm_SRC_SEL_MSK))

#if defined(Cpwm__CFG3)
/* CFG3 phase mask */
#define Cpwm_PHASE_MASK         Cpwm__CFG3_PHASE_DLY_MASK
#endif /* defined(Cpwm__CFG3) */

#endif /* CY_CLOCK_Cpwm_H */


/* [] END OF FILE */
