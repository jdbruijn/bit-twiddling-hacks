################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BitOperations.c \
../src/BitOperations_UnitTest.c 

OBJS += \
./src/BitOperations.o \
./src/BitOperations_UnitTest.o 

C_DEPS += \
./src/BitOperations.d \
./src/BitOperations_UnitTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I../ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


