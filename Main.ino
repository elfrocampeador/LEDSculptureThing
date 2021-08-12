#include <FastLED.h>
#include "src/led_control/led_control.h"

// How many leds per strip (With our real shapes these will not be equal, see comments in setup below
#define NUM_LEDS 60
#define NUM_STRIPS 2

// Define the array of leds
const int strip_data_pins [] = {3, 6}; // Chose some random pins here.
CRGB leds[NUM_STRIPS][NUM_LEDS];

LEDPanel test_panel = LEDPanel(1, 5);
int target = 1;

void setup() 
{
	FastLED.setBrightness(255);
	
	Serial.begin(57600);
	Serial.println("resetting");
}

// What we're really going to want to do, I think, is have a master counter in the main loop, and have separate functions for each type of effect
// Each with it's own parameters or something, each maybe with different framerates so things are more dynamic, if we want.
// This example merely runs a single red pixel down the lengths of the two strips.  Just a proof of concept.
void loop() 
{ 
	// First slide the led in one direction

	bool done;
	if(target == 1)
	{
		done = test_panel.FadeToColor(255, 0, 0, 4.0, 0);
	}
	else
	{
		done = test_panel.FadeToColor(0, 0, 255, 4.0, 0);
	}
	
	if(done)
	{
		if(target == 1)
		{
			target = 2;
			test_panel.status_buffer[0] = 255;
			test_panel.status_buffer[1] = 0;
			test_panel.status_buffer[2] = 0;
		}
		else
		{
			target = 1;
			test_panel.status_buffer[0] = 0;
			test_panel.status_buffer[1] = 0;
			test_panel.status_buffer[2] = 255;
		}
	}

	Serial.println("show");
	FastLED.show();
	delay(1000/60);
}
