#include "IODefinitions.h"
#include <algorithm>
#include <Arduino.h>
#include "Logger.h"

const std::array<IODefinitions::IOPin, 8> IODefinitions::INPUT_PINS = {
    IODefinitions::UNDEFINED, // Stuffing for IN1, unavailable on MCU side 
    IODefinitions::UNDEFINED, // Stuffing for IN2, unavailable on MCU side 
    IODefinitions::IN3, 
    IODefinitions::IN4, 
    IODefinitions::UNDEFINED, // Stuffing for unused IN5 
    IODefinitions::UNDEFINED, // Stuffing for unused IN6 
    IODefinitions::IN7, 
    IODefinitions::IN8
};
const std::array<IODefinitions::IOPin, 10> IODefinitions::OUTPUT_PINS = {
    IODefinitions::OUT1, 
    IODefinitions::OUT2, 
    IODefinitions::OUT3, 
    IODefinitions::OUT4, 
    IODefinitions::OUT5, 
    IODefinitions::OUT6, 
    IODefinitions::OUT7, 
    IODefinitions::OUT8, 
    IODefinitions::OUT9, 
    IODefinitions::CAN_SLEEP
};

std::vector<IODefinitions::IOPin> IODefinitions::manualInitPins;

void IODefinitions::addManualInitPin(IOPin pin)
{
    manualInitPins.push_back(pin);
}

void IODefinitions::initGPIO()
{
#ifdef ARDUINO
    for (auto pin: INPUT_PINS)
    {
        if (pin != UNDEFINED && std::find(manualInitPins.begin(), manualInitPins.end(), pin) == manualInitPins.end())
        {
            pinMode(pin, INPUT_PULLUP);
        }
        else
        {
            LOG_INFO("IODefs", "Not initializing GPIO[%d] as INPUT", pin);
        }
    }

    for (auto pin: OUTPUT_PINS)
    {
        if (pin != UNDEFINED && std::find(manualInitPins.begin(), manualInitPins.end(), pin) == manualInitPins.end())
        {
            gpio_hold_dis(pin);
            if (pin != GPIO_NUM_9)
                pinMode(pin, OUTPUT);
            else
                pinMode(pin, OUTPUT_OPEN_DRAIN);  // wired to an external pull-up resistor on the PCB.
        }
        else
        {
            LOG_INFO("IODefs", "Not initializing GPIO[%d] as OUTPUT", pin);
        }
    }
#else
    #warning "IODefinitions::initGPIO() is not implemented for non-ARDUINO platforms"
#endif
}
