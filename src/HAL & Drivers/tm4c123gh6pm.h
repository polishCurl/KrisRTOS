/*******************************************************************************
* File:     	tm4c123gh6pm.h
* Brief:    	External register definitions for tm4c123gh6pm microcontroller 
* Author: 		Krzysztof Koch
* Version:		V1.00
* Date created:	30/09/2016
* Last mod: 	04/12/2016
*
* Note: 		
*******************************************************************************/
#include "common.h"
#ifndef TM4C123GH6PM_H					// Include barrier
#define TM4C123GH6PM_H
#pragma anon_unions



/*-------------------------------------------------------------------------------
* IO definitions (access restrictions to peripheral registers)
*------------------------------------------------------------------------------*/
#define __I volatile const 				// input, read-only
#define __O volatile 					// output, write-only
#define __IO volatile 					// input-output, read and write permissions
	


/*-------------------------------------------------------------------------------
* Interrupt Number Definition 
--------------------------------------------------------------------------------*/
typedef enum {
	// Cortex-M4 Processor Exceptions Numbers 
	Reset_IRQn 				= -15,          
	NonMaskableInt_IRQn 	= -14,          
	HardFault_IRQn          = -13,          
	MemoryManagement_IRQn   = -12,          									                                                        
	BusFault_IRQn           = -11,          
	UsageFault_IRQn         = -10,          
	SVCall_IRQn             =  -5,          
	DebugMonitor_IRQn       =  -4,          
	PendSV_IRQn             =  -2,          
	SysTick_IRQn            =  -1,          
	
	// TM4C123GH6PM Specific Interrupt Numbers  
	GPIOA_IRQn              =   0,                                                                   
	GPIOB_IRQn              =   1,          
	GPIOC_IRQn              =   2,          
	GPIOD_IRQn              =   3,          
	GPIOE_IRQn              =   4,          
	UART0_IRQn              =   5,                                                                     
	UART1_IRQn              =   6,          
	SSI0_IRQn               =   7,                                                                       
	I2C0_IRQn               =   8,                                                                       
	PWM0_FAULT_IRQn         =   9,                                                                 
	PWM0_0_IRQn             =  10,                                                                    
	PWM0_1_IRQn             =  11,                                                                     
	PWM0_2_IRQn             =  12,                                                                    
	QEI0_IRQn               =  13,                                                                       
	ADC0SS0_IRQn            =  14,                                                                    
	ADC0SS1_IRQn            =  15,                                                                   
	ADC0SS2_IRQn            =  16,                                                                    
	ADC0SS3_IRQn            =  17,                                                                    
	WATCHDOG0_IRQn          =  18,                                                               
	TIMER0A_IRQn            =  19,                                                                   
	TIMER0B_IRQn            =  20,                                                                    
	TIMER1A_IRQn            =  21,          
	TIMER1B_IRQn            =  22,          
	TIMER2A_IRQn            =  23,          
	TIMER2B_IRQn            =  24,          
	COMP0_IRQn              =  25,                                                                     
	COMP1_IRQn              =  26,          
	SYSCTL_IRQn             =  28,          
	FLASH_CTRL_IRQn         =  29,                                                                
	GPIOF_IRQn              =  30,                                                                      
	UART2_IRQn              =  33,          
	SSI1_IRQn               =  34,          
	TIMER3A_IRQn            =  35,          
	TIMER3B_IRQn            =  36,          
	I2C1_IRQn               =  37,          
	QEI1_IRQn               =  38,          
	CAN0_IRQn               =  39,                                                                    
	CAN1_IRQn               =  40,                                                                      
	HIB_IRQn                =  43,          
	USB0_IRQn               =  44,                                                                    
	PWM0_3_IRQn             =  45,                                                                    
	UDMA_IRQn               =  46,          
	UDMAERR_IRQn            =  47,          
	ADC1SS0_IRQn            =  48,                                                                  
	ADC1SS1_IRQn            =  49,          
	ADC1SS2_IRQn            =  50,                                                                  
	ADC1SS3_IRQn            =  51,          
	SSI2_IRQn               =  57,          
	SSI3_IRQn               =  58,          
	UART3_IRQn              =  59,          
	UART4_IRQn              =  60,                                                                    
	UART5_IRQn              =  61,          
	UART6_IRQn              =  62,          
	UART7_IRQn              =  63,          
	I2C2_IRQn               =  68,          
	I2C3_IRQn               =  69,          
	TIMER4A_IRQn            =  70,                                                             
	TIMER4B_IRQn            =  71,          
	TIMER5A_IRQn            =  92,          
	TIMER5B_IRQn            =  93,          
	WTIMER0A_IRQn           =  94,                                                    
	WTIMER0B_IRQn           =  95,                                                
	WTIMER1A_IRQn           =  96,          
	WTIMER1B_IRQn           =  97,          
	WTIMER2A_IRQn           =  98,          
	WTIMER2B_IRQn           =  99,          
	WTIMER3A_IRQn           = 100,                                                               
	WTIMER3B_IRQn           = 101,                                               
	WTIMER4A_IRQn           = 102,                                                    
	WTIMER4B_IRQn           = 103,                                    
	WTIMER5A_IRQn           = 104,                                 
	WTIMER5B_IRQn           = 105,                         
	SYSEXC_IRQn             = 106,                                                       
	PWM1_0_IRQn             = 134,                                      
	PWM1_1_IRQn             = 135,                          
	PWM1_2_IRQn             = 136,                                                                     
	PWM1_3_IRQn             = 137,                                                                     
	PWM1_FAULT_IRQn         = 138                                                                 
} IRQn_Type;



