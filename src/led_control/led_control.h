#include <FastLED.h>

#ifndef led_control_h
#define led_control_h

#include "Arduino.h"

class LEDPanel
{
	public:
		LEDPanel(short row, short number);
		CRGB* GetLED(short x, short y); // Convert from x, y to an index in the led strip array
		void SetColor(short target_r, short target_g, short target_b);
		
		// The following uses no buffer space
		void StaticVerticalGradient(short start_r, short start_g, short start_b, short target_y, short target_g, short target_b);
		
		// The following uses one index of buffer space
		bool WipeVertical(short target_r, short target_g, short target_b, bool go_up, double duration, short buffer0);
		bool WipeHorizontal(short target_r, short target_g, short target_b, bool go_right, double duration, short buffer0);
		bool Explosion(short target_r, short target_g, short target_b, bool go_out, double duration, short buffer0);
		// The following use three indices of buffer space
		bool FadeToColor(short target_r, short target_g, short target_b, double duration, short buffer0);
		
		void PrintGridToSerial();
		
		short status_buffer[50]; // This is bad, but a way to store context between frames.  Come up with something better.
	private:
		short num_strips;
		short *strip_lengths; // This will be an array num_strips long, with the number of LEDs in each strip in the panel
		short longest_strip_length;
		short *strip_start_addresses; // This will be an array num_strips long, with the row in the leds array below that each strip starts.
		CRGB *leds; // This will be an array of all leds (as to the board the matrix looks like one long strip).
};

#endif
