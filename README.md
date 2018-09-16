# GRBL port for MC5S3DP-XHAT board

***

MC5S3DP-XHAT is 5 axis motion controller addon board for Raspberry PI designed for controlling 3D printers, CNCs, PnP machines, etc.

**Features:**
 - 5x Pololu format stepper drivers, FAULT signal support with IRQ capability
 - 10x Digital Inputs for EndStops, Min and Max for all axes, all with IRQ capability
 - 5x Digital Inputs for general use, all with IRQ capability
 - 6x Open Drain Outputs, one with 12A, two with 3A and three with 500mA current carrying capacity, PWM support on all outputs using 16bit timers
 - 3x Thermistor Inputs, 100K at 25C 

The MC5S3DP-XHAT is based on the STM32F411RC MCU, an ARM® Cortex®-M4 core running at 100 MHz.


**EXTI pin map:**

| Signal | Pin      | EXTI   |
| ------ |:--------:| ------:|
| A_MAX  | PC0(FT)  | EXTI0  |
| B_MAX  | PC1(FT)  | EXTI1  |
| Y_MIN  | PD2(FT)  | EXTI2  |
| Z_MIN  | PB3(FT)  | EXTI3  |
| A_MIN  | PB4(FT)  | EXTI4  |
| FAULT  | PA5(FT)  | EXTI5  |
| B_MIN  | PB6(FT)  | EXTI6  |
| X_MAX  | PB7(FT)  | EXTI7  |
| Y_MAX  | PB8(FT)  | EXTI8  |
| Z_MAX  | PB9(FT)  | EXTI9  |
| DI_3   | PC10(FT) | EXTI10 |
| DI_4   | PC11(FT) | EXTI11 |
| X_MIN  | PC12(FT) | EXTI12 |
| DI_0   | PB13(FT) | EXTI13 |
| DI_1   | PB14(FT) | EXTI14 |
| DI_2   | PA15(FT) | EXTI15 |

FT - Five Volts Tolerant