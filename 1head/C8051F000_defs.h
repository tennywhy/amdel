//-----------------------------------------------------------------------------
// C8051F000_defs.h
//-----------------------------------------------------------------------------
// Copyright 2008 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// Register/bit definitions for the C8051F0xx family.
// **Important Note**: The si_toolchain.h header file should be included
// before including this header file.
//
// Target:         C8051F0xx
// Tool chain:     Keil
// Command Line:   None
//
// Release 2.2 - 20 AUG 2012 (TP)
//    -Added #define for _XPAGE to provide support for SDCC memory paging
//     (pdata)
// Release 2.1 - 21 July 2008 (ES)
//    -Corrected 16-bit address definition for ADC0GT
// Release 2.0
//    -28 FEB 2008
//    -Made compiler independant by AS
//    -Added 16-bit sfr definitions
//
//-----------------------------------------------------------------------------
// Header File Preprocessor Directive
//-----------------------------------------------------------------------------

#ifndef C8051F000_DEFS_H
#define C8051F000_DEFS_H

//-----------------------------------------------------------------------------
// Byte Registers
//-----------------------------------------------------------------------------

SI_SFR(P0, 0x80);         // PORT 0
SI_SFR(SP, 0x81);         // STACK POINTER
SI_SFR(DPL, 0x82);        // DATA POINTER - LOW BYTE
SI_SFR(DPH, 0x83);        // DATA POINTER - HIGH BYTE
SI_SFR(PCON, 0x87);       // POWER CONTROL
SI_SFR(TCON, 0x88);       // TIMER CONTROL
SI_SFR(TMOD, 0x89);       // TIMER MODE
SI_SFR(TL0, 0x8A);        // TIMER 0 - LOW BYTE
SI_SFR(TL1, 0x8B);        // TIMER 1 - LOW BYTE
SI_SFR(TH0, 0x8C);        // TIMER 0 - HIGH BYTE
SI_SFR(TH1, 0x8D);        // TIMER 1 - HIGH BYTE
SI_SFR(CKCON, 0x8E);      // CLOCK CONTROL
SI_SFR(PSCTL, 0x8F);      // PROGRAM STORE R/W CONTROL
SI_SFR(P1, 0x90);         // PORT 1
SI_SFR(TMR3CN, 0x91);     // TIMER 3 CONTROL
SI_SFR(TMR3RLL, 0x92);    // TIMER 3 RELOAD REGISTER - LOW BYTE
SI_SFR(TMR3RLH, 0x93);    // TIMER 3 RELOAD REGISTER - HIGH BYTE
SI_SFR(TMR3L, 0x94);      // TIMER 3 - LOW BYTE
SI_SFR(TMR3H, 0x95);      // TIMER 3 - HIGH BYTE
SI_SFR(SCON, 0x98);       // SERIAL PORT CONTROL
SI_SFR(SBUF, 0x99);       // SERIAL PORT BUFFER
SI_SFR(SPI0CFG, 0x9A);    // SERIAL PERIPHERAL INTERFACE 0 CONFIGURATION
SI_SFR(SPI0DAT, 0x9B);    // SERIAL PERIPHERAL INTERFACE 0 DATA
SI_SFR(SPI0CKR, 0x9D);    // SERIAL PERIPHERAL INTERFACE 0 CLOCK RATE CONTROL
SI_SFR(CPT0CN, 0x9E);     // COMPARATOR 0 CONTROL
SI_SFR(CPT1CN, 0x9F);     // COMPARATOR 1 CONTROL
SI_SFR(P2, 0xA0);         // PORT 2
SI_SFR(PRT0CF, 0xA4);     // PORT 0 CONFIGURATION
SI_SFR(PRT1CF, 0xA5);     // PORT 1 CONFIGURATION
SI_SFR(PRT2CF, 0xA6);     // PORT 2 CONFIGURATION
SI_SFR(PRT3CF, 0xA7);     // PORT 3 CONFIGURATION
SI_SFR(IE, 0xA8);         // INTERRUPT ENABLE
SI_SFR(PRT1IF, 0xAD);     // PORT 1 EXTERNAL INTERRUPT FLAGS
SI_SFR(EMI0CN, 0xAF);      // EXTERNAL MEMORY INTERFACE CONTROL
SI_SFR(P3, 0xB0);         // PORT 3
SI_SFR(OSCXCN, 0xB1);     // EXTERNAL OSCILLATOR CONTROL
SI_SFR(OSCICN, 0xB2);     // INTERNAL OSCILLATOR CONTROL
SI_SFR(FLSCL, 0xB6);      // FLASH MEMORY TIMING PRESCALER
SI_SFR(FLACL, 0xB7);      // FLASH ACESS LIMIT
SI_SFR(IP, 0xB8);         // INTERRUPT PRIORITY
SI_SFR(AMX0CF, 0xBA);     // ADC 0 MUX CONFIGURATION
SI_SFR(AMX0SL, 0xBB);     // ADC 0 MUX CHANNEL SELECTION
SI_SFR(ADC0CF, 0xBC);     // ADC 0 CONFIGURATION
SI_SFR(ADC0L, 0xBE);      // ADC 0 DATA - LOW BYTE
SI_SFR(ADC0H, 0xBF);      // ADC 0 DATA - HIGH BYTE
SI_SFR(SMB0CN, 0xC0);     // SMBUS 0 CONTROL
SI_SFR(SMB0STA, 0xC1);    // SMBUS 0 STATUS
SI_SFR(SMB0DAT, 0xC2);    // SMBUS 0 DATA
SI_SFR(SMB0ADR, 0xC3);    // SMBUS 0 SLAVE ADDRESS
SI_SFR(ADC0GTL, 0xC4);    // ADC 0 GREATER-THAN REGISTER - LOW BYTE
SI_SFR(ADC0GTH, 0xC5);    // ADC 0 GREATER-THAN REGISTER - HIGH BYTE
SI_SFR(ADC0LTL, 0xC6);    // ADC 0 LESS-THAN REGISTER - LOW BYTE
SI_SFR(ADC0LTH, 0xC7);    // ADC 0 LESS-THAN REGISTER - HIGH BYTE
SI_SFR(T2CON, 0xC8);      // TIMER 2 CONTROL
SI_SFR(RCAP2L, 0xCA);     // TIMER 2 CAPTURE REGISTER - LOW BYTE
SI_SFR(RCAP2H, 0xCB);     // TIMER 2 CAPTURE REGISTER - HIGH BYTE
SI_SFR(TL2, 0xCC);        // TIMER 2 - LOW BYTE
SI_SFR(TH2, 0xCD);        // TIMER 2 - HIGH BYTE
SI_SFR(SMB0CR, 0xCF);     // SMBUS 0 CLOCK RATE
SI_SFR(PSW, 0xD0);        // PROGRAM STATUS WORD
SI_SFR(REF0CN, 0xD1);     // VOLTAGE REFERENCE 0 CONTROL
SI_SFR(DAC0L, 0xD2);      // DAC 0 REGISTER - LOW BYTE
SI_SFR(DAC0H, 0xD3);      // DAC 0 REGISTER - HIGH BYTE
SI_SFR(DAC0CN, 0xD4);     // DAC 0 CONTROL
SI_SFR(DAC1L, 0xD5);      // DAC 1 REGISTER - LOW BYTE
SI_SFR(DAC1H, 0xD6);      // DAC 1 REGISTER - HIGH BYTE
SI_SFR(DAC1CN, 0xD7);     // DAC 1 CONTROL
SI_SFR(PCA0CN, 0xD8);     // PCA 0 COUNTER CONTROL
SI_SFR(PCA0MD, 0xD9);     // PCA 0 COUNTER MODE
SI_SFR(PCA0CPM0, 0xDA);   // CONTROL REGISTER FOR PCA 0 MODULE 0
SI_SFR(PCA0CPM1, 0xDB);   // CONTROL REGISTER FOR PCA 0 MODULE 1
SI_SFR(PCA0CPM2, 0xDC);   // CONTROL REGISTER FOR PCA 0 MODULE 2
SI_SFR(PCA0CPM3, 0xDD);   // CONTROL REGISTER FOR PCA 0 MODULE 3
SI_SFR(PCA0CPM4, 0xDE);   // CONTROL REGISTER FOR PCA 0 MODULE 4
SI_SFR(ACC, 0xE0);        // ACCUMULATOR
SI_SFR(XBR0, 0xE1);       // DIGITAL CROSSBAR CONFIGURATION REGISTER 0
SI_SFR(XBR1, 0xE2);       // DIGITAL CROSSBAR CONFIGURATION REGISTER 1
SI_SFR(XBR2, 0xE3);       // DIGITAL CROSSBAR CONFIGURATION REGISTER 2
SI_SFR(EIE1, 0xE6);       // EXTERNAL INTERRUPT ENABLE 1
SI_SFR(EIE2, 0xE7);       // EXTERNAL INTERRUPT ENABLE 2
SI_SFR(ADC0CN, 0xE8);     // ADC 0 CONTROL
SI_SFR(PCA0L, 0xE9);      // PCA 0 TIMER - LOW BYTE
SI_SFR(PCA0CPL0, 0xEA);   // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 0 - LOW BYTE
SI_SFR(PCA0CPL1, 0xEB);   // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 1 - LOW BYTE
SI_SFR(PCA0CPL2, 0xEC);   // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 2 - LOW BYTE
SI_SFR(PCA0CPL3, 0xED);   // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 3 - LOW BYTE
SI_SFR(PCA0CPL4, 0xEE);   // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 4 - LOW BYTE
SI_SFR(RSTSRC, 0xEF);     // RESET SOURCE
SI_SFR(B, 0xF0);          // B REGISTER
SI_SFR(EIP1, 0xF6);       // EXTERNAL INTERRUPT PRIORITY REGISTER 1
SI_SFR(EIP2, 0xF7);       // EXTERNAL INTERRUPT PRIORITY REGISTER 2
SI_SFR(SPI0CN, 0xF8);     // SERIAL PERIPHERAL INTERFACE 0 CONTROL
SI_SFR(PCA0H, 0xF9);       // PCA 0 TIMER - HIGH BYTE
SI_SFR(PCA0CPH0, 0xFA);    // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 0 - HIGH BYTE
SI_SFR(PCA0CPH1, 0xFB);    // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 1 - HIGH BYTE
SI_SFR(PCA0CPH2, 0xFC);    // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 2 - HIGH BYTE
SI_SFR(PCA0CPH3, 0xFD);    // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 3 - HIGH BYTE
SI_SFR(PCA0CPH4, 0xFE);    // CAPTURE/COMPARE REGISTER FOR PCA 0 MODULE 4 - HIGH BYTE
SI_SFR(WDTCN, 0xFF);       // WATCHDOG TIMER CONTROL