/*-------------------------------------------------------------------------------
* System Control Block registers
*------------------------------------------------------------------------------*/
typedef struct
{
  __I  uint32_t CPUID;                  // CPUID Base Register 
  __IO uint32_t ICSR;                   // Interrupt Control and State Register 
  __IO uint32_t VTOR;                   // Vector Table Offset Register 
  __IO uint32_t AIRCR;                  // Application Interrupt and Reset Control Register 
  __IO uint32_t SCR;                    // System Control Register 
  __IO uint32_t CCR;                    // Configuration Control Register 
  __IO uint8_t  SHP[12U];               // System Handlers Priority Registers (4-7, 8-11, 12-15) 
  __IO uint32_t SHCSR;                  // System Handler Control and State Register 
  __IO uint32_t CFSR;                   // Configurable Fault Status Register 
  __IO uint32_t HFSR;                   // HardFault Status Register 
  __IO uint32_t DFSR;                   // Debug Fault Status Register 
  __IO uint32_t MMFAR;                  // MemManage Fault Address Register 
  __IO uint32_t BFAR;                   // BusFault Address Register 
  __IO uint32_t AFSR;                   // Auxiliary Fault Status Register 
  __I  uint32_t PFR[2U];                // Processor Feature Register 
  __I  uint32_t DFR;                    // Debug Feature Register 
  __I  uint32_t ADR;                    // Auxiliary Feature Register 
  __I  uint32_t MMFR[4U];               // Memory Model Feature Register 
  __I  uint32_t ISAR[5U];               // Instruction Set Attributes Register 
       uint32_t RESERVED0[5U];
  __IO uint32_t CPACR;                  // Coprocessor Access Control Register 
} SCB_Type;
#define SCB_Base 0xE000ED00
#define SCB ((SCB_Type*) SCB_Base)

// ICSR register bit numbers
#define NMISET_Pos 31 					// NMI Set Pending
#define PENDSV_Pos 28 					// PendSV Set Pending
#define UNPENDSV_Pos 27 				// PendSV Clear Pending
#define PENDSTSET_Pos 26 				// SysTick Set Pending
#define PENDSTCLR_Pos 25 				// SysTick Clear Pending
#define ISRPRE_Pos 23 					// Debug Inrerrupt Handling
#define ISRPEND 22 						// Interrupt Pending
#define VECPEND_Pos 12 					// Interrupt Pending Vector Number
#define RETBASE_Pos 11 					// Return to Base
#define VECACT_Pos 0					// Interrupt Active Vector Number



