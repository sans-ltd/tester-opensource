#pragma once

#include <can_common.h>
#include "CANPlugin.h"
#include <vector>

/**
 * A virtual CAN interface for the SANS Gateway / SANS Tester hardware.
 * This class implements the CAN_COMMON interface like a CAN bus driver,
 * but instead it feeds the incoming frames to the configured CANPlugins.
 */
class VirtualCAN : public CAN_COMMON, public CANFrameHandler
{
public:
    explicit VirtualCAN(CANBus _canBus = CANBus::VIRTUAL_CAN, CANFrameHandler* nextHandler = nullptr);

    virtual int _setFilterSpecific(uint8_t mailbox, uint32_t id, uint32_t mask, bool extended) override;
    virtual int _setFilter(uint32_t id, uint32_t mask, bool extended) override;
    virtual uint32_t init(uint32_t ul_baudrate) override;
    virtual uint32_t beginAutoSpeed() override;
    virtual uint32_t set_baudrate(uint32_t ul_baudrate) override;
    virtual void setListenOnlyMode(bool state) override;
    virtual void enable() override;
    virtual void disable() override;
    virtual bool sendFrame(CAN_FRAME& txFrame) override;
    virtual bool rx_avail() override;
    virtual uint16_t available() override; // like rx_avail but returns the number of waiting frames
    virtual uint32_t get_rx_buff(CAN_FRAME &msg) override;
    
    virtual void processFrame(CANBus bus, CAN_FRAME* frame) override;
    void addPlugin(CANPlugin* plugin);

private:
    static const char* TAG;
    CANBus canBus;

    int toNumber(CANBus bus);

    std::vector<CAN_FRAME> rxBuffer;
    CANFrameHandler* nextHandlerAfterThePlugins = nullptr;
    CANPluginHandler pluginHandler;
};