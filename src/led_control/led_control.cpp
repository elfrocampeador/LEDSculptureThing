#include "led_control.h"

// Unfortunately, the way FastLED is set up makes this quite awkward.
// We can't specify pin numbers by variable, so we're going to have to make this constructor super ugly
// Seriously, this mess is going to use up kilobytes of our really limited RAM
LEDPanel::LEDPanel(short row, short number)
{
	short panel_number = (row * 10) + number;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// TO DO: FILL IN APPROPRIATE VALUES FOR ALL THIS, AND THEN INEVITABLY REWRITE IT AS IT IS A HORRIBLE KLUDGE
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	switch(panel_number)
	{
		case 11: // Upper row, first panel
		case 12: // Upper row, second panel
		case 13: // Upper row, third panel
		case 14: // Upper row, fourth panel
		case 15: // Upper row, fifth panel
			num_strips = 2; // set panel strip count to 6
			strip_lengths = (short*)malloc(sizeof(short) * num_strips);
			strip_lengths[0] = 60;
			strip_lengths[1] = 30;
			
			longest_strip_length = 60;
			
			strip_start_addresses = (short*)malloc(sizeof(short) * num_strips);
			strip_start_addresses[0] = 0;
			strip_start_addresses[1] = 0;
			
			//leds = (CRGB*)malloc(sizeof(CRGB) * num_strips * longest_strip_length);
			
			int i, j;
			leds = (CRGB**)malloc(sizeof(CRGB*) * num_strips);
			for(i = 0; i < num_strips; i++)
			{
				leds[i] = (CRGB*)malloc(sizeof(CRGB) * longest_strip_length);
				for(j = 0; j < longest_strip_length; j++)
				{
					leds[i][j] = CRGB(0, 0, 0);
				}
			}
			
			// There needs to be a line here for each strip in the panel
			FastLED.addLeds<WS2812, 3, GRB>(leds[0], strip_lengths[0]);
			FastLED.addLeds<WS2812, 4, GRB>(leds[1], strip_lengths[1]);
			//FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[2], strip_lengths[2]);
			//FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[3], strip_lengths[3]);
			//FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[4], strip_lengths[4]);
			//FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[5], strip_lengths[5]);
		/*case 21: // Lower row, first panel
		case 22: // Lower row, second panel
		case 23: // Lower row, third panel
		case 24: // Lower row, fourth panel
		case 25: // Lower row, fifth panel
			num_strips = 6; // set panel strip count to 6
			short (*tmp_strip_lengths)[] = {FILL THIS IN};
			strip_lengths = tmp_strip_lengths; // This is probably bad, I haven't had to do something this weird in years
			
			longest_strip_length = FILL THIS IN;
			
			short (*tmp_strip_start_addresses)[] = {FILL THIS IN};
			strip_start_addresses = tmp_strip_start_addresses;
			
			CRGB (*tmp_leds)[num_strips][longest_strip_length];
			leds = tmp_leds;
			
			// There needs to be a line here for each strip in the panel
			FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[0], strip_lengths[0]);
			FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[1], strip_lengths[1]);
			FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[2], strip_lengths[2]);
			FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[3], strip_lengths[3]);
			FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[4], strip_lengths[4]);
			FastLED.addLeds<WS2812, FILL THIS IN, GRB>(leds[5], strip_lengths[5]);*/
	}
}

// Return a reference to the cell in the main leds 2D array indicated by x and y
// This will adjust for the fact that different strips start at different indices and are different lengths
// If the desired LED is outside the usable bounds, return NULL.  Make sure to always check for nullness
CRGB* LEDPanel::GetLED(short x, short y)
{
	short true_y = y - strip_start_addresses[x];
	
	if(true_y < 0 || true_y >= strip_lengths[x])
		return NULL;
	
	return &leds[x][true_y];
}

// Fade from whatever the current color of each pixel in the whole panel to the target r, g, back
// Do so in approximately duration seconds.  Assumes system framerate of ~60fps (delay of 16ms between frames.  This is actually about 62fps)
// Return true when ALL current r g b values = target r g b values
bool LEDPanel::FadeToColor(short target_r, short target_g, short target_b, double duration)
{
	short x, y;
	bool done = true; // if ANY led is encountered that isn't at the target rgb, this will be set to false
	
	for(x = 0; x < num_strips; x++)
	{
		for(y = 0; y < longest_strip_length; y++)
		{
			CRGB *current_led = GetLED(x, y);
			
			if(current_led != NULL)
			{
				/*int r_dist = current_led->r - target_r;
				int g_dist = current_led->g - target_g;
				int b_dist = current_led->b - target_b;
				int r_step = ceil(((double)current_led->r - (double)target_r) / 60.0);
				int g_step = ceil(((double)current_led->g - (double)target_g) / 60.0);
				int b_step = ceil(((double)current_led->b - (double)target_b) / 60.0);
									
				// These conditions will prevent overshooting the target
				if(abs8(r_step) >= abs(r_dist))
					r_step = r_dist;
				if(abs8(g_step) >= abs(g_dist))
					g_step = g_dist;
				if(abs8(b_step) >= abs(b_dist))
					b_step = b_dist;
					*/
				
				short r_step = -1;
				short g_step = 0;
				short b_step = 0;
			
				Serial.println("HI");
				if(leds[0][5].r == 50)
					return true;
			
				if(r_step != 0 || g_step != 0 || b_step != 0) // This LED isn't done fading
				{
					done = false;
					//(*current_led) = CRGB(qsub8(current_led->r, r_step), qsub8(current_led->g, g_step), qsub8(current_led->b, b_step));
					(*current_led) = CRGB(current_led->r - r_step, current_led->g - g_step, current_led->b - b_step);
				}
			}
		}
	}

	return done;
}