/**************---------------------------------------------------------------
// F00x_UART0_Interrupt.c
//-----------------------------------------------------------------------------
// Copyright 2006 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program demonstrates how to configure the C8051F000 to write to and read
// from the UART interface. The program reads a word using the UART1 interrupts
// and outputs that word to the screen, with all characters in uppercase
//
// How To Test:
//
// 1) Download code to a 'F00x device that is connected to a UART transceiver
// 2) Connect serial cable from the transceiver to a PC
// 3) On the PC, open HyperTerminal (or any other terminal program) and connect
//    to the COM port at <BAUDRATE> and 8-N-1
// 4) Download and execute code on an 'F00x target board.
//
//
// Target:         C8051F00x
// Tool chain:     Keil C51 7.50 / Keil EVAL C51
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (SM)
//    -6 JUN 2007
//
//---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <C8051F000.h>                 // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include "LCD_INIT.H"

//#include <STARTUP.A51>
void s_delay(int sec);
void ms_delay(int ms);
void print_key(void);
void read_key(unsigned char keyName);
void CheckBusy(void);
//void Lcd_init(void);
void LcdDisplay(void);
//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F0xx
//-----------------------------------------------------------------------------

sfr16 RCAP2    = 0xCA;                 // Timer2 capture/reload
sfr16 TMR2     = 0xCC;                 // Timer2
//sbit LED = P1^6;	//LED on DK board
//sbit LED = P2^2;	//LED on DK board
//sbit LD6 = P1^6;	
sbit TKey = P1^7; //push buttom on DK board
sbit AKey = P3^3;
sbit BKey = P3^2;
sbit CKey = P3^1;
sbit DKey = P3^0;

sbit FIN0 = P0^2; //digit pulse Input
//unsigned char keyVar1 = 0;

#if (0) 
	sbit rs  = P2^0;  //LCD_DI
	sbit rw  = P3^6; // 默认低，接地
	sbit e	 = P3^7;
	sbit cs1 = P2^2;
	sbit lcd_cs2 = P2^1;
	sbit rst = P2^3;	
#endif
	
#if (0) 
	sbit lcd_cs2 = P2^0;
	sbit rst = P2^1; 
	sbit rw  = P2^4; // 默认低，接地
	sbit lcd_en  = P2^6;
	sbit cs1 = P2^7;	
	sbit nBLEN = P3^6;
	sbit rs  = P3^7;  //LCD_DI	
#endif

unsigned long int LoopNum = 0;


//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define TRUE 1
#define FALSE 0
#define BAUDRATE    256000          //8500  Baud rate of UART in bps
#define ExOSC TRUE  //设置外部晶振
#define UlONGINT 4294967295

// SYSCLK = System clock frequency in Hz

//#define SYSCLK     22118400L         // SYSCLK in Hz
//#define SYSCLK       16000000L         // SYSCLK in Hz
#define SYSCLK       24576000L         // SYSCLK in Hz
//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void OSCILLATOR_Init(void);
void PORT_Init(void);
void UART0_Init(void);
void DebugStop(void);
void LCD_TEST(void);

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

#define UART_BUFFERSIZE 64
unsigned char UART_Buffer[UART_BUFFERSIZE];
unsigned char UART_Buffer_Size = 0;
unsigned char UART_Input_First = 0;
unsigned char UART_Output_First = 0;
unsigned char TX_Ready =1;
static char Byte;
unsigned char keyVar;
unsigned short int knumber  = 1;
//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void LCD_TEST(void) 
{
	unsigned int PORT1VAL;
	nBLEN = 0; //打开背光
	rst = 1;
	delaym(1);
	rst = 0;
	delaym(1);
	_nop_();
	rst = 1;
	delaym(1);
	ca();
	//cs1 = 1; lcd_cs2 = 0;
	rs  =  0;         //指令
	rw  =  1;
	DB  =  0xFF;      //输出0xff以便读取正确
	lcd_en   =  1;	
	PORT1VAL = DB;
	lcd_en	 =	0;
	
	//nca();
	_nop_();

	printf("lcd display DB= %x \n", PORT1VAL);
	//while((DB & 0x80));       //Status Read BUSY Bit7 = 1 
	//printf("lcd display 44 \n");
	//lcd_en   =  0;
	_nop_();
	
	printf("LCD end \n");	
	//DebugStop();
}




void main (void)
{

	unsigned char keyCheckNub = 0;
	unsigned char inputcharacter;
	unsigned short int port3Var = 0XF0;
	unsigned short int keyButton = 0XF0;
    EA = 0;
    WDTCN = 0xDE;                       // Disable watchdog timer
    WDTCN = 0xAD;
 
    OSCILLATOR_Init ();                 // Initialize oscillator
    PORT_Init ();                       // Initialize crossbar and GPIO
    UART0_Init ();                      // Initialize UART0
    //EA = 1;
    TI = 1;		// Set transmit flag to 1
 	// set up Crossbar and GPIO
 	XBR2 = 0x40;						// Enable crossbar and weak pull-ups
 	PRT1CF |= 0x40;						// enable P1.6 (LED) as a push-pull output
 	PRT2CF |= 0x0F;	
 	//CheckBusy ();
 	
 	Lcd_init();
	LCD_TEST();
 	//EA = 1;

	
 	printf("init end \n");
   while (1)
   { 
   	LoopNum ++;
   	  TI = 1;		// Set transmit flag to 1
	// 闪烁 LED指示灯	  
	  if (0 == LoopNum % 2000)
		{
		LED = ~LED;
		}
	  
	 //检测按键，并执行相对应的菜单功能 
	  if (0 == LoopNum % 400)
		{
		keyCheckNub ++;
		//printf("=== check key ===\n");
		port3Var |= P3;
		//port3Var = 0xAA;
		//printf("port3 is %X \n", port3Var);
		//printf("port2 is %X \n", P2);
		//read_key();
		if (2 == keyCheckNub)
			{
			//printf("port3 is %X \n", port3Var);
			
			port3Var |= 0xF0;
			keyButton = port3Var;
			keyCheckNub = 0;
			port3Var = 0;			
			}
		if (0XF7 == keyButton)
			{
			printf("button is set \n");
			keyButton = 0xF0;
			}	
		if (0XFB == keyButton)
			{
			printf("button is right \n");
			keyButton = 0xF0;
			}	
		if (0XFD == keyButton)
			{
			printf("button is down \n");
			keyButton = 0xF0;
			}	
		if (0XFE == keyButton)
			{
			printf("button is esc \n");
			keyButton = 0xF0;
			}	
		
		}
	  
	  //串口输入
	  if (0 == LoopNum % 1000)
		{
		if ((SCON & 0x02) == 0x02) // Check if transmit flag is set
			{
			//LED = ~LED;	 
			inputcharacter = 0x62;
			//SBUF = 'b';
			// printf ("this is good %s", inputcharacter);
			//printf("I AM A HERO %d \n", LoopNum);
	  
			//SCON = (SCON & 0xFD);
			}
	  
		//printf("I AM A HERO %d", LoopNum);
	  
		}
	  
	  //采集脉冲数
	  if (0 == LoopNum % 3100)
		{
		//printf("sample pulse \n");
	  
		}
	  
	  //更新LCD显示
	  if (0 == LoopNum % 2000)
	  //if (1)
		{
		nBLEN = 0; //打开背光
		CheckBusy();
		
		//printf("lcd display start main point \n");
		LcdDisplay ();
		//LCD_TEST();
	    printf("lcd display end main point\n");
		nBLEN = 1; //关背光
		CheckBusy();
		}
	  
	  //计算脉冲输入的计算结果
	  if (0 == LoopNum % 3300)
		{
		//printf("solve result \n");
	  
		}
	  
	  //DebugStop();
	 
		 

      // If the complete word has been entered via the hyperterminal followed by
      // carriage return
//      if((TX_Ready == 1) && (UART_Buffer_Size != 0) && (Byte == 13))
//      {
//         TX_Ready = 0;                  // Set the flag to zero
//         TI = 1;       // Set transmit flag to 1
//      }
   }
}

void s_delay(sec)
{
	unsigned int i,j;

	for (j = 0; j < sec*1000; j++)
	{
		for (i = 0; i < 256; i++); 
	} 
	
}


void ms_delay(ms)
{
	unsigned int i,j;

	for (j = 0; j < ms*1; j++)
	{
		for (i = 0; i < 256; i++); 
	}
	
}
//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// OSCILLATOR_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function initializes the system clock to use an external 22.1184MHz
// crystal.
//
//-----------------------------------------------------------------------------
void OSCILLATOR_Init(void)
{
   int i;                              // Software timer

 #ifdef ExOSC
//====================
   //OSCICN |= 0x80;                     // Enable the missing clock detector
   // Initialize external crystal oscillator to use 22.1184 MHz crystal
   OSCXCN = 0x67;                      // Enable external crystal osc.
   //OSCICN = 0x67;                      // Enable external crystal osc.
   for (i = 0; i < 256; i++);          // Wait at least 1 ms
   while ((OSCXCN & 0x80) == 0);           // Wait for crystal osc to settle
   OSCICN = 0x08;                     // Select external clock source
   //OSCICN &= ~0x04;                    // Disable the internal osc.
   CKCON = 0X10; //use T1 as systerm clock
#else
   OSCICN |= 0x80;                     // Enable the missing clock detector
   //OSCICN |= 0x86;                     // Enable 8Mhz internal osc
   // Initialize external crystal oscillator to use 22.1184 MHz crystal
	OSCICN |= 0x84;                     // Enable internal osc

	 for (i = 0; i < 256; i++);          // Wait at least 1 ms
	OSCICN &= 0xF7;                     // uses internal osc
	OSCICN |= 0x03;                     // select 16M internal osc
   OSCXCN = 0x00;                      // disable external crystal osc.
   //while (!(OSCXCN & 0x87));           // Wait for crystal osc to settle
#endif
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the crossbar and GPIO ports.
//
// Pinout:
//
// P0.0   digital   push-pull     UART TX
// P0.1   digital   open-drain    UART RX
//-----------------------------------------------------------------------------
void PORT_Init(void)
{
   XBR0     = 0x04;     // Enable UART0
   XBR1     = 0x02;		//0x00			
   XBR2     = 0x40;     // Enable crossbar and weak pull-up

   //PRT0CF |= 0x01;      // Set TX pin to push-pull
   //PRT1CF    = 0x40;
   ////PRT3CF    = 0x00;

// four key I/O on port3[3:0] open drain
	PRT1CF    = 0x00;
    PRT2CF    = 0xFF;
    PRT3CF    = 0xFF;
    //PRT3CF	  = 0x00;
}


//-----------------------------------------------------------------------------
// UART0_Init   Variable baud rate, Timer 2, 8-N-1
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure UART0 for operation at <baudrate> 8-N-1 using Timer2 as
// baud rate source.
//
//-----------------------------------------------------------------------------
void UART0_Init (void)
{
   CKCON = 0x20;        // Timer2 uses the system clock
   TMOD = 0x20;			//Mode 2: 8-bit counter/timer with auto-reload
   T2CON = 0x34;        // Timer2 used for TX and RX, enabled
   //RCAP2 = - ((long) (SYSCLK/BAUDRATE)/33);  //8M/9600/32 = 26
   RCAP2 = - ((long) (SYSCLK/BAUDRATE)/29);  //8M/9600/32 = 26
   //RCAP2 = BAUDRATE/16;  //8M/9600/32 = 26
   
   //RCAP2L = 0x60;    //FFCB C7
   //RCAP2H = 0xFF;
   TMR2 = RCAP2;
   TR2= 1;                             // Start Timer2

   SCON = 0x50;                        // 8-bit variable baud rate;
                                       // 9th bit ignored; RX enabled
                                       // clear all flags
   TX_Ready = 1;                       // Flag showing that UART can transmit
   //ES  = 1;
}

//-----------------------------------------------------------------------------
// UART1_Interrupt
//-----------------------------------------------------------------------------
//
// This routine is invoked whenever a character is entered or displayed on the
// Hyperterminal.
//
//-----------------------------------------------------------------------------

void UART0_Interrupt (void) interrupt 4
{
   //LED = ~LED;	  


   if ((SCON & 0x01) == 0x01)    //是否有收刿
   {
   
	
      // Check if a new word is being entered
      if( UART_Buffer_Size == 0)  {
         UART_Input_First = 0; } 

      SCON = (SCON & 0xFE);          //RI1 = 0 清接收标忿;
      //Byte = SBUF;                    // Read a character from Hyperterminal
      //Byte = 0xaa;

      if (UART_Buffer_Size < UART_BUFFERSIZE)
      {
         UART_Buffer[UART_Input_First] = Byte;  // Store character

         UART_Buffer_Size++;            // Update array's size

         UART_Input_First++;            // Update counter
      }
   }
 


  //TI = 1;
   //LED = ~LED; 

   if ((SCON & 0x02) == 0x02)         // Check if transmit flag is set
   {
        
      SCON = (SCON & 0xFD);
      if (UART_Buffer_Size != 1)        // If buffer not empty
      {
         // Check if a new word is being output
         if ( UART_Buffer_Size == UART_Input_First )  
         {
            UART_Output_First = 0;
         }

         // Store a character in the variable byte
         Byte = UART_Buffer[UART_Output_First];
		 
		 Byte = 0x62;

         if ((Byte >= 0x61) && (Byte <= 0x7A)) { // If lower case letter
            Byte -= 32; }

         SBUF = Byte;

         UART_Output_First++;           // Update counter
         UART_Buffer_Size--;            // Decrease array size
      }
      else
      {
         UART_Buffer_Size = 0;           // Set the array size to 0
         TX_Ready = 1;                   // Indicate transmission complete
      }
   }
}

void UART0_tx (void) 
{

   if ((SCON & 0x01) == 0x01)
   {
   
	  //LED = ~LED;	 
      // Check if a new word is being entered
      if( UART_Buffer_Size == 0)  {
         UART_Input_First = 0; } 

      SCON = (SCON & 0xFE);          //RI1 = 0;
      //Byte = SBUF;                    // Read a character from Hyperterminal
      //Byte = 0xaa;

      if (UART_Buffer_Size < UART_BUFFERSIZE)
      {
         UART_Buffer[UART_Input_First] = Byte;  // Store character

         UART_Buffer_Size++;            // Update array's size

         UART_Input_First++;            // Update counter
      }
   }
   
  if (UART_Buffer_Size < UART_BUFFERSIZE)
  {
	 UART_Buffer[UART_Input_First] = 'c';	// Store character
  
	 UART_Buffer_Size++;			// Update array's size
  
	 UART_Input_First++;			// Update counter
  }


  //TI = 1;
   //LED = ~LED; 

   if ((SCON & 0x02) == 0x02)         // Check if transmit flag is set
   {
        
      SCON = (SCON & 0xFD);
      if (UART_Buffer_Size != 1)        // If buffer not empty
      {


         // Check if a new word is being output
         if ( UART_Buffer_Size == UART_Input_First )  
         {
            UART_Output_First = 0;
         }

         // Store a character in the variable byte
         Byte = UART_Buffer[UART_Output_First];
		 
		 Byte = 0x62;

         if ((Byte >= 0x61) && (Byte <= 0x7A)) { // If lower case letter
            Byte -= 32; }

         SBUF = Byte;

         UART_Output_First++;           // Update counter
         UART_Buffer_Size--;            // Decrease array size
      }
      else
      {
         UART_Buffer_Size = 0;           // Set the array size to 0
         TX_Ready = 1;                   // Indicate transmission complete
      }
   }
}


void print_key (void)
{
		unsigned char TKeyVar = 0;
		if (keyVar == 0x01) {
			//knumber =1;
			TKeyVar =1;
			keyVar = 0x00;
			}
		TKeyVar = TKey;
		//test the key
		//printf("\n ===test key start ==== \n");
		if ((AKey == 1) && (knumber == 1)) { 
			printf("keyNum %d \n",knumber);
			TKeyVar = 0;
			knumber++;
			keyVar = 0x00;}
		if ((BKey == 1) && (knumber == 2)) { 
			printf("keyNum %d \n",knumber);
			TKeyVar = 0;
			knumber++;
			keyVar = 0x00;}
		if ((CKey == 1) && (knumber == 3)) { 
			printf("keyNum %d \n",knumber);
			TKeyVar = 0;
			knumber++;
			keyVar = 0x00;}
		if ((DKey == 1) && (knumber == 4)) { 
			printf("keyNum %d \n",knumber);

			knumber=1;
			keyVar = 0x00;}
		//knumber = 0;
		TKeyVar = 0;

}

void read_key (unsigned char keyName)
{
if (keyName == 1) {
	ms_delay(50);
	if (keyName == 1) {
		ms_delay(80);
		if (keyName == 1) {
			keyVar = 0x01;
			printf("buttom is pushed down \n");
		}
	}	
}

}

void DebugStop (void)
{ 
	while(1);
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------