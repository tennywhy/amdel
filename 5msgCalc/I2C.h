#ifndef __I2C_H__
#define __I2C_H__

/*---------------- Function Header -------------------------------------------

 FUNCTION InitI2c
 PURPOSE  Initialises I2c driver
 INPUT  None
 OUTPUT  I2c status byte indicating the idle-state of the bus

----------------------------------------------------------------------------*/
uchar InitI2c(void);

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
void FramWrite(short offset, char *buf, short len);

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
void FramRead(short offset, char *buf, short len);

void FramTest(void);


#endif /* __I2C_H__ */
