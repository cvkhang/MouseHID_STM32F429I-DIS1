################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/mouse/mouse_click.c \
../Application/User/mouse/mouse_config.c \
../Application/User/mouse/mouse_hid.c \
../Application/User/mouse/mouse_macro.c \
../Application/User/mouse/mouse_scroll.c \
../Application/User/mouse/touchpad.c 

C_DEPS += \
./Application/User/mouse/mouse_click.d \
./Application/User/mouse/mouse_config.d \
./Application/User/mouse/mouse_hid.d \
./Application/User/mouse/mouse_macro.d \
./Application/User/mouse/mouse_scroll.d \
./Application/User/mouse/touchpad.d 

OBJS += \
./Application/User/mouse/mouse_click.o \
./Application/User/mouse/mouse_config.o \
./Application/User/mouse/mouse_hid.o \
./Application/User/mouse/mouse_macro.o \
./Application/User/mouse/mouse_scroll.o \
./Application/User/mouse/touchpad.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/mouse/%.o Application/User/mouse/%.su Application/User/mouse/%.cyclo: ../Application/User/mouse/%.c Application/User/mouse/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DDEBUG -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -I"D:/STUDY/HUST/Subject/Nhúng/TouchGFXProject/MyMouse/STM32CubeIDE/Application/User/mouse/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-mouse

clean-Application-2f-User-2f-mouse:
	-$(RM) ./Application/User/mouse/mouse_click.cyclo ./Application/User/mouse/mouse_click.d ./Application/User/mouse/mouse_click.o ./Application/User/mouse/mouse_click.su ./Application/User/mouse/mouse_config.cyclo ./Application/User/mouse/mouse_config.d ./Application/User/mouse/mouse_config.o ./Application/User/mouse/mouse_config.su ./Application/User/mouse/mouse_hid.cyclo ./Application/User/mouse/mouse_hid.d ./Application/User/mouse/mouse_hid.o ./Application/User/mouse/mouse_hid.su ./Application/User/mouse/mouse_macro.cyclo ./Application/User/mouse/mouse_macro.d ./Application/User/mouse/mouse_macro.o ./Application/User/mouse/mouse_macro.su ./Application/User/mouse/mouse_scroll.cyclo ./Application/User/mouse/mouse_scroll.d ./Application/User/mouse/mouse_scroll.o ./Application/User/mouse/mouse_scroll.su ./Application/User/mouse/touchpad.cyclo ./Application/User/mouse/touchpad.d ./Application/User/mouse/touchpad.o ./Application/User/mouse/touchpad.su

.PHONY: clean-Application-2f-User-2f-mouse

