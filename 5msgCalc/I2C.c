#include "..\1head\0common.h"
#include "i2c.h"

/* Ports */
sbit WP  = P0 ^ 4;
sbit SCL  = P0 ^ 5;
sbit SDA  = P2 ^ 5;

/* ------------ DEFINES --------------- */
/* I2c read/write flags */
#define I2C_WRITE_FLAG 0x00 /* bit 0 of slave-addres byte */
#define I2C_READ_FLAG 0x01
#define I2C_ERROR_SDA_STUCK 0x1
#define I2C_ERROR_SCL_STUCK 0x2
#define I2C_ERROR_NO_ACK    0x4

/* bus logic levels */
#define LO  0
#define HI 1

typedef unsigned char UINT8;
typedef unsigned short UINT16;
enum {
	false = 0,
	true,
};


/* Delay constants */
#define _5US 8

/* Retry times on NACK */
#define NACK_RETRY_MAX 5

/* ------------ LOCAL DATA ------------ */
xdata UINT8 I2cStatus;
xdata UINT8 RxBit;
xdata UINT8 RxByte;

/* ---------- MODULE FUNCTIONS  ------- */
void Delay ( UINT8 Time );
UINT8 SetScl( UINT8 State );
UINT8 SetSda( UINT8 State );
void FloatSda( void );
UINT8 I2cStart();
UINT8 I2cStop();
UINT8 I2cTxBit( UINT8 BitVal );
UINT8 I2cRxBit( void );
UINT8 I2cTxByte( UINT8 TxData);
UINT8 I2cRxByte( UINT8 AckState );
void SetI2cWp(UINT8 enable);



/*---------------- Function Header -------------------------------------------

 FUNCTION InitI2c
 PURPOSE  Initialises I2c driver
 INPUT  None
 OUTPUT  I2c status byte indicating the idle-state of the bus

----------------------------------------------------------------------------*/
uchar InitI2c ( void )
{

 /* configure C8051F310 ports for I2C operation:
  SDA is connected to Port0, bit6
  SCL is connected to Port0, bit7
  both pins function in open-drain mode
 */
 I2cStatus = 0;  /* initialise driver status */

 SetI2cWp(0);

 /* set initial idle state for bus (SDA and SCL = 1) */
 return (uchar)( SetSda( HI ) || SetScl( HI ) );
}

/*---------------- Function Header -------------------------------------------

 FUNCTION SetI2cWp
 PURPOSE  enable or disable I2C write protect
----------------------------------------------------------------------------*/
void SetI2cWp(short enable)
{
	WP = enable;
}

/*---------------- Function Header -------------------------------------------

 FUNCTION Delay
 PURPOSE  Programme delay in the microsecond range -
    Called to meet I2C bus timing requirements

----------------------------------------------------------------------------*/
void Delay ( UINT8 Time )
{
 UINT8 i;

 for (i = 0; i < Time; i++);
}

/*---------------- Function Header -------------------------------------------

 FUNCTION SetScl
 PURPOSE  Sets I2C SCL line to the required level. Because the bus is a
    wire-OR configuration, it may take some time to establish a
    logic '1' due to slow risetime, clock stretching etc.
    An arbitrary timeout of 250us is allowed.
 INPUT  Required bus state
 OUTPUT  Flag indicating result: 1 = OK, 0 = bus line stuck.
 MODIFIES I2cStatus

----------------------------------------------------------------------------*/
UINT8 SetScl( UINT8 State )
{
/* sys clk = 24.576MHz */
 UINT16 Timeout = 250; /* approx 100KHz */

 SCL = State;
 while ( (SCL != State) && --Timeout);

 if ( Timeout )
  return true;
 else
 {
  I2cStatus |= I2C_ERROR_SCL_STUCK;
  return false;
 }
}

