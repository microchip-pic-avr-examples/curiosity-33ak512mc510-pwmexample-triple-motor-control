// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file pwm.c
 *
 * @brief This module configures and enables the PWM Module 
 * 
 * Definitions in this file are for dsPIC33AK512MC510
 *
 * Component: PWM
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
#include <stdint.h>

#include "pwm.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

/**
* <B> Function: InitPWMGenerators()    </B>
*
* @brief Function initializes the registers common for all PWM modules and 
* configures individual PWM module.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPWMGenerators();     </CODE>
*
*/
void InitPWMGenerators(void)
{

    PCLKCON      = 0x0000;
    /* PWM Clock Divider Selection bits
       0b11 = 1:16 ; 0b10 = 1:8 ;0b01 = 1:4 ; 0b00 = 1:2*/
    PCLKCONbits.DIVSEL = 0;
    /* PWM Master Clock Selection bits
       0b11 = AFPLLO ; 0b10 = FPLLO ; 0b01 = AFVCO/2 ; 0b00 = FOSC */
    PCLKCONbits.MCLKSEL = 1;
    /* Lock bit: 0 = Write-protected registers and bits are unlocked   */
    PCLKCONbits.LOCK = 0;

    /* Initialize Master Phase Register */
    MPHASE       = 0x0000;
    /* Initialize Master Duty Cycle */
    MDC          = 0x0000;
    /* Initialize Master Period Register */
    MPER         = LOOPTIME_TCY;
    
    /* Initialize FREQUENCY SCALE REGISTER*/
    FSCL          = 0x0000;
    /* Initialize FREQUENCY SCALING MINIMUM PERIOD REGISTER */
    FSMINPER     = 0x0000;
    /* Initialize Linear Feedback Shift Register */
    LFSR         = 0x0000;
    /* Initialize Combinational Trigger Register */
    CMBTRIG     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER 1 */
    LOGCONA     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER 1 */
    LOGCONB     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER 2 */
    LOGCONC     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER 2 */
    LOGCOND     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER 3 */
    LOGCONE     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER 3 */
    LOGCONF     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER A */
    PWMEVTA     = 0x0000;     
    /* PWM EVENT OUTPUT CONTROL REGISTER B */
    PWMEVTB     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER C */
    PWMEVTC     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER D */
    PWMEVTD     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER E */
    PWMEVTE     = 0x0000;
    /* PWM EVENT OUTPUT CONTROL REGISTER F */
    PWMEVTF     = 0x0000;
    
    APWMEVTA = 0x0000;
    
    /* Function call to Initialize individual PWM modules*/
    InitPWMGenerator5 ();
    
    InitAuxPWMGenerator1 ();
    InitAuxPWMGenerator2 ();
    InitAuxPWMGenerator3 ();
    
    InitPWMGenerator1 ();
    InitPWMGenerator2 ();
    InitPWMGenerator3 (); 
    
    InitPWMGenerator6 ();
    InitPWMGenerator7 ();
    InitPWMGenerator8 ();
    
    /* Enable the PWM module after initializing generators*/
	PG2CONbits.ON = 1;      
    PG3CONbits.ON = 1;      
    PG1CONbits.ON = 1;  
    
    PG7CONbits.ON = 1;      
    PG8CONbits.ON = 1;      
    PG6CONbits.ON = 1; 
    
    APG1CONbits.ON = 1; 
    APG2CONbits.ON = 1; 
    APG3CONbits.ON = 1; 
    
    PG5CONbits.ON = 1;     
    
}

/**
* <B> Function: InitPWMGenerator5()    </B>
*
* @brief Function to configure PWM Module # 5
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPWMGenerator5();     </CODE>
*
*/
void InitPWMGenerator5 (void)
{

    /* Initialize PWM GENERATOR 5 CONTROL REGISTER */
    PG5CON      = 0x0000;
    /* PWM Generator 5 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG5CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG5CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    PG5CONbits.MODSEL = 6;
#else
    PG5CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG5CONbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 5 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG5DC
       0 = Macro uses the PG5DC register*/
    PG5CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG5PER
       0 = Macro uses the PG5PER register */
    PG5CONbits.MPERSEL = 0;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG5PHASE
       0 = Macro uses the PG5PHASE register */
    PG5CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG5CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG5CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG5CONbits.TRGMOD = 0;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    PG5CONbits.SOCS = 0;
    
    /* Clear PWM GENERATOR 5 STATUS REGISTER*/
    PG5STAT      = 0x0000;
    /* Initialize PWM GENERATOR 5 I/O CONTROL REGISTER */
    PG5IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG5IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to PWM5H and PWM5L Device Pins bit 
       0 = PWM1H/L signals are mapped to their respective pins */
    PG5IOCON1bits.SWAP = 0;
    /* User Override Enable for PWM5H Pin bit
       0 = PWM Generator provides data for the PWM5H pin*/
    PG5IOCON2bits.OVRENH = 0;
    /* User Override Enable for PWM5L Pin bit
       0 = PWM Generator provides data for the PWM5L pin*/
    PG5IOCON2bits.OVRENL = 0;
    /* Data for PWM1H/PWM1L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM5H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM5L */
    PG5IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG5IOCON2bits.OSYNC = 0;
    /* Data for PWM5H/PWM5L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM5H.
       If Fault is active, then FLTDAT<0> provides data for PWM5L.*/
    PG5IOCON2bits.FLT1DAT = 0;
    /* Data for PWM5H/PWM5L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM5H.
       If current limit is active, then CLDAT<0> provides data for PWM5L.*/
    PG5IOCON2bits.CLDAT = 0;
    /* Data for PWM5H/PWM5L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM5H.
       If feed-forward is active, then FFDAT<0> provides data for PWM5L.*/
    PG5IOCON2bits.FFDAT = 0;
    /* Data for PWM5H/PWM5L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM5H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM5L data. */
    PG5IOCON2bits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 5 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG5IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG5IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG5IOCON1bits.PMOD = 0;
    /* PWM5H Output Port Enable bit
       1 = PWM Generator controls the PWM5H output pin
       0 = PWM Generator does not control the PWM5H output pin */
    PG5IOCON1bits.PENH = 1;
    /* PWM5L Output Port Enable bit
       1 = PWM Generator controls the PWM5L output pin
       0 = PWM Generator does not control the PWM5L output pin */
    PG5IOCON1bits.PENL = 0;
    /* PWM5H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG5IOCON1bits.POLH = 0;
    /* PWM5L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG5IOCON1bits.POLL = 0;
    
    /* Initialize PWM GENERATOR 5 EVENT REGISTER */
    PG5EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG5EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG5TRIGC Compare Event Enable bit
       0 = PG5TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG5EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG5TRIGB Compare Event Enable bit
       0 = PG5TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG5EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is PG5TRIGA Compare Event Enable bit
       1 = PG5TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG5EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG5DC register automatically sets the UPDATE bit*/
    PG5EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG5EVT1bits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 5 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    PG5EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG5EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG5EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG5EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG5EVT1bits.IEVTSEL = 3;

        /* ADC Trigger 2 Source is PG5TRIGC Compare Event Enable bit
       0 = PG5TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG5EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG5TRIGB Compare Event Enable bit
       0 = PG5TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG5EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG5TRIGA Compare Event Enable bit
       0 = PG5TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG5EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG5EVT1bits.ADTR1OFS = 0;

    /* PWM GENERATOR 5 Current Limit PCI REGISTER */
    PG5CLPCI1    = 0x0000;
    /* PWM GENERATOR 5 Feed Forward PCI REGISTER  */
    PG5FFPCI1    = 0x0000;
    /* PWM GENERATOR 5 Sync PCI REGISTER */
    PG5SPCI1    = 0x0000;
    
    /* Initialize PWM GENERATOR 5 LEADING-EDGE BLANKING REGISTER */
    PG5LEB      = 0x0000;
    
    /* Initialize PWM GENERATOR 5 PHASE REGISTER */
    PG5PHASE     = MIN_DUTY;
    /* Initialize PWM GENERATOR 5 DUTY CYCLE REGISTER */
    PG5DC        = LOOPTIME_TCY/3;
    /* Initialize PWM GENERATOR 5 DUTY CYCLE ADJUSTMENT REGISTER */
    PG5DCA       = 0x0000;
    /* Initialize PWM GENERATOR 5 PERIOD REGISTER */
    PG5PER       = LOOPTIME_TCY;
    /* Initialize PWM GENERATOR 5 DEAD-TIME REGISTER */
    PG5DTbits.DTH = DEADTIME;
    /* Initialize PWM GENERATOR 5 DEAD-TIME REGISTER */
    PG5DTbits.DTL = DEADTIME;

    /* Initialize PWM GENERATOR 5 TRIGGER A REGISTER */
    PG5TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 5 TRIGGER B REGISTER */
    PG5TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 5 TRIGGER C REGISTER */
    PG5TRIGC     = 0x0000;   
}

