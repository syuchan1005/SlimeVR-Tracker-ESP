#define BOARD BOARD_WROOM32

// Battery monitoring options (comment to disable):
// BAT_EXTERNAL for ADC pin, BAT_INTERNAL for internal - can detect only low battery, BAT_MCP3021 for external ADC
#define BATTERY_MONITOR BAT_EXTERNAL
#define BATTERY_SHIELD_RESISTANCE 180 //130k BatteryShield, 180k SlimeVR or fill in external resistor value in kOhm

#define PIN_IMU_SDA 21
#define PIN_IMU_SCL 22
#define PIN_BATTERY_LEVEL 36

#define IMU_1 IMU_MPU6050
#define IMU_ROTATION_1 DEG_180
#define IMU_INT_1 23
#define IMU_2 IMU_MPU6050
#define IMU_ROTATION_2 DEG_0
#define IMU_INT_2 25