/*---------------- Function Header -------------------------------------------

 FUNCTION SetSda
 PURPOSE  Sets I2C SDA line to the required level. Because the bus is a
    wire-OR configuration, it may take some time to establish a
    logic '1' due to slow risetime, clock stretching etc.
    An arbitrary timeout of 250us is allowed.
 INPUT  Required bus state
 OUTPUT  Flag indicating result: 1 = OK, 0 = bus line stuck.
 MODIFIES I2cStatus

----------------------------------------------------------------------------*/
UINT8 SetSda( UINT8 State )
{
/* sys clk = 24.576MHz */
 UINT16 Timeout = 250; /* approx 100KHz */

 SDA = State;
 while ( (SDA != State) && --Timeout);

 if ( Timeout )
  return true;
 else
 {
  I2cStatus |= I2C_ERROR_SDA_STUCK;
  return false;
 }
}

/*---------------- Function Header -------------------------------------------

 FUNCTION FloatSda
 PURPOSE  Sets I2C SDA line to 'input mode'.
    Note: this function does not check the line is high because
    a slave may be legitimately driving SDA low.

----------------------------------------------------------------------------*/
void FloatSda( void )
{
 SDA = HI;
}

/*---------------- Function Header -------------------------------------------

 FUNCTION I2cStart
 PURPOSE  Applies an appropriately timed START condition to the I2c bus.
 OUTPUT  Flag indicating result: 1 = OK, 0 = bus line stuck.
 MODIFIES I2cStatus

----------------------------------------------------------------------------*/
UINT8 I2cStart()
{
 if ( !SDA )  /* ensure SDA is high */
 {
  if ( !SetSda(HI) )
   return false;
 }

 if ( !SCL )  /* ensure SCL is high */
 {
  if ( !SetScl(HI) )
   return false;
 }

 Delay( _5US );    /* Philips tSU:STA > 4.7us */

 SetSda(LO);
 Delay( _5US );    /* Philips tHD:SDA > 4us */

 return ( SetScl(LO) );
}

/*---------------- Function Header -------------------------------------------

 FUNCTION I2cStop
 PURPOSE  Applies an appropriately timed STOP condition to the I2c bus.
 OUTPUT  Flag indicating result: 1 = OK, 0 = bus line stuck.
 MODIFIES I2cStatus

----------------------------------------------------------------------------*/
UINT8 I2cStop()
{
 SetSda(LO); /* ensure SDA is low */

 if ( !SetScl(HI) )
  return false;
 Delay( _5US );    /* Philips tSU:STO > 4us */

 return ( SetSda(HI) );
}

/*---------------- Function Header -------------------------------------------

 FUNCTION I2cTxBit
 PURPOSE  Drives the specified data bit to the I2c bus.
 OUTPUT  Flag indicating result: 1 = OK, 0 = bus line stuck.
 MODIFIES I2cStatus

----------------------------------------------------------------------------*/
UINT8 I2cTxBit( UINT8 BitVal )
{
 if ( !SetSda(BitVal) )
  return false;
 Delay( _5US );    /* Philips tLOW > 4.7us */

 if ( !SetScl(HI) )
  return false;
 Delay( _5US );    /* Philips tHIGH > 4us */

 return ( SetScl(LO) );
}

/*---------------- Function Header -------------------------------------------

 FUNCTION I2cRxBit
 PURPOSE  Receives a data bit from the I2c bus.
 OUTPUT  Flag indicating result: 1 = OK, 0 = bus line stuck.
    Data bit is saved to RxBit
 MODIFIES I2cStatus

----------------------------------------------------------------------------*/
UINT8 I2cRxBit( void )
{
 FloatSda(); /* float SDA - can't check state as slave maybe driving SDA */
 Delay( _5US );    /* Philips tLOW > 4.7us */

 if ( !SetScl(HI) )
  return false;
 Delay( _5US );    /* Philips tHIGH > 4us */
 RxBit = SDA;
 return ( SetScl(LO) );
}

