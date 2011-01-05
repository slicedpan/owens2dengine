################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/engine.cpp \
../src/gameinstance.cpp \
../src/main.cpp \
../src/menuinstance.cpp \
../src/testinstance.cpp 

OBJS += \
./src/engine.o \
./src/gameinstance.o \
./src/main.o \
./src/menuinstance.o \
./src/testinstance.o 

CPP_DEPS += \
./src/engine.d \
./src/gameinstance.d \
./src/main.d \
./src/menuinstance.d \
./src/testinstance.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/owen/workspace/guitest/include" -I/usr/local/include/CEGUI -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


