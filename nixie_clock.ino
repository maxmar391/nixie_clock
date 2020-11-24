//libraries
#include <Adafruit_NeoPixel.h>    // https://github.com/adafruit/Adafruit_NeoPixel
#include <DS3231.h>               // http://www.rinkydinkelectronics.com/library.php?id=73    ACHTUNG: Dies ist NICHT die Bibliothek, die ueber den Bibliotheksverwalter eingebunden werden kann! Ggf. vorher die andere Bibliothek entfernen oder lokalen Speicherort angeben ("")


// uint8_t = 8 unsigned bits, cross-platform data type
const int PIN = 7;       // data pin (insert 220 ohm resistor!)
const int DIGITS = 4;    // number of digits

int tens;
int mappedTens;
int ones;
int mappedOnes;


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

// definition of RGB structure with three properties
struct RGB {
  int red;
  int green;
  int blue;
};


//******************************************************************
// function to map the time input values to the correct pixels
int Mapping (int value) {

  switch (value) {
    case 0: return 5;
    case 1: return 0;
    case 2: return 6;
    case 3: return 1;
    case 4: return 7;
    case 5: return 2;
    case 6: return 8;
    case 7: return 3;
    case 8: return 9;
    case 9: return 4;
  }
}


// function to display the hours in the pixels
void DisplayHours (int hours, struct RGB* farbe) {

  tens = (int)(hours / 10);     // Extract first digit from input value by using division by 10 and convert it to integer
  mappedTens = Mapping(tens);

  ones = (int)(hours % 10);     // Extract second digit from input by using modulo 10 function and convert it to integer
  mappedOnes = Mapping(ones);

  pixels.setPixelColor(mappedTens, pixels.Color (farbe->red, farbe->green, farbe->blue));
  pixels.setPixelColor(mappedOnes + 10, pixels.Color (farbe->red, farbe->green, farbe->blue));
}


// function to display the minutes in the pixels
void DisplayMinutes (int minutes, struct RGB* farbe) {

  tens = (int)(minutes / 10);   // Extract first digit from input value by using division by 10 and convert it to integer
  mappedTens = Mapping(tens);

  ones = (int)(minutes % 10);   // Extract second digit from input by using modulo 10 function and convert it to integer
  mappedOnes = Mapping(ones);

  pixels.setPixelColor(mappedTens + 20, pixels.Color (farbe->red, farbe->green, farbe->blue));
  pixels.setPixelColor(mappedOnes + 30, pixels.Color (farbe->red, farbe->green, farbe->blue));
}




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
  // Create RGB structure here, otherwise the variable "farbe" is not recognized in the loop
  RGB farbe;

  // Initialize time module here, otherwise the "time" variable is not recognized in the loop
  DS3231  rtc(SDA, SCL);      // Initialize the DS3231 time module using the hardware interface
  Time zeit;          // Define variable for storing the time
  rtc.begin();                // Initialize the time module
  // rtc.setTime(21, 30, 0);      // Set time module to 12:00:00 (24 hours format)


  while (1) // create artifical loop
  {
    zeit = rtc.getTime();     // read time

    Serial.print(zeit.hour);  // print hours
    Serial.print(":");        // print separator
    Serial.print(zeit.min);   // print minutes
    Serial.println();         // print new line


    switch (zeit.hour % 6) // Calculate hours modulo 6 to define one out of six colors, color changes thus every full hour
	{ 
      case 0: // red
        farbe.red = 255;
        farbe.green = 0;
        farbe.blue = 0;
        break;
      case 1: // yellow
        farbe.red = 255;
        farbe.green = 200;
        farbe.blue = 0;
        break;
      case 2: // green
        farbe.red = 0;
        farbe.green = 255;
        farbe.blue = 0;
        break;
      case 3:  // turqouise
        farbe.red = 0;
        farbe.green = 255;
        farbe.blue = 200;
        break;
      case 4: // blue
        farbe.red = 0;
        farbe.green = 0;
        farbe.blue = 255;
        break;
      case 5: // purple
        farbe.red = 136;
        farbe.green = 0;
        farbe.blue = 255;
        break;
    }

    pixels.clear();                     // Clear the pixels
    pixels.setBrightness(255);          // Set brightness of pixels
    DisplayHours(zeit.hour, &farbe);    // Send the digits for hours to the pixels
    DisplayMinutes(zeit.min, &farbe);   // Send the digits for minutes to the pixels
    pixels.show();                      // Show the digits in the pixels

    delay(10000);                       // wait for 10 seconds
  }
}
