#include "LSM6DS33.h"

/*
Relevant Pololu products:
#2738  LSM6DS33 + LIS3MDL Carrier (v5)
*/

// LSM6DS33 addresses:
#define DS33_SA0_HIGH_ADDRESS              0x6a
#define DS33_SA0_LOW_ADDRESS               0x6b

#define DS33_WHO_ID    0x69

LSM6DS33::LSM6DS33(const char * i2cDeviceName) :
  i2c_mag(i2cDeviceName), i2c_acc(i2cDeviceName)
{
    I2CBus i2c(i2cDeviceName);
    bool sa0;
    if (i2c.tryReadByte(DS33_SA0_HIGH_ADDRESS, _LSM6DS33_REG_WHO_AM_I) == DS33_WHO_ID)
    {
        // Detected LSM6DS33 with SA0 high.
	// printf("LSM6DS33 SA0 high\n");
        device = Device::LSM6DS33;
        sa0 = true;
    }
    else if (i2c.tryReadByte(DS33_SA0_LOW_ADDRESS, _LSM6DS33_REG_WHO_AM_I) == DS33_WHO_ID)
    {
        // device responds to address 0011110 with D ID; it's a D with SA0 low
        // printf("LSM6DS33 SA0 low\n");
	device = Device::LSM6DS33;
        sa0 = false;
    }
    else
    {
        throw std::runtime_error("Could not detect accelerometer.");
    }

    // Set the I2C addresses.
    
    uint8_t address = sa0 ? DS33_SA0_HIGH_ADDRESS : DS33_SA0_LOW_ADDRESS;
    i2c_acc.addressSet(address);
    i2c_mag.addressSet(address);

    // Make sure we can actually read an accelerometer control register.
    // (This throws an exception if there is a problem.)
    readAccReg(_LSM6DS33_REG_CTRL1_XL);
}

uint8_t LSM6DS33::readMagReg(uint8_t reg)
{
    return i2c_mag.readByte(reg);
}

uint8_t LSM6DS33::readAccReg(uint8_t reg)
{
    return i2c_acc.readByte(reg);
}

void LSM6DS33::writeMagReg(uint8_t reg, uint8_t value)
{
    i2c_mag.writeByte(reg, value);
}

void LSM6DS33::writeAccReg(uint8_t reg, uint8_t value)
{
    i2c_acc.writeByte(reg, value);
}

// Turns on the LSM303's accelerometer and magnetometers and places them in normal
// mode.
void LSM6DS33::enable(void)
{
    if (device == Device::LSM6DS33)
    {
    // Accelerometer

    // 0x80 = 0b10000000
    // ODR = 1000 (1.66 kHz (high performance)); FS_XL = 00 (+/-2 g full scale)
    writeAccReg(_LSM6DS33_REG_CTRL1_XL, 0b01111000);

    // Gyro

    // 0x80 = 0b010000000
    // ODR = 1000 (1.66 kHz (high performance)); FS_XL = 00 (245 dps)
    writeAccReg(CTRL2_G, 0b01111000);

    }
}

void LSM6DS33::readAcc(void)
{
    uint8_t block[6];
    i2c_acc.readBlock(LSM6DS33_XL, sizeof(block), block);
    a[0] = (int16_t)(block[0] | block[1] << 8);
    a[1] = (int16_t)(block[2] | block[3] << 8);
    a[2] = (int16_t)(block[4] | block[5] << 8);
}

void LSM6DS33::readMag(void)
{
    uint8_t block[6];

    if (device == Device::LSM6DS33)
    {
        i2c_mag.readBlock(LSM6DS33_GYRO, sizeof(block), block);
        m[0] = (int16_t)(block[0] | block[1] << 8);
        m[1] = (int16_t)(block[2] | block[3] << 8);
        m[2] = (int16_t)(block[4] | block[5] << 8);
    }
}

void LSM6DS33::read(void)
{
    readAcc();
    readMag();
}