/**
* <B> Function: InitPWMGenerator1()    </B>
*
* @brief Function to configure PWM Module # 1
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPWMGenerator1();     </CODE>
*
*/
void InitPWMGenerator1 (void)
{

    /* Initialize PWM GENERATOR 1 CONTROL REGISTER */
    PG1CON      = 0x0000;
    /* PWM Generator 1 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG1CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG1CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    PG1CONbits.MODSEL = 6;
#else
    PG1CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG1CONbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 1 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG1DC
       0 = Macro uses the PG1DC register*/
    PG1CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG1PER
       0 = Macro uses the PG1PER register */
    PG1CONbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG1PHASE
       0 = Macro uses the PG1PHASE register */
    PG1CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG1CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG1CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG1CONbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    PG1CONbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 1 STATUS REGISTER*/
    PG1STAT      = 0x0000;
    /* Initialize PWM GENERATOR 1 I/O CONTROL REGISTER */
    PG1IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG1IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to PWM1H and PWM1L Device Pins bit 
       0 = PWM1H/L signals are mapped to their respective pins */
    PG1IOCON1bits.SWAP = 0;
    /* User Override Enable for PWM1H Pin bit
       0 = PWM Generator provides data for the PWM1H pin*/
    PG1IOCON2bits.OVRENH = 0;
    /* User Override Enable for PWM1L Pin bit
       0 = PWM Generator provides data for the PWM1L pin*/
    PG1IOCON2bits.OVRENL = 0;
    /* Data for PWM1H/PWM1L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM1H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM1L */
    PG1IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG1IOCON2bits.OSYNC = 0;
    /* Data for PWM1H/PWM1L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM1H.
       If Fault is active, then FLTDAT<0> provides data for PWM1L.*/
    PG1IOCON2bits.FLT1DAT = 0;
    /* Data for PWM1H/PWM1L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM1H.
       If current limit is active, then CLDAT<0> provides data for PWM1L.*/
    PG1IOCON2bits.CLDAT = 0;
    /* Data for PWM1H/PWM1L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM1H.
       If feed-forward is active, then FFDAT<0> provides data for PWM1L.*/
    PG1IOCON2bits.FFDAT = 0;
    /* Data for PWM1H/PWM1L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM1H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM1L data. */
    PG1IOCON2bits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 1 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG1IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG1IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG1IOCON1bits.PMOD = 0;
    /* PWM1H Output Port Enable bit
       1 = PWM Generator controls the PWM1H output pin
       0 = PWM Generator does not control the PWM1H output pin */
    PG1IOCON1bits.PENH = 1;
    /* PWM1L Output Port Enable bit
       1 = PWM Generator controls the PWM1L output pin
       0 = PWM Generator does not control the PWM1L output pin */
    PG1IOCON1bits.PENL = 1;
    /* PWM1H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG1IOCON1bits.POLH = 0;
    /* PWM1L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG1IOCON1bits.POLL = 0;
    
    /* Initialize PWM GENERATOR 1 EVENT REGISTER */
    PG1EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG1EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG1TRIGC Compare Event Enable bit
       0 = PG1TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG1EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG1TRIGB Compare Event Enable bit
       0 = PG1TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG1EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is PG1TRIGA Compare Event Enable bit
       1 = PG1TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG1EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG1DC register automatically sets the UPDATE bit*/
    PG1EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG1EVT1bits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 1 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    PG1EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG1EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG1EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG1EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG1EVT1bits.IEVTSEL = 3;

        /* ADC Trigger 2 Source is PG1TRIGC Compare Event Enable bit
       0 = PG1TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG1TRIGB Compare Event Enable bit
       0 = PG1TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG1TRIGA Compare Event Enable bit
       0 = PG1TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG1EVT1bits.ADTR1OFS = 0;  

    /* PWM GENERATOR 1 Current Limit PCI REGISTER */
    PG1CLPCI1    = 0x0000;
    /* PWM GENERATOR 1 Feed Forward PCI REGISTER  */
    PG1FFPCI1    = 0x0000;
    /* PWM GENERATOR 1 Sync PCI REGISTER */
    PG1SPCI1    = 0x0000;
    
    PG1EVT1bits.PWMPCI  = 4;
    PG1SPCI1bits.PPS = 0 ;
    PG1SPCI2 = 8388608;
    
    
    /* Initialize PWM GENERATOR 1 LEADING-EDGE BLANKING REGISTER */
    PG1LEB      = 0x0000;
     
    /* Initialize PWM GENERATOR 1 PHASE REGISTER */
    PG1PHASE     = MIN_DUTY;
    /* Initialize PWM GENERATOR 1 DUTY CYCLE REGISTER */
    PG1DC        = LOOPTIME_TCY>>1;
    /* Initialize PWM GENERATOR 1 DUTY CYCLE ADJUSTMENT REGISTER */
    PG1DCA       = 0x0000;
    /* Initialize PWM GENERATOR 1 PERIOD REGISTER */
    PG1PER       = 0x0000;
    /* Initialize PWM GENERATOR 1 DEAD-TIME REGISTER */
    PG1DTbits.DTH = DEADTIME;
    /* Initialize PWM GENERATOR 1 DEAD-TIME REGISTER */
    PG1DTbits.DTL = DEADTIME;

    /* Initialize PWM GENERATOR 1 TRIGGER A REGISTER */
    PG1TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 1 TRIGGER B REGISTER */
    PG1TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 1 TRIGGER C REGISTER */
    PG1TRIGC     = 0x0000;
    
} 

