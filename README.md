# temperature-control-system
A system to control the motors and temperature. The implementation is for ATMega32 using c.
The schema is as follows:

![atmega](https://github.com/nikimajidifard/temperature-control-system/assets/56204470/4993d253-cbbd-4a76-a75e-39a4dac49928)

Hence, the following steps have to be done:
* The ambient temperature is received by the sensor.(It is recommended to use the 35LM piece.)
* The ambient temperature is displayed on LCD.
* One motor is used for cooler and one for heater.
* Motors are turned on and off according to ambient temperature changes and considered temperature limits.
