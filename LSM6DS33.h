#ifndef LSM6DS33_h
#define LSM6DS33_h

#include <stdint.h>
#include "I2CBus.h"

// register addresses

#define LSM6DS33_GYRO 0x22
#define LSM6DS33_XL 0x28

#define _LSM6DS33_REG_WHO_AM_I 0x0f
#define _LSM6DS33_VAL_WHO_AM_I 0x69
#define _LSM6DS33_REG_CTRL1_XL 0x10
#define _LSM6DS33_REG_CTRL2_G 0x11
#define _LIS3MDL_REG_WHO_AM_I 0x0f
#define _LIS3MDL_VAL_WHO_AM_I 0x3d
#define _LIS3MDL_REG_CTRL_REG1 0x20
#define _LIS3MDL_REG_CTRL_REG2 0x21
#define _LIS3MDL_REG_CTRL_REG3 0x22
#define _LIS3MDL_REG_OUT_X_L 0x28

class LSM6DS33
{
 public:
    int a[3];  // accelerometer readings
    int m[3];  // magnetometer readings

    LSM6DS33(const char * i2cDeviceName);

    void enable(void);

    void writeAccReg(uint8_t reg, uint8_t value);
    uint8_t readAccReg(uint8_t reg);
    void writeMagReg(uint8_t reg, uint8_t value);
    uint8_t readMagReg(uint8_t reg);

    void readAcc(void);
    void readMag(void);
    void read(void);

    enum regAddr
    {
      FUNC_CFG_ACCESS   = 0x01,

      FIFO_CTRL1        = 0x06,
      FIFO_CTRL2        = 0x07,
      FIFO_CTRL3        = 0x08,
      FIFO_CTRL4        = 0x09,
      FIFO_CTRL5        = 0x0A,
      ORIENT_CFG_G      = 0x0B,

      INT1_CTRL         = 0x0D,
      INT2_CTRL         = 0x0E,
      WHO_AM_I          = 0x0F,
      CTRL1_XL          = 0x10,
      CTRL2_G           = 0x11,
      CTRL3_C           = 0x12,
      CTRL4_C           = 0x13,
      CTRL5_C           = 0x14,
      CTRL6_C           = 0x15,
      CTRL7_G           = 0x16,
      CTRL8_XL          = 0x17,
      CTRL9_XL          = 0x18,
      CTRL10_C          = 0x19,

      WAKE_UP_SRC       = 0x1B,
      TAP_SRC           = 0x1C,
      D6D_SRC           = 0x1D,
      STATUS_REG        = 0x1E,

      OUT_TEMP_L        = 0x20,
      OUT_TEMP_H        = 0x21,
      OUTX_L_G          = 0x22,
      OUTX_H_G          = 0x23,
      OUTY_L_G          = 0x24,
      OUTY_H_G          = 0x25,
      OUTZ_L_G          = 0x26,
      OUTZ_H_G          = 0x27,
      OUTX_L_XL         = 0x28,
      OUTX_H_XL         = 0x29,
      OUTY_L_XL         = 0x2A,
      OUTY_H_XL         = 0x2B,
      OUTZ_L_XL         = 0x2C,
      OUTZ_H_XL         = 0x2D,

      FIFO_STATUS1      = 0x3A,
      FIFO_STATUS2      = 0x3B,
      FIFO_STATUS3      = 0x3C,
      FIFO_STATUS4      = 0x3D,
      FIFO_DATA_OUT_L   = 0x3E,
      FIFO_DATA_OUT_H   = 0x3F,
      TIMESTAMP0_REG    = 0x40,
      TIMESTAMP1_REG    = 0x41,
      TIMESTAMP2_REG    = 0x42,

      STEP_TIMESTAMP_L  = 0x49,
      STEP_TIMESTAMP_H  = 0x4A,
      STEP_COUNTER_L    = 0x4B,
      STEP_COUNTER_H    = 0x4C,

      FUNC_SRC          = 0x53,

      TAP_CFG           = 0x58,
      TAP_THS_6D        = 0x59,
      INT_DUR2          = 0x5A,
      WAKE_UP_THS       = 0x5B,
      WAKE_UP_DUR       = 0x5C,
      FREE_FALL         = 0x5D,
      MD1_CFG           = 0x5E,
      MD2_CFG           = 0x5F,
    };
private:
    I2CBus i2c_mag, i2c_acc;
    enum class Device {
        LSM6DS33
    } device;
};

#endif
