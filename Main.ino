#include <FastLED.h>
#include "src/led_control/led_control.h"

// Define the array of leds
LEDPanel *panels[10];

int step = 1;

void setup() 
{
	FastLED.setBrightness(255);
	
	Serial.begin(57600);
	Serial.println("resetting");
	
	
	panels[0] = new LEDPanel(1, 1);
	panels[1] = new LEDPanel(1, 2);
	panels[2] = new LEDPanel(1, 3);
	panels[3] = new LEDPanel(1, 4);
	panels[4] = new LEDPanel(1, 5);
	panels[5] = new LEDPanel(2, 1);
	panels[6] = new LEDPanel(2, 2);
	panels[7] = new LEDPanel(2, 3);
	panels[8] = new LEDPanel(2, 4);
	panels[9] = new LEDPanel(2, 5);
	
	panels[0]->ResetStatus();
	panels[1]->ResetStatus();
	panels[2]->ResetStatus();
	panels[3]->ResetStatus();
	panels[4]->ResetStatus();
	panels[5]->ResetStatus();
	panels[6]->ResetStatus();
	panels[7]->ResetStatus();
	panels[8]->ResetStatus();
	panels[9]->ResetStatus();
	
	CRGB color = CRGB::Black;
	panels[0]->SetColor(color.red, color.green, color.blue);
	panels[1]->SetColor(color.red, color.green, color.blue);
	panels[2]->SetColor(color.red, color.green, color.blue);
	panels[3]->SetColor(color.red, color.green, color.blue);
	panels[4]->SetColor(color.red, color.green, color.blue);
	panels[5]->SetColor(color.red, color.green, color.blue);
	panels[6]->SetColor(color.red, color.green, color.blue);
	panels[7]->SetColor(color.red, color.green, color.blue);
	panels[8]->SetColor(color.red, color.green, color.blue);
	
}

// What we're really going to want to do, I think, is have a master counter in the main loop, and have separate functions for each type of effect
// Each with it's own parameters or something, each maybe with different framerates so things are more dynamic, if we want.
// This example merely runs a single red pixel down the lengths of the two strips.  Just a proof of concept.
void loop() 
{ 
	// First slide the led in one direction
	Serial.println("Update Phase");

	bool done;
	CRGB color;
	
	switch(step)
	{
		case 1:
			color = CRGB::Blue;
			done = panels[0]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			panels[5]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			break;
		case 2:
			color = CRGB::Blue;
			done = panels[1]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			panels[6]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			break;
		case 3:
			color = CRGB::Blue;
			done = panels[2]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			panels[7]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			break;
		case 4:
			color = CRGB::Blue;
			done = panels[3]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			panels[8]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			break;
		case 5:
			color = CRGB::Blue;
			done = panels[4]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			panels[9]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			break;
		case 6:
			color = CRGB::Green;
			done = panels[0]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[1]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[2]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[3]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[4]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[5]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[6]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[7]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[8]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[9]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			break;
		case 7:
			color = CRGB::Red;
			done = panels[4]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			panels[9]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			break;
		case 8:
			color = CRGB::Red;
			done = panels[3]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			panels[8]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			break;
		case 9:
			color = CRGB::Red;
			done = panels[2]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			panels[7]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			break;
		case 10:
			color = CRGB::Red;
			done = panels[1]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			panels[6]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			break;
		case 11:
			color = CRGB::Red;
			done = panels[0]->WipeHorizontal(color.red, color.green, color.blue, 0, 0.5, 0);
			panels[5]->WipeHorizontal(color.red, color.green, color.blue, 1, 0.5, 0);
			break;
		case 12:
			color = CRGB::Green;
			done = panels[0]->WipeVertical(color.red, color.green, color.blue, 0, 1.0, 0);
			panels[1]->WipeVertical(color.red, color.green, color.blue, 0, 1.0, 0);
			panels[2]->WipeVertical(color.red, color.green, color.blue, 0, 1.0, 0);
			panels[3]->WipeVertical(color.red, color.green, color.blue, 0, 1.0, 0);
			panels[4]->WipeVertical(color.red, color.green, color.blue, 0, 1.0, 0);
			break;
		case 13:
			color = CRGB::Green;
			done = panels[0]->WipeVertical(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[1]->WipeVertical(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[2]->WipeVertical(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[3]->WipeVertical(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[4]->WipeVertical(color.red, color.green, color.blue, 1, 1.0, 0);
			break;
		case 14:
			color = CRGB::Brown;
			done = panels[0]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[1]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[2]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[3]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[4]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[5]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[6]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[7]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[8]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[9]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			break;
		case 15:
			color = CRGB::Purple;
			done = panels[0]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[1]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[2]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[3]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[4]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[5]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[6]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[7]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[8]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[9]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			break;
		case 16:
			color = CRGB::Black;
			done = panels[0]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[1]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[2]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[3]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[4]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[5]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[6]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[7]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[8]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			panels[9]->Explosion(color.red, color.green, color.blue, 1, 1.0, 0);
			break;
	}
	
	if(done)
	{
		step += 1;
		
		if(step > 16)
			step = 1;
	}

	FastLED.show();
	delay(1000/30);
}