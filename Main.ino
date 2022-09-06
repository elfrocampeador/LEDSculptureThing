#include <FastLED.h>
#include "src/led_control/panel_manager.h"

int target = 1;
int upper_target = 1;
PanelManager *panel_man;

void setup() 
{
	FastLED.setBrightness(255);
	
	Serial.begin(57600);
	Serial.println("resetting");
	panel_man = new PanelManager();
}

// What we're really going to want to do, I think, is have a master counter in the main loop, and have separate functions for each type of effect
// Each with it's own parameters or something, each maybe with different framerates so things are more dynamic, if we want.
// This example merely runs a single red pixel down the lengths of the two strips.  Just a proof of concept.
void loop() 
{ 
	// First slide the led in one direction
	Serial.println("Update Phase");
	
	panel_man->CoordinateEffects();

	FastLED.show();
	delay(1000/30);
}