/*-------------------------------------------------------------------------------
* System control registers
*------------------------------------------------------------------------------*/
typedef struct {                          // SYSCTL Structure 
	__IO uint32_t  DID0;                  // Device Identification 0                                               
	__IO uint32_t  DID1;                  // Device Identification 1                                               
	__IO uint32_t  DC0;                   // Device Capabilities 0                                                 
	__I  uint32_t  RESERVED;
	__IO uint32_t  DC1;                   // Device Capabilities 1                                                 
	__IO uint32_t  DC2;                   // Device Capabilities 2                                                 
	__IO uint32_t  DC3;                   // Device Capabilities 3                                                 
	__IO uint32_t  DC4;                   // Device Capabilities 4                                                 
	__IO uint32_t  DC5;                   // Device Capabilities 5                                                 
	__IO uint32_t  DC6;                   // Device Capabilities 6                                                 
	__IO uint32_t  DC7;                   // Device Capabilities 7                                                 
	__IO uint32_t  DC8;                   // Device Capabilities 8                                                 
	__IO uint32_t  PBORCTL;               // Brown-Out Reset Control                                               
	__I  uint32_t  RESERVED1[3];
	__IO uint32_t  SRCR0;                 // Software Reset Control 0                                              
	__IO uint32_t  SRCR1;                 // Software Reset Control 1                                              
	__IO uint32_t  SRCR2;                 // Software Reset Control 2                                              
	__I  uint32_t  RESERVED2;
	__IO uint32_t  RIS;                   // Raw Interrupt Status                                                  
	__IO uint32_t  IMC;                   // Interrupt Mask Control                                                
	__IO uint32_t  MISC;                  // Masked Interrupt Status and Clear                                     
	__IO uint32_t  RESC;                  // Reset Cause                                                           
	__IO uint32_t  RCC;                   // Run-Mode Clock Configuration                                          
	__I  uint32_t  RESERVED3[2];
	__IO uint32_t  GPIOHBCTL;             // GPIO High-Performance Bus Control                                     
	__IO uint32_t  RCC2;                  // Run-Mode Clock Configuration 2                                        
	__I  uint32_t  RESERVED4[2];
	__IO uint32_t  MOSCCTL;               // Main Oscillator Control                                               
	__I  uint32_t  RESERVED5[32];
	__IO uint32_t  RCGC0;                 // Run Mode Clock Gating Control Register 0                              
	__IO uint32_t  RCGC1;                 // Run Mode Clock Gating Control Register 1                              
	__IO uint32_t  RCGC2;                 // Run Mode Clock Gating Control Register 2                              
	__I  uint32_t  RESERVED6;
	__IO uint32_t  SCGC0;                 // Sleep Mode Clock Gating Control Register 0                            
	__IO uint32_t  SCGC1;                 // Sleep Mode Clock Gating Control Register 1                            
	__IO uint32_t  SCGC2;                 // Sleep Mode Clock Gating Control Register 2                            
	__I  uint32_t  RESERVED7;
	__IO uint32_t  DCGC0;                 // Deep Sleep Mode Clock Gating Control Register 0                       
	__IO uint32_t  DCGC1;                 // Deep-Sleep Mode Clock Gating Control Register 1                       
	__IO uint32_t  DCGC2;                 // Deep Sleep Mode Clock Gating Control Register 2                       
	__I  uint32_t  RESERVED8[6];
	__IO uint32_t  DSLPCLKCFG;            // Deep Sleep Clock Configuration                                        
	__I  uint32_t  RESERVED9;
	__IO uint32_t  SYSPROP;               // System Properties                                                     
	__IO uint32_t  PIOSCCAL;              // Precision Internal Oscillator Calibration                             
	__IO uint32_t  PIOSCSTAT;             // Precision Internal Oscillator Statistics                              
	__I  uint32_t  RESERVED10[2];
	__IO uint32_t  PLLFREQ0;              // PLL Frequency 0                                                       
	__IO uint32_t  PLLFREQ1;              // PLL Frequency 1                                                       
	__IO uint32_t  PLLSTAT;               // PLL Status                                                            
	__I  uint32_t  RESERVED11[7];
	__IO uint32_t  SLPPWRCFG;             // Sleep Power Configuration                                             
	__IO uint32_t  DSLPPWRCFG;            // Deep-Sleep Power Configuration                                        
	__IO uint32_t  DC9;                   // Device Capabilities 9                                                 
	__I  uint32_t  RESERVED12[3];
	__IO uint32_t  NVMSTAT;               // Non-Volatile Memory Information                                       
	__I  uint32_t  RESERVED13[4];
	__IO uint32_t  LDOSPCTL;              // LDO Sleep Power Control                                               
	__I  uint32_t  RESERVED14;
	__IO uint32_t  LDODPCTL;              // LDO Deep-Sleep Power Control                                          
	__I  uint32_t  RESERVED15[80];
	__IO uint32_t  PPWD;                  // Watchdog Timer Peripheral Present                                     
	__IO uint32_t  PPTIMER;               // 16/32-Bit General-Purpose Timer Peripheral Present                    
	__IO uint32_t  PPGPIO;                // General-Purpose Input/Output Peripheral Present                       
	__IO uint32_t  PPDMA;                 // Micro Direct Memory Access Peripheral Present                         
	__I  uint32_t  RESERVED16;
	__IO uint32_t  PPHIB;                 // Hibernation Peripheral Present                                        
	__IO uint32_t  PPUART;                // Universal Asynchronous Receiver/Transmitter Peripheral Present        
	__IO uint32_t  PPSSI;                 // Synchronous Serial Interface Peripheral Present                       
	__IO uint32_t  PPI2C;                 // Inter-Integrated Circuit Peripheral Present                           
	__I  uint32_t  RESERVED17;
	__IO uint32_t  PPUSB;                 // Universal Serial Bus Peripheral Present                               
	__I  uint32_t  RESERVED18[2];
	__IO uint32_t  PPCAN;                 // Controller Area Network Peripheral Present                            
	__IO uint32_t  PPADC;                 // Analog-to-Digital Converter Peripheral Present                        
	__IO uint32_t  PPACMP;                // Analog Comparator Peripheral Present                                  
	__IO uint32_t  PPPWM;                 // Pulse Width Modulator Peripheral Present                              
	__IO uint32_t  PPQEI;                 // Quadrature Encoder Interface Peripheral Present                       
	__I  uint32_t  RESERVED19[4];
	__IO uint32_t  PPEEPROM;              // EEPROM Peripheral Present                                             
	__IO uint32_t  PPWTIMER;              // 32/64-Bit Wide General-Purpose Timer Peripheral Present               
	__I  uint32_t  RESERVED20[104];
	__IO uint32_t  SRWD;                  // Watchdog Timer Software Reset                                         
	__IO uint32_t  SRTIMER;               // 16/32-Bit General-Purpose Timer Software Reset                        
	__IO uint32_t  SRGPIO;                // General-Purpose Input/Output Software Reset                           
	__IO uint32_t  SRDMA;                 // Micro Direct Memory Access Software Reset                             
	__I  uint32_t  RESERVED21;
	__IO uint32_t  SRHIB;                 // Hibernation Software Reset                                            
	__IO uint32_t  SRUART;                // Universal Asynchronous Receiver/Transmitter Software Reset            
	__IO uint32_t  SRSSI;                 // Synchronous Serial Interface Software Reset                           
	__IO uint32_t  SRI2C;                 // Inter-Integrated Circuit Software Reset                               
	__I  uint32_t  RESERVED22;
	__IO uint32_t  SRUSB;                 // Universal Serial Bus Software Reset                                   
	__I  uint32_t  RESERVED23[2];
	__IO uint32_t  SRCAN;                 // Controller Area Network Software Reset                                
	__IO uint32_t  SRADC;                 // Analog-to-Digital Converter Software Reset                            
	__IO uint32_t  SRACMP;                // Analog Comparator Software Reset                                      
	__IO uint32_t  SRPWM;                 // Pulse Width Modulator Software Reset                                  
	__IO uint32_t  SRQEI;                 // Quadrature Encoder Interface Software Reset                           
	__I  uint32_t  RESERVED24[4];
	__IO uint32_t  SREEPROM;              // EEPROM Software Reset                                                 
	__IO uint32_t  SRWTIMER;              // 32/64-Bit Wide General-Purpose Timer Software Reset                   
	__I  uint32_t  RESERVED25[40];
	__IO uint32_t  RCGCWD;                // Watchdog Timer Run Mode Clock Gating Control                          
	__IO uint32_t  RCGCTIMER;             // 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control         
	__IO uint32_t  RCGCGPIO;              // General-Purpose Input/Output Run Mode Clock Gating Control            
	__IO uint32_t  RCGCDMA;               // Micro Direct Memory Access Run Mode Clock Gating Control              
	__I  uint32_t  RESERVED26;
	__IO uint32_t  RCGCHIB;               // Hibernation Run Mode Clock Gating Control                             
	__IO uint32_t  RCGCUART;              // Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control
	__IO uint32_t  RCGCSSI;               // Synchronous Serial Interface Run Mode Clock Gating Control            
	__IO uint32_t  RCGCI2C;               // Inter-Integrated Circuit Run Mode Clock Gating Control                
	__I  uint32_t  RESERVED27;
	__IO uint32_t  RCGCUSB;               // Universal Serial Bus Run Mode Clock Gating Control                    
	__I  uint32_t  RESERVED28[2];
	__IO uint32_t  RCGCCAN;               // Controller Area Network Run Mode Clock Gating Control                 
	__IO uint32_t  RCGCADC;               // Analog-to-Digital Converter Run Mode Clock Gating Control             
	__IO uint32_t  RCGCACMP;              // Analog Comparator Run Mode Clock Gating Control                       
	__IO uint32_t  RCGCPWM;               // Pulse Width Modulator Run Mode Clock Gating Control                   
	__IO uint32_t  RCGCQEI;               // Quadrature Encoder Interface Run Mode Clock Gating Control            
	__I  uint32_t  RESERVED29[4];
	__IO uint32_t  RCGCEEPROM;            // EEPROM Run Mode Clock Gating Control                                  
	__IO uint32_t  RCGCWTIMER;            // 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control    
	__I  uint32_t  RESERVED30[40];
	__IO uint32_t  SCGCWD;                // Watchdog Timer Sleep Mode Clock Gating Control                        
	__IO uint32_t  SCGCTIMER;             // 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control       
	__IO uint32_t  SCGCGPIO;              // General-Purpose Input/Output Sleep Mode Clock Gating Control          
	__IO uint32_t  SCGCDMA;               // Micro Direct Memory Access Sleep Mode Clock Gating Control            
	__I  uint32_t  RESERVED31;
	__IO uint32_t  SCGCHIB;               // Hibernation Sleep Mode Clock Gating Control                           
	__IO uint32_t  SCGCUART;              // Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control
	__IO uint32_t  SCGCSSI;               // Synchronous Serial Interface Sleep Mode Clock Gating Control          
	__IO uint32_t  SCGCI2C;               // Inter-Integrated Circuit Sleep Mode Clock Gating Control              
	__I  uint32_t  RESERVED32;
	__IO uint32_t  SCGCUSB;               // Universal Serial Bus Sleep Mode Clock Gating Control                  
	__I  uint32_t  RESERVED33[2];
	__IO uint32_t  SCGCCAN;               // Controller Area Network Sleep Mode Clock Gating Control               
	__IO uint32_t  SCGCADC;               // Analog-to-Digital Converter Sleep Mode Clock Gating Control           
	__IO uint32_t  SCGCACMP;              // Analog Comparator Sleep Mode Clock Gating Control                     
	__IO uint32_t  SCGCPWM;               // Pulse Width Modulator Sleep Mode Clock Gating Control                 
	__IO uint32_t  SCGCQEI;               // Quadrature Encoder Interface Sleep Mode Clock Gating Control          
	__I  uint32_t  RESERVED34[4];
	__IO uint32_t  SCGCEEPROM;            // EEPROM Sleep Mode Clock Gating Control                                
	__IO uint32_t  SCGCWTIMER;            // 32/64-Bit Wide General-Purpose Timer Sleep Mode Clock Gating Control  
	__I  uint32_t  RESERVED35[40];
	__IO uint32_t  DCGCWD;                // Watchdog Timer Deep-Sleep Mode Clock Gating Control                   
	__IO uint32_t  DCGCTIMER;             // 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control 
	__IO uint32_t  DCGCGPIO;              // General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control     
	__IO uint32_t  DCGCDMA;               // Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control       
	__I  uint32_t  RESERVED36;
	__IO uint32_t  DCGCHIB;               // Hibernation Deep-Sleep Mode Clock Gating Control                      
	__IO uint32_t  DCGCUART;              // Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control 
	__IO uint32_t  DCGCSSI;               // Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control     
	__IO uint32_t  DCGCI2C;               // Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control         
	__I  uint32_t  RESERVED37;
	__IO uint32_t  DCGCUSB;               // Universal Serial Bus Deep-Sleep Mode Clock Gating Control             
	__I  uint32_t  RESERVED38[2];
	__IO uint32_t  DCGCCAN;               // Controller Area Network Deep-Sleep Mode Clock Gating Control          
	__IO uint32_t  DCGCADC;               // Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control      
	__IO uint32_t  DCGCACMP;              // Analog Comparator Deep-Sleep Mode Clock Gating Control                
	__IO uint32_t  DCGCPWM;               // Pulse Width Modulator Deep-Sleep Mode Clock Gating Control            
	__IO uint32_t  DCGCQEI;               // Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control     
	__I  uint32_t  RESERVED39[4];
	__IO uint32_t  DCGCEEPROM;            // EEPROM Deep-Sleep Mode Clock Gating Control                           
	__IO uint32_t  DCGCWTIMER;            // 32/64-Bit Wide General-Purpose Timer Deep-Sleep Mode Clock Gating Control 
	__I  uint32_t  RESERVED40[104];
	__IO uint32_t  PRWD;                  // Watchdog Timer Peripheral Ready                                       
	__IO uint32_t  PRTIMER;               // 16/32-Bit General-Purpose Timer Peripheral Ready                      
	__IO uint32_t  PRGPIO;                // General-Purpose Input/Output Peripheral Ready                         
	__IO uint32_t  PRDMA;                 // Micro Direct Memory Access Peripheral Ready                           
	__I  uint32_t  RESERVED41;
	__IO uint32_t  PRHIB;                 // Hibernation Peripheral Ready                                          
	__IO uint32_t  PRUART;                // Universal Asynchronous Receiver/Transmitter Peripheral Ready          
	__IO uint32_t  PRSSI;                 // Synchronous Serial Interface Peripheral Ready                         
	__IO uint32_t  PRI2C;                 // Inter-Integrated Circuit Peripheral Ready                             
	__I  uint32_t  RESERVED42;
	__IO uint32_t  PRUSB;                 // Universal Serial Bus Peripheral Ready                                 
	__I  uint32_t  RESERVED43[2];
	__IO uint32_t  PRCAN;                 // Controller Area Network Peripheral Ready                              
	__IO uint32_t  PRADC;                 // Analog-to-Digital Converter Peripheral Ready                          
	__IO uint32_t  PRACMP;                // Analog Comparator Peripheral Ready                                    
	__IO uint32_t  PRPWM;                 // Pulse Width Modulator Peripheral Ready                                
	__IO uint32_t  PRQEI;                 // Quadrature Encoder Interface Peripheral Ready                         
	__I  uint32_t  RESERVED44[4];
	__IO uint32_t  PREEPROM;              // EEPROM Peripheral Ready                                               
	__IO uint32_t  PRWTIMER;              // 32/64-Bit Wide General-Purpose Timer Peripheral Ready                 
} SYSCTL_Type;