/**
* <B> Function: InitPWMGenerator2()    </B>
*
* @brief Function to configure PWM Module # 2
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPWMGenerator2();     </CODE>
*
*/
void InitPWMGenerator2 (void)
{

    /* Initialize PWM GENERATOR 2 CONTROL REGISTER */
    PG2CON      = 0x0000;
    /* PWM Generator 2 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG2CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG2CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    PG2CONbits.MODSEL = 6;
#else
    PG2CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG2CONbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 2 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG2DC
       0 = Macro uses the PG2DC register*/
    PG2CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG2PER
       0 = Macro uses the PG2PER register */
    PG2CONbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG2PHASE
       0 = Macro uses the PG2PHASE register */
    PG2CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG2CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG2CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG2CONbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    PG2CONbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 2 STATUS REGISTER*/
    PG2STAT      = 0x0000;
    /* Initialize PWM GENERATOR 2 I/O CONTROL REGISTER */
    PG2IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG2IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to PWM2H and PWM2L Device Pins bit 
       0 = PWM2H/L signals are mapped to their respective pins */
    PG2IOCON1bits.SWAP = 0;
    /* User Override Enable for PWM2H Pin bit
       0 = PWM Generator provides data for the PWM2H pin*/
    PG2IOCON2bits.OVRENH = 0;
    /* User Override Enable for PWM2L Pin bit
       0 = PWM Generator provides data for the PWM2L pin*/
    PG2IOCON2bits.OVRENL = 0;
    /* Data for PWM2H/PWM2L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM2H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM2L */
    PG2IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG2IOCON2bits.OSYNC = 0;
    /* Data for PWM2H/PWM2L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM2H.
       If Fault is active, then FLTDAT<0> provides data for PWM2L.*/
    PG2IOCON2bits.FLT1DAT = 0;
    /* Data for PWM2H/PWM2L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM2H.
       If current limit is active, then CLDAT<0> provides data for PWM2L.*/
    PG2IOCON2bits.CLDAT = 0;
    /* Data for PWM2H/PWM2L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM2H.
       If feed-forward is active, then FFDAT<0> provides data for PWM2L.*/
    PG2IOCON2bits.FFDAT = 0;
    /* Data for PWM2H/PWM2L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM2H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM2L data. */
    PG2IOCON2bits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 2 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG2IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG2IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG2IOCON1bits.PMOD = 0;
    /* PWM2H Output Port Enable bit
       1 = PWM Generator controls the PWM2H output pin
       0 = PWM Generator does not control the PWM2H output pin */
    PG2IOCON1bits.PENH = 1;
    /* PWM2L Output Port Enable bit
       1 = PWM Generator controls the PWM2L output pin
       0 = PWM Generator does not control the PWM2L output pin */
    PG2IOCON1bits.PENL = 1;
    /* PWM2H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG2IOCON1bits.POLH = 0;
    /* PWM2L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG2IOCON1bits.POLL = 0;
    
    /* Initialize PWM GENERATOR 2 EVENT REGISTER */
    PG2EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG2EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG2TRIGC Compare Event Enable bit
       0 = PG2TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG2EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG2TRIGB Compare Event Enable bit
       0 = PG2TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG2EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is PG2TRIGA Compare Event Enable bit
       1 = PG2TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG2EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG2DC register automatically sets the UPDATE bit*/
    PG2EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG2EVT1bits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 2 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    PG2EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG2EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG2EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG2EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG2EVT1bits.IEVTSEL = 3;

        /* ADC Trigger 2 Source is PG2TRIGC Compare Event Enable bit
       0 = PG2TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG2TRIGB Compare Event Enable bit
       0 = PG2TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG2TRIGA Compare Event Enable bit
       0 = PG2TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG2EVT1bits.ADTR1OFS = 0;
    
    /* PWM GENERATOR 2 Current Limit PCI REGISTER */
    PG2CLPCI1    = 0x0000;
    /* PWM GENERATOR 2 Feed Forward PCI REGISTER  */
    PG2FFPCI1    = 0x0000;
    /* PWM GENERATOR 2 Sync PCI REGISTER */
    PG2SPCI1    = 0x0000;
    
    /* Initialize PWM GENERATOR 2 LEADING-EDGE BLANKING REGISTER */
    PG2LEB      = 0x0000;
    
    PG2EVT1bits.PWMPCI  = 4;
    PG2SPCI1bits.PPS = 0 ;
    PG2SPCI2 = 8388608;
    
    /* Initialize PWM GENERATOR 2 PHASE REGISTER */
    PG2PHASE     = MIN_DUTY;
    /* Initialize PWM GENERATOR 2 DUTY CYCLE REGISTER */
    PG2DC        = LOOPTIME_TCY>>1;
    /* Initialize PWM GENERATOR 2 DUTY CYCLE ADJUSTMENT REGISTER */
    PG2DCA       = 0x0000;
    /* Initialize PWM GENERATOR 2 PERIOD REGISTER */
    PG2PER       = 0x0000;
    /* Initialize PWM GENERATOR 2 DEAD-TIME REGISTER */
    PG2DTbits.DTH = DEADTIME;
    /* Initialize PWM GENERATOR 2 DEAD-TIME REGISTER */
    PG2DTbits.DTL = DEADTIME;

    /* Initialize PWM GENERATOR 2 TRIGGER A REGISTER */
    PG2TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 2 TRIGGER B REGISTER */
    PG2TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 2 TRIGGER C REGISTER */
    PG2TRIGC     = 0x0000;
    
}

/**
* <B> Function: InitPWMGenerator3()    </B>
*
* @brief Function to configure PWM Module # 3
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPWMGenerator3();     </CODE>
*
*/
void InitPWMGenerator3 (void)
{


    /* Initialize PWM GENERATOR 3 CONTROL REGISTER */
    PG3CON      = 0x0000;
    /* PWM Generator 3 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG3CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG3CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    PG3CONbits.MODSEL = 6;
#else
    PG3CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG3CONbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 3 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG3DC
       0 = Macro uses the PG3DC register*/
    PG3CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG3PER
       0 = Macro uses the PG3PER register */
    PG3CONbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG3PHASE
       0 = Macro uses the PG3PHASE register */
    PG3CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG3CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG3CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG3CONbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    PG3CONbits.SOCS = 3;
    
    /* Clear PWM GENERATOR 3 STATUS REGISTER*/
    PG3STAT      = 0x0000;
    /* Initialize PWM GENERATOR 3 I/O CONTROL REGISTER */
    PG3IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG3IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to PWM3H and PWM3L Device Pins bit 
       0 = PWM3H/L signals are mapped to their respective pins */
    PG3IOCON1bits.SWAP = 0;
    /* User Override Enable for PWM3H Pin bit
       0 = PWM Generator provides data for the PWM3H pin*/
    PG3IOCON2bits.OVRENH = 0;
    /* User Override Enable for PWM3L Pin bit
       0 = PWM Generator provides data for the PWM3L pin*/
    PG3IOCON2bits.OVRENL = 0;
    /* Data for PWM3H/PWM3L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM3H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM3L */
    PG3IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG3IOCON2bits.OSYNC = 0;
    /* Data for PWM3H/PWM3L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM3H.
       If Fault is active, then FLTDAT<0> provides data for PWM3L.*/
    PG3IOCON2bits.FLT1DAT = 0;
    /* Data for PWM3H/PWM3L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM3H.
       If current limit is active, then CLDAT<0> provides data for PWM3L.*/
    PG3IOCON2bits.CLDAT = 0;
    /* Data for PWM3H/PWM3L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM3H.
       If feed-forward is active, then FFDAT<0> provides data for PWM3L.*/
    PG3IOCON2bits.FFDAT = 0;
    /* Data for PWM3H/PWM3L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM3H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM3L data. */
    PG3IOCON2bits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 3 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG3IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG3IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG3IOCON1bits.PMOD = 0;
    /* PWM1H Output Port Enable bit
       1 = PWM Generator controls the PWM1H output pin
       0 = PWM Generator does not control the PWM1H output pin */
    PG3IOCON1bits.PENH = 1;
    /* PWM1L Output Port Enable bit
       1 = PWM Generator controls the PWM1L output pin
       0 = PWM Generator does not control the PWM1L output pin */
    PG3IOCON1bits.PENL = 1;
    /* PWM1H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG3IOCON1bits.POLH = 0;
    /* PWM1L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG3IOCON1bits.POLL = 0;
    
    /* Initialize PWM GENERATOR 3 EVENT REGISTER */
    PG3EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG3EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG3TRIGC Compare Event Enable bit
       0 = PG3TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG3EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG3TRIGB Compare Event Enable bit
       0 = PG3TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG3EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is PG3TRIGA Compare Event Enable bit
       1 = PG3TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG3EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG3DC register automatically sets the UPDATE bit*/
    PG3EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG3EVT1bits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 3 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    PG3EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG3EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG3EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG3EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG3EVT1bits.IEVTSEL = 3;

    /* ADC Trigger 2 Source is PG3TRIGC Compare Event Enable bit
       0 = PG3TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG3TRIGB Compare Event Enable bit
       0 = PG3TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG3TRIGA Compare Event Enable bit
       0 = PG3TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG3EVT1bits.ADTR1OFS = 0;

    /* PWM GENERATOR 3 Current Limit PCI REGISTER */
    PG3CLPCI1    = 0x0000;
    /* PWM GENERATOR 3 Feed Forward PCI REGISTER  */
    PG3FFPCI1    = 0x0000;
    /* PWM GENERATOR 3 Sync PCI REGISTER */
    PG3SPCI1    = 0x0000;
    
    /* Initialize PWM GENERATOR 3 LEADING-EDGE BLANKING REGISTER */
    PG3LEB      = 0x0000;
    
    PG3EVT1bits.PWMPCI  = 4;
    PG3SPCI1bits.PPS = 0 ;
    PG3SPCI2 = 8388608;    
    
    /* Initialize PWM GENERATOR 3 PHASE REGISTER */
    PG3PHASE     = MIN_DUTY;
    /* Initialize PWM GENERATOR 3 DUTY CYCLE REGISTER */
    PG3DC        = LOOPTIME_TCY>>1;
    /* Initialize PWM GENERATOR 3 DUTY CYCLE ADJUSTMENT REGISTER */
    PG3DCA       = 0x0000;
    /* Initialize PWM GENERATOR 3 PERIOD REGISTER */
    PG3PER       = 0x0000;
    /* Initialize PWM GENERATOR 3 DEAD-TIME REGISTER */
    PG3DTbits.DTH = DEADTIME;
    /* Initialize PWM GENERATOR 3 DEAD-TIME REGISTER */
    PG3DTbits.DTL = DEADTIME;

    /* Initialize PWM GENERATOR 3 TRIGGER A REGISTER */
    PG3TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 3 TRIGGER B REGISTER */
    PG3TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 3 TRIGGER C REGISTER */
    PG3TRIGC     = 0x0000;
    
}

