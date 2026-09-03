#pragma once
#include <map>
#include <can_common.h>

#ifdef ARDUINO
#include "WString.h"
#endif 

/**
 * The available CAN buses on the SANS Gateway / SANS Tester hardware.
 */
enum class CANBus
{
    CAN0,  
    CAN1,
    VIRTUAL_CAN  
};

/**
 * A basic interface for handling CAN frames.
 */
class CANFrameHandler
{
    public:
        virtual void processFrame(CANBus bus, CAN_FRAME* frame) = 0;

        static void copy(const CAN_FRAME &in, CAN_FRAME *out)
        {
            if (out == nullptr)
                return;
            
            out->id = in.id;
            out->length = in.length;
            out->extended = in.extended;
            memcpy(out->data.uint8, in.data.uint8, in.length);
        }

        static bool equals(const CAN_FRAME &f1, const CAN_FRAME &f2)
        {
            if (f1.id != f2.id || f1.length != f2.length)
                return false;

            return memcmp(f1.data.uint8, f2.data.uint8, f1.length) == 0;
        }

        #ifdef ARDUINO
        static String toString(CANBus canBus, const CAN_FRAME &frame)
        {
            String msg;
            switch (canBus)
            {
                case CANBus::CAN0:
                    msg += "CAN0: (";
                    break;
                case CANBus::CAN1:
                    msg += "CAN1: (";
                    break;
                case CANBus::VIRTUAL_CAN:
                    msg += "VCAN: (";
                    break;
            }

            msg += String(frame.timestamp, 10);
            msg += ") ";
            msg += String(frame.id, HEX);
            msg += "#";
            for (int i = 0; i < frame.length; i++)
            {
                if (frame.data.uint8[i] < 0x10)
                    msg += "0";
                msg += String(frame.data.uint8[i], HEX);
            }
            if (frame.fid != 0)
            {
                
                msg += " [0x";
                msg += String(frame.fid, 16);
                msg += "]";
            }
            return msg;
        }
        #endif
};

/**
 * A base class for CAN plugins, providing a mechanism to handle CAN frames and chain multiple handlers.
 */
class CANPlugin: public CANFrameHandler
{
    public:
        virtual void begin() {}
        virtual void doLoop() {}
        virtual void setNextFrameHandler(CANFrameHandler* handler) {nextCanFrameHandler = handler;}
        virtual CANFrameHandler* getNextFrameHandler() const {return nextCanFrameHandler;}
        virtual const char* getUseCase(CANBus canBus) const = 0;
        
    protected:
        CANFrameHandler* nextCanFrameHandler = nullptr;
};        