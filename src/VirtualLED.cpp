#include "VirtualLED.h"
#ifdef COMPILE_VIRTUAL_LED
VirtualLEDs::VirtualLEDs() {}

void VirtualLED::operator=(uint32_t newState)
{
    state = newState;

    if (stateBitmaps.find(lastState) != stateBitmaps.end() && stateBitmaps[lastState] != nullptr)
    {
        display->drawBitmap(x, y, stateBitmaps[lastState], width, height, 0);
    }
    if (stateBitmaps.find(state) != stateBitmaps.end() && stateBitmaps[state] != nullptr)
    {
        display->drawBitmap(x, y, stateBitmaps[state], width, height, 1);
        lastState = state;
    }

    if (autoUpdateDisplay)
    {
        display->display();
    }
}

void VirtualLEDs::begin(Adafruit_SSD1306* display, uint8_t screenAddress)
{
    this->display = display;
    display->begin(SSD1306_SWITCHCAPVCC, screenAddress);
    display->clearDisplay();
}

VirtualLED& VirtualLEDs::addLED(bool autoUpdateDisplay)
{
    auto& led = leds[leds.size()];
    led.id = leds.size();
    led.display = display;
    led.autoUpdateDisplay = autoUpdateDisplay;
    return led;
}

void VirtualLEDs::show()
{
    if (display)
        display->display();
}

VirtualLED& VirtualLEDs::operator[](uint8_t id)
{
    return leds[id];
}

Adafruit_SSD1306* VirtualLEDs::getDisplay()
{
    return display;
}
#endif