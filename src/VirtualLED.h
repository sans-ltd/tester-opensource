#pragma once
#include <cstdint>
#include <map>
#define NO_ADAFRUIT_SSD1306_COLOR_COMPATIBILITY
#include <Adafruit_SSD1306.h>

/**
 * This class emulates a single RGB LED on a OLED display with icons.
 * For each color of which the app displays on the RGB LED, an icon is used on the OLED screen.
 */
class VirtualLED {
    friend class VirtualLEDs;
public:
    uint8_t id = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    uint32_t state = 0;
    std::map<uint32_t, const uint8_t*> stateBitmaps;

    void operator=(uint32_t newState);

private:
    Adafruit_SSD1306* display = nullptr;
    bool autoUpdateDisplay = false;
    uint32_t lastState = 0;
};

/**
 * This class manages multiple VirtualLED instances and the OLED display they are drawn on, like multiple RGB LEDs on a strip.
 */
class VirtualLEDs
{
public:
    VirtualLEDs();

    void begin(Adafruit_SSD1306* display, uint8_t screenAddress = 0x3C);
    VirtualLED& addLED(bool autoUpdateDisplay = false);

    void show();
    VirtualLED& operator[](uint8_t id);

    Adafruit_SSD1306* getDisplay();

private:
    std::map<uint8_t,VirtualLED> leds;
    Adafruit_SSD1306* display = nullptr;
};

