#pragma once
#include <array>
#include <soc/gpio_num.h>

class Standby;

class IODefinitions
{
    public:
        typedef gpio_num_t IOPin;
        static const IOPin CAN0_TX = GPIO_NUM_2;                            
        static const IOPin CAN0_RX = GPIO_NUM_3; 
        static const IOPin CAN1_TX = GPIO_NUM_16;
        static const IOPin CAN1_RX = GPIO_NUM_17;
        static const IOPin CAN_SLEEP = GPIO_NUM_6;  // IO_OPT_1
        static const IOPin I2C_SDA = GPIO_NUM_14;
        static const IOPin I2C_SCL = GPIO_NUM_8; 

        static const IOPin IN1 = GPIO_NUM_11;
        static const IOPin IN2 = GPIO_NUM_10;
        static const IOPin IN3 = GPIO_NUM_1;
        static const IOPin IN4 = GPIO_NUM_0;
        // static const IOPin IN5 = GPIO_NUM_7;
        // static const IOPin IN6 = GPIO_NUM_6;
        static const IOPin IN7 = GPIO_NUM_5;
        static const IOPin IN8 = GPIO_NUM_4;

        static const IOPin OUT1 = GPIO_NUM_9;
        static const IOPin OUT2 = GPIO_NUM_18;
        static const IOPin OUT3 = GPIO_NUM_19;
        static const IOPin OUT4 = GPIO_NUM_20;
        static const IOPin OUT5 = GPIO_NUM_21;
        static const IOPin OUT6 = GPIO_NUM_22;
        static const IOPin OUT7 = GPIO_NUM_23;

        static const IOPin OUT8 = GPIO_NUM_15;
        static const IOPin OUT9 = GPIO_NUM_7;  // IO_OPT_2

        static const std::array<IOPin, 8> INPUT_PINS;
        static const std::array<IOPin, 10> OUTPUT_PINS;

        static const IOPin UNDEFINED = GPIO_NUM_NC;
};