/*
    SlimeVR Code is placed under the MIT license
    Copyright (c) 2022 TheDevMinerTV

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include "SensorManager.h"
#include <i2cscan.h>
#include "network/network.h"
#include "bno055sensor.h"
#include "bno080sensor.h"
#include "mpu9250sensor.h"
#include "mpu6050sensor.h"
#include "bmi160sensor.h"
#include "icm20948sensor.h"
#include "ErroneousSensor.h"

namespace SlimeVR
{
    namespace Sensors
    {
        void SensorManager::setup()
        {
            int i = 0;
            for (auto sensorInfo : m_SensorInfos)
            {
                m_Sensors.push_back(createSensor(m_Logger, i, sensorInfo));
                i++;
            }

            for (auto sensor : m_Sensors)
            {
                sensor->motionSetup();
            }
        }

        void SensorManager::postSetup()
        {
            for (auto sensor : m_Sensors)
            {
                sensor->postSetup();
            }
        }

        void SensorManager::update()
        {
            // Gather IMU data
            for (auto sensor : m_Sensors)
            {
                sensor->motionLoop();
            }

            if (!ServerConnection::isConnected())
            {
                return;
            }

            // Send updates
            for (auto sensor : m_Sensors)
            {
                sensor->sendData();
            }
        }

        void SensorManager::updateSensorData()
        {
            Network::update(m_Sensors);
        }

        Sensor * SensorManager::createSensor(SlimeVR::Logging::Logger logger, uint8_t id, SlimeVR::Sensors::SensorInfo sensorInfo)
        {
            uint8_t imuAddress = 0;
            switch (sensorInfo.sensorType)
            {
            case IMU_BNO080:
            case IMU_BNO085:
            case IMU_BNO086:
                imuAddress = I2CSCAN::pickDevice(0x4A, 0x4B, true);
                break;
            case IMU_BNO055:
                imuAddress = I2CSCAN::pickDevice(0x29, 0x28, true);
                break;
            case IMU_MPU9250:
            case IMU_BMI160:
            case IMU_MPU6500:
            case IMU_MPU6050:
            case IMU_ICM20948:
                if (id % 2 == 0)
                    imuAddress = I2CSCAN::pickDevice(0x68, 0x69, true);
                else
                    imuAddress = I2CSCAN::pickDevice(0x69, 0x68, true);
                break;
            default:
                break;
            }

            if (imuAddress == 0)
            {
                return new ErroneousSensor(id, sensorInfo.sensorType);
            }

            logger.trace("IMU found at address 0x%02X", imuAddress);

            switch (sensorInfo.sensorType)
            {
            case IMU_BNO080:
            case IMU_BNO085:
            case IMU_BNO086:
                return new BNO080Sensor(id, sensorInfo.sensorType, imuAddress, sensorInfo.sensorRotation, sensorInfo.sensorIntPin);
            case IMU_BNO055:
                return new BNO055Sensor(id, imuAddress, sensorInfo.sensorRotation);
            case IMU_MPU9250:
                return new MPU9250Sensor(id, imuAddress, sensorInfo.sensorRotation);
            case IMU_BMI160:
                return new BMI160Sensor(id, imuAddress, sensorInfo.sensorRotation);
            case IMU_MPU6500:
            case IMU_MPU6050:
                return new MPU6050Sensor(id, sensorInfo.sensorType, imuAddress, sensorInfo.sensorRotation);
            case IMU_ICM20948:
                return new ICM20948Sensor(id, imuAddress, sensorInfo.sensorRotation);
            default:
                return new ErroneousSensor(id, sensorInfo.sensorType);
            }
        }
    }
}
