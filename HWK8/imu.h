#ifndef IMU_H
#define IMU_H

#define SLAVE_ADDR 0b1101011
#define SLAVE_ADDR_R 0b11010111
#define SLAVE_ADDR_W 0b11010110
#define WHO_AM_I 0x0F
#define CTRL1_XL 0x10
#define CTRL2_G 0x11
#define CTRL3_C 0x12
#define OUTZ_H_XL 0x2D
#define OUT_TEMP_L 0x20

void initIMU(void);
void I2C_read_multiple(unsigned char address, unsigned char reg, unsigned char * data, int length);

#endif

