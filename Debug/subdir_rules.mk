################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
L138_LCDK_aic3106_init.obj: ../L138_LCDK_aic3106_init.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/Users/EE113D/MyProjects/OMAP-L138_GEL_BSL_Files/bsl/inc" --include_path="C:/Users/EE113D/MyProjects/L138_support" --define=omapl138 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="L138_LCDK_aic3106_init.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

miniproj1.obj: ../miniproj1.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/Users/EE113D/MyProjects/OMAP-L138_GEL_BSL_Files/bsl/inc" --include_path="C:/Users/EE113D/MyProjects/L138_support" --define=omapl138 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="miniproj1.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

miniproj1_good.obj: ../miniproj1_good.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/Users/EE113D/MyProjects/OMAP-L138_GEL_BSL_Files/bsl/inc" --include_path="C:/Users/EE113D/MyProjects/L138_support" --define=omapl138 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="miniproj1_good.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


