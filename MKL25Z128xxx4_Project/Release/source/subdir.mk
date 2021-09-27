################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Human_Interface.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/Human_Interface.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/Human_Interface.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -I"F:\Blinkenlights\MKL25Z128xxx4_Project\board" -I"F:\Blinkenlights\MKL25Z128xxx4_Project\source" -I"F:\Blinkenlights\MKL25Z128xxx4_Project" -I"F:\Blinkenlights\MKL25Z128xxx4_Project\drivers" -I"F:\Blinkenlights\MKL25Z128xxx4_Project\CMSIS" -I"F:\Blinkenlights\MKL25Z128xxx4_Project\utilities" -I"F:\Blinkenlights\MKL25Z128xxx4_Project\startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

