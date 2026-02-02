#include "IODefinitions.h"

const std::array<IODefinitions::IOPin, 8> IODefinitions::INPUT_PINS = {
    IODefinitions::IN1, 
    IODefinitions::IN2, 
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

