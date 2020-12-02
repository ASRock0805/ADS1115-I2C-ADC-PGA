/*
 * ADS1115 Analog to Digital Converter
 *
 * Address pin (ADDR) connected to ground: Address 0x48 (1001000)
 * 
   | Arduino | A4   - SDA (Serial Data Line)  --- SDA  |         |
   |   UNO   | A5   - SCL (Serial Clock Line) --- SCL  | ADS1115 |
   |         | GND                            --- ADDR |         |
   |         | 3.3V                           --- A0   |         |
*/

/*--- Preprocessor ---*/
#include <Wire.h>             // For I^2C communication
#include <Adafruit_ADS1015.h> // Import the Adafruit_ADS1x15 library

/*--- Constants ---*/
const unsigned long baudSpeed = 115200;	// Sets the data rate in bits per second (baud) for serial data transmission

/*--- Constructor ---*/
Adafruit_ADS1115 ads(0x48);   // Construct an ADS1115 at address 0x48

/*--- Global Variables ---*/
float vOut = 0.0;             // Output of the ADC

/*--- Initialization ---*/
void setup(void) {
  Serial.begin(baudSpeed);  // Initializes serial port
	ads.begin();              // Initializes ADC
}

/*--- Running ---*/
void loop(void) {
	int16_t adc0;	// Read from the ADC, we have a sixteen bit integer as a result
								// ADC Range: +/- 6.144 V (1 bit = 3 mV)
								// Signed range of integer values in 16-bit = +/- 32767 (2^15 - 1)
								// Scale factor = 6.144 V / 32767 = 0.1875 mV/bit
	adc0 = ads.readADC_SingleEnded(0);
	vOut = (adc0 * 0.1875) / 1000;	// Convert ADS1115 raw reading into a voltage

	// Print the results to the Serial Monitor
	Serial.print("A0: "); 
	Serial.println(adc0);
	Serial.print("Voltage: ");
	Serial.print(vOut, 4);              
	Serial.println(" V");
  delay(1000);                    // Delay in between reads for stability
}
