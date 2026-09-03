#include "VirtualCAN.h"
#include "Logger.h"

const char* VirtualCAN::TAG = "VCAN";

VirtualCAN::VirtualCAN(CANBus _canBus, CANFrameHandler* nextHandler)
    : CAN_COMMON(/* numFilt */ 1), canBus(_canBus), nextHandler(nextHandler)
{
}

int VirtualCAN::_setFilterSpecific(uint8_t mailbox, uint32_t id, uint32_t mask, bool extended)
{
    LOG_WARN(TAG, "Not Implemented: %s", __FUNCTION__);
    return -1;
}

int VirtualCAN::_setFilter(uint32_t id, uint32_t mask, bool extended)
{
    LOG_WARN(TAG, "Not Implemented: %s", __FUNCTION__);
    return -1;
}

uint32_t VirtualCAN::init(uint32_t ul_baudrate)
{
    LOG_WARN(TAG, "Not Implemented: %s", __FUNCTION__);
    return ul_baudrate;
}

uint32_t VirtualCAN::beginAutoSpeed()
{
    LOG_WARN(TAG, "Not Implemented: %s", __FUNCTION__);
    return 500;
}

uint32_t VirtualCAN::set_baudrate(uint32_t ul_baudrate)
{
    LOG_WARN(TAG, "Not Implemented: %s", __FUNCTION__);
    return ul_baudrate;
}

void VirtualCAN::setListenOnlyMode(bool state)
{
    LOG_WARN(TAG, "Not Implemented: %s", __FUNCTION__);
}

void VirtualCAN::enable()
{
    LOG_WARN(TAG, "Not Implemented: %s", __FUNCTION__);
}

void VirtualCAN::disable()
{
    LOG_WARN(TAG, "Not Implemented: %s", __FUNCTION__);
}

bool VirtualCAN::sendFrame(CAN_FRAME& txFrame)
{
    if (plugins.size() > 0)
    {
        plugins[0]->processFrame(canBus, &txFrame);
    }
    return true;
}

bool VirtualCAN::rx_avail()
{
    return !rxBuffer.empty();
}

uint16_t VirtualCAN::available()
{
    return rxBuffer.size();
}

uint32_t VirtualCAN::get_rx_buff(CAN_FRAME &msg)
{
    if (rxBuffer.empty())
        return false;

    copy(rxBuffer.front(), &msg);
    rxBuffer.erase(rxBuffer.begin());
    return true;
}

void VirtualCAN::processFrame(CANBus bus, CAN_FRAME* frame)
{
    if (nextHandler != nullptr)
        nextHandler->processFrame(CANBus::VIRTUAL_CAN, frame);
    else
    {
        rxBuffer.push_back(*frame);
        logInfo(TAG, "got from plugin:" + toString(bus, rxBuffer.back()) + ", rxBuffer size: " + rxBuffer.size());
    }
}

void VirtualCAN::addPlugin(CANPlugin* plugin)
{
    if (plugins.size() > 0)
    {
        plugin->setNextFrameHandler(plugins.back()->getNextFrameHandler());
    }
    else
    {
        plugin->setNextFrameHandler(this);
    }
    plugins.push_back(plugin);
}

int VirtualCAN::toNumber(CANBus bus)
{
    switch (bus)
    {
        case CANBus::CAN0: return 0;
        case CANBus::CAN1: return 1;
        case CANBus::VIRTUAL_CAN: return 2;
        default: return -1;
    }
}