//-----------------------------------------------------------------------------
// 16-bit Register Definitions (might not be supported by all compilers)
//-----------------------------------------------------------------------------

SI_SFR16(DP, 0x82);                      // Data Pointer
SI_SFR16(TMR3RL, 0x92);                  // Timer 3 Reload
SI_SFR16(TMR3, 0x94);                    // Timer 3 Counter
SI_SFR16(ADC0, 0xBE);                    // ADC0 Data
SI_SFR16(ADC0GT, 0xC4);                  // ADC0 Greater-Than Compare
SI_SFR16(ADC0LT, 0xC6);                  // ADC0 Less-Than Compare
SI_SFR16(RCAP2, 0xCA);                   // Timer 2 Capture
SI_SFR16(T2, 0xCC);                      // Timer 2 Data
SI_SFR16(DAC0, 0xD2);                    // DAC 0 Data
SI_SFR16(DAC1, 0xD5);                    // DAC 1 Data

//-----------------------------------------------------------------------------
// Address Definitions for Bit-addressable Registers
//-----------------------------------------------------------------------------

#define SFR_SPI0CN     0xF8
#define SFR_B          0xF0
#define SFR_ADC0CN     0xE8
#define SFR_ACC        0xE0
#define SFR_PCA0CN     0xD8
#define SFR_PSW        0xD0
#define SFR_T2CON      0xC8
#define SFR_SMB0CN     0xC0
#define SFR_IP         0xB8
#define SFR_P3         0xB0
#define SFR_IE         0xA8
#define SFR_P2         0xA0
#define SFR_SCON       0x98
#define SFR_P1         0x90
#define SFR_TCON       0x88
#define SFR_P0         0x80

