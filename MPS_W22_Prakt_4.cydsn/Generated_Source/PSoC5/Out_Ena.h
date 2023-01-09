/*******************************************************************************
* File Name: Out_Ena.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Out_Ena_H) /* CY_CONTROL_REG_Out_Ena_H */
#define CY_CONTROL_REG_Out_Ena_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Out_Ena_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Out_Ena_Write(uint8 control) ;
uint8   Out_Ena_Read(void) ;

void Out_Ena_SaveConfig(void) ;
void Out_Ena_RestoreConfig(void) ;
void Out_Ena_Sleep(void) ; 
void Out_Ena_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Out_Ena_Control        (* (reg8 *) Out_Ena_Sync_ctrl_reg__CONTROL_REG )
#define Out_Ena_Control_PTR    (  (reg8 *) Out_Ena_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Out_Ena_H */


/* [] END OF FILE */
