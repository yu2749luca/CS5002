################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/array_list.c \
../src/array_list_crawler.c \
../src/arraylist_iterator.c \
../src/main.c 

OBJS += \
./src/array_list.o \
./src/array_list_crawler.o \
./src/arraylist_iterator.o \
./src/main.o 

C_DEPS += \
./src/array_list.d \
./src/array_list_crawler.d \
./src/arraylist_iterator.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