//-----------------------------------------------------------------------------
// Bit Definitions
//-----------------------------------------------------------------------------

//  TCON  0x88
SI_SBIT(TF1, SFR_TCON, 7);                 // TIMER 1 OVERFLOW FLAG
SI_SBIT(TR1, SFR_TCON, 6);                 // TIMER 1 ON/OFF CONTROL
SI_SBIT(TF0, SFR_TCON, 5);                 // TIMER 0 OVERFLOW FLAG
SI_SBIT(TR0, SFR_TCON, 4);                 // TIMER 0 ON/OFF CONTROL
SI_SBIT(IE1, SFR_TCON, 3);                 // EXT. INTERRUPT 1 EDGE FLAG
SI_SBIT(IT1, SFR_TCON, 2);                 // EXT. INTERRUPT 1 TYPE
SI_SBIT(IE0, SFR_TCON, 1);                 // EXT. INTERRUPT 0 EDGE FLAG
SI_SBIT(IT0, SFR_TCON, 0);                 // EXT. INTERRUPT 0 TYPE

//  SCON  0x98
SI_SBIT(SM0, SFR_SCON, 7);                 // SERIAL MODE CONTROL BIT 0
SI_SBIT(SM1, SFR_SCON, 6);                 // SERIAL MODE CONTROL BIT 1
SI_SBIT(SM2, SFR_SCON, 5);                 // MULTIPROCESSOR COMMUNICATION ENABLE
SI_SBIT(REN, SFR_SCON, 4);                 // RECEIVE ENABLE
SI_SBIT(TB8, SFR_SCON, 3);                 // TRANSMIT BIT 8
SI_SBIT(RB8, SFR_SCON, 2);                 // RECEIVE BIT 8
SI_SBIT(TI, SFR_SCON, 1);                  // TRANSMIT INTERRUPT FLAG
SI_SBIT(RI, SFR_SCON, 0);                  // RECEIVE INTERRUPT FLAG

