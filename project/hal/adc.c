// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file adc.c
 *
 * @brief This module configures and enables the ADC Module 
 * 
 * Definitions in this file are for dsPIC33AK512MC510
 *
 * Component: ADC
 *
 */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Disclaimer ">

/*******************************************************************************
* SOFTWARE LICENSE AGREEMENT
* 
* © [2024] Microchip Technology Inc. and its subsidiaries
* 
* Subject to your compliance with these terms, you may use this Microchip 
* software and any derivatives exclusively with Microchip products. 
* You are responsible for complying with third party license terms applicable to
* your use of third party software (including open source software) that may 
* accompany this Microchip software.
* 
* Redistribution of this Microchip software in source or binary form is allowed 
* and must include the above terms of use and the following disclaimer with the
* distribution and accompanying materials.
* 
* SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL 
* MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR 
* CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO
* THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE 
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY
* LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL
* NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS
* SOFTWARE
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
*******************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <xc.h>
#include <stdint.h>

#include "adc.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
/**
* <B> Function: InitializeADCs() </B>
*
* @brief Function initializes and enable the ADC Module
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitializeADCs(); </CODE>
*
*/
void InitializeADCs(void)
{
    /* Channel Configuration for IA*/
    /*ADC1 Channel 0 for IA : OA1OUT/AD1AN0/CVDAN2/CMP1A/RP3/RA2 */
    AD1CH0CON1bits.PINSEL = 0;       
    AD1CH0CON1bits.SAMC = 3;              
    AD1CH0CON1bits.FRAC = 0;
    AD1CH0CON1bits.DIFF = 0;

    /* Channel Configuration for IB*/
    /*ADC2 Channel 0 for IB : OA2OUT/AD2AN0/CVDAN16/CVDTX0/CMP2A/RP17/RB0 */    
    AD2CH0CON1bits.PINSEL = 0;       
    AD2CH0CON1bits.SAMC = 3;              
    AD2CH0CON1bits.FRAC = 0;
    AD2CH0CON1bits.DIFF = 0;
    
    /* Channel Configuration for IBUS1*/
    /*ADC3 Channel 0 for IBUS1 : OA3OUT/AD3AN0/CVDAN5/CMP3A/RP6/INT0/RA5 */ 
    AD3CH0CON1bits.PINSEL = 0;      
    AD3CH0CON1bits.SAMC = 3;      
    AD3CH0CON1bits.FRAC = 0;
    AD3CH0CON1bits.DIFF = 0;

    /* Channel Configuration for IBUS2*/
    /*ADC3 Channel 1 for IBUS2 : OA3OUT/AD3AN0/CVDAN5/CMP3A/RP6/INT0/RA5 */ 
    AD3CH1CON1bits.PINSEL = 0;      
    AD3CH1CON1bits.SAMC = 3;      
    AD3CH1CON1bits.FRAC = 0;
    AD3CH1CON1bits.DIFF = 0;
    
    /* Channel Configuration for POT*/
    /*ADC2 Channel 1 for POT : AD2AN5/CVDAN31/CVDTX15/RP32/RB15 */     
    AD2CH1CON1bits.PINSEL = 5;      
    AD2CH1CON1bits.SAMC = 3;              
    AD2CH1CON1bits.FRAC = 0;
    AD2CH1CON1bits.DIFF = 0;

    /* Channel Configuration for VBUS*/
    /*ADC1 Channel 4 for VBUS : AD3AN4/CVDTX29/RP81/RF0 */     
    AD3CH2CON1bits.PINSEL = 4;   
    AD3CH2CON1bits.SAMC = 3;         
    AD3CH2CON1bits.FRAC = 0;
    AD3CH2CON1bits.DIFF = 0;
    
    /* Turn on the ADC Core 1 */   
    AD1CONbits.ON = 1;     
    /* Waiting till the ADC Core 1 is ready*/
    while(AD1CONbits.ADRDY == 0);  
    
    /* Turn on the ADC Core 2 */
    AD2CONbits.ON = 1;             
    /* Waiting till the ADC Core 2 is ready*/
    while(AD2CONbits.ADRDY == 0);   
    
    /* Turn on the ADC Core 3 */   
    AD3CONbits.ON = 1;     
    /* Waiting till the ADC Core 3 is ready*/
    while(AD3CONbits.ADRDY == 0);  

#ifdef SINGLE_SHUNT 
    /*AD3CH1 - IBUS2 used for ADC Interrupt in Single Shunt*/
    /* Set ADC interrupt priority IPL 7  */ 
    _AD3CH1IP = 7;
    /* Clear ADC interrupt flag */
    _AD3CH1IF = 0;
    /* Disable the AD3CH1 interrupt  */
    _AD3CH1IE = 0;
#else 
    /*AD2CH1 - POT used for ADC Interrupt in Dual Shunt*/
    /* Set ADC interrupt priority IPL 7  */ 
    _AD2CH1IP = 7;
    /* Clear ADC interrupt flag */
    _AD2CH1IF = 0;
    /* Disable the AD2CH1 interrupt  */
    _AD2CH1IE = 0;
#endif
    
    /*Selecting the Trigger Sources for ADC Channels*/
#ifdef SINGLE_SHUNT 
    /*PWM2 ADC Trigger 1 for IBUS1 - AD3CH0*/
    AD3CH0CON1bits.TRG1SRC = 6;   
    /*PWM2 ADC Trigger 2 for IBUS2 - AD3CH1*/
    AD3CH1CON1bits.TRG1SRC = 7;    
#else 
    /*PWM1 ADC Trigger 1 for IA - AD1CH0*/
    AD1CH0CON1bits.TRG1SRC = 4;      
    /*PWM1 ADC Trigger 1 for IB - AD2CH0*/
    AD2CH0CON1bits.TRG1SRC = 4;    

#endif
    /*PWM1 ADC Trigger 1 for POT - AD2CH1*/
    AD2CH1CON1bits.TRG1SRC = 4;      
    
    /*PWM1 ADC Trigger 1 for VBUS - AD3CH2*/
    AD3CH2CON1bits.TRG1SRC = 4;     

}

// </editor-fold>