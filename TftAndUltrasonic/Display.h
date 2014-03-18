#ifndef _DISPLAY_H
#define _DISPLAY_H
//----------------
#include "Arduino.h"
#include <Adafruit_TFTLCD.h>

// lcd configuration
#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class Display
{
    public:
        Display(unsigned int maxRangeValue);
        ~Display();
        
        void Update(long newRange);
        
    private:
        void UpdateGauge(void);
        void UpdateText(void);
        void DrawStaticDisplayElements(void);
        float PixelsPerRangeUnit(void);
        
        long _range;
        long _previousRange;
        unsigned int _maxRangeValue;
        
        Adafruit_TFTLCD *_tft;
        
        static const uint16_t BackgroundColor = BLACK;
        static const uint16_t TextColor = WHITE;
        static const uint16_t GaugeColor = BLUE;
        static const uint16_t GaugeMarkerColor = RED;
        
        static const uint8_t TextSize = 4;
        static const uint8_t CountOfGaugeMarks = 10;
        static const uint8_t GaugePaddingTopBottom = 10;
        static const uint8_t GaugePaddingRight = 40;
        static const uint8_t GaugeMarksWidth = 10;
};

#endif