//  IE  0xA8
SI_SBIT(EA, SFR_IE, 7);                    // GLOBAL INTERRUPT ENABLE
SI_SBIT(ET2, SFR_IE, 5);                   // TIMER 2 INTERRUPT ENABLE
SI_SBIT(ES, SFR_IE, 4);                    // SERIAL PORT INTERRUPT ENABLE
SI_SBIT(ET1, SFR_IE, 3);                   // TIMER 1 INTERRUPT ENABLE
SI_SBIT(EX1, SFR_IE, 2);                   // EXTERNAL INTERRUPT 1 ENABLE
SI_SBIT(ET0, SFR_IE, 1);                   // TIMER 0 INTERRUPT ENABLE
SI_SBIT(EX0, SFR_IE, 0);                   // EXTERNAL INTERRUPT 0 ENABLE

//  IP  0xB8
SI_SBIT(PT2, SFR_IP, 5);                   // TIMER 2 PRIORITY
SI_SBIT(PS, SFR_IP, 4);                    // SERIAL PORT PRIORITY
SI_SBIT(PT1, SFR_IP, 3);                   // TIMER 1 PRIORITY
SI_SBIT(PX1, SFR_IP, 2);                   // EXTERNAL INTERRUPT 1 PRIORITY
SI_SBIT(PT0, SFR_IP, 1);                   // TIMER 0 PRIORITY
SI_SBIT(PX0, SFR_IP, 0);                   // EXTERNAL INTERRUPT 0 PRIORITY

