################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/HC06.c \
../Sources/MAX30102.c \
../Sources/OLED.c \
../Sources/algorithm.c \
../Sources/main.c 

OBJS += \
./Sources/Events.o \
./Sources/HC06.o \
./Sources/MAX30102.o \
./Sources/OLED.o \
./Sources/algorithm.o \
./Sources/main.o 

C_DEPS += \
./Sources/Events.d \
./Sources/HC06.d \
./Sources/MAX30102.d \
./Sources/OLED.d \
./Sources/algorithm.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/System" -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/PDD" -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/IO_Map" -I"C:\Freescale\KDSK_1.3.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"//Mac/Home/workspace.kds/HRmonitor/Sources" -I"//Mac/Home/workspace.kds/HRmonitor/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


