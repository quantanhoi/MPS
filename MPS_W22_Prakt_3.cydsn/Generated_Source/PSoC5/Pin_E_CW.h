/*******************************************************************************
* File Name: Pin_E_CW.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin_E_CW_H) /* Pins Pin_E_CW_H */
#define CY_PINS_Pin_E_CW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_E_CW_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_E_CW__PORT == 15 && ((Pin_E_CW__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pin_E_CW_Write(uint8 value);
void    Pin_E_CW_SetDriveMode(uint8 mode);
uint8   Pin_E_CW_ReadDataReg(void);
uint8   Pin_E_CW_Read(void);
void    Pin_E_CW_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin_E_CW_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pin_E_CW_SetDriveMode() function.
     *  @{
     */
        #define Pin_E_CW_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pin_E_CW_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pin_E_CW_DM_RES_UP          PIN_DM_RES_UP
        #define Pin_E_CW_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pin_E_CW_DM_OD_LO           PIN_DM_OD_LO
        #define Pin_E_CW_DM_OD_HI           PIN_DM_OD_HI
        #define Pin_E_CW_DM_STRONG          PIN_DM_STRONG
        #define Pin_E_CW_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pin_E_CW_MASK               Pin_E_CW__MASK
#define Pin_E_CW_SHIFT              Pin_E_CW__SHIFT
#define Pin_E_CW_WIDTH              1u

/* Interrupt constants */
#if defined(Pin_E_CW__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin_E_CW_SetInterruptMode() function.
     *  @{
     */
        #define Pin_E_CW_INTR_NONE      (uint16)(0x0000u)
        #define Pin_E_CW_INTR_RISING    (uint16)(0x0001u)
        #define Pin_E_CW_INTR_FALLING   (uint16)(0x0002u)
        #define Pin_E_CW_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pin_E_CW_INTR_MASK      (0x01u) 
#endif /* (Pin_E_CW__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_E_CW_PS                     (* (reg8 *) Pin_E_CW__PS)
/* Data Register */
#define Pin_E_CW_DR                     (* (reg8 *) Pin_E_CW__DR)
/* Port Number */
#define Pin_E_CW_PRT_NUM                (* (reg8 *) Pin_E_CW__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_E_CW_AG                     (* (reg8 *) Pin_E_CW__AG)                       
/* Analog MUX bux enable */
#define Pin_E_CW_AMUX                   (* (reg8 *) Pin_E_CW__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_E_CW_BIE                    (* (reg8 *) Pin_E_CW__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_E_CW_BIT_MASK               (* (reg8 *) Pin_E_CW__BIT_MASK)
/* Bypass Enable */
#define Pin_E_CW_BYP                    (* (reg8 *) Pin_E_CW__BYP)
/* Port wide control signals */                                                   
#define Pin_E_CW_CTL                    (* (reg8 *) Pin_E_CW__CTL)
/* Drive Modes */
#define Pin_E_CW_DM0                    (* (reg8 *) Pin_E_CW__DM0) 
#define Pin_E_CW_DM1                    (* (reg8 *) Pin_E_CW__DM1)
#define Pin_E_CW_DM2                    (* (reg8 *) Pin_E_CW__DM2) 
/* Input Buffer Disable Override */
#define Pin_E_CW_INP_DIS                (* (reg8 *) Pin_E_CW__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_E_CW_LCD_COM_SEG            (* (reg8 *) Pin_E_CW__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_E_CW_LCD_EN                 (* (reg8 *) Pin_E_CW__LCD_EN)
/* Slew Rate Control */
#define Pin_E_CW_SLW                    (* (reg8 *) Pin_E_CW__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_E_CW_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_E_CW__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_E_CW_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_E_CW__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_E_CW_PRTDSI__OE_SEL0        (* (reg8 *) Pin_E_CW__PRTDSI__OE_SEL0) 
#define Pin_E_CW_PRTDSI__OE_SEL1        (* (reg8 *) Pin_E_CW__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_E_CW_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_E_CW__PRTDSI__OUT_SEL0) 
#define Pin_E_CW_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_E_CW__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_E_CW_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_E_CW__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pin_E_CW__SIO_CFG)
    #define Pin_E_CW_SIO_HYST_EN        (* (reg8 *) Pin_E_CW__SIO_HYST_EN)
    #define Pin_E_CW_SIO_REG_HIFREQ     (* (reg8 *) Pin_E_CW__SIO_REG_HIFREQ)
    #define Pin_E_CW_SIO_CFG            (* (reg8 *) Pin_E_CW__SIO_CFG)
    #define Pin_E_CW_SIO_DIFF           (* (reg8 *) Pin_E_CW__SIO_DIFF)
#endif /* (Pin_E_CW__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pin_E_CW__INTSTAT)
    #define Pin_E_CW_INTSTAT            (* (reg8 *) Pin_E_CW__INTSTAT)
    #define Pin_E_CW_SNAP               (* (reg8 *) Pin_E_CW__SNAP)
    
	#define Pin_E_CW_0_INTTYPE_REG 		(* (reg8 *) Pin_E_CW__0__INTTYPE)
#endif /* (Pin_E_CW__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_E_CW_H */


/* [] END OF FILE */