// SMB0CN 0xC0
SI_SBIT(BUSY, SFR_SMB0CN, 7);              // SMBUS 0 BUSY
SI_SBIT(ENSMB, SFR_SMB0CN, 6);             // SMBUS 0 ENABLE
SI_SBIT(STA, SFR_SMB0CN, 5);               // SMBUS 0 START FLAG
SI_SBIT(STO, SFR_SMB0CN, 4);               // SMBUS 0 STOP FLAG
SI_SBIT(SI, SFR_SMB0CN, 3);                // SMBUS 0 INTERRUPT PENDING FLAG
SI_SBIT(AA, SFR_SMB0CN, 2);                // SMBUS 0 ASSERT/ACKNOWLEDGE FLAG
SI_SBIT(SMBFTE, SFR_SMB0CN, 1);            // SMBUS 0 FREE TIMER ENABLE
SI_SBIT(SMBTOE, SFR_SMB0CN, 0);            // SMBUS 0 TIMEOUT ENABLE

//  T2CON  0xC8
SI_SBIT(TF2, SFR_T2CON, 7);                // TIMER 2 OVERFLOW FLAG
SI_SBIT(EXF2, SFR_T2CON, 6);               // EXTERNAL FLAG
SI_SBIT(RCLK, SFR_T2CON, 5);               // RECEIVE CLOCK FLAG
SI_SBIT(TCLK, SFR_T2CON, 4);               // TRANSMIT CLOCK FLAG
SI_SBIT(EXEN2, SFR_T2CON, 3);              // TIMER 2 EXTERNAL ENABLE FLAG
SI_SBIT(TR2, SFR_T2CON, 2);                // TIMER 2 ON/OFF CONTROL
SI_SBIT(CT2, SFR_T2CON, 1);                // TIMER OR COUNTER SELECT
SI_SBIT(CPRL2, SFR_T2CON, 0);              // CAPTURE OR RELOAD SELECT

//  PSW  0xD0
SI_SBIT(CY, SFR_PSW, 7);                   // CARRY FLAG
SI_SBIT(AC, SFR_PSW, 6);                   // AUXILIARY CARRY FLAG
SI_SBIT(F0, SFR_PSW, 5);                   // USER FLAG 0
SI_SBIT(RS1, SFR_PSW, 4);                  // REGISTER BANK SELECT 1
SI_SBIT(RS0, SFR_PSW, 3);                  // REGISTER BANK SELECT 0
SI_SBIT(OV, SFR_PSW, 2);                   // OVERFLOW FLAG
SI_SBIT(F1, SFR_PSW, 1);                   // USER FLAG 1
SI_SBIT(P, SFR_PSW, 0);                    // ACCUMULATOR PARITY FLAG

// PCA0CN 0xD8
SI_SBIT(CF, SFR_PCA0CN, 7);                // PCA 0 COUNTER OVERFLOW FLAG
SI_SBIT(CR, SFR_PCA0CN, 6);                // PCA 0 COUNTER RUN CONTROL BIT
SI_SBIT(CCF4, SFR_PCA0CN, 4);              // PCA 0 MODULE 4 INTERRUPT FLAG
SI_SBIT(CCF3, SFR_PCA0CN, 3);              // PCA 0 MODULE 3 INTERRUPT FLAG
SI_SBIT(CCF2, SFR_PCA0CN, 2);              // PCA 0 MODULE 2 INTERRUPT FLAG
SI_SBIT(CCF1, SFR_PCA0CN, 1);              // PCA 0 MODULE 1 INTERRUPT FLAG
SI_SBIT(CCF0, SFR_PCA0CN, 0);              // PCA 0 MODULE 0 INTERRUPT FLAG