/*---------------- Function Header -------------------------------------------

 FUNCTION I2cTxByte
 PURPOSE  Sequences transmission of a data byte to the I2c bus.
 OUTPUT  Flag indicating result: 1 = slave acknowledged, 0 = no ack/fail.
    Data bit is saved to RxBit
 MODIFIES I2cStatus: State of ACK bit and error flags

----------------------------------------------------------------------------*/
UINT8 I2cTxByte( UINT8 TxData)
{
 UINT8 i;
 UINT8 t = TxData;

 for (i= 0;i < 8;i++)
 {
  if ( !I2cTxBit( (t & 0x80) ? 1 : 0 ) )
   return false;
  t <<= 1;
 }

 if ( I2cRxBit() )
 {
  if (RxBit)
   I2cStatus |= I2C_ERROR_NO_ACK;
  return ( !RxBit ); /* returns '1' if ACK recieved */
 }
 else
  return false;

}

/*---------------- Function Header -------------------------------------------

 FUNCTION I2cTxByte
 PURPOSE  Sequences reception of a data byte from the I2c bus.
 INPUT  Flag indicating state of ACK bit to be sent to the slave
 OUTPUT  Flag indicating result: 1 = OK, 0 = fail.
    Data byte is saved to RxByte
 MODIFIES I2cStatus: State of error flags

----------------------------------------------------------------------------*/
UINT8 I2cRxByte( UINT8 AckState )
{
 UINT8 i;
 UINT8 r = 0;

 for (i= 0;i < 8;i++)
 {
  if ( !I2cRxBit() )
   return false;
  r <<= 1;
  r |= RxBit;
 }

 RxByte = r;

 return ( I2cTxBit ( AckState ) );

}

/*---------------- Function Header -------------------------------------------

 FUNCTION I2cWrite
 PURPOSE  Sequences a write-cycle to a slave device on the I2c bus.
    send START
    send slave-adddress + write flag (check ACK)
    send write pointer (check ACK)
    read data bytes (with NACK at last byte) (check all ACKs)
 INPUT  I2cAddress:    specifies slave device 7-bit address
    DeviceAddress: specifies address pointer within the device
    Data:          Pointer to write-data (byte) array
    ByteCount:     specifies number of bytes to write
 OUTPUT  I2cStatus byte indicating result of I2c cycle.
 MODIFIES I2cStatus:     all flags

----------------------------------------------------------------------------*/
UINT8 I2cWrite( UINT8 I2cAddress, UINT8 DeviceAddress, UINT8 *Data, UINT8 ByteCount)
{
 UINT8 i;
 UINT8 *WriteDataPtr;

 i = 0;

 do { /* attempt to address device up to NACK_RETRY_MAX times */

  I2cStatus = 0;

  if ( I2cStart() )
  {
   if ( !I2cTxByte( (I2cAddress << 1) + I2C_WRITE_FLAG ) )
    I2cStop();
  }
 } while ( (I2cStatus != 0) && (++i < NACK_RETRY_MAX) );

 if ( i >= NACK_RETRY_MAX )
  return I2cStatus;


 if ( !I2cTxByte( DeviceAddress ) )
 {
  I2cStop();
  return I2cStatus;
 }

 WriteDataPtr = Data;
 for ( i = 0; i < ByteCount; i++)
 {
  if ( !I2cTxByte( *WriteDataPtr++ ) )
  {
   I2cStop();
   return I2cStatus;
  }
 }

 I2cStop();
 return I2cStatus;
}

