// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file port_config.c
 *
 * @brief This module initializes the GPIO pins as analog/digital,input or 
 * output etc. Also to PPS functionality to Re-mappable input or output pins.
 * 
 * Definitions in this file are for dsPIC33AK512MC510
 *
 * Component: PORTS
 *
 */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Disclaimer ">

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <xc.h>

#include "port_config.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

/**
* <B> Function: SetupGPIOPorts() </B>
*
* @brief Function initialize all ports as input and digital pins
*        
* @param none.
* @return none.
* 
* @example
* <CODE> SetupGPIOPorts(); </CODE>
*
*/
void SetupGPIOPorts(void)
{
    /* Reset all PORTx register (all inputs) */
    
    #ifdef TRISA
        TRISA = 0xFFFF;
        LATA  = 0x0000;
    #endif
    #ifdef ANSELA
        ANSELA = 0x0000;
    #endif

    #ifdef TRISB
        TRISB = 0xFFFF;
        LATB  = 0x0000;
    #endif
    #ifdef ANSELB
        ANSELB = 0x0000;
    #endif

    #ifdef TRISC
        TRISC = 0xFFFF;
        LATC  = 0x0000;
    #endif
    #ifdef ANSELC
        ANSELC = 0x0000;
    #endif

    #ifdef TRISD
        TRISD = 0xFFFF;
        LATD  = 0x0000;
    #endif
    #ifdef ANSELD
        ANSELD = 0x0000;
    #endif

    #ifdef TRISE
        TRISE = 0xFFFF;
        LATE  = 0x0000;
    #endif
    #ifdef ANSELE
        ANSELE = 0x0000;
    #endif

    #ifdef TRISF
        TRISF = 0xFFFF;
        LATF  = 0x0000;
    #endif
    #ifdef ANSELF
        ANSELF = 0x0000;
    #endif

    #ifdef TRISG
        TRISG = 0xFFFF;
        LATG  = 0x0000;
    #endif
    #ifdef ANSELG
        ANSELG = 0x0000;
    #endif

    MapGPIOHWFunction();

}
/**
* <B> Function: MapGPIOHWFunction() </B>
*
* @brief Function maps port pins as input or output, analog or digital
*        
* @param none.
* @return none.
* 
* @example
* <CODE> MapGPIOHWFunction(); </CODE>
*
*/
void MapGPIOHWFunction(void)
{      
    /* Digital SIGNALS */   
    /* Inverter Control - PWM Outputs
     * PWM1L : DIM:003 - PIN #83  TDI/RP52/PWM1L/IOMAD0/RD3
     * PWM1H : DIM:001 - PIN #82  TDO/RP51/PWM1H/IOMAD1/RD2
     * PWM2L : DIM:007 - PIN #79  TCK/RP50/PWM2L/IOMAD2/RD1
     * PWM2H : DIM:005 - PIN #78  RP49/PWM2H/IOMAD3/RD0
     * PWM3L : DIM:004 - PIN #67  RP37/PWM3L/IOMAD4/RC4
     * PWM3H : DIM:002 - PIN #66  RP36/PWM3H/IOMAD5/RC3      */
    TRISDbits.TRISD3 = 0 ;          
    TRISDbits.TRISD2 = 0 ;         
    TRISDbits.TRISD1 = 0 ;          
    TRISDbits.TRISD0 = 0 ;           
    TRISCbits.TRISC4 = 0 ;          
    TRISCbits.TRISC3 = 0 ;  
 
     /* Inverter Control - PWM Outputs
     * PWM6L : DIM:090 - PIN #77  RP59/PWM6L/IOMBD2/IOMAF9/IOMBF9/RD10
     * PWM6H : DIM:086 - PIN #76  RP58/PWM6H/IOMBD3/IOMBF7/RD9
     * PWM7L : DIM:104 - PIN #69  RP44/PWM7L/IOMBD4/IOMBF0/RC11
     * PWM7H : DIM:005 - PIN #78  RP43/PWM7H/IOMBD5/IOMBF1/RC10
     * PWM8L : DIM:092 - PIN #71  RP46/PWM8L/IOMBD6/RC13
     * PWM8H : DIM:088 - PIN #70  RP45/PWM8H/IOMBD7/RC12      */
    
    TRISDbits.TRISD10 = 0;
    TRISDbits.TRISD9  = 0;
    TRISCbits.TRISC11 = 0;
    TRISCbits.TRISC10 = 0;
    TRISCbits.TRISC13 = 0;
    TRISCbits.TRISC12 = 0;
    
     /* Inverter Control - PWM Outputs
     * APWM1L : DIM:067 - PIN #56  RP41/APWM1L/IOMAD8/IOMBF3/RC8
     * APWM1H : DIM:056 - PIN #93  RP60/APWM1H/IOMAD9/IOMAF8/IOMBF8/RD11
     * APWM2L : DIM:045 - PIN #97  RP64/APWM2L/IOMAD10/IOMBF5/RD15
     * APWM2H : DIM:042 - PIN #96  RP63/APWM2H/IOMAD11/RD14
     * APWM3L : DIM:052 - PIN #75  RP48/APWM3L/IOMBD8/RC15 
     * APWM3H : DIM:054 - PIN #74  RP47/APWM3H/IOMBD9/RC14      */
    
    TRISCbits.TRISC8  = 0;
    TRISDbits.TRISD11 = 0;
    TRISDbits.TRISD15 = 0;
    TRISDbits.TRISD14 = 0;
    TRISCbits.TRISC15 = 0;
    TRISCbits.TRISC14 = 0;
    
    
    
    
    /* PWM5H : DIM:068 - PIN #90  RP54/PWM5H/ASCL1/IOMBD1/RD5 */
    TRISDbits.TRISD5 = 0;
    
    //PWM5L
    _RP55R = 62;    // RPn tied to PWM Event B
    
}

// </editor-fold>