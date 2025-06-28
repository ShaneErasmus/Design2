//********************************************************************
//*                          Micro Mouse                             *
//*                          IMU Library                             *
//*==================================================================*
//* @author:    Jesse Jabez Arendse                                  *
//* @date:      24-10-2023                                           *
//*==================================================================*

#include "main.h"
#include "IMU.h"
#include <math.h>

extern I2C_HandleTypeDef hi2c2;

uint8_t checking = 0;

float accel_x = 0;
float accel_y = 0;
float accel_z = 0;
float gyro_x  = 0;
float gyro_y  = 0;
float gyro_z  = 0;

uint16_t accelMem[3];
uint16_t gyroMem[3];

short IMUCounter = 0;

float IMU_Accel[3];
float IMU_Gyro[3];
float IMU_Temp;
uint8_t checkIMU;
float accelDivisor = 16384.0f;
float gyroDivisor = 131.0f;

int16_t signNumber16(uint16_t unsignedValue){
	int16_t signedValue;

	if (unsignedValue <= INT16_MAX) {
        signedValue = (int16_t)unsignedValue; // No change needed, it fits in the signed range.
    } else {
        signedValue = -((int16_t)(UINT16_MAX - unsignedValue + 1));
    }

	return signedValue;
}

static void WriteMem(uint8_t devAddress, uint8_t RegisterAddress, uint16_t Value)
{
	uint8_t addr[2];
	addr[0] = (Value >> 8) & 0xff;  // upper byte
	addr[1] = (Value >> 0) & 0xff; // lower byte
	HAL_I2C_Mem_Write(&hi2c2, (devAddress<<1)+0, RegisterAddress, 1, (uint8_t*)addr, 2, HAL_MAX_DELAY);
}

static uint16_t ReadMem(uint8_t devAddress, uint8_t RegisterAddress)
{
	uint8_t Value[2];

	HAL_I2C_Mem_Read(&hi2c2, (devAddress<<1)+1, RegisterAddress, 1, &Value, 2, HAL_MAX_DELAY);

	return ((Value[0] << 8) | Value[1]);
}

#ifdef IMU_MPU6050

void refreshIMUValues() {  
    IMU_Accel[0] = signNumber16(ReadMem(IMU_MPU6050_I2C_ADDRESS, IMU_MPU6050_ACCEL_XOUT_H)) * IMU_GRAVITATIONAL_ACCELERATION / accelDivisor;  // Convert to m/s^2
    IMU_Accel[1] = signNumber16(ReadMem(IMU_MPU6050_I2C_ADDRESS, IMU_MPU6050_ACCEL_YOUT_H)) * IMU_GRAVITATIONAL_ACCELERATION / accelDivisor; 
    IMU_Accel[2] = signNumber16(ReadMem(IMU_MPU6050_I2C_ADDRESS, IMU_MPU6050_ACCEL_ZOUT_H)) * IMU_GRAVITATIONAL_ACCELERATION / accelDivisor; 

    IMU_Gyro[0] = signNumber16(ReadMem(IMU_MPU6050_I2C_ADDRESS, IMU_MPU6050_GYRO_XOUT_H)) * IMU_DPS2RAD / gyroDivisor;  // Convert to rad/s
    IMU_Gyro[1] = signNumber16(ReadMem(IMU_MPU6050_I2C_ADDRESS, IMU_MPU6050_GYRO_YOUT_H)) * IMU_DPS2RAD / gyroDivisor;
    IMU_Gyro[2] = signNumber16(ReadMem(IMU_MPU6050_I2C_ADDRESS, IMU_MPU6050_GYRO_ZOUT_H)) * IMU_DPS2RAD / gyroDivisor;

    IMU_Temp = ((int16_t)ReadMem(IMU_MPU6050_I2C_ADDRESS, IMU_MPU6050_TEMP_OUT_H)) / 340.0f + 36.53f;  // Convert to °C

    #ifdef IMU_DYNAMIC_FSR
    calibrateIMU();
    #endif
}