/*---------------- Function Header -------------------------------------------

 FUNCTION I2cRead
 PURPOSE  Sequences a read-cycle to a slave device on the I2c bus:
    send START
    send slave-adddress + write flag (check ACK)
    send read pointer (check ACK)
    send re-START
    send slave-adddress + read flag (check ACK)
    read data bytes (with NACK at last byte)
 INPUT  I2cAddress:    specifies slave device 7-bit address
    DeviceAddress: specifies address pointer within the device
    Data:          Pointer to return-data (byte) array
    ByteCount:     specifies number of bytes to read
 OUTPUT  I2cStatus byte indicating result of I2c cycle.
 MODIFIES I2cStatus:     all flags

----------------------------------------------------------------------------*/
UINT8 I2cRead( UINT8 I2cAddress, UINT8 DeviceAddress, UINT8 *Data, UINT8 ByteCount)
{
 UINT8 i;
 UINT8 *ReadDataPtr;

 i = 0;
 do { /* attempt to address device up to NACK_RETRY_MAX times */

  I2cStatus = 0;

  if ( I2cStart() )
  {
   if ( !I2cTxByte( (I2cAddress << 1) + I2C_WRITE_FLAG ) )
    I2cStop();
  }
 } while ( (I2cStatus != 0) && (++i < NACK_RETRY_MAX) );

 if ( i >= NACK_RETRY_MAX )
  return I2cStatus;


 if ( !I2cTxByte( DeviceAddress ) )
 {
  I2cStop();
  return I2cStatus;
 }

 i = 0;
 do { /* attempt to address device up to NACK_RETRY_MAX times */

  I2cStatus = 0;

  if ( I2cStart() )
  {
   if ( !I2cTxByte( (I2cAddress * 2) + I2C_READ_FLAG ) )
    I2cStop();
  }
 } while ( (I2cStatus != 0) && (++i < NACK_RETRY_MAX) );

 if ( i >= NACK_RETRY_MAX )
  return I2cStatus;


 ReadDataPtr = Data;
 for ( i = 0; i < ByteCount; i++)
 {
  if ( I2cRxByte( (i == (ByteCount - 1) ? 1 : 0 ) ) )
    *ReadDataPtr++ = RxByte;
  else
  {
   I2cStop();
   return I2cStatus;
  }
 }

 I2cStop();
 return I2cStatus;
}

/*---------------- Function Header -------------------------------------------

 FUNCTION FramWrite
 PURPOSE  Sequences a write-cycle to a slave device on the I2c bus:
    send START
    send slave-adddress + write flag (check ACK)
    send read pointer (check ACK)
    send re-START
    send slave-adddress + read flag (check ACK)
    read data bytes (with NACK at last byte)
 INPUT DeviceAddress: specifies address pointer within the device
    Data:          Pointer to return-data (byte) array
    ByteCount:     specifies number of bytes to read

----------------------------------------------------------------------------*/
void FramWrite(short offset, char *buf, short len)
{
	I2cWrite(0x50, offset, buf, len);
}

/*---------------- Function Header -------------------------------------------

 FUNCTION FramRead
 PURPOSE  Sequences a read-cycle to a slave device on the I2c bus:
    send START
    send slave-adddress + write flag (check ACK)
    send read pointer (check ACK)
    send re-START
    send slave-adddress + read flag (check ACK)
    read data bytes (with NACK at last byte)
 INPUT DeviceAddress: specifies address pointer within the device
    Data:          Pointer to return-data (byte) array
    ByteCount:     specifies number of bytes to read

----------------------------------------------------------------------------*/

void FramRead(short offset, char *buf, short len)
{
	I2cRead(0x50, offset, buf, len);
}

void FramTest(void)
{
#define FRAM_SIZE 0x100
	char buf[0x20];
	char out[0x20];
	char chip = 0x50;
	int i = 0;
	int j = 0;
	int len = sizeof(buf) / sizeof(buf[0]);

	for (j = 0; j < FRAM_SIZE / len; j++) {
		for (i = 0; i < len; i++)
			buf[i] = i + j * len;

		I2cWrite(chip, j * len, buf, len);
	}

	for (j = 0; j < FRAM_SIZE / len; j++) {
		for (i = 0; i < len; i++)
			out[i] = 0;

		I2cRead(chip, j * len, out, len);
		for (i = 0; i < len; i++) {
			printf("out[%d] 0x%x\n", (short)(i + j * len), (((short)out[i]) & 0x00ff));
		}
	}
}

