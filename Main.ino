#include <FastLED.h>
#include "src/led_control/led_control.h"

// Define the array of leds
LEDPanel test_panel = LEDPanel(2, 5);
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
	Serial.println("Update Phase");

	bool done;
	
	if(target == 1)
	{
		CRGB color = CRGB::Blue;
		done = test_panel.WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 5);
	}
	else if(target == 2)
	{
		CRGB color = CRGB::OrangeRed;
		done = test_panel.WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 5);
	}
	else if(target == 3)
	{
		CRGB color = CRGB::Yellow;
		done = test_panel.WipeVertical(color.red, color.green, color.blue, 1, 1.0, 0);
	}
	else if(target == 4)
	{
		CRGB color = CRGB::Green;
		done = test_panel.WipeVertical(color.red, color.green, color.blue, 0, 1.0, 0);
	}
	else if(target == 5)
	{
		CRGB color = CRGB::Blue;
		done = test_panel.WipeVertical(color.red, color.green, color.blue, 1, 1.0, 0);
	}
	else
	{
		CRGB color = CRGB::Purple;
		done = test_panel.WipeVertical(color.red, color.green, color.blue, 0, 1.0, 0);
	}
	
	if(done)
	{
		// This initialization logic should be moved into the function, somehow.
		if(target == 1)
			target = 2;
		else if(target == 2)
			target = 3;
		else if(target == 3)
			target = 4;
		else if(target == 4)
			target = 5;
		else if(target == 5)
			target = 6;
		else if(target == 6)
			target = 1;
	}

	FastLED.show();
	delay(1000/30);
}