void initIMU() {
    uint8_t wake = 0;
    HAL_I2C_Mem_Write(&hi2c2, (IMU_MPU6050_I2C_ADDRESS << 1) + 0, IMU_MPU6050_PWR_MGMT_1, 1, &wake, 1, HAL_MAX_DELAY);
    uint8_t sampleRate = 0x07; // Set sample rate to 1 kHz
    HAL_I2C_Mem_Write(&hi2c2, (IMU_MPU6050_I2C_ADDRESS << 1) + 0, IMU_MPU6050_SMPLRT_DIV, 1, &sampleRate, 1, HAL_MAX_DELAY);
    uint8_t accelConfig = IMU_MPU6050_ACCEL_FS_2; // Full range: ±2g
    HAL_I2C_Mem_Write(&hi2c2, (IMU_MPU6050_I2C_ADDRESS << 1) + 0, IMU_MPU6050_ACCEL_CONFIG, 1, &accelConfig, 1, HAL_MAX_DELAY);
    uint8_t gyroConfig = IMU_MPU6050_GYRO_FS_250; // Full range: ±250°/s
    HAL_I2C_Mem_Write(&hi2c2, (IMU_MPU6050_I2C_ADDRESS << 1) + 0, IMU_MPU6050_GYRO_CONFIG, 1, &gyroConfig, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Read(&hi2c2, (IMU_MPU6050_I2C_ADDRESS << 1) + 1, IMU_MPU6050_WHO_AM_I, 1, &checkIMU, 1, HAL_MAX_DELAY);
}

void calibrateIMU() {
    static uint8_t lastAccelConfig = IMU_MPU6050_ACCEL_FS_2; // Default ±2g
    static uint8_t lastGyroConfig = IMU_MPU6050_GYRO_FS_250; // Default ±250°/s

    uint8_t accelConfig = lastAccelConfig;
    uint8_t gyroConfig = lastGyroConfig;

    // Check each accelerometer axis
    float accelMaxMag = 0;
    for (int i = 0; i < 3; i++) {
        float absAccel = fabsf(IMU_Accel[i] / IMU_GRAVITATIONAL_ACCELERATION); // Convert m/s² to g
        accelMaxMag = (absAccel > accelMaxMag) ? absAccel : accelMaxMag;
    }


    accelConfig = IMU_MPU6050_ACCEL_FS_2;
    accelDivisor = 16384.0f;
    // Dynamic adjustment of accelerometer FSR
    if (accelMaxMag >= 1.75f && accelMaxMag < 3.75f) { // Near ±2g limit, switch to ±4g
        accelConfig = IMU_MPU6050_ACCEL_FS_4;
        accelDivisor = 8192.0f;
    } if (accelMaxMag >= 3.75f && accelMaxMag < 7.75f) { // Near ±4g limit, switch to ±8g
        accelConfig = IMU_MPU6050_ACCEL_FS_8;
        accelDivisor = 4096.0f;
    } if (accelMaxMag >= 7.75f) { // Near ±8g limit, switch to ±16g
        accelConfig = IMU_MPU6050_ACCEL_FS_16;
        accelDivisor = 2048.0f;
    }

    // Check each gyroscope axis
    float gyroMaxMag = 0;
    for (int i = 0; i < 3; i++) {
        float absGyro = fabsf(IMU_Gyro[i]); // Gyro is already in radians
        gyroMaxMag = (absGyro > gyroMaxMag) ? absGyro : gyroMaxMag;
    }

    // Dynamic adjustment of gyroscope FSR (values in radians/s)
    if (gyroMaxMag >= 4.3633f && gyroMaxMag < 8.7266f) { // Near ±250°/s limit, switch to ±500°/s
        gyroConfig = IMU_MPU6050_GYRO_FS_500;
        gyroDivisor = 65.5f;
    } else if (gyroMaxMag >= 8.7266f && gyroMaxMag < 17.4533f) { // Near ±500°/s limit, switch to ±1000°/s
        gyroConfig = IMU_MPU6050_GYRO_FS_1000;
        gyroDivisor = 32.8f;
    } else if (gyroMaxMag >= 17.4533f && gyroMaxMag < 34.9066f) { // Near ±1000°/s limit, switch to ±2000°/s
        gyroConfig = IMU_MPU6050_GYRO_FS_2000;
        gyroDivisor = 16.4f;
    } else { // Default to ±250°/s for maximum resolution
        gyroConfig = IMU_MPU6050_GYRO_FS_250;
        gyroDivisor = 131.0f;
    }

    // Apply new configurations if they changed
    if (lastAccelConfig != accelConfig) {
        HAL_I2C_Mem_Write(&hi2c2, (IMU_MPU6050_I2C_ADDRESS << 1) + 0, IMU_MPU6050_ACCEL_CONFIG, 1, &accelConfig, 1, HAL_MAX_DELAY);
        lastAccelConfig = accelConfig;
    }

    if (lastGyroConfig != gyroConfig) {
        HAL_I2C_Mem_Write(&hi2c2, (IMU_MPU6050_I2C_ADDRESS << 1) + 0, IMU_MPU6050_GYRO_CONFIG, 1, &gyroConfig, 1, HAL_MAX_DELAY);
        lastGyroConfig = gyroConfig;
    }

    // Update the divisor values globally
    accelDivisor = (accelConfig == IMU_MPU6050_ACCEL_FS_16) ? 2048.0f :
                   (accelConfig == IMU_MPU6050_ACCEL_FS_8) ? 4096.0f :
                   (accelConfig == IMU_MPU6050_ACCEL_FS_4) ? 8192.0f : 16384.0f;

    gyroDivisor = (gyroConfig == IMU_MPU6050_GYRO_FS_2000) ? 16.4f :
                  (gyroConfig == IMU_MPU6050_GYRO_FS_1000) ? 32.8f :
                  (gyroConfig == IMU_MPU6050_GYRO_FS_500) ? 65.5f : 131.0f;
}

#endif // IMU_MPU6050
#ifdef IMU_ICM42605

// Global variables for ICM42605
float _aRes, _gRes; // Resolution variables for accel and gyro

float getAres(uint8_t Ascale) {
  switch (Ascale)
  {
    // Possible accelerometer scales (and their register bit settings) are:
    // 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
    case AFS_2G:
      _aRes = 2.0f / 32768.0f;
      return _aRes;
      break;
    case AFS_4G:
      _aRes = 4.0f / 32768.0f;
      return _aRes;
      break;
    case AFS_8G:
      _aRes = 8.0f / 32768.0f;
      return _aRes;
      break;
    case AFS_16G:
      _aRes = 16.0f / 32768.0f;
      return _aRes;
      break;
    default:
      return 0;
  }
}

float getGres(uint8_t Gscale) {
  switch (Gscale)
  {
    case GFS_15_125DPS:
      _gRes = 15.125f / 32768.0f;
      return _gRes;
      break;
    case GFS_31_25DPS:
      _gRes = 31.25f / 32768.0f;
      return _gRes;
      break;
    case GFS_62_5DPS:
      _gRes = 62.5f / 32768.0f;
      return _gRes;
      break;
    case GFS_125DPS:
      _gRes = 125.0f / 32768.0f;
      return _gRes;
      break;
    case GFS_250DPS:
      _gRes = 250.0f / 32768.0f;
      return _gRes;
      break;
    case GFS_500DPS:
      _gRes = 500.0f / 32768.0f;
      return _gRes;
      break;
    case GFS_1000DPS:
      _gRes = 1000.0f / 32768.0f;
      return _gRes;
      break;
    case GFS_2000DPS:
      _gRes = 2000.0f / 32768.0f;
      return _gRes;
      break;
    default:
      return 0;
  }
}

static uint8_t readByte(uint8_t devAddress, uint8_t regAddress) {
  uint8_t data;
  HAL_I2C_Mem_Read(&hi2c2, (devAddress<<1)+1, regAddress, 1, &data, 1, HAL_MAX_DELAY);
  return data;
}

static void writeByte(uint8_t devAddress, uint8_t regAddress, uint8_t data) {
  HAL_I2C_Mem_Write(&hi2c2, (devAddress<<1)+0, regAddress, 1, &data, 1, HAL_MAX_DELAY);
}

static void readBytes(uint8_t devAddress, uint8_t regAddress, uint8_t count, uint8_t *dest) {
  HAL_I2C_Mem_Read(&hi2c2, (devAddress<<1)+1, regAddress, 1, dest, count, HAL_MAX_DELAY);
}

void refreshIMUValues() {
    uint8_t rawData[14];  // x/y/z accel and gyro register data stored here
    int16_t tempData[7]; // Temperature, gyro x/y/z, accel x/y/z
  
    // Read the 14 raw data registers into data array
    readBytes(IMU_ICM42605_ADDRESS, IMU_ICM42605_TEMP_DATA1, 14, rawData);

    IMU_Accel[0] = ((int16_t)(rawData[8] << 8 | rawData[9])) * _aRes * IMU_GRAVITATIONAL_ACCELERATION; // Convert to m/s²
    IMU_Accel[1] = ((int16_t)(rawData[10] << 8 | rawData[11])) * _aRes * IMU_GRAVITATIONAL_ACCELERATION;
    IMU_Accel[2] = ((int16_t)(rawData[12] << 8 | rawData[13])) * _aRes * IMU_GRAVITATIONAL_ACCELERATION;

    IMU_Gyro[0] = ((int16_t)(rawData[2] << 8 | rawData[3])) * _gRes * IMU_DPS2RAD; // Convert to rad/s
    IMU_Gyro[1] = ((int16_t)(rawData[4] << 8 | rawData[5])) * _gRes * IMU_DPS2RAD;
    IMU_Gyro[2] = ((int16_t)(rawData[6] << 8 | rawData[7])) * _gRes * IMU_DPS2RAD;

    IMU_Temp = ((int16_t)(rawData[0] << 8 | rawData[1])) / 132.48f + 25.0f; // Convert to °C

    #ifdef IMU_DYNAMIC_FSR
    calibrateIMU();
    #endif
}

void initIMU() {
    uint8_t wake = 0x01; // Reset device
    writeByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_DEVICE_CONFIG, wake);
    HAL_Delay(1);

    uint8_t powerConfig = 0x0F; // Enable gyro and accel in low noise mode
    writeByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_PWR_MGMT0, powerConfig);

    uint8_t accelConfig = (AFS_2G << 5) | AODR_1000Hz; // ±2g, 1 kHz
    writeByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_ACCEL_CONFIG0, accelConfig);

    uint8_t gyroConfig = (GFS_250DPS << 5) | GODR_1000Hz; // ±250°/s, 1 kHz
    writeByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_GYRO_CONFIG0, gyroConfig);

    checkIMU = readByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_WHO_AM_I);
}