/**
* <B> Function: InitPWMGenerator6()    </B>
*
* @brief Function to configure PWM Module # 6
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPWMGenerator6 ();     </CODE>
*
*/
void InitPWMGenerator6 (void)
{

    /* Initialize PWM GENERATOR 6 CONTROL REGISTER */
    PG6CON      = 0x0000;
    /* PWM Generator 6 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG6CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG6CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    PG6CONbits.MODSEL = 6;
#else
    PG6CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG6CONbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 6 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG6DC
       0 = Macro uses the PG6DC register*/
    PG6CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG6PER
       0 = Macro uses the PG6PER register */
    PG6CONbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG6PHASE
       0 = Macro uses the PG6PHASE register */
    PG6CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG6CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG6CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG6CONbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    PG6CONbits.SOCS = 5;
    
    /* Clear PWM GENERATOR 6 STATUS REGISTER*/
    PG6STAT      = 0x0000;
    /* Initialize PWM GENERATOR 6 I/O CONTROL REGISTER */
    PG6IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG6IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to PWM6H and PWM6L Device Pins bit 
       0 = PWM6H/L signals are mapped to their respective pins */
    PG6IOCON1bits.SWAP = 0;
    /* User Override Enable for PWM6H Pin bit
       0 = PWM Generator provides data for the PWM6H pin*/
    PG6IOCON2bits.OVRENH = 0;
    /* User Override Enable for PWM6L Pin bit
       0 = PWM Generator provides data for the PWM6L pin*/
    PG6IOCON2bits.OVRENL = 0;
    /* Data for PWM6H/PWM6L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM6H
       If OVERENL = 1, then OVRDAT<0> provides data for PWM6L */
    PG6IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG6IOCON2bits.OSYNC = 0;
    /* Data for PWM6H/PWM6L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM6H.
       If Fault is active, then FLTDAT<0> provides data for PWM6L.*/
    PG6IOCON2bits.FLT1DAT = 0;
    /* Data for PWM6H/PWM6L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM6H.
       If current limit is active, then CLDAT<0> provides data for PWM6L.*/
    PG6IOCON2bits.CLDAT = 0;
    /* Data for PWM6H/PWM6L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM6H.
       If feed-forward is active, then FFDAT<0> provides data for PWM6L.*/
    PG6IOCON2bits.FFDAT = 0;
    /* Data for PWM6H/PWM6L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM6H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM6L data. */
    PG6IOCON2bits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 6 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG6IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG6IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG6IOCON1bits.PMOD = 0;
    /* PWM6H Output Port Enable bit
       1 = PWM Generator controls the PWM6H output pin
       0 = PWM Generator does not control the PWM6H output pin */
    PG6IOCON1bits.PENH = 1;
    /* PWM6L Output Port Enable bit
       1 = PWM Generator controls the PWM6L output pin
       0 = PWM Generator does not control the PWM6L output pin */
    PG6IOCON1bits.PENL = 1;
    /* PWM6H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG6IOCON1bits.POLH = 0;
    /* PWM6L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG6IOCON1bits.POLL = 0;
    
    /* Initialize PWM GENERATOR 6 EVENT REGISTER */
    PG6EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG6EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG6TRIGC Compare Event Enable bit
       0 = PG6TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG6EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG6TRIGB Compare Event Enable bit
       0 = PG6TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG6EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is PG6TRIGA Compare Event Enable bit
       1 = PG6TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG6EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG6DC register automatically sets the UPDATE bit*/
    PG6EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG6EVT1bits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 6 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    PG6EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG6EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG6EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG6EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG6EVT1bits.IEVTSEL = 3;

        /* ADC Trigger 2 Source is PG6TRIGC Compare Event Enable bit
       0 = PG6TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG6EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG6TRIGB Compare Event Enable bit
       0 = PG6TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG6EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG6TRIGA Compare Event Enable bit
       0 = PG6TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG6EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG6EVT1bits.ADTR1OFS = 0;

    /* PWM GENERATOR 6 Current Limit PCI REGISTER */
    PG6CLPCI1    = 0x0000;
    /* PWM GENERATOR 6 Feed Forward PCI REGISTER  */
    PG6FFPCI1    = 0x0000;
    /* PWM GENERATOR 6 Sync PCI REGISTER */
    PG6SPCI1    = 0x0000;
    
    /* Initialize PWM GENERATOR 6 LEADING-EDGE BLANKING REGISTER */
    PG6LEB      = 0x0000;
    
    /* Initialize PWM GENERATOR 6 PHASE REGISTER */
//    PG6PHASE     = MIN_DUTY;
    /* Initialize PWM GENERATOR 6 DUTY CYCLE REGISTER */
    PG6DC        = (LOOPTIME_TCY)>>1;
    /* Initialize PWM GENERATOR 6 DUTY CYCLE ADJUSTMENT REGISTER */
    PG6DCA       = 0x0000;
    /* Initialize PWM GENERATOR 6 PERIOD REGISTER */
    PG6PER       = LOOPTIME_TCY;
    /* Initialize PWM GENERATOR 6 DEAD-TIME REGISTER */
    PG6DTbits.DTH = DEADTIME;
    /* Initialize PWM GENERATOR 6 DEAD-TIME REGISTER */
    PG6DTbits.DTL = DEADTIME;

    /* Initialize PWM GENERATOR 6 TRIGGER A REGISTER */
    PG6TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 6 TRIGGER B REGISTER */
    PG6TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 6 TRIGGER C REGISTER */
    PG6TRIGC     = 0x0000;
    
} 