#define SYSCTL_Base 0x400FE000
#define SYSCTL ((SYSCTL_Type*) SYSCTL_Base)

// RCGCUART register bit numbers
#define RCGCUART_UART0_Pos 0
#define RCGCUART_UART1_Pos 1
#define RCGCUART_UART2_Pos 2
#define RCGCUART_UART3_Pos 3
#define RCGCUART_UART4_Pos 4
#define RCGCUART_UART5_Pos 5
#define RCGCUART_UART6_Pos 6
#define RCGCUART_UART7_Pos 7

// RCGCGPIO register bit numbers
#define RCGCGPIO_PORTA_Pos 0
#define RCGCGPIO_PORTB_Pos 1
#define RCGCGPIO_PORTC_Pos 2
#define RCGCGPIO_PORTD_Pos 3
#define RCGCGPIO_PORTE_Pos 4
#define RCGCGPIO_PORTF_Pos 5

// RCC register bit numbers
#define ACG_Pos 27
#define SYSDIV_Pos 23
#define USESYSDIV_Pos 22
#define USEPWMDIV_Pos 20
#define PWMDIV_Pos 17
#define PWRDN_Pos 13
#define BYPASS_Pos 11
#define XTAL_Pos 6
#define OSCSRC_Pos 4
#define MOSCDIS_Pos 0