void calibrateIMU() {
    static uint8_t lastAccelConfig = AFS_2G;
    static uint8_t lastGyroConfig = GFS_250DPS;

    uint8_t accelConfig = lastAccelConfig;
    uint8_t gyroConfig = lastGyroConfig;

    // Check each accelerometer axis
    float accelMaxMag = 0;
    for (int i = 0; i < 3; i++) {
        float absAccel = fabsf(IMU_Accel[i] / IMU_GRAVITATIONAL_ACCELERATION); // Convert m/s² to g
        accelMaxMag = (absAccel > accelMaxMag) ? absAccel : accelMaxMag;
    }

    accelConfig = AFS_2G;
    _aRes = getAres(AFS_2G);
    // Dynamic adjustment of accelerometer FSR
    if (accelMaxMag >= 1.75f && accelMaxMag < 3.75f) {
        accelConfig = AFS_4G;
        _aRes = getAres(AFS_4G);
    } else if (accelMaxMag >= 3.75f && accelMaxMag < 7.75f) {
        accelConfig = AFS_8G;
        _aRes = getAres(AFS_8G);
    } else if (accelMaxMag >= 7.75f) {
        accelConfig = AFS_16G;
        _aRes = getAres(AFS_16G);
    }

    // Check each gyroscope axis
    float gyroMaxMag = 0;
    for (int i = 0; i < 3; i++) {
        float absGyro = fabsf(IMU_Gyro[i]);
        gyroMaxMag = (absGyro > gyroMaxMag) ? absGyro : gyroMaxMag;
    }

    // Dynamic adjustment of gyroscope FSR (values in radians/s)
    if (gyroMaxMag >= 4.3633f && gyroMaxMag < 8.7266f) {
        gyroConfig = GFS_500DPS;
        _gRes = getGres(GFS_500DPS);
    } else if (gyroMaxMag >= 8.7266f && gyroMaxMag < 17.4533f) {
        gyroConfig = GFS_1000DPS;
        _gRes = getGres(GFS_1000DPS);
    } else if (gyroMaxMag >= 17.4533f) {
        gyroConfig = GFS_2000DPS;
        _gRes = getGres(GFS_2000DPS);
    }

    if (lastAccelConfig != accelConfig) {
        uint8_t temp = readByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_ACCEL_CONFIG0);
        temp = (temp & ~0xE0) | (accelConfig << 5);
        writeByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_ACCEL_CONFIG0, temp);
        lastAccelConfig = accelConfig;
    }

    if (lastGyroConfig != gyroConfig) {
        uint8_t temp = readByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_GYRO_CONFIG0);
        temp = (temp & ~0xE0) | (gyroConfig << 5);
        writeByte(IMU_ICM42605_ADDRESS, IMU_ICM42605_GYRO_CONFIG0, temp);
        lastGyroConfig = gyroConfig;
    }
}

#endif // IMU_ICM42605