################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DigitalIoPin.cpp \
../src/Lab2_2.cpp \
../src/Led.cpp \
../src/Menu.cpp \
../src/PrintItm.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc15xx.cpp 

C_SRCS += \
../src/ITM_write.c \
../src/crp.c \
../src/sysinit.c 

CPP_DEPS += \
./src/DigitalIoPin.d \
./src/Lab2_2.d \
./src/Led.d \
./src/Menu.d \
./src/PrintItm.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc15xx.d 

C_DEPS += \
./src/ITM_write.d \
./src/crp.d \
./src/sysinit.d 

OBJS += \
./src/DigitalIoPin.o \
./src/ITM_write.o \
./src/Lab2_2.o \
./src/Led.o \
./src/Menu.o \
./src/PrintItm.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc15xx.o \
./src/crp.o \
./src/sysinit.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"/Users/DBY/Metro_SemesterV/Embedded Programming/MCUXpressoIDE_11.6.0_8187/workspace/lpc_board_nxp_lpcxpresso_1549/inc" -I"/Users/DBY/Metro_SemesterV/Embedded Programming/MCUXpressoIDE_11.6.0_8187/workspace/lpc_chip_15xx/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"/Users/DBY/Metro_SemesterV/Embedded Programming/MCUXpressoIDE_11.6.0_8187/workspace/lpc_board_nxp_lpcxpresso_1549/inc" -I"/Users/DBY/Metro_SemesterV/Embedded Programming/MCUXpressoIDE_11.6.0_8187/workspace/lpc_chip_15xx/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/DigitalIoPin.d ./src/DigitalIoPin.o ./src/ITM_write.d ./src/ITM_write.o ./src/Lab2_2.d ./src/Lab2_2.o ./src/Led.d ./src/Led.o ./src/Menu.d ./src/Menu.o ./src/PrintItm.d ./src/PrintItm.o ./src/cr_cpp_config.d ./src/cr_cpp_config.o ./src/cr_startup_lpc15xx.d ./src/cr_startup_lpc15xx.o ./src/crp.d ./src/crp.o ./src/sysinit.d ./src/sysinit.o

.PHONY: clean-src

