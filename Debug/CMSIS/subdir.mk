################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/system_MKL46Z4.c 

OBJS += \
./CMSIS/system_MKL46Z4.o 

C_DEPS += \
./CMSIS/system_MKL46Z4.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/%.o: ../CMSIS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DCPU_MKL46Z256VLL4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Nicolas\Documents\MCUXpressoIDE_11.3.1_5262\workspace\MKL46Z4_TEST_XMODEM\board" -I"C:\Users\Nicolas\Documents\MCUXpressoIDE_11.3.1_5262\workspace\MKL46Z4_TEST_XMODEM\source" -I"C:\Users\Nicolas\Documents\MCUXpressoIDE_11.3.1_5262\workspace\MKL46Z4_TEST_XMODEM" -I"C:\Users\Nicolas\Documents\MCUXpressoIDE_11.3.1_5262\workspace\MKL46Z4_TEST_XMODEM\drivers" -I"C:\Users\Nicolas\Documents\MCUXpressoIDE_11.3.1_5262\workspace\MKL46Z4_TEST_XMODEM\utilities" -I"C:\Users\Nicolas\Documents\MCUXpressoIDE_11.3.1_5262\workspace\MKL46Z4_TEST_XMODEM\startup" -I"C:\Users\Nicolas\Documents\MCUXpressoIDE_11.3.1_5262\workspace\MKL46Z4_TEST_XMODEM\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


