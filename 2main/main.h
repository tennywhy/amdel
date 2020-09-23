#ifndef _main_H_
#define _main_H_

#include "..\3display\display.H"
	//#include <C8051F000.h>				 // SFR declarations
	//#include <stdio.h>
	//#include <intrins.h>
	//#include "..\3display\LCD_INIT.H"
	//#include <STARTUP.A51>


	void s_delay(int sec);
	void ms_delay(int ms);
	void print_key(void);
	void read_key(unsigned char keyName);
	void CheckBusy(void);
	void Lcd_init(void);
	void LcdDisplay(void);
	void LCD_TEST(void);

#endif



































	
	
	