/**
* <B> Function: InitPWMGenerator7()    </B>
*
* @brief Function to configure PWM Module # 7
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPWMGenerator7 ();     </CODE>
*
*/
void InitPWMGenerator7 (void)
{

    /* Initialize PWM GENERATOR 7 CONTROL REGISTER */
    PG7CON      = 0x0000;
    /* PWM Generator 1 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG7CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG7CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    PG7CONbits.MODSEL = 6;
#else
    PG7CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG7CONbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 7 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG7DC
       0 = Macro uses the PG7DC register*/
    PG7CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG7PER
       0 = Macro uses the PG7PER register */
    PG7CONbits.MPERSEL = 0;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG7PHASE
       0 = Macro uses the PG7PHASE register */
    PG7CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG7CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG7CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG7CONbits.TRGMOD = 0;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    PG7CONbits.SOCS = 5;
    
    /* Clear PWM GENERATOR 7 STATUS REGISTER*/
    PG7STAT      = 0x0000;
    /* Initialize PWM GENERATOR 7 I/O CONTROL REGISTER */
    PG7IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG7IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to PWM7H and PWM7L Device Pins bit 
       0 = PWM7H/L signals are mapped to their respective pins */
    PG7IOCON1bits.SWAP = 0;
    /* User Override Enable for PWM7H Pin bit
       0 = PWM Generator provides data for the PWM7H pin*/
    PG7IOCON2bits.OVRENH = 0;
    /* User Override Enable for PWM7L Pin bit
       0 = PWM Generator provides data for the PWM7L pin*/
    PG7IOCON2bits.OVRENL = 0;
    /* Data for PWM7H/PWM7L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM7H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM7L */
    PG7IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG7IOCON2bits.OSYNC = 0;
    /* Data for PWM7H/PWM7L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM7H.
       If Fault is active, then FLTDAT<0> provides data for PWM7L.*/
    PG7IOCON2bits.FLT1DAT = 0;
    /* Data for PWM7H/PWM7L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM7H.
       If current limit is active, then CLDAT<0> provides data for PWM7L.*/
    PG7IOCON2bits.CLDAT = 0;
    /* Data for PWM7H/PWM7L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM7H.
       If feed-forward is active, then FFDAT<0> provides data for PWM7L.*/
    PG7IOCON2bits.FFDAT = 0;
    /* Data for PWM7H/PWM7L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM7H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM7L data. */
    PG7IOCON2bits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 7 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG7IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG7IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG7IOCON1bits.PMOD = 0;
    /* PWM1H Output Port Enable bit
       1 = PWM Generator controls the PWM1H output pin
       0 = PWM Generator does not control the PWM1H output pin */
    PG7IOCON1bits.PENH = 1;
    /* PWM1L Output Port Enable bit
       1 = PWM Generator controls the PWM1L output pin
       0 = PWM Generator does not control the PWM1L output pin */
    PG7IOCON1bits.PENL = 1;
    /* PWM1H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG7IOCON1bits.POLH = 0;
    /* PWM1L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG7IOCON1bits.POLL = 0;
    
    /* Initialize PWM GENERATOR 7 EVENT REGISTER */
    PG7EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG7EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG7TRIGC Compare Event Enable bit
       0 = PG7TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG7EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG7TRIGB Compare Event Enable bit
       0 = PG7TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG7EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is PG7TRIGA Compare Event Enable bit
       1 = PG7TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG7EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG7DC register automatically sets the UPDATE bit*/
    PG7EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG7EVT1bits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 7 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    PG7EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG7EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG7EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG7EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG7EVT1bits.IEVTSEL = 3;

        /* ADC Trigger 2 Source is PG7TRIGC Compare Event Enable bit
       0 = PG7TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG7EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG7TRIGB Compare Event Enable bit
       0 = PG7TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG7EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG7TRIGA Compare Event Enable bit
       0 = PG7TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG7EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG7EVT1bits.ADTR1OFS = 0;

    /* PWM GENERATOR 7 Current Limit PCI REGISTER */
    PG7CLPCI1    = 0x0000;
    /* PWM GENERATOR 7 Feed Forward PCI REGISTER  */
    PG7FFPCI1    = 0x0000;
    /* PWM GENERATOR 7 Sync PCI REGISTER */
    PG7SPCI1    = 0x0000;
    
    /* Initialize PWM GENERATOR 7 LEADING-EDGE BLANKING REGISTER */
    PG7LEB      = 0x0000;
    
    /* Initialize PWM GENERATOR 7 PHASE REGISTER */
    PG7PHASE     = MIN_DUTY;
    /* Initialize PWM GENERATOR 7 DUTY CYCLE REGISTER */
    PG7DC        = (LOOPTIME_TCY)>>1;
    /* Initialize PWM GENERATOR 7 DUTY CYCLE ADJUSTMENT REGISTER */
    PG7DCA       = 0x0000;
    /* Initialize PWM GENERATOR 7 PERIOD REGISTER */
    PG7PER       = LOOPTIME_TCY;
    /* Initialize PWM GENERATOR 7 DEAD-TIME REGISTER */
    PG7DTbits.DTH = DEADTIME;
    /* Initialize PWM GENERATOR 7 DEAD-TIME REGISTER */
    PG7DTbits.DTL = DEADTIME;

    /* Initialize PWM GENERATOR 7 TRIGGER A REGISTER */
    PG7TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 7 TRIGGER B REGISTER */
    PG7TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 7 TRIGGER C REGISTER */
    PG7TRIGC     = 0x0000;
    
} 

