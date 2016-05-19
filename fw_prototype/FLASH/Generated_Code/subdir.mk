################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/AD.c" \
"../Generated_Code/AS.c" \
"../Generated_Code/BitDCCTL.c" \
"../Generated_Code/BitsCS.c" \
"../Generated_Code/BitsMux.c" \
"../Generated_Code/CAN.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/IO_Map.c" \
"../Generated_Code/PE_Timer.c" \
"../Generated_Code/SM.c" \
"../Generated_Code/TIKrnl.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/AD.c \
../Generated_Code/AS.c \
../Generated_Code/BitDCCTL.c \
../Generated_Code/BitsCS.c \
../Generated_Code/BitsMux.c \
../Generated_Code/CAN.c \
../Generated_Code/Cpu.c \
../Generated_Code/IO_Map.c \
../Generated_Code/PE_Timer.c \
../Generated_Code/SM.c \
../Generated_Code/TIKrnl.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/AD_c.obj \
./Generated_Code/AS_c.obj \
./Generated_Code/BitDCCTL_c.obj \
./Generated_Code/BitsCS_c.obj \
./Generated_Code/BitsMux_c.obj \
./Generated_Code/CAN_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/PE_Timer_c.obj \
./Generated_Code/SM_c.obj \
./Generated_Code/TIKrnl_c.obj \
./Generated_Code/Vectors_c.obj \

OBJS_QUOTED += \
"./Generated_Code/AD_c.obj" \
"./Generated_Code/AS_c.obj" \
"./Generated_Code/BitDCCTL_c.obj" \
"./Generated_Code/BitsCS_c.obj" \
"./Generated_Code/BitsMux_c.obj" \
"./Generated_Code/CAN_c.obj" \
"./Generated_Code/Cpu_c.obj" \
"./Generated_Code/IO_Map_c.obj" \
"./Generated_Code/PE_Timer_c.obj" \
"./Generated_Code/SM_c.obj" \
"./Generated_Code/TIKrnl_c.obj" \
"./Generated_Code/Vectors_c.obj" \

C_DEPS += \
./Generated_Code/AD_c.d \
./Generated_Code/AS_c.d \
./Generated_Code/BitDCCTL_c.d \
./Generated_Code/BitsCS_c.d \
./Generated_Code/BitsMux_c.d \
./Generated_Code/CAN_c.d \
./Generated_Code/Cpu_c.d \
./Generated_Code/IO_Map_c.d \
./Generated_Code/PE_Timer_c.d \
./Generated_Code/SM_c.d \
./Generated_Code/TIKrnl_c.d \
./Generated_Code/Vectors_c.d \

C_DEPS_QUOTED += \
"./Generated_Code/AD_c.d" \
"./Generated_Code/AS_c.d" \
"./Generated_Code/BitDCCTL_c.d" \
"./Generated_Code/BitsCS_c.d" \
"./Generated_Code/BitsMux_c.d" \
"./Generated_Code/CAN_c.d" \
"./Generated_Code/Cpu_c.d" \
"./Generated_Code/IO_Map_c.d" \
"./Generated_Code/PE_Timer_c.d" \
"./Generated_Code/SM_c.d" \
"./Generated_Code/TIKrnl_c.d" \
"./Generated_Code/Vectors_c.d" \

OBJS_OS_FORMAT += \
./Generated_Code/AD_c.obj \
./Generated_Code/AS_c.obj \
./Generated_Code/BitDCCTL_c.obj \
./Generated_Code/BitsCS_c.obj \
./Generated_Code/BitsMux_c.obj \
./Generated_Code/CAN_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/PE_Timer_c.obj \
./Generated_Code/SM_c.obj \
./Generated_Code/TIKrnl_c.obj \
./Generated_Code/Vectors_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/AD_c.obj: ../Generated_Code/AD.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/AD.args" -ObjN="Generated_Code/AD_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/%.d: ../Generated_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Generated_Code/AS_c.obj: ../Generated_Code/AS.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/AS.args" -ObjN="Generated_Code/AS_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/BitDCCTL_c.obj: ../Generated_Code/BitDCCTL.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/BitDCCTL.args" -ObjN="Generated_Code/BitDCCTL_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/BitsCS_c.obj: ../Generated_Code/BitsCS.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/BitsCS.args" -ObjN="Generated_Code/BitsCS_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/BitsMux_c.obj: ../Generated_Code/BitsMux.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/BitsMux.args" -ObjN="Generated_Code/BitsMux_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CAN_c.obj: ../Generated_Code/CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/CAN.args" -ObjN="Generated_Code/CAN_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu_c.obj: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Cpu.args" -ObjN="Generated_Code/Cpu_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_Map_c.obj: ../Generated_Code/IO_Map.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/IO_Map.args" -ObjN="Generated_Code/IO_Map_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_Timer_c.obj: ../Generated_Code/PE_Timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/PE_Timer.args" -ObjN="Generated_Code/PE_Timer_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/SM_c.obj: ../Generated_Code/SM.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/SM.args" -ObjN="Generated_Code/SM_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TIKrnl_c.obj: ../Generated_Code/TIKrnl.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/TIKrnl.args" -ObjN="Generated_Code/TIKrnl_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors_c.obj: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Vectors.args" -ObjN="Generated_Code/Vectors_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


