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

#ifndef SLIMEVR_SENSORMANAGER
#define SLIMEVR_SENSORMANAGER

#include "globals.h"
#include "sensor.h"
#include "EmptySensor.h"
#include "logging/Logger.h"

namespace SlimeVR
{
    namespace Sensors
    {

        namespace ToggleSensor
        {
            /**
             * Behavior class representing sensor switching.
             * This is a base class of sealed class. Do not extend this class outside of this file.
             */
            class AbstractBehavior
            {
            public:
                virtual void init(){};
                virtual void startUseSensor(){};
                virtual void endUseSensor(){};

                uint8_t getPreferableIMUAddr()
                {
                    return m_preferableIMUAddr;
                };

            protected:
                uint8_t m_preferableIMUAddr = 0;
            };

            class None : public AbstractBehavior
            {
            };
        };

        class SensorInfo
        {
        public:
            SensorInfo(
                uint8_t sensorType,
                float sensorRotation,
                uint8_t sensorIntPin,
                ToggleSensor::AbstractBehavior *toggleSensorBehavior)
            {
                this->sensorType = sensorType;
                this->sensorRotation = sensorRotation;
                this->sensorIntPin = sensorIntPin;
                this->toggleSensorBehavior = toggleSensorBehavior;
            }

            uint8_t sensorType;
            float sensorRotation;
            uint8_t sensorIntPin;
            ToggleSensor::AbstractBehavior *toggleSensorBehavior;
        };

        class SensorManager
        {
        public:
            SensorManager(std::vector<SlimeVR::Sensors::SensorInfo> sensorInfos)
                : m_Logger(SlimeVR::Logging::Logger("SensorManager")), m_SensorInfos(sensorInfos) {}

            ~SensorManager()
            {
                for (auto sensor : m_Sensors)
                {
                    delete sensor;
                }
            }

            void setup();
            void postSetup();

            void update();
            void updateSensorData();

        private:
            SlimeVR::Logging::Logger m_Logger;

            std::vector<SensorInfo> m_SensorInfos;
            std::vector<Sensor *> m_Sensors;

            static Sensor *createSensor(SlimeVR::Logging::Logger logger, uint8_t id, SlimeVR::Sensors::SensorInfo sensorInfo);
        };
    }
}

#endif // SLIMEVR_SENSORFACTORY_H_
