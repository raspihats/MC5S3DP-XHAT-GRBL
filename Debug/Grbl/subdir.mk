################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Grbl/CoolantControl.c \
../Grbl/GCode.c \
../Grbl/Jog.c \
../Grbl/Limits.c \
../Grbl/MotionControl.c \
../Grbl/Planner.c \
../Grbl/Probe.c \
../Grbl/Protocol.c \
../Grbl/Report.c \
../Grbl/Settings.c \
../Grbl/SpindleControl.c \
../Grbl/Stepper.c \
../Grbl/System.c \
../Grbl/util.c 

OBJS += \
./Grbl/CoolantControl.o \
./Grbl/GCode.o \
./Grbl/Jog.o \
./Grbl/Limits.o \
./Grbl/MotionControl.o \
./Grbl/Planner.o \
./Grbl/Probe.o \
./Grbl/Protocol.o \
./Grbl/Report.o \
./Grbl/Settings.o \
./Grbl/SpindleControl.o \
./Grbl/Stepper.o \
./Grbl/System.o \
./Grbl/util.o 

C_DEPS += \
./Grbl/CoolantControl.d \
./Grbl/GCode.d \
./Grbl/Jog.d \
./Grbl/Limits.d \
./Grbl/MotionControl.d \
./Grbl/Planner.d \
./Grbl/Probe.d \
./Grbl/Protocol.d \
./Grbl/Report.d \
./Grbl/Settings.d \
./Grbl/SpindleControl.d \
./Grbl/Stepper.d \
./Grbl/System.d \
./Grbl/util.d 


# Each subdirectory must supply rules for building sources it contributes
Grbl/%.o: ../Grbl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_FULL_LL_DRIVER '-DHSE_VALUE=16000000' '-DHSE_STARTUP_TIMEOUT=100' '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DEXTERNAL_CLOCK_VALUE=12288000' '-DHSI_VALUE=16000000' '-DLSI_VALUE=32000' '-DVDD_VALUE=3300' '-DPREFETCH_ENABLE=1' '-DINSTRUCTION_CACHE_ENABLE=1' '-DDATA_CACHE_ENABLE=1' '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DSTM32F411xE -I"/home/fcos/workspace/git_source/MC5S3DP-XHAT-GRBL/Inc" -I"/home/fcos/workspace/git_source/MC5S3DP-XHAT-GRBL/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/fcos/workspace/git_source/MC5S3DP-XHAT-GRBL/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/fcos/workspace/git_source/MC5S3DP-XHAT-GRBL/Drivers/CMSIS/Include" -I"/home/fcos/workspace/git_source/MC5S3DP-XHAT-GRBL/Grbl" -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