// RCC2 register bit numbers
#define USERCC2_Pos 31
#define DIV400_Pos 30
#define SYSDIV2_Pos 23
#define SYSDIV2LSB_Pos 22
#define USBPWRDN 14
#define PWRDN2_Pos 13
#define BYPASS2_Pos 11
#define OSCSRC2_Pos 4

// RIS register bit numbers
#define PLLRIS_Pos 6



/*-------------------------------------------------------------------------------
* NVIC registers
*------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t ISER[8];               	// Interrupt Set Enable Register 
	__I  uint32_t RESERVED0[24];
	__IO uint32_t ICER[8];               	// Interrupt Clear Enable Register 
	__I  uint32_t RESERVED1[24];
	__IO uint32_t ISPR[8];               	// Interrupt Set Pending Register 
	__I  uint32_t RESERVED2[24];
	__IO uint32_t ICPR[8];               	// Interrupt Clear Pending Register 
	__I  uint32_t RESERVED3[24];
	__IO uint32_t IABR[8];               	// Interrupt Active bit Register 
	__I  uint32_t RESERVED4[56];
	__IO uint8_t  IP[240];               	// Interrupt Priority Register (8Bit wide) 
	__I  uint32_t RESERVED5[644];
	__O  uint32_t STIR;                   	// Software Trigger Interrupt Register 
}  NVIC_Type;

#define NVIC_Base 0xE000E100
#define NVIC ((NVIC_Type*) NVIC_Base)



/*-------------------------------------------------------------------------------
* SysTick timer registers
*------------------------------------------------------------------------------*/
typedef struct
{
	__IO uint32_t CTRL;                  	// SysTick Control and Status Register
	__IO uint32_t RELOAD;                   // SysTick Reload Value Register
	__IO uint32_t CURRENT;					// SysTick Current Value Register
} SYSTICK_Type;

