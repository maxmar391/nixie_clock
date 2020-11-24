
#include <Adafruit_NeoPixel.h>    // https://github.com/adafruit/Adafruit_NeoPixel
#include <DS3231.h>               // http://www.rinkydinkelectronics.com/library.php?id=73    ACHTUNG: Dies ist NICHT die Bibliothek, die ueber den Bibliotheksverwalter eingebunden werden kann! Ggf. vorher die andere Bibliothek entfernen oder lokalen Speicherort angeben ("")


// uint8_t = 8 unsigned bits, cross-platform data type
const uint8_t PIN = 7;       // data pin (insert 220 ohm resistor!)
const uint8_t DIGITS = 4;    // number of digits

uint32_t farbe;    // define variable to store 32 bit color value and RGB values
uint8_t red;
uint8_t green;
uint8_t blue;


// Declare NeoPixel strip object
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(DIGITS * 20, PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


//******************************************************************
// SETUP
void setup()
{
  // Initialize output pin
  pinMode(PIN, OUTPUT);

  // Initialize serial monitor
  Serial.begin(9600);           // open serial port with 9600 baud rate

  // Initialize pixels
  pixels.begin();               // Initialize the pixel array
  pixels.clear();               // Turn all pixels off
  pixels.setBrightness(255);    // Set brightness of pixels

}

//******************************************************************
// LOOP
void loop()
{
  // Initialize time module here, otherwise the "time" variable is not recognized in the loop
  DS3231  rtc(SDA, SCL);      // Initialize the DS3231 time module using the hardware interface
  Time zeit;          // Define variable for storing the time
  rtc.begin();                // Initialize the time module
  rtc.setTime(11, 59, 0);      // Set time module to 12:00:00 (24 hours format)


  while (1) // create artifical loop
  {
    zeit = rtc.getTime();     // read time

    Serial.print(zeit.hour);  // print hours
    Serial.print(":");
    Serial.print(zeit.min);   // print minutes
    Serial.println();         // print new line


    switch (zeit.hour % 6)  // Calculate hours modulo 6 to define one out of six colors, color changes thus every full hour
    {
      case 0: // red
        red = 255;
        green = 0;
        blue = 0;
        break;

      case 1: // yellow
        red = 255;
        green = 200;
        blue = 0;
        break;

      case 2: // green
        red = 0;
        green = 255;
        blue = 0;
        break;

      case 3:  // turqouise
        red = 0;
        green = 255;
        blue = 200;
        break;

      case 4: // blue
        red = 0;
        green = 0;
        blue = 255;
        break;

      case 5: // purple
        red = 136;
        green = 0;
        blue = 255;
        break;
    }

    farbe = pixels.Color(red, green, blue);    // Calculate the 32 color value from the RGB values

    pixels.clear();                                       // Clear the pixels
    pixels.setBrightness(255);                            // Set brightness of pixels
    pixels.setPixelColor(zeit.hour / 10, farbe);          // Send the first digit
    pixels.setPixelColor((zeit.hour % 10) + 10, farbe);   // Send the second digit
    pixels.setPixelColor((zeit.min / 10) + 20 , farbe);   // Send the third digit
    pixels.setPixelColor((zeit.min % 10) + 30, farbe);    // Send the fourth digit
    pixels.show();                                        // Show the digits in the pixels

    delay(10000);                       // wait for 10 seconds

  }

}
