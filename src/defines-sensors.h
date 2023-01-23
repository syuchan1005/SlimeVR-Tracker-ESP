#include <vector>
#include "sensors/SensorManager.h"

#define TCA9548A_ADDR 0x70
#define IMU_PORT_1 0x68
#define IMU_PORT_2 0x69

using namespace SlimeVR::Sensors;

// NOTE: This is a sample settings. Please edit it when you using this branch.
const std::vector<SlimeVR::Sensors::SensorInfo> SENSOR_INFOS = {
    SensorInfo(IMU_BMI160, DEG_180, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 0, IMU_PORT_2)), // weist
    SensorInfo(IMU_BMI160, DEG_270, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 5, IMU_PORT_1)), // chest
    SensorInfo(IMU_BMI160, DEG_90, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 1, IMU_PORT_1)), // right - upper
    SensorInfo(IMU_BMI160, DEG_180, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 1, IMU_PORT_2)), // right - lower
    SensorInfo(IMU_BMI160, DEG_90, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 2, IMU_PORT_1)), // left - upper
    SensorInfo(IMU_BMI160, DEG_180, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 2, IMU_PORT_2)), // left - lower
};
