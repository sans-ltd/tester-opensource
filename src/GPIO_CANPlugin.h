#pragma once 
#include "CANPlugin.h"

/**
 * This plugin allows to control the digital IOs via CAN messages.
 */
class GPIO_CANPlugin : public CANPlugin
{
    public:
        GPIO_CANPlugin(CANBus canBus);
        virtual void begin() override;
        virtual void doLoop() override;
        virtual void processFrame(CANBus bus, CAN_FRAME* frame) override;
        virtual const char* getUseCase(CANBus canBus) const override;
        
    private:
        static const char* TAG;
        CANBus canBus;
        uint16_t outputCanID = 0x7f0;
        uint16_t inputCanID = 0x7f1;
        uint16_t inputState = 0xffff;
};