/**
* <B> Function: InitPWMGenerator8()    </B>
*
* @brief Function to configure PWM Module # 8
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPWMGenerator8 ();     </CODE>
*
*/
void InitPWMGenerator8 (void)
{

    /* Initialize PWM GENERATOR 8 CONTROL REGISTER */
    PG8CON      = 0x0000;
    /* PWM Generator 8 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG8CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG8CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    PG8CONbits.MODSEL = 6;
#else
    PG8CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG8CONbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 8 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG8DC
       0 = Macro uses the PG8DC register*/
    PG8CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG8PER
       0 = Macro uses the PG8PER register */
    PG8CONbits.MPERSEL = 0;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG8PHASE
       0 = Macro uses the PG8PHASE register */
    PG8CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG8CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    PG8CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    PG8CONbits.TRGMOD = 0;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    PG8CONbits.SOCS = 5;
    
    /* Clear PWM GENERATOR 8 STATUS REGISTER*/
    PG8STAT      = 0x0000;
    /* Initialize PWM GENERATOR 8 I/O CONTROL REGISTER */
    PG8IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG8IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to PWM8H and PWM8L Device Pins bit 
       0 = PWM8H/L signals are mapped to their respective pins */
    PG8IOCON1bits.SWAP = 0;
    /* User Override Enable for PWM8H Pin bit
       0 = PWM Generator provides data for the PWM8H pin*/
    PG8IOCON2bits.OVRENH = 0;
    /* User Override Enable for PWM8L Pin bit
       0 = PWM Generator provides data for the PWM8L pin*/
    PG8IOCON2bits.OVRENL = 0;
    /* Data for PWM8H/PWM8L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM8H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM8L */
    PG8IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG8IOCON2bits.OSYNC = 0;
    /* Data for PWM8H/PWM8L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM8H.
       If Fault is active, then FLTDAT<0> provides data for PWM8L.*/
    PG8IOCON2bits.FLT1DAT = 0;
    /* Data for PWM8H/PWM8L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM8H.
       If current limit is active, then CLDAT<0> provides data for PWM8L.*/
    PG8IOCON2bits.CLDAT = 0;
    /* Data for PWM8H/PWM8L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM8H.
       If feed-forward is active, then FFDAT<0> provides data for PWM8L.*/
    PG8IOCON2bits.FFDAT = 0;
    /* Data for PWM8H/PWM8L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM8H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM8L data. */
    PG8IOCON2bits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 8 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG8IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG8IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG8IOCON1bits.PMOD = 0;
    /* PWM8H Output Port Enable bit
       1 = PWM Generator controls the PWM8H output pin
       0 = PWM Generator does not control the PWM8H output pin */
    PG8IOCON1bits.PENH = 1;
    /* PWM8L Output Port Enable bit
       1 = PWM Generator controls the PWM8L output pin
       0 = PWM Generator does not control the PWM8L output pin */
    PG8IOCON1bits.PENL = 1;
    /* PWM8H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG8IOCON1bits.POLH = 0;
    /* PWM8L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG8IOCON1bits.POLL = 0;
    
    /* Initialize PWM GENERATOR 8 EVENT REGISTER */
    PG8EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG8EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG8TRIGC Compare Event Enable bit
       0 = PG8TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG8EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG8TRIGB Compare Event Enable bit
       0 = PG8TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG8EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is PG8TRIGA Compare Event Enable bit
       1 = PG8TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG8EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG8DC register automatically sets the UPDATE bit*/
    PG8EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG8EVT1bits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 8 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    PG8EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG8EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG8EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG8EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG8EVT1bits.IEVTSEL = 3;

        /* ADC Trigger 2 Source is PG8TRIGC Compare Event Enable bit
       0 = PG8TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG8EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG8TRIGB Compare Event Enable bit
       0 = PG8TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG8EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG8TRIGA Compare Event Enable bit
       0 = PG8TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG8EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG8EVT1bits.ADTR1OFS = 0;

    /* PWM GENERATOR 8 Current Limit PCI REGISTER */
    PG8CLPCI1    = 0x0000;
    /* PWM GENERATOR 8 Feed Forward PCI REGISTER  */
    PG8FFPCI1    = 0x0000;
    /* PWM GENERATOR 8 Sync PCI REGISTER */
    PG8SPCI1    = 0x0000;
    
    /* Initialize PWM GENERATOR 8 LEADING-EDGE BLANKING REGISTER */
    PG8LEB      = 0x0000;
    
    /* Initialize PWM GENERATOR 8 PHASE REGISTER */
    PG8PHASE     = MIN_DUTY;
    /* Initialize PWM GENERATOR 8 DUTY CYCLE REGISTER */
    PG8DC        = (LOOPTIME_TCY)>>1;
    /* Initialize PWM GENERATOR 8 DUTY CYCLE ADJUSTMENT REGISTER */
    PG8DCA       = 0x0000;
    /* Initialize PWM GENERATOR 8 PERIOD REGISTER */
    PG8PER       = LOOPTIME_TCY;
    /* Initialize PWM GENERATOR 8 DEAD-TIME REGISTER */
    PG8DTbits.DTH = DEADTIME;
    /* Initialize PWM GENERATOR 8 DEAD-TIME REGISTER */
    PG8DTbits.DTL = DEADTIME;

    /* Initialize PWM GENERATOR 8 TRIGGER A REGISTER */
    PG8TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 8 TRIGGER B REGISTER */
    PG8TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 8 TRIGGER C REGISTER */
    PG8TRIGC     = 0x0000;
    
} 

/**
* <B> Function: InitAuxPWMGenerator1()    </B>
*
* @brief Function to configure APWM Module # 1
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitAuxPWMGenerator1 ();     </CODE>
*
*/
void InitAuxPWMGenerator1 (void)
{

    /* Initialize APWM GENERATOR 1 CONTROL REGISTER */
    APG1CON      = 0x0000;
    /* APWM Generator 1 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring APWM Generator is disabled prior to configuring module */
    APG1CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    APG1CONbits.CLKSEL = 1;
    /* APWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    APG1CONbits.MODSEL = 6;
#else
    APG1CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    APG1CONbits.TRGCNT = 0;
    
    /* Initialize APWM GENERATOR 1 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of APG1DC
       0 = Macro uses the APG1DC register*/
    APG1CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of APG1PER
       0 = Macro uses the APG1PER register */
    APG1CONbits.MPERSEL = 0;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of APG1PHASE
       0 = Macro uses the APG1PHASE register */
    APG1CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    APG1CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    APG1CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    APG1CONbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    APG1CONbits.SOCS = 0xF;
    
    /* Clear APWM GENERATOR 1 STATUS REGISTER*/
    APG1STAT      = 0x0000;
    /* Initialize APWM GENERATOR 1 I/O CONTROL REGISTER */
    APG1IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    APG1IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to APWM1H and APWM1L Device Pins bit 
       0 = APW1H/L signals are mapped to their respective pins */
    APG1IOCON1bits.SWAP = 0;
    /* User Override Enable for APW1H Pin bit
       0 = PWM Generator provides data for the APW1H pin*/
    APG1IOCON2bits.OVRENH = 0;
    /* User Override Enable for APW1L Pin bit
       0 = PWM Generator provides data for the APW1L pin*/
    APG1IOCON2bits.OVRENL = 0;
    /* Data for APW1H/APW1L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for APW1H.
       If OVERENL = 1, then OVRDAT<0> provides data for APW1L */
    APG1IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    APG1IOCON2bits.OSYNC = 0;
    /* Data for APW1H/APW1L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for APW1H.
       If Fault is active, then FLTDAT<0> provides data for APW1L.*/
    APG1IOCON2bits.FLT1DAT = 0;
    /* Data for APW1H/APW1L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for APW1H.
       If current limit is active, then CLDAT<0> provides data for APW1L.*/
    APG1IOCON2bits.CLDAT = 0;
    /* Data for APW1H/APW1L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for APW1H.
       If feed-forward is active, then FFDAT<0> provides data for APW1L.*/
    APG1IOCON2bits.FFDAT = 0;
    /* Data for APW1H/APW1L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides APW1H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides APW1L data. */
    APG1IOCON2bits.DBDAT = 0;
    
    /* Initialize APWM GENERATOR 1 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    APG1IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    APG1IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    APG1IOCON1bits.PMOD = 0;
    /* APW1H Output Port Enable bit
       1 = PWM Generator controls the APW1H output pin
       0 = PWM Generator does not control the APW1H output pin */
    APG1IOCON1bits.PENH = 1;
    /* APW1L Output Port Enable bit
       1 = PWM Generator controls the APW1L output pin
       0 = APWM Generator does not control the PWM1L output pin */
    APG1IOCON1bits.PENL = 1;
    /* APW1H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    APG1IOCON1bits.POLH = 0;
    /* APW1L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    APG1IOCON1bits.POLL = 0;
    
    /* Initialize APWM GENERATOR 1 EVENT REGISTER */
    APG1EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    APG1EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is APG1TRIGC Compare Event Enable bit
       0 = APG1TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    APG1EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is APG1TRIGB Compare Event Enable bit
       0 = APG1TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    APG1EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is APG1TRIGA Compare Event Enable bit
       1 = APG1TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    APG1EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the APG1DC register automatically sets the UPDATE bit*/
    APG1EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    APG1EVT1bits.PGTRGSEL = 0;
    
    /* Initialize APWM GENERATOR 1 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    APG1EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    APG1EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    APG1EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    APG1EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    APG1EVT1bits.IEVTSEL = 3;

        /* ADC Trigger 2 Source is APG1TRIGC Compare Event Enable bit
       0 = APG1TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG1EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is APG1TRIGB Compare Event Enable bit
       0 = APG1TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG1EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is APG1TRIGA Compare Event Enable bit
       0 = APG1TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG1EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    APG1EVT1bits.ADTR1OFS = 0;

    /* APWM GENERATOR 1 Current Limit PCI REGISTER */
    APG1CLPCI1    = 0x0000;
    /* APWM GENERATOR 1 Feed Forward PCI REGISTER  */
    APG1FFPCI1    = 0x0000;
    /* APWM GENERATOR 1 Sync PCI REGISTER */
    APG1SPCI1    = 0x0000;
    
    /* Initialize APWM GENERATOR 1 LEADING-EDGE BLANKING REGISTER */
    APG1LEB      = 0x0000;
    
    APG1EVT1bits.PWMPCI  = 3;
    APG1SPCI1bits.PPS = 1 ;

    
    APG1SPCI2 = 8388608;
    
    /* Initialize APWM GENERATOR 1 PHASE REGISTER */
    APG1PHASE     = MIN_DUTY;
    /* Initialize APWM GENERATOR 1 DUTY CYCLE REGISTER */
    APG1DC        = AUX_PWM_LOOPTIME_TCY>>1;
    /* Initialize APWM GENERATOR 1 DUTY CYCLE ADJUSTMENT REGISTER */
    APG1DCA       = 0x0000;
    /* Initialize APWM GENERATOR 1 PERIOD REGISTER */
    APG1PER       = AUX_PWM_LOOPTIME_TCY;
    /* Initialize APWM GENERATOR 1 DEAD-TIME REGISTER */
    APG1DTbits.DTH = DEADTIME;
    /* Initialize APWM GENERATOR 1 DEAD-TIME REGISTER */
    APG1DTbits.DTL = DEADTIME;

    /* Initialize APWM GENERATOR 1 TRIGGER A REGISTER */
    APG1TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize APWM GENERATOR 1 TRIGGER B REGISTER */
    APG1TRIGB     = 0x0000;
    /* Initialize APWM GENERATOR 1 TRIGGER C REGISTER */
    APG1TRIGC     = 0x0000;
    
} 

