
#include "IODefinitions.h"
#include "Logger.h"

#include "GPIO_CANPlugin.h"

const char* GPIO_CANPlugin::TAG = "GPIO";

GPIO_CANPlugin::GPIO_CANPlugin(CANBus canBus) :
    canBus(canBus)
{
}

void GPIO_CANPlugin::begin()
{
}

void GPIO_CANPlugin::doLoop()
{
    uint16_t newInputState = 0;
    const auto& inputPins = IODefinitions::INPUT_PINS;

    for (size_t i = 0; i < inputPins.size(); i++)
    {
        const auto pin = inputPins[i];
        if (pin != IODefinitions::UNDEFINED && pin != IODefinitions::CAN_SLEEP)
        {
            if (!digitalRead(pin)) // ULN2803 inverts the inputs
                newInputState = newInputState + static_cast<uint16_t>(1 << i);       
        }
    }

    // LOG_INFO(TAG, "doLoop() newInputState 0x%x", newInputState);

    if (newInputState != inputState)
    {
        inputState = newInputState;

        CAN_FRAME txFrame;
        txFrame.id = inputCanID;
        txFrame.length = 2;
        txFrame.data.uint8[0] = static_cast<uint8_t>(inputState >> 8);
        txFrame.data.uint8[1] = static_cast<uint8_t>(inputState & 0xFF);
        logInfo(TAG, "Sending " + toString(canBus, txFrame));
        injectFrame(canBus, &txFrame);
    }
}

void GPIO_CANPlugin::processFrame(CANBus bus, CAN_FRAME *frame)
{
    if (frame->id == outputCanID && frame->length == 2)
    {
        for (size_t i = 0; i < IODefinitions::OUTPUT_PINS.size(); i++)
        {
            uint16_t bitmask = frame->data.uint8[0] << 8 | frame->data.uint8[1];
            // logInfo(TAG, "Processing output frame with bitmask 0x" + String(bitmask, HEX));
            const auto pin = IODefinitions::OUTPUT_PINS[i];
            if (pin != IODefinitions::UNDEFINED && pin != IODefinitions::CAN_SLEEP)
                digitalWrite(pin, (bitmask & static_cast<uint16_t>(1 << i)) > 0);
        }
    }
}

const char *GPIO_CANPlugin::getUseCase(CANBus canBus) const
{
    switch (canBus)
    {
        case CANBus::CAN0: return "CAN0";
        case CANBus::CAN1: return "CAN1";
        case CANBus::VIRTUAL_CAN: return "VIRTUAL_CAN";
    } 
    return "";
}