// ADC0CN 0xE8
SI_SBIT(ADCEN, SFR_ADC0CN, 7);             // ADC 0 ENABLE
SI_SBIT(ADCTM, SFR_ADC0CN, 6);             // ADC 0 TRACK MODE
SI_SBIT(ADCINT, SFR_ADC0CN, 5);            // ADC 0 CONVERISION COMPLETE INTERRUPT FLAG
SI_SBIT(ADBUSY, SFR_ADC0CN, 4);            // ADC 0 BUSY FLAG
SI_SBIT(ADSTM1, SFR_ADC0CN, 3);            // ADC 0 START OF CONVERSION MODE BIT 1
SI_SBIT(ADSTM0, SFR_ADC0CN, 2);            // ADC 0 START OF CONVERSION MODE BIT 0
SI_SBIT(ADWINT, SFR_ADC0CN, 1);            // ADC 0 WINDOW COMPARE INTERRUPT FLAG
SI_SBIT(ADLJST, SFR_ADC0CN, 0);            // ADC 0 RIGHT JUSTIFY DATA BIT

// SPI0CN 0xF8
SI_SBIT(SPIF, SFR_SPI0CN, 7);              // SPI 0 INTERRUPT FLAG
SI_SBIT(WCOL, SFR_SPI0CN, 6);              // SPI 0 WRITE COLLISION FLAG
SI_SBIT(MODF, SFR_SPI0CN, 5);              // SPI 0 MODE FAULT FLAG
SI_SBIT(RXOVRN, SFR_SPI0CN, 4);            // SPI 0 RX OVERRUN FLAG
SI_SBIT(TXBSY, SFR_SPI0CN, 3);             // SPI 0 TX BUSY FLAG
SI_SBIT(SLVSEL, SFR_SPI0CN, 2);            // SPI 0 SLAVE SELECT
SI_SBIT(MSTEN, SFR_SPI0CN, 1);             // SPI 0 MASTER ENABLE
SI_SBIT(SPIEN, SFR_SPI0CN, 0);             // SPI 0 SPI ENABLE

//-----------------------------------------------------------------------------
// Interrupt Priorities
//-----------------------------------------------------------------------------

#define INTERRUPT_INT0                  0 // External Interrupt 0
#define INTERRUPT_TIMER0                1 // Timer0 Overflow
#define INTERRUPT_INT1                  2 // External Interrupt 1
#define INTERRUPT_TIMER1                3 // Timer1 Overflow
#define INTERRUPT_UART                  4 // Serial Port
#define INTERRUPT_TIMER2                5 // Timer2 Overflow
#define INTERRUPT_SPI                   6 // Serial Peripheral Interface
#define INTERRUPT_SMBUS                 7 // SMBus Interface
#define INTERRUPT_ADC0_WINDOW           8 // ADC0 Window Comparison
#define INTERRUPT_PCA0                  9 // PCA0 Peripheral
#define INTERRUPT_COMPARATOR0_FALLING  10 // Comparator 0 Falling edge
#define INTERRUPT_COMPARATOR0_RISING   11 // Comparator 0 Rising edge
#define INTERRUPT_COMPARATOR1_FALLING  12 // Comparator 1 Falling edge
#define INTERRUPT_COMPARATOR1_RISING   13 // Comparator 1 Rising edge
#define INTERRUPT_TIMER3               14 // Timer3 Overflow
#define INTERRUPT_ADC0_EOC             15 // ADC0 End Of Conversion
#define INTERRUPT_INT4                 16 // External Interrupt 4
#define INTERRUPT_INT5                 17 // External Interrupt 5
#define INTERRUPT_INT6                 18 // External Interrupt 6
#define INTERRUPT_INT7                 19 // External Interrupt 7
                                          // 20 Unused Interrupt Location
#define INTERRUPT_EXT_OSC_READY        21 // External Crystal Oscillator Ready

//-----------------------------------------------------------------------------
// SDCC PDATA External Memory Paging Support
//-----------------------------------------------------------------------------

#if defined SDCC

SI_SFR(_XPAGE, 0xAF); // Point to the EMI0CN register

#endif

//-----------------------------------------------------------------------------
// Header File PreProcessor Directive
//-----------------------------------------------------------------------------

#endif                                 // #define C8051F000_DEFS_H

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
