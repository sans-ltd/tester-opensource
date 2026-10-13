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
 * A base class for CAN plugins which can react, forward, manipulate, and inject CAN frames.
 */
class CANPlugin: public CANFrameHandler
{
    public:
        // A plugin can stop the processing of a frame by setting its ID to INVALID_FRAME_ID.
        static constexpr uint32_t INVALID_FRAME_ID = 0xFFFFFFFF;

        virtual void begin() {}
        virtual void doLoop() {}

        virtual const char* getUseCase(CANBus canBus) const = 0;      
        // Sets the callback function to be called when a frame is injected.
        void setInjectFrameCallback(std::function<void(const CANPlugin* source, CANBus, CAN_FRAME*)> callback) {
            injectFrameCallback = callback;
        }

    protected:
        void injectFrame(CANBus bus, CAN_FRAME* frame) {
            if (injectFrameCallback)
                injectFrameCallback(this, bus, frame);
        }

    private:
        std::function<void(const CANPlugin* source, CANBus, CAN_FRAME*)> injectFrameCallback;
};

// A handler that manages multiple CAN plugins and frame handlers and coordinates the injection and processing of CAN frames.
class CANPluginHandler
{
    public:
        void addPlugin(CANPlugin* plugin) {
            plugin->setInjectFrameCallback([this](const CANPlugin* source, CANBus bus, CAN_FRAME* frame) {
                this->onFrameInjected(source, bus, frame);
            });
            plugins.push_back(plugin);
        }

        void setFinalFrameHandler(CANFrameHandler* handler) {
            finalFrameHandler = handler;
        }

        void processFrameWithPlugins(CANBus bus, CAN_FRAME* frame)  {
            for (auto plugin : plugins) {
                if (plugin == currentInjectingPlugin)
                    continue;

                plugin->processFrame(bus, frame);

                if (frame->id == CANPlugin::INVALID_FRAME_ID)
                    break;
            }
            
            if (finalFrameHandler && frame->id != CANPlugin::INVALID_FRAME_ID) 
            {
                finalFrameHandler->processFrame(bus, frame);
            }
        }

        bool isInjectedFrame() const {
            return currentInjectingPlugin != nullptr;
        }

    private:
        std::vector<CANPlugin*> plugins;

        const CANPlugin* currentInjectingPlugin = nullptr;

        virtual void onFrameInjected(const CANPlugin* source, CANBus bus, CAN_FRAME* frame) {
            currentInjectingPlugin = source;
            processFrameWithPlugins(bus, frame);
            currentInjectingPlugin = nullptr;
        }

        CANFrameHandler* finalFrameHandler = nullptr;
};