#define SYSTICK_Base 0xE000E010
#define SYSTICK ((SYSTICK_Type*) SYSTICK_Base)

// CTRL register bit numbers
#define COUNT_Pos 16
#define CLK_SRC_Pos 2
#define INTEN_Pos 1
#define ENABLE_Pos 0


/*-------------------------------------------------------------------------------
* GPIO registers
*------------------------------------------------------------------------------*/
typedef struct {                       // GPIOA Structure                                                       
	__I  uint32_t  RESERVED[255];
	__IO uint32_t  DATA;                 // GPIO Data                                                             
	__IO uint32_t  DIR;                  // GPIO Direction                                                        
	__IO uint32_t  IS;                   // GPIO Interrupt Sense                                                  
	__IO uint32_t  IBE;                  // GPIO Interrupt Both Edges                                             
	__IO uint32_t  IEV;                  // GPIO Interrupt Event                                                  
	__IO uint32_t  IM;                   // GPIO Interrupt Mask                                                   
	__IO uint32_t  RIS;                  // GPIO Raw Interrupt Status                                             
	__IO uint32_t  MIS;                  // GPIO Masked Interrupt Status                                          
	__O  uint32_t  ICR;                  // GPIO Interrupt Clear                                                  
	__IO uint32_t  AFSEL;                // GPIO Alternate Function Select                                        
	__I  uint32_t  RESERVED1[55];
	__IO uint32_t  DR2R;                 // GPIO 2-mA Drive Select                                                
	__IO uint32_t  DR4R;                 // GPIO 4-mA Drive Select                                                
	__IO uint32_t  DR8R;                 // GPIO 8-mA Drive Select                                                
	__IO uint32_t  ODR;                  // GPIO Open Drain Select                                                
	__IO uint32_t  PUR;                  // GPIO Pull-Up Select                                                   
	__IO uint32_t  PDR;                  // GPIO Pull-Down Select                                                 
	__IO uint32_t  SLR;                  // GPIO Slew Rate Control Select                                         
	__IO uint32_t  DEN;                  // GPIO Digital Enable                                                   
	__IO uint32_t  LOCK;                 // GPIO Lock                                                             
	__IO uint32_t  CR;                   // GPIO Commit                                                           
	__IO uint32_t  AMSEL;                // GPIO Analog Mode Select                                               
	__IO uint32_t  PCTL;                 // GPIO Port Control                                                     
	__IO uint32_t  ADCCTL;               // GPIO ADC Control                                                      
	__IO uint32_t  DMACTL;               // GPIO DMA Control                                                      
} GPIO_Type;

