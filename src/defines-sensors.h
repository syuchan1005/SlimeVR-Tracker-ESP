#include <vector>
#include "sensors/SensorManager.h"

#define TCA9548A_ADDR 0x70
#define IMU_PORT_1 0x68
#define IMU_PORT_2 0x69

using namespace SlimeVR::Sensors;

const std::vector<SlimeVR::Sensors::SensorInfo> SENSOR_INFOS = {
    SensorInfo(IMU_BMI160, DEG_180, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 0, IMU_PORT_1)),
    SensorInfo(IMU_BMI160, DEG_0, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 1, IMU_PORT_1)),
    SensorInfo(IMU_BMI160, DEG_0, 23, new ToggleSensor::TCA9548A(TCA9548A_ADDR, 1, IMU_PORT_2)),
    };
