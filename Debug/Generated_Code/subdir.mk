################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/BT1.c \
../Generated_Code/CI2C1.c \
../Generated_Code/CLS1.c \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/CsIO1.c \
../Generated_Code/EInt1.c \
../Generated_Code/ExtIntLdd1.c \
../Generated_Code/GI2C1.c \
../Generated_Code/IO1.c \
../Generated_Code/MCUC1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/Serial1.c \
../Generated_Code/UTIL1.c \
../Generated_Code/WAIT1.c \
../Generated_Code/XF1.c 

OBJS += \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/BT1.o \
./Generated_Code/CI2C1.o \
./Generated_Code/CLS1.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/CsIO1.o \
./Generated_Code/EInt1.o \
./Generated_Code/ExtIntLdd1.o \
./Generated_Code/GI2C1.o \
./Generated_Code/IO1.o \
./Generated_Code/MCUC1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/Serial1.o \
./Generated_Code/UTIL1.o \
./Generated_Code/WAIT1.o \
./Generated_Code/XF1.o 

C_DEPS += \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/BT1.d \
./Generated_Code/CI2C1.d \
./Generated_Code/CLS1.d \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/CsIO1.d \
./Generated_Code/EInt1.d \
./Generated_Code/ExtIntLdd1.d \
./Generated_Code/GI2C1.d \
./Generated_Code/IO1.d \
./Generated_Code/MCUC1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/Serial1.d \
./Generated_Code/UTIL1.d \
./Generated_Code/WAIT1.d \
./Generated_Code/XF1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/System" -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/PDD" -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/IO_Map" -I"C:\Freescale\KDSK_1.3.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"//Mac/Home/workspace.kds/HRmonitor/Sources" -I"//Mac/Home/workspace.kds/HRmonitor/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


