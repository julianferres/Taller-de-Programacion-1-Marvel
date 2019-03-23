################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ControladorTexturas.cpp \
../Juego.cpp \
../Personaje.cpp \
../main.cpp 

OBJS += \
./ControladorTexturas.o \
./Juego.o \
./Personaje.o \
./main.o 

CPP_DEPS += \
./ControladorTexturas.d \
./Juego.d \
./Personaje.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/emanuel/Facultad/Taller/juego1" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


