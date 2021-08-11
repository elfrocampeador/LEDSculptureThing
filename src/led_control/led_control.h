#include <FastLED.h>

#ifndef led_control_h
#define led_control_h

#include "Arduino.h"

class LEDPanel
{
	public:
		LEDPanel(short row, short number);
		CRGB* GetLED(short x, short y);
		bool FadeToColor(short target_r, short target_g, short target_b, double duration);
	private:
		short num_strips;
		short *strip_lengths; // This will be an array num_strips long, with the number of LEDs in each strip in the panel
		short longest_strip_length;
		short *strip_start_addresses; // This will be an array num_strips long, with the row in the leds array below that each strip starts.
		CRGB **leds; // This will be a 2D array [num_strips, length_of_longest_strip].
};

#endif
