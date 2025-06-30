// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file pwm.h
 *
 * @brief This header file lists the functions and definitions to configure the 
 * PWM Module
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

#ifndef _PWM_H
#define _PWM_H

#ifdef __cplusplus  // Provide C++ Compatability
    extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <xc.h>
#include <stdint.h>
        
#include "clock.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="DEFINITIONS/CONSTANTS ">
        
#define PWM_PDC1                    PG1DC
#define PWM_PDC2                    PG2DC
#define PWM_PDC3                    PG3DC
        
#define PWM_PHASE1                  PG1PHASE 
#define PWM_PHASE2                  PG2PHASE
#define PWM_PHASE3                  PG3PHASE  
        
#define PWM_TRIGA                   PG1TRIGA 
#define PWM_TRIGB                   PG1TRIGB   
#define PWM_TRIGC                   PG1TRIGC  
              
/*Specify PWM Switching Frequency in Hertz*/
#define PWMFREQUENCY_HZ                     16000
/*Specify PWM Module Clock in Mega Hertz*/
#define PWM_CLOCK_MHZ                       400   
/* Specify PWM module dead time in micro seconds*/
#define DEADTIME_MICROSEC                   1.0f
#define MC1_LOOPTIME_SEC                    (float)(1.0/PWMFREQUENCY_HZ)        
/*Dead time in terms of PWM clock period*/  
#define DEADTIME                            (uint32_t)(DEADTIME_MICROSEC*16*PWM_CLOCK_MHZ)
/* Loop Time in micro seconds*/
#define LOOPTIME_MICROSEC                   (MC1_LOOPTIME_SEC * 1000000.0f)
/*Loop time in terms of PWM clock period*/
#define LOOPTIME_TCY                        (uint32_t)((LOOPTIME_MICROSEC*8*PWM_CLOCK_MHZ)-16)

# define AUX_PWM_LOOPTIME_TCY               (uint32_t)((2*LOOPTIME_MICROSEC*PWM_CLOCK_MHZ)-16)       
/*Specify ADC Triggering Point w.r.t PWM Output for sensing Analog Inputs*/ 
#define ADC_SAMPLING_POINT                  0

#define MIN_DUTY            (uint32_t)(DEADTIME)
#define MAX_DUTY            LOOPTIME_TCY - (uint32_t)(DEADTIME)
// </editor-fold>      

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
        
void InitPWMGenerators(void);  
void InitPWMGenerator1 (void);
void InitPWMGenerator2 (void);
void InitPWMGenerator3 (void);

void InitPWMGenerator5 (void);

void InitPWMGenerator6 (void);
void InitPWMGenerator7 (void);
void InitPWMGenerator8 (void);

void InitAuxPWMGenerator1 (void);
void InitAuxPWMGenerator2 (void);
void InitAuxPWMGenerator3 (void);

void InitPWMGenerators(void);   

// </editor-fold>
        
#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
#endif      // end of PWM_H


