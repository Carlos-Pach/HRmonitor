################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Static_Code/Peripherals/PTD_Init.c 

OBJS += \
./Static_Code/Peripherals/PTD_Init.o 

C_DEPS += \
./Static_Code/Peripherals/PTD_Init.d 


# Each subdirectory must supply rules for building sources it contributes
Static_Code/Peripherals/%.o: ../Static_Code/Peripherals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/System" -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/PDD" -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/IO_Map" -I"C:\Freescale\KDSK_1.3.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"//Mac/Home/workspace.kds/HRmonitor/Sources" -I"//Mac/Home/workspace.kds/HRmonitor/Generated_Code" -I"//Mac/Home/workspace.kds/HRmonitor/Static_Code/Peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


