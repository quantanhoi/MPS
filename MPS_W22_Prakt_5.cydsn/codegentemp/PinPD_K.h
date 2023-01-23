/*******************************************************************************
* File Name: PinPD_K.h  
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

#if !defined(CY_PINS_PinPD_K_H) /* Pins PinPD_K_H */
#define CY_PINS_PinPD_K_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinPD_K_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PinPD_K__PORT == 15 && ((PinPD_K__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PinPD_K_Write(uint8 value);
void    PinPD_K_SetDriveMode(uint8 mode);
uint8   PinPD_K_ReadDataReg(void);
uint8   PinPD_K_Read(void);
void    PinPD_K_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinPD_K_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PinPD_K_SetDriveMode() function.
     *  @{
     */
        #define PinPD_K_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PinPD_K_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PinPD_K_DM_RES_UP          PIN_DM_RES_UP
        #define PinPD_K_DM_RES_DWN         PIN_DM_RES_DWN
        #define PinPD_K_DM_OD_LO           PIN_DM_OD_LO
        #define PinPD_K_DM_OD_HI           PIN_DM_OD_HI
        #define PinPD_K_DM_STRONG          PIN_DM_STRONG
        #define PinPD_K_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PinPD_K_MASK               PinPD_K__MASK
#define PinPD_K_SHIFT              PinPD_K__SHIFT
#define PinPD_K_WIDTH              1u

/* Interrupt constants */
#if defined(PinPD_K__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinPD_K_SetInterruptMode() function.
     *  @{
     */
        #define PinPD_K_INTR_NONE      (uint16)(0x0000u)
        #define PinPD_K_INTR_RISING    (uint16)(0x0001u)
        #define PinPD_K_INTR_FALLING   (uint16)(0x0002u)
        #define PinPD_K_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PinPD_K_INTR_MASK      (0x01u) 
#endif /* (PinPD_K__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinPD_K_PS                     (* (reg8 *) PinPD_K__PS)
/* Data Register */
#define PinPD_K_DR                     (* (reg8 *) PinPD_K__DR)
/* Port Number */
#define PinPD_K_PRT_NUM                (* (reg8 *) PinPD_K__PRT) 
/* Connect to Analog Globals */                                                  
#define PinPD_K_AG                     (* (reg8 *) PinPD_K__AG)                       
/* Analog MUX bux enable */
#define PinPD_K_AMUX                   (* (reg8 *) PinPD_K__AMUX) 
/* Bidirectional Enable */                                                        
#define PinPD_K_BIE                    (* (reg8 *) PinPD_K__BIE)
/* Bit-mask for Aliased Register Access */
#define PinPD_K_BIT_MASK               (* (reg8 *) PinPD_K__BIT_MASK)
/* Bypass Enable */
#define PinPD_K_BYP                    (* (reg8 *) PinPD_K__BYP)
/* Port wide control signals */                                                   
#define PinPD_K_CTL                    (* (reg8 *) PinPD_K__CTL)
/* Drive Modes */
#define PinPD_K_DM0                    (* (reg8 *) PinPD_K__DM0) 
#define PinPD_K_DM1                    (* (reg8 *) PinPD_K__DM1)
#define PinPD_K_DM2                    (* (reg8 *) PinPD_K__DM2) 
/* Input Buffer Disable Override */
#define PinPD_K_INP_DIS                (* (reg8 *) PinPD_K__INP_DIS)
/* LCD Common or Segment Drive */
#define PinPD_K_LCD_COM_SEG            (* (reg8 *) PinPD_K__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinPD_K_LCD_EN                 (* (reg8 *) PinPD_K__LCD_EN)
/* Slew Rate Control */
#define PinPD_K_SLW                    (* (reg8 *) PinPD_K__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinPD_K_PRTDSI__CAPS_SEL       (* (reg8 *) PinPD_K__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinPD_K_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinPD_K__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinPD_K_PRTDSI__OE_SEL0        (* (reg8 *) PinPD_K__PRTDSI__OE_SEL0) 
#define PinPD_K_PRTDSI__OE_SEL1        (* (reg8 *) PinPD_K__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinPD_K_PRTDSI__OUT_SEL0       (* (reg8 *) PinPD_K__PRTDSI__OUT_SEL0) 
#define PinPD_K_PRTDSI__OUT_SEL1       (* (reg8 *) PinPD_K__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinPD_K_PRTDSI__SYNC_OUT       (* (reg8 *) PinPD_K__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PinPD_K__SIO_CFG)
    #define PinPD_K_SIO_HYST_EN        (* (reg8 *) PinPD_K__SIO_HYST_EN)
    #define PinPD_K_SIO_REG_HIFREQ     (* (reg8 *) PinPD_K__SIO_REG_HIFREQ)
    #define PinPD_K_SIO_CFG            (* (reg8 *) PinPD_K__SIO_CFG)
    #define PinPD_K_SIO_DIFF           (* (reg8 *) PinPD_K__SIO_DIFF)
#endif /* (PinPD_K__SIO_CFG) */

/* Interrupt Registers */
#if defined(PinPD_K__INTSTAT)
    #define PinPD_K_INTSTAT            (* (reg8 *) PinPD_K__INTSTAT)
    #define PinPD_K_SNAP               (* (reg8 *) PinPD_K__SNAP)
    
	#define PinPD_K_0_INTTYPE_REG 		(* (reg8 *) PinPD_K__0__INTTYPE)
#endif /* (PinPD_K__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PinPD_K_H */


/* [] END OF FILE */