/**
* <B> Function: InitAuxPWMGenerator2()    </B>
*
* @brief Function to configure APWM Module # 2
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitAuxPWMGenerator2 ();     </CODE>
*
*/
void InitAuxPWMGenerator2 (void)
{

    /* Initialize APWM GENERATOR 2 CONTROL REGISTER */
    APG2CON      = 0x0000;
    /* APWM Generator 2 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    APG2CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    APG2CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    APG2CONbits.MODSEL = 6;
#else
    APG2CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    APG2CONbits.TRGCNT = 0;
    
    /* Initialize APWM GENERATOR 2 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of APG2DC
       0 = Macro uses the APG2DC register*/
    APG2CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of APG2PER
       0 = Macro uses the APG2PER register */
    APG2CONbits.MPERSEL = 0;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of APG2PHASE
       0 = Macro uses the APG2PHASE register */
    APG2CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    APG2CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    APG2CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    APG2CONbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    APG2CONbits.SOCS = 0xF;
    
    /* Clear APWM GENERATOR 2 STATUS REGISTER*/
    APG2STAT      = 0x0000;
    /* Initialize APWM GENERATOR 2 I/O CONTROL REGISTER */
    APG2IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the APWM output levels */
    APG2IOCON2bits.CLMOD = 0;
    /* Swap APWM Signals to APWM2H and APWM2L Device Pins bit 
       0 = APWM2H/L signals are mapped to their respective pins */
    APG2IOCON1bits.SWAP = 0;
    /* User Override Enable for APWM2H Pin bit
       0 = PWM Generator provides data for the APWM2H pin*/
    APG2IOCON2bits.OVRENH = 0;
    /* User Override Enable for APWM2L Pin bit
       0 = PWM Generator provides data for the APWM2L pin*/
    APG2IOCON2bits.OVRENL = 0;
    /* Data for APWM2H/APWM2L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for APWM2H.
       If OVERENL = 1, then OVRDAT<0> provides data for APWM2L */
    APG2IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    APG2IOCON2bits.OSYNC = 0;
    /* Data for APWM2H/APWM2L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for APWM2H.
       If Fault is active, then FLTDAT<0> provides data for APWM2L.*/
    APG2IOCON2bits.FLT1DAT = 0;
    /* Data for APWM2H/APWM2L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for APWM2H.
       If current limit is active, then CLDAT<0> provides data for APWM2L.*/
    APG2IOCON2bits.CLDAT = 0;
    /* Data for APWM2H/APWM2L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for APWM2H.
       If feed-forward is active, then FFDAT<0> provides data for APWM2L.*/
    APG2IOCON2bits.FFDAT = 0;
    /* Data for APWM2H/APWM2L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides APWM2H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides APWM2L data. */
    APG2IOCON2bits.DBDAT = 0;
    
    /* Initialize APWM GENERATOR 2 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    APG2IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    APG2IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    APG2IOCON1bits.PMOD = 0;
    /* APWM2H Output Port Enable bit
       1 = PWM Generator controls the APWM2H output pin
       0 = PWM Generator does not control the APWM2H output pin */
    APG2IOCON1bits.PENH = 1;
    /* APWM2L Output Port Enable bit
       1 = PWM Generator controls the APWM2L output pin
       0 = PWM Generator does not control the APWM2L output pin */
    APG2IOCON1bits.PENL = 1;
    /* APWM1H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    APG2IOCON1bits.POLH = 0;
    /* APWM1L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    APG2IOCON1bits.POLL = 0;
    
    /* Initialize APWM GENERATOR 2 EVENT REGISTER */
    APG2EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    APG2EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is APG2TRIGC Compare Event Enable bit
       0 = APG2TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    APG2EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is APG2TRIGB Compare Event Enable bit
       0 = APG2TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    APG2EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is APG2TRIGA Compare Event Enable bit
       1 = APG2TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    APG2EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the APG2DC register automatically sets the UPDATE bit*/
    APG2EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    APG2EVT1bits.PGTRGSEL = 0;
    
    /* Initialize APWM GENERATOR 2 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    APG2EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    APG2EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    APG2EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    APG2EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    APG2EVT1bits.IEVTSEL = 3;

    /* ADC Trigger 2 Source is APG2TRIGC Compare Event Enable bit
       0 = APG2TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG2EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is APG2TRIGB Compare Event Enable bit
       0 = APG2TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG2EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is APG2TRIGA Compare Event Enable bit
       0 = APG2TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG2EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    APG2EVT1bits.ADTR1OFS = 0;

    /* APWM GENERATOR 2 Current Limit PCI REGISTER */
    APG2CLPCI1    = 0x0000;
    /* APWM GENERATOR 2 Feed Forward PCI REGISTER  */
    APG2FFPCI1    = 0x0000;
    /* APWM GENERATOR 2 Sync PCI REGISTER */
    APG2SPCI1    = 0x0000;
    
    /* Initialize APWM GENERATOR 2 LEADING-EDGE BLANKING REGISTER */
    APG2LEB      = 0x0000;
    
    APG2EVT1bits.PWMPCI  = 3;
    APG2SPCI1bits.PPS = 1 ;
    
    APG2SPCI2 = 8388608;
    
    /* Initialize APWM GENERATOR 2 PHASE REGISTER */
    APG2PHASE     = MIN_DUTY;
    /* Initialize APWM GENERATOR 2 DUTY CYCLE REGISTER */
    APG2DC        = AUX_PWM_LOOPTIME_TCY>>1;
    /* Initialize APWM GENERATOR 2 DUTY CYCLE ADJUSTMENT REGISTER */
    APG2DCA       = 0x0000;
    /* Initialize APWM GENERATOR 2 PERIOD REGISTER */
    APG2PER       = AUX_PWM_LOOPTIME_TCY;
    /* Initialize APWM GENERATOR 2 DEAD-TIME REGISTER */
    APG2DTbits.DTH = DEADTIME;
    /* Initialize APWM GENERATOR 2 DEAD-TIME REGISTER */
    APG2DTbits.DTL = DEADTIME;

    /* Initialize APWM GENERATOR 2 TRIGGER A REGISTER */
    APG2TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize APWM GENERATOR 2 TRIGGER B REGISTER */
    APG2TRIGB     = 0x0000;
    /* Initialize APWM GENERATOR 2 TRIGGER C REGISTER */
    APG2TRIGC     = 0x0000;
    
} 

