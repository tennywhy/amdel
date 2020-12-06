/**************---------------------------------------------------------------
// main.c
//---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "..\1head\0common.h"
#include "main.h"



//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F0xx
//-----------------------------------------------------------------------------

sfr16 RCAP2    = 0xCA;                 // Timer2 capture/reload
sfr16 TMR2     = 0xCC;                 // Timer2
//sbit LED = P1^6;	//LED on DK board
//sbit LED = P2^2;	//LED on DK board
//sbit LD6 = P1^6;	
sbit TKey = P1^7; //push buttom on DK board
sbit setKey = P3^3;
sbit rgtKey = P3^2;
sbit dwnKey = P3^1;
sbit esckey = P3^0;

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
uchar UART_Buffer[UART_BUFFERSIZE];
uchar UART_Buffer_Size = 0;
uchar UART_Input_First = 0;
uchar UART_Output_First = 0;
uchar TX_Ready =1;
static char Byte;
uchar keyVar;
uchar keyStu=0xff; 
uchar knumber  = 1;
uchar setKeyVal=0, rgtKeyVal=0, dwnKeyVal=0, escKeyVal=0, passwrdRead=0;
uchar setKeyValLast=0, rgtKeyValLast=0, dwnKeyValLast=0, escKeyValLast=0xff;
bit setKpressed = 0, rgtKpressed = 0, dwnKpressed = 0, escKpressed = 0;
uchar currentStatus = 0x00;
menu_disp_t menu_disp;
//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------



void main (void)
{

	unsigned char keyCheckNub = 0;
	unsigned char inputcharacter;
	unsigned short int port3Var = 0XF0;
	unsigned short int keyButton = 0XF0;
    EA = 0;
    WDTCN = 0xDE;                       // Disable watchdog timer
    WDTCN = 0xAD;
	menu_disp.top_menu_select_row = 1;
	menu_disp.sub_menu_select_row = 3;
	menu_disp.top_menu_disp_status = 0;
	menu_disp.sub_menu_disp_status = 0;
	menu_disp.menu_disp_flag = TRUE;
	menu_disp.pswd_enter_flag = FALSE;
	menu_disp.sub_menu_enter_flag = FALSE;
	menu_disp.sub_menu_disp_flag = FALSE;
	menu_disp.top_menu_disp_flag = FALSE;
	menu_disp.pswd_menu_disp_flag = FALSE;
 
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
	LCD_Clear();
	
	//读入参数 
	ParmReadIn();
	
//	Lcd_init();
 	//EA = 1;
 	//printf("init end \n");
   while (1)
   { 
   	LoopNum ++;
   	  TI = 1;		// Set transmit flag to 1
	// 闪烁 LED指示灯	  
	  if (0 == LoopNum % 2000)
		{
			LED = ~LED;
		}
	  
	 //检测按键，并记录按键值
	  if (0 == LoopNum % 2)
		{
			KeyHand();
			//printf("key exit\n");
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
	  //显示程序由按键驱动，按键有动作则更新显示
	  if (0 == LoopNum % 2000)	  	
		{
		//CheckBusy();
//			printf("skey %d %d\n" ,  (short) setKeyValLast, (short) setKeyVal);
//			printf("rkey %d %d\n" ,  (short) rgtKeyValLast, (short) rgtKeyVal);
//			printf("dkey %d %d\n" ,  (short) dwnKeyValLast, (short) dwnKeyVal);
//			printf("ekey %d %d\n" ,  (short) escKeyValLast, (short) escKeyVal);
		// 判断是否有键按下
		if ( setKeyValLast != setKeyVal )
			{ setKpressed = 1;}
		if ( rgtKeyValLast != rgtKeyVal )
			{ rgtKpressed = 1;}
		if ( dwnKeyValLast != dwnKeyVal )
			{ dwnKpressed = 1;}
		if ( escKeyValLast != escKeyVal )
			{ escKpressed = 1;}
			  
		
		if ( 
			(setKeyValLast != setKeyVal)||
			(rgtKeyValLast != rgtKeyVal)|| 
			(dwnKeyValLast != dwnKeyVal)||
			(escKeyValLast != escKeyVal) )
			{

				printf("GOE111\n");

				if (setKpressed) {
					uchar menu_disp_flg = menu_disp.menu_disp_flag;
					if (!menu_disp_flg && menu_disp.pswd_menu_disp_flag) {
						if (menu_disp.sub_menu_disp_flag && !menu_disp.pswd_enter_flag)
							menu_disp.sub_menu_disp_status++;
					}
					
					if (!menu_disp_flg && menu_disp.top_menu_disp_flag) {
						menu_disp.pswd_menu_disp_flag = TRUE;
					}
					
					if (menu_disp.menu_disp_flag) {
						menu_disp.menu_disp_flag = FALSE;
						menu_disp.top_menu_disp_flag = TRUE;
						menu_disp.sub_menu_disp_flag  = FALSE;
						menu_disp.pswd_menu_disp_flag = FALSE;
					}
				}

				if (dwnKpressed) {
					if (!menu_disp.menu_disp_flag
						&& menu_disp.top_menu_disp_flag
						&& !menu_disp.pswd_menu_disp_flag) {
						menu_disp.top_menu_disp_status++;
						menu_disp.top_menu_disp_status %= 3;
					}

					//获取输入参数密码
					if (menu_disp.pswd_menu_disp_flag) {
					
					} else if (menu_disp.sub_menu_disp_flag) {
						//获取子菜单的参数
					}
				}

				if (rgtKpressed) {
					//获取输入参数密码
					if (menu_disp.pswd_menu_disp_flag) {
					
					} else if (menu_disp.sub_menu_disp_flag) {
						//获取子菜单的参数
					}
				}
				
				if (escKpressed) 
				{
					extern uchar passwrd;
					if (!menu_disp.pswd_enter_flag || !menu_disp.sub_menu_enter_flag) {
						menu_disp.menu_disp_flag = TRUE;
						menu_disp.sub_menu_disp_flag = FALSE;
						menu_disp.pswd_menu_disp_flag = FALSE;
						menu_disp.top_menu_disp_status = 0;
						menu_disp.sub_menu_disp_status = 0;
						menu_disp.top_menu_select_row = 1;
						menu_disp.sub_menu_select_col = 0;
					}
				#if 0
					setKeyVal = 0; 
					rgtKeyVal = 0;
					dwnKeyVal = 0;
					passwrd = 0;
					escKeyVal = 0;
					currentStatus = 0; //显示开始/状态界面
					setKpressed = 0;
					rgtKpressed = 0;
					dwnKpressed = 0;
					escKpressed = 0;
				
					setKeyValLast = setKeyVal;
					rgtKeyValLast = rgtKeyVal;
					dwnKeyValLast = dwnKeyVal;
					escKeyValLast = escKeyVal;
				#endif
					printf("esc reset start\n");
				}
				
				LcdDisplay(&menu_disp);

			  setKeyValLast = setKeyVal;
			  rgtKeyValLast = rgtKeyVal;
			  dwnKeyValLast = dwnKeyVal;
			  escKeyValLast = escKeyVal;				

			}
	//处理完按键，
		setKpressed = 0;
		rgtKpressed = 0;
		dwnKpressed = 0;
		escKpressed = 0;		
		//CheckBusy();
		}
	  
	  //计算脉冲输入的计算结果
	  if (0 == LoopNum % 3300)
		{
		//printf("solve result \n");
	  
		}
	  
	  //DebugStop();
	  //parameters refresh
	  gInitTag++;
	  gInitTag = gInitTag%200;

		 

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
		if ((setKey == 1) && (knumber == 1)) { 
			//printf("keyNum %d \n",knumber);
			TKeyVar = 0;
			knumber++;
			keyVar = 0x00;}
		if ((rgtKey == 1) && (knumber == 2)) { 
			//printf("keyNum %d \n",knumber);
			TKeyVar = 0;
			knumber++;
			keyVar = 0x00;}
		if ((dwnKey == 1) && (knumber == 3)) { 
			//printf("keyNum %d \n",knumber);
			TKeyVar = 0;
			knumber++;
			keyVar = 0x00;}
		if ((esckey == 1) && (knumber == 4)) { 
			//printf("keyNum %d \n",knumber);

			knumber=1;
			keyVar = 0x00;}
		//knumber = 0;
		TKeyVar = 0;

}

void read_key(void)
{
	uchar p3L=0xff,i=0;
	//uchar setKeyVal=0, rgtKeyVal=0, dwnKeyVal=0, escKeyVal=0;
	//低4位对应4个按键上一状态，1未按，0按下
	//按键状态必须翻转一次才是有效的按键
	//uchar keyStu=0xff; 
	p3L=P3;
	for(i=0;i<4;i++)
		{
			delaym(1);
			if(!(p3L == P3))
				{
					p3L=0xff;
					break;
				}	
		}
	p3L &= 0x0f;  //读取按键状态
	//printf("%X \n", p3L);
	// 不允许同时按下两个按键 
	//keystu=xxxx set rgt dwn esc
	if(0x07 == p3L)
		{
			i=keyStu&0x08; //上一个状态未按
			if(0x08 == i)
				{
					setKeyVal++;
					keyStu = keyStu&0xf7;
					i=setKeyVal;
			 		printf( "set %d\n", (short) i);
				}
			//printf("set key invalid");
		}
	else if(0x0b == p3L)
		{
			i=keyStu&0x04; //上一个状态未按
			if(0x04 == i)
				{
					rgtKeyVal++;
					keyStu &= 0xfb;
					//rgtKeyVal++;
					i=rgtKeyVal;
			 		printf( "rgt %d\n", (short) i);
				}
		}
	else if(0x0d == p3L)
		{
			i=keyStu&0x02; //上一个状态未按
			if(0x02 == i)
				{
					dwnKeyVal++;
					keyStu &= 0xfd;
					//dwnKeyVal++;
					i=dwnKeyVal;
			 		printf( "dwn %d\n", (short) i);
				}
		}	
	else if(0x0e == p3L)
		{
			i=keyStu&0x01; //上一个状态未按
			if(0x01 == i)
				{
					escKeyVal++;
					keyStu &= 0xfe;
					escKeyVal != escKeyVal;
					i=escKeyVal;
			 		printf( "esc %d\n", (short) i);
				}
		}
	else if(!0xff == p3L)
		{ printf( "push one button\n"); }
	else { keyStu=0xff; 
			//printf("button reset \n");
		}
	//printf("goies111\n");
	
}

void KeyHand(void)
{
	//printf("enter key hand\n");
	read_key();
	//printf("end key hand\n");
}

void DebugStop (void)
{ 
	while(1);
}


//把保存的参数读入
void ParmReadIn(void)
{
	uchar i=0;
	for(i=0;i<25;i++)
		{
			parameterCurrent[i] = parameterSet[i][0];
			
		}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------