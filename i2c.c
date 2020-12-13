#include "si_toolchain.h"
#include "C8051F000_defs.h"

// Peripheral specific initialization functions,
// Called from the Init_Device() function
void SMBus_Init()
{
    SMB0CN    = 0x43;
    SMB0CR    = 0xF8;
}

void Port_IO_Init()
{
    // P0.0  -  SDA (SMBUS), Open-Drain  
    // P0.1  -  SCL (SMBUS), Open-Drain  
    // P0.2  -  Unassigned,  Open-Drain  
    // P0.3  -  Unassigned,  Open-Drain  
    // P0.4  -  Unassigned,  Open-Drain  
    // P0.5  -  Unassigned,  Open-Drain  
    // P0.6  -  Unassigned,  Open-Drain  
    // P0.7  -  Unassigned,  Open-Drain  

    // P1.0  -  Unassigned,  Open-Drain  
    // P1.1  -  Unassigned,  Open-Drain  
    // P1.2  -  Unassigned,  Open-Drain  
    // P1.3  -  Unassigned,  Open-Drain  
    // P1.4  -  Unassigned,  Open-Drain  
    // P1.5  -  Unassigned,  Open-Drain  
    // P1.6  -  Unassigned,  Open-Drain  
    // P1.7  -  Unassigned,  Open-Drain  

    // P2.0  -  Unassigned,  Open-Drain  
    // P2.1  -  Unassigned,  Open-Drain  
    // P2.2  -  Unassigned,  Open-Drain  
    // P2.3  -  Unassigned,  Open-Drain  
    // P2.4  -  Unassigned,  Open-Drain  
    // P2.5  -  Unassigned,  Open-Drain  
    // P2.6  -  Unassigned,  Open-Drain  
    // P2.7  -  Unassigned,  Open-Drain  

    XBR0      = 0x00;
    XBR2      = 0x00;
}