/**
* <B> Function: InitAuxPWMGenerator3()    </B>
*
* @brief Function to configure APWM Module # 3
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitAuxPWMGenerator3 ();     </CODE>
*
*/
void InitAuxPWMGenerator3 (void)
{

    /* Initialize APWM GENERATOR 3 CONTROL REGISTER */
    APG3CON      = 0x0000;
    /* APWM Generator 1 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    APG3CONbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    APG3CONbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
#ifdef SINGLE_SHUNT
    APG3CONbits.MODSEL = 6;
#else
    APG3CONbits.MODSEL = 4;
#endif 
    /* Trigger Count Select bits
       000 = APWM Generator produces 1 PWM cycle after triggered */
    APG3CONbits.TRGCNT = 0;
    
    /* Initialize APWM GENERATOR 3 CONTROL REGISTER */
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of APG3DC
       0 = Macro uses the APG3DC register*/
    APG3CONbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of APG3PER
       0 = Macro uses the APG3PER register */
    APG3CONbits.MPERSEL = 0;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of APG3PHASE
       0 = Macro uses the APG3PHASE register */
    APG3CONbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    APG3CONbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       Update Data registers at start of next PWM cycle if UPDATE = 1. */
    APG3CONbits.UPDMOD = 0;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode */
    APG3CONbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC*/
    APG3CONbits.SOCS = 0xF;
    
    /* Clear APWM GENERATOR 3 STATUS REGISTER*/
    APG3STAT      = 0x0000;
    /* Initialize APWM GENERATOR 3 I/O CONTROL REGISTER */
    APG3IOCON2    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    APG3IOCON2bits.CLMOD = 0;
    /* Swap PWM Signals to APWM1H and APWM1L Device Pins bit 
       0 = APWM1H/L signals are mapped to their respective pins */
    APG3IOCON1bits.SWAP = 0;
    /* User Override Enable for APWM1H Pin bit
       0 = PWM Generator provides data for the APWM1H pin*/
    APG3IOCON2bits.OVRENH = 0;
    /* User Override Enable for APWM1L Pin bit
       0 = PWM Generator provides data for the APWM1L pin*/
    APG3IOCON2bits.OVRENL = 0;
    /* Data for APWM1H/APWM1L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for APWM1H.
       If OVERENL = 1, then OVRDAT<0> provides data for APWM1L */
    APG3IOCON2bits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    APG3IOCON2bits.OSYNC = 0;
    /* Data for APWM1H/APWM1L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for APWM1H.
       If Fault is active, then FLTDAT<0> provides data for APWM1L.*/
    APG3IOCON2bits.FLT1DAT = 0;
    /* Data for APWM1H/APWM1L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for APWM1H.
       If current limit is active, then CLDAT<0> provides data for APWM1L.*/
    APG3IOCON2bits.CLDAT = 0;
    /* Data for APWM1H/APWM1L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for APWM1H.
       If feed-forward is active, then FFDAT<0> provides data for APWM1L.*/
    APG3IOCON2bits.FFDAT = 0;
    /* Data for APWM1H/APWM1L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides APWM1H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides APWM1L data. */
    APG3IOCON2bits.DBDAT = 0;
    
    /* Initialize APWM GENERATOR 3 I/O CONTROL REGISTER */    

    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    APG3IOCON1bits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    APG3IOCON1bits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    APG3IOCON1bits.PMOD = 0;
    /* APWM1H Output Port Enable bit
       1 = PWM Generator controls the APWM1H output pin
       0 = PWM Generator does not control the APWM1H output pin */
    APG3IOCON1bits.PENH = 1;
    /* APWM1L Output Port Enable bit
       1 = PWM Generator controls the APWM1L output pin
       0 = PWM Generator does not control the APWM1L output pin */
    APG3IOCON1bits.PENL = 1;
    /* APWM1H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    APG3IOCON1bits.POLH = 0;
    /* APWM1L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    APG3IOCON1bits.POLL = 0;
    
    /* Initialize APWM GENERATOR 3 EVENT REGISTER */
    APG3EVT1      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    APG3EVT1bits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is APG3TRIGC Compare Event Enable bit
       0 = APG3TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    APG3EVT1bits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is APG3TRIGB Compare Event Enable bit
       0 = APG3TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    APG3EVT1bits.ADTR1EN2 = 0;    
    /* ADC Trigger 1 Source is APG3TRIGA Compare Event Enable bit
       1 = APG3TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    APG3EVT1bits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the APG3DC register automatically sets the UPDATE bit*/
    APG3EVT1bits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    APG3EVT1bits.PGTRGSEL = 0;
    
    /* Initialize APWM GENERATOR 3 EVENT REGISTER */
    /* FLTIEN: PCI Fault Interrupt Enable bit
       1 = Fault interrupt is enabled */
    APG3EVT1bits.FLT1IEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    APG3EVT1bits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    APG3EVT1bits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    APG3EVT1bits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    APG3EVT1bits.IEVTSEL = 3;

        /* ADC Trigger 2 Source is APG3TRIGC Compare Event Enable bit
       0 = APG3TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG3EVT2bits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is APG3TRIGB Compare Event Enable bit
       0 = APG3TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG3EVT2bits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is APG3TRIGA Compare Event Enable bit
       0 = APG3TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    APG3EVT2bits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    APG3EVT1bits.ADTR1OFS = 0;
    
    /* APWM GENERATOR 3 Current Limit PCI REGISTER */
    APG3CLPCI1    = 0x0000;
    /* APWM GENERATOR 3 Feed Forward PCI REGISTER  */
    APG3FFPCI1    = 0x0000;
    /* APWM GENERATOR 3 Sync PCI REGISTER */
    APG3SPCI1    = 0x0000;
    
    /* Initialize APWM GENERATOR 3 LEADING-EDGE BLANKING REGISTER */
    APG3LEB      = 0x0000;
    
    APG3EVT1bits.PWMPCI  = 3;
    APG3SPCI1bits.PPS = 1 ;
    
    APG3SPCI2 = 8388608;
    
    /* Initialize APWM GENERATOR 3 PHASE REGISTER */
    APG3PHASE     = MIN_DUTY;
    /* Initialize APWM GENERATOR 3 DUTY CYCLE REGISTER */
    APG3DC        = AUX_PWM_LOOPTIME_TCY>>1;
    /* Initialize APWM GENERATOR 3 DUTY CYCLE ADJUSTMENT REGISTER */
    APG3DCA       = 0x0000;
    /* Initialize APWM GENERATOR 3 PERIOD REGISTER */
    APG3PER       = AUX_PWM_LOOPTIME_TCY;
    /* Initialize APWM GENERATOR 3 DEAD-TIME REGISTER */
    APG3DTbits.DTH = DEADTIME;
    /* Initialize APWM GENERATOR 3 DEAD-TIME REGISTER */
    APG3DTbits.DTL = DEADTIME;

    /* Initialize APWM GENERATOR 3 TRIGGER A REGISTER */
    APG3TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize APWM GENERATOR 3 TRIGGER B REGISTER */
    APG3TRIGB     = 0x0000;
    /* Initialize APWM GENERATOR 3 TRIGGER C REGISTER */
    APG3TRIGC     = 0x0000;
    
} 
// </editor-fold>