#include <Adafruit_NeoPixel.h>

// Example to control LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 60;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 6;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(nLEDs, dataPin, NEO_GRB + NEO_KHZ800);

void setup() {

  
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
  
}



void loop() {

  int seq = random(1, 14);

  
  if (seq == 1)
  {
      collideMain();
  }
  else if (seq == 2)
  {
      randomIt();
  }
  else if (seq == 3)
  {
      colorChaseMain();
  }
  else if (seq == 4)
  {
      setColor(strip.Color(127,   0,   0), 500);
  }
  else if (seq == 5)
  {
      xmasBlink();
  }
  else if (seq == 6)
  {
      xmasChaseMain();
  }
  else if (seq == 7)
  {
      chanuChaseMain();
  }
  else if (seq == 8)
  {
      colorWipe(strip.Color(  0, 127,   0), 50);  // Green
  }
  else if (seq == 9)
  {
      int wait = random(5, 20);
      rainbow(wait);
  }
  else if (seq == 10)
  {
      rainbowCycle(0);  // make it go through the cycle fairly fast
  }
  else if (seq == 11)
  {
      delay(4000);
  }
  else if (seq == 12)
  {
      randomBlink();
  }
  else if (seq == 13)
  {
      chanuBlink();
  }
}

void colorChaseMain()
{
  int count = random(1, 6);
  int wait = random(40, 80);
  
  for (int i=0; i<count; i++)
  {
      // Send a simple pixel chase in...
      int r = random(0, 2);
      int g = random(0, 2);
      int b = random(0, 2);
  
      colorChase(strip.Color(127 * r, 127 * g, 127 * b), wait); 
  }
}

void blinkMain()
{
    int wait = random(50, 100);
    int count = random(2,7);
    blinkIt(strip.Color(127,   0,   0),  wait, count);
    blinkIt(strip.Color(0,   127,   0),  wait, count);
}

void xmasChaseMain()
{
    int wait = random(30, 100);
    xmasChase(strip.Color(127,   0,   0), strip.Color(0,   127,   0), wait, false, true);
    xmasChase(strip.Color(127,   0,   0), strip.Color(0,   127,   0), wait, true, true);
}

void chanuChaseMain()
{
    int wait = random(30, 100);
  xmasChase(strip.Color(0,   0,   127), strip.Color(127,   127,   127), wait, false, true);
  xmasChase(strip.Color(0,   0,   127), strip.Color(127,   127,   127), wait, true, true);
}


void setColor(uint32_t c, int wait)
{
    // Start by turning all pixels off:
    for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
    
     for (int j=0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, c);
    }
    strip.show(); 
    delay(wait);
}

void randomIt()
{
    int count = random(1, 33);

    // Start by turning all pixels off:
    for(int j=0; j<strip.numPixels(); j++) 
      strip.setPixelColor(j, 0);
      
    for (int i=0; i<count; i++)
    {
          int wait = random(50, 1000);
          int r = random(0, 127);
          int g = random(0, 127);
          int b = random(0, 127);
          int cell = random(0, 32);
          strip.setPixelColor(cell, strip.Color(r,g,b));
          strip.show(); 
          delay(wait);
    }
}

void randomBlink()
{
    int count = random(1, 32);

    // Start by turning all pixels off:
    for(int j=0; j<strip.numPixels(); j++) 
      strip.setPixelColor(j, 0);
      
    for (int i=0; i<count; i++)
    {
          int wait = random(50, 80);
          int r = random(0, 2) * 127;
          int g = random(0, 2) * 127;
          int b = random(0, 2) * 127;
          
          int cell = random(0, 32);
          strip.setPixelColor(cell, strip.Color(r,g,b));
          strip.setPixelColor(cell+1, strip.Color(r,g,b));
          strip.show(); 
          delay(wait);
          strip.setPixelColor(cell, 0);
          strip.setPixelColor(cell+1, 0);
          strip.show(); 
          delay(wait);
          strip.setPixelColor(cell, strip.Color(r,g,b));
          strip.setPixelColor(cell+1, strip.Color(r,g,b));
          strip.show(); 
          delay(wait);
          strip.setPixelColor(cell, 0);
          strip.setPixelColor(cell+1, 0);
          strip.show(); 
          delay(wait);
    }
}

void xmasBlink()
{
  int count = random(2, 8);
  int wait = random(100, 500);
  
  for (int i=0; i < count; i++)
  {
    blinkIt(strip.Color(127,   0,   0),  wait, 1);
    blinkIt(strip.Color(0,   127,   0),  wait, 1);
  }
}

void chanuBlink()
{
  int count = random(2, 8);
  int wait = random(100, 500);
  
  for (int i=0; i < count; i++)
  {
    blinkIt(strip.Color(127,   127,   127),  wait, 1);
    blinkIt(strip.Color(0,   0,   127),  wait, 1);
  }
}

// Fill the dots progressively along the strip.
void blinkIt(uint32_t c, int theWait, int theCount) {
 
  for (int i=0; i < theCount; i++)
  {
    // Start by turning all pixels off:
    for(int j=0; j<strip.numPixels(); j++) 
      strip.setPixelColor(j, 0);
      
    strip.show();
    delay(theWait);
    
    for (int j=0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, c);
    }
    
    strip.show();
    delay(theWait);
  }

}


void xmasChase(uint32_t c1, uint32_t c2, uint32_t wait, bool back, bool cleanUp) {
  int i, j;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    if (back)
     j = strip.numPixels() - i;
    else
      j =  i;
    
    strip.setPixelColor(j, c1); // Set new pixel 'on'
    if (i > 0)
      strip.setPixelColor(j-1, c2); // Set new pixel 'on'
      
    strip.show();              // Refresh LED states
    
    if (cleanUp)
    {
      strip.setPixelColor(j, 0); // Erase pixel, but don't refresh!
      if (i > 0)
        strip.setPixelColor(j-1, 0); // Set new pixel 'on'
    }
    
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}




void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Fill the dots progressively along the strip.
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}


void collideMain()
{
  int count = random(1, 6);
  
  for (int i=0; i<1; i++)
  {
    collide(strip.Color(127,   0,   0));
  }
}

// Chase one dot down the full strip.
void collide(uint32_t c) {
  int i;
  int wait = random(20, 70);
  
  // Start by turning all pixels off:
  for(i=0; i < strip.numPixels(); i++) 
    strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.setPixelColor(strip.numPixels() - i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    strip.setPixelColor(strip.numPixels() - i, 0); // Set new pixel 'on'
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}

/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}