#define GPIOA_Base 0x40004000
#define GPIOB_Base 0x40005000
#define GPIOC_Base 0x40006000
#define GPIOD_Base 0x40007000
#define GPIOE_Base 0x40024000
#define GPIOF_Base 0x40025000
#define GPIOA ((GPIO_Type*) GPIOA_Base)
#define GPIOB ((GPIO_Type*) GPIOB_Base)
#define GPIOC ((GPIO_Type*) GPIOC_Base)
#define GPIOD ((GPIO_Type*) GPIOD_Base)
#define GPIOE ((GPIO_Type*) GPIOE_Base)
#define GPIOF ((GPIO_Type*) GPIOF_Base)

// GPIOPCTL register bit numbers
#define PCTL_PMC0_Pos 0
#define PCTL_PMC1_Pos 4
#define PCTL_PMC2_Pos 8
#define PCTL_PMC3_Pos 12
#define PCTL_PMC4_Pos 16
#define PCTL_PMC5_Pos 20
#define PCTL_PMC6_Pos 24
#define PCTL_PMC7_Pos 28

// PIN offsets
#define PIN0_Pos 0
#define PIN1_Pos 1
#define PIN2_Pos 2
#define PIN3_Pos 3
#define PIN4_Pos 4
#define PIN5_Pos 5
#define PIN6_Pos 6
#define PIN7_Pos 7

