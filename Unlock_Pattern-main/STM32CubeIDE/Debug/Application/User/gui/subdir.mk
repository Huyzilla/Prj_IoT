################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/TouchGFX/gui/src/draw_screen/DrawPresenter.cpp \
C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/TouchGFX/gui/src/draw_screen/DrawView.cpp \
C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/TouchGFX/gui/src/common/FrontendApplication.cpp \
C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/TouchGFX/gui/src/model/Model.cpp \
../Application/User/gui/PatternStorage.cpp 

OBJS += \
./Application/User/gui/DrawPresenter.o \
./Application/User/gui/DrawView.o \
./Application/User/gui/FrontendApplication.o \
./Application/User/gui/Model.o \
./Application/User/gui/PatternStorage.o 

CPP_DEPS += \
./Application/User/gui/DrawPresenter.d \
./Application/User/gui/DrawView.d \
./Application/User/gui/FrontendApplication.d \
./Application/User/gui/Model.d \
./Application/User/gui/PatternStorage.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/gui/DrawPresenter.o: C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/TouchGFX/gui/src/draw_screen/DrawPresenter.cpp Application/User/gui/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DDEBUG -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I"C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/STM32CubeIDE/Application/User/gui" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/gui/DrawView.o: C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/TouchGFX/gui/src/draw_screen/DrawView.cpp Application/User/gui/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DDEBUG -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I"C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/STM32CubeIDE/Application/User/gui" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/gui/FrontendApplication.o: C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/TouchGFX/gui/src/common/FrontendApplication.cpp Application/User/gui/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DDEBUG -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I"C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/STM32CubeIDE/Application/User/gui" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/gui/Model.o: C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/TouchGFX/gui/src/model/Model.cpp Application/User/gui/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DDEBUG -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I"C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/STM32CubeIDE/Application/User/gui" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/gui/%.o Application/User/gui/%.su Application/User/gui/%.cyclo: ../Application/User/gui/%.cpp Application/User/gui/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DDEBUG -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I"C:/Users/huyzi/Downloads/Unlock_Pattern-main/Unlock_Pattern-main/STM32CubeIDE/Application/User/gui" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-gui

clean-Application-2f-User-2f-gui:
	-$(RM) ./Application/User/gui/DrawPresenter.cyclo ./Application/User/gui/DrawPresenter.d ./Application/User/gui/DrawPresenter.o ./Application/User/gui/DrawPresenter.su ./Application/User/gui/DrawView.cyclo ./Application/User/gui/DrawView.d ./Application/User/gui/DrawView.o ./Application/User/gui/DrawView.su ./Application/User/gui/FrontendApplication.cyclo ./Application/User/gui/FrontendApplication.d ./Application/User/gui/FrontendApplication.o ./Application/User/gui/FrontendApplication.su ./Application/User/gui/Model.cyclo ./Application/User/gui/Model.d ./Application/User/gui/Model.o ./Application/User/gui/Model.su ./Application/User/gui/PatternStorage.cyclo ./Application/User/gui/PatternStorage.d ./Application/User/gui/PatternStorage.o ./Application/User/gui/PatternStorage.su

.PHONY: clean-Application-2f-User-2f-gui

