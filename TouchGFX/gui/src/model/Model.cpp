#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "stm32f4xx_hal.h"

Model::Model() : modelListener(0)
{

}

bool isBootButtonHeld3Seconds()
{
    static uint32_t pressStartTime = 0;

    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
    {
        if (pressStartTime == 0)
        {
            pressStartTime = HAL_GetTick();
        }
        else if (HAL_GetTick() - pressStartTime >= 3000)
        {
            pressStartTime = 0; // reset lại sau khi phát hiện
            return true;
        }
    }
    else
    {
        pressStartTime = 0; // reset nếu nhả nút
    }

    return false;
}


void Model::tick()
{
    if (isBootButtonHeld3Seconds())
    {
        modelListener->onRequestRegisterMode(); // Bắt đầu chế độ đăng ký
    }
}
