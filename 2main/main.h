#ifndef _main_H_
#define _main_H_

#include "..\3display\display.H"
	//#include <C8051F000.h>				 // SFR declarations
	//#include <stdio.h>
	//#include <intrins.h>
	//#include "..\3display\LCD_INIT.H"
	//#include <STARTUP.A51>


	extern uint parameterCurrent[30];
	extern uint parameterCurrentTemp[30];

	extern uint code parameterSet[25][4];
	extern uchar gInitTag;
	extern uchar currentStatus;
	

	void s_delay(int sec);
	void ms_delay(int ms);
	void print_key(void);
	void read_key(void);
	void CheckBusy(void);
	void Lcd_init(void);
	void LcdDisplay(menu_disp_t *disp);
	void LCD_TEST(void);
	void KeyHand(void);
	void ParmReadIn(void);

	

#endif



































	
	
	
