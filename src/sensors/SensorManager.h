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

#include <Wire.h>

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

            class Pin : public AbstractBehavior
            {
            public:
                Pin(uint8_t pin) : pinNum(pin){};
                Pin(uint8_t pin, uint8_t preferableIMUAddr) : pinNum(pin) { m_preferableIMUAddr = preferableIMUAddr; };

                void init() override { pinMode(pinNum, OUTPUT); }

                void startUseSensor() override { digitalWrite(pinNum, LOW); }

                void endUseSensor() override { digitalWrite(pinNum, HIGH); }

            private:
                uint8_t pinNum;
            };

            class TCA9548A : public AbstractBehavior
            {
            public:
                TCA9548A(uint8_t addr, uint8_t ch) : m_addr(addr), m_ch(ch){};
                TCA9548A(uint8_t addr, uint8_t ch, uint8_t preferableIMUAddr) : m_addr(addr), m_ch(ch) { m_preferableIMUAddr = preferableIMUAddr; };

                void startUseSensor() override
                {
                    Wire.beginTransmission(m_addr);
                    Wire.write(1 << m_ch);
                    Wire.endTransmission();
                };

            private:
                uint8_t m_addr;
                uint8_t m_ch;
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
