################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Serial.obj: ../Serial.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TexasInstruments/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/yusuf/OneDrive/University Documents/Sophomore Year - 2019-2020/Fall Semester/15-348 Embedded Systems/Embedded Systems/DigitalCanvas" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/TexasInstruments/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Serial.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TexasInstruments/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/yusuf/OneDrive/University Documents/Sophomore Year - 2019-2020/Fall Semester/15-348 Embedded Systems/Embedded Systems/DigitalCanvas" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/TexasInstruments/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

timer.obj: ../timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TexasInstruments/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/yusuf/OneDrive/University Documents/Sophomore Year - 2019-2020/Fall Semester/15-348 Embedded Systems/Embedded Systems/DigitalCanvas" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/TexasInstruments/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="timer.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tm4c123gh6pm_startup_ccs.obj: ../tm4c123gh6pm_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TexasInstruments/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/yusuf/OneDrive/University Documents/Sophomore Year - 2019-2020/Fall Semester/15-348 Embedded Systems/Embedded Systems/DigitalCanvas" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/TexasInstruments/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tm4c123gh6pm_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


