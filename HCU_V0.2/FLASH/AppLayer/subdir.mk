################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../AppLayer/StateMachineManagement.c" \
"../AppLayer/SysParameters.c" \
"../AppLayer/TaskSchedule.c" \

C_SRCS += \
../AppLayer/StateMachineManagement.c \
../AppLayer/SysParameters.c \
../AppLayer/TaskSchedule.c \

OBJS += \
./AppLayer/StateMachineManagement_c.obj \
./AppLayer/SysParameters_c.obj \
./AppLayer/TaskSchedule_c.obj \

OBJS_QUOTED += \
"./AppLayer/StateMachineManagement_c.obj" \
"./AppLayer/SysParameters_c.obj" \
"./AppLayer/TaskSchedule_c.obj" \

C_DEPS += \
./AppLayer/StateMachineManagement_c.d \
./AppLayer/SysParameters_c.d \
./AppLayer/TaskSchedule_c.d \

C_DEPS_QUOTED += \
"./AppLayer/StateMachineManagement_c.d" \
"./AppLayer/SysParameters_c.d" \
"./AppLayer/TaskSchedule_c.d" \

OBJS_OS_FORMAT += \
./AppLayer/StateMachineManagement_c.obj \
./AppLayer/SysParameters_c.obj \
./AppLayer/TaskSchedule_c.obj \


# Each subdirectory must supply rules for building sources it contributes
AppLayer/StateMachineManagement_c.obj: ../AppLayer/StateMachineManagement.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"AppLayer/StateMachineManagement.args" -ObjN="AppLayer/StateMachineManagement_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

AppLayer/%.d: ../AppLayer/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

AppLayer/SysParameters_c.obj: ../AppLayer/SysParameters.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"AppLayer/SysParameters.args" -ObjN="AppLayer/SysParameters_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

AppLayer/TaskSchedule_c.obj: ../AppLayer/TaskSchedule.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"AppLayer/TaskSchedule.args" -ObjN="AppLayer/TaskSchedule_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


