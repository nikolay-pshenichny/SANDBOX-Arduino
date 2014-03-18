#include "Arduino.h"
#include "Display.h"


Display::Display(unsigned int maxRangeValue) {
    _previousRange = 0;
    _range = 0;
    _maxRangeValue = maxRangeValue;
    
    _tft = new Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
    
    Serial.println(F("TFT LCD test"));

    #ifdef USE_ADAFRUIT_SHIELD_PINOUT
        Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
    #else
      Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
    #endif
    
    _tft->reset();

    uint16_t identifier = _tft->readID();
    if (identifier == 0x9325) {
        Serial.println(F("Found ILI9325 LCD driver"));
    } else if (identifier == 0x9328) {
        Serial.println(F("Found ILI9328 LCD driver"));
    } else if (identifier == 0x7575) {
        Serial.println(F("Found HX8347G LCD driver"));
    } else {
        Serial.print(F("Unknown LCD driver chip: "));
        Serial.println(identifier, HEX);
        return;
    }
    
    _tft->begin(identifier);

    DrawStaticDisplayElements();
}


// ------------------
Display::~Display() {
    delete this->_tft;
}


// ------------------
void Display::Update(long newRange) {
    if (this->_range != newRange) {
        this->_previousRange = this->_range;
        this->_range = newRange;
        
        UpdateText();
        UpdateGauge();
    }
}


// ------------------
void Display::UpdateText(void) {
    // Erase old value from screen
      _tft->setTextSize(this->TextSize);

    if (_previousRange >= 0)
    {
      _tft->setCursor(0,0);
      _tft->setTextColor(this->BackgroundColor);
      _tft->println(_previousRange);
    }
  
    // Print out new value
    _tft->setCursor(0, 0);
    _tft->setTextColor(this->TextColor);
    _tft->print(_range);
}


// ------------------
float Display::PixelsPerRangeUnit(void)
{
    return (float)(_tft->height() - this->GaugePaddingTopBottom * 2) / _maxRangeValue;
}


// ------------------
void Display::UpdateGauge(void) {       
    unsigned int xStart = _tft->width() - this->GaugePaddingRight - this->GaugeMarksWidth * 3;
    unsigned int xEnd = _tft->width() - this->GaugePaddingRight - this->GaugeMarksWidth * 2;
    
    unsigned int yPosition;
    // erase previous marker
    if (_previousRange >= 0)
    {
       yPosition = (_previousRange * PixelsPerRangeUnit()) + this->GaugePaddingTopBottom;
       _tft->drawLine(xStart, yPosition - 5, xEnd, yPosition, this->BackgroundColor);
       _tft->drawLine(xStart, yPosition + 5, xEnd, yPosition, this->BackgroundColor);
    }
    
    // draw a new marker
     yPosition = (_range * PixelsPerRangeUnit()) + this->GaugePaddingTopBottom;
    _tft->drawLine(xStart, yPosition - 5, xEnd, yPosition, this->GaugeMarkerColor);
    _tft->drawLine(xStart, yPosition + 5, xEnd, yPosition, this->GaugeMarkerColor);
}


// ------------------
void Display::DrawStaticDisplayElements(void)
{
     // Clear screen
    _tft->fillScreen(this->BackgroundColor);
    
    // Distance Units
    _tft->setCursor(0, 0);
    _tft->setTextColor(this->TextColor);
    _tft->setTextSize(this->TextSize);
    _tft->println();
    _tft->println("cm");
    
    // Gauge
    unsigned int gaugeX = _tft->width() - this->GaugePaddingRight - this->GaugeMarksWidth;
    _tft->drawLine(gaugeX, this->GaugePaddingTopBottom, gaugeX, _tft->height() - this->GaugePaddingTopBottom, this->GaugeColor);
    
    // tick markings
    unsigned int stepSize = 40;// (_tft->height() - this->GaugePadding * 2) / CountOfGaugeMarks;
    
    for(unsigned int rangeValue = 0; rangeValue < _maxRangeValue; rangeValue += stepSize)
    {
        unsigned int xStart = _tft->width() - this->GaugePaddingRight - this->GaugeMarksWidth;
        unsigned int xEnd =   _tft->width() - this->GaugePaddingRight;
        unsigned int y = rangeValue * PixelsPerRangeUnit() + this->GaugePaddingTopBottom;
        _tft->drawLine(xStart, y, xEnd, y, this->GaugeColor);
        
        // label
        _tft->setTextSize(1);
        _tft->setCursor(xEnd + this->GaugeMarksWidth, y - 4);
        _tft->print(rangeValue);
    }
}

