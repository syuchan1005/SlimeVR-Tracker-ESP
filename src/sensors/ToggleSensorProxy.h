#include <stdexcept>

#include "SensorManager.h"
#include "sensor.h"

class ToggleSensorProxy : public Sensor
{
public:
    ToggleSensorProxy(
        Sensor *sensor,
        SlimeVR::Sensors::ToggleSensor::AbstractBehavior *toggleSensorBehavior) : Sensor("ToggleSensorProxy", 1, 1, 1, 1.0), m_sensor(sensor), m_toggleSensorBehavior(toggleSensorBehavior){};
    ~ToggleSensorProxy(){};

    void motionSetup() override
    {
        m_toggleSensorBehavior->startUseSensor();
        m_sensor->motionSetup();
        m_toggleSensorBehavior->endUseSensor();
    }

    void postSetup() override
    {
        m_toggleSensorBehavior->startUseSensor();
        m_sensor->postSetup();
        m_toggleSensorBehavior->endUseSensor();
    }

    void motionLoop() override
    {
        m_toggleSensorBehavior->startUseSensor();
        m_sensor->motionLoop();
        m_toggleSensorBehavior->endUseSensor();
    }

    void sendData() override
    {
        m_toggleSensorBehavior->startUseSensor();
        m_sensor->sendData();
        m_toggleSensorBehavior->endUseSensor();
    }

    void startCalibration(int calibrationType) override
    {
        m_toggleSensorBehavior->startUseSensor();
        m_sensor->startCalibration(calibrationType);
        m_toggleSensorBehavior->endUseSensor();
    }

    uint8_t getSensorState() override
    {
        m_toggleSensorBehavior->startUseSensor();
        uint8_t result = m_sensor->getSensorState();
        m_toggleSensorBehavior->endUseSensor();
        return result;
    }

    bool isWorking() override { return m_sensor->isWorking(); }
    uint8_t getSensorId() override { return m_sensor->getSensorId(); }
    uint8_t getSensorType() override { return m_sensor->getSensorType(); }

private:
    Sensor *m_sensor = NULL;
    SlimeVR::Sensors::ToggleSensor::AbstractBehavior *m_toggleSensorBehavior;
};
