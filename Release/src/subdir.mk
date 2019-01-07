################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GLBatchMini.cpp \
../src/GLShaderManagerMini.cpp \
../src/crosd.cpp \
../src/dctext.cpp \
../src/glosd.cpp \
../src/gltext.cpp \
../src/math3d.cpp 

OBJS += \
./src/GLBatchMini.o \
./src/GLShaderManagerMini.o \
./src/crosd.o \
./src/dctext.o \
./src/glosd.o \
./src/gltext.o \
./src/math3d.o 

CPP_DEPS += \
./src/GLBatchMini.d \
./src/GLShaderManagerMini.d \
./src/crosd.d \
./src/dctext.d \
./src/glosd.d \
./src/gltext.d \
./src/math3d.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I../src -I../src/GL -I../include -I../include/osa -O3 -Xcompiler -fPIC -ccbin aarch64-linux-gnu-g++ -gencode arch=compute_50,code=sm_50 -m64 -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I../src -I../src/GL -I../include -I../include/osa -O3 -Xcompiler -fPIC --compile -m64 -ccbin aarch64-linux-gnu-g++  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