/*-------------------------------------------------------------------------------
* UART0 registers
*------------------------------------------------------------------------------*/
typedef struct {                     	// UART0 Structure                                                       
  __IO uint32_t  DR;                   	// UART Data                                                             
  __IO uint32_t  RSR;                	// UART Receive Status/Error Clear                                       
  __I  uint32_t  RESERVED[4];
  __IO uint32_t  FR;                   	// UART Flag                                                             
  __I  uint32_t  RESERVED1;
  __IO uint32_t  ILPR;                 	// UART IrDA Low-Power Register                                          
  __IO uint32_t  IBRD;                 	// UART Integer Baud-Rate Divisor                                        
  __IO uint32_t  FBRD;                 	// UART Fractional Baud-Rate Divisor                                     
  __IO uint32_t  LCRH;                 	// UART Line Control                                                     
  __IO uint32_t  CTL;                  	// UART Control                                                          
  __IO uint32_t  IFLS;                 	// UART Interrupt FIFO Level Select                                      
  __IO uint32_t  IM;                   	// UART Interrupt Mask                                                   
  __IO uint32_t  RIS;                  	// UART Raw Interrupt Status                                             
  __IO uint32_t  MIS;                  	// UART Masked Interrupt Status                                          
  __O  uint32_t  ICR;                  	// UART Interrupt Clear                                                  
  __IO uint32_t  DMACTL;               	// UART DMA Control                                                      
  __I  uint32_t  RESERVED2[22];
  __IO uint32_t  _9BITADDR;            	// UART 9-Bit Self Address                                               
  __IO uint32_t  _9BITAMASK;           	// UART 9-Bit Self Address Mask                                          
  __I  uint32_t  RESERVED3[965];
  __IO uint32_t  PP;                   	// UART Peripheral Properties                                            
  __I  uint32_t  RESERVED4;
  __IO uint32_t  CC;                   	// UART Clock Configuration                                              
} UART_Type;

#define UART0_Base 0x4000C000
#define UART0 ((UART_Type*) UART0_Base)

// CTL register bit numbers
#define CTL_CTSEN_Pos 15
#define CTL_RTSEN_Pos 14
#define CTL_RTS_Pos 11
#define CTL_RXE_Pos 9
#define CTL_TXE_Pos 8
#define CTL_LBE_Pos 7
#define CTL_HSE_Pos 5
#define CTL_EOT_Pos 4
#define CTL_SMART_Pos 3
#define CTL_SIRLP_Pos 2
#define CTL_SIREN_Pos 1
#define CTL_UARTEN_Pos 0

// LCRH register bit numbers
#define LCHR_SPS_Pos 7
#define LCHR_WLEN_Pos 5
#define LCHR_FEN_Pos 4
#define LCHR_STP2_Pos 3
#define LCHR_EPS_Pos 2
#define LCHR_PEN_Pos 1
#define LCHR_BRK_Pos 0

// FR register bit numbers
#define TXFE_Pos 7 				// Transmit FIFO empty
#define RXFF_Pos 6				// Receive FIFO full
#define TXFF_Pos 5 				// Transmit FIFO full
#define RXFE_Pos 4 				// Receive FIFO empty
#define BUSY_Pos 3 				// UART busy
#define CTS_Pos 0 				// Clear to send

#endif
