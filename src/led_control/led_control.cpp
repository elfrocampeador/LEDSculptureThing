#include "led_control.h"

// Each panel is intended to be wired as a zig-zagging snake of strips oriented up and down
// With the data pin being fed from the bottom left of the panel, and then from the top of 
// Each odd numbered column to the top of the next even numbered column, and the bottom of
// Each even numbered colum to the bottom of the next odd numbered colum.
// Each panel, thus, requires only a single data pin on the arduino


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
	
	int num_leds;
	int i;
	switch(panel_number)
	{
		case 11: // Upper row, first panel
		case 12: // Upper row, second panel
		case 13: // Upper row, third panel
		case 14: // Upper row, fourth panel
		case 15: // Upper row, fifth panel
			num_strips = 9; // set panel strip count to 9
			strip_lengths = (short*)malloc(sizeof(short) * num_strips);
			strip_lengths[0] = 20;
			strip_lengths[1] = 23;
			strip_lengths[2] = 42;
			strip_lengths[3] = 46;
			strip_lengths[4] = 62;
			strip_lengths[5] = 46;
			strip_lengths[6] = 42;
			strip_lengths[7] = 23;
			strip_lengths[8] = 20;
				
			longest_strip_length = 62;
			
			// Each column (sub strip) may be of a different length (as described in strip_lengths)
			// And, thus, to establish a coherent grid, we need to know where each strip starts relative to the others.
			// Specifically, this is how far each strip starts *from the bottom*
			// Offset of 0 is for the longest column(s) as those take up the entire vertical height of the coordinate grid
			strip_start_addresses = (short*)malloc(sizeof(short) * num_strips); 
			strip_start_addresses[0] = 8;
			strip_start_addresses[1] = 6;
			strip_start_addresses[2] = 4;
			strip_start_addresses[3] = 2;
			strip_start_addresses[4] = 0;
			strip_start_addresses[5] = 2;
			strip_start_addresses[6] = 4;
			strip_start_addresses[7] = 6;
			strip_start_addresses[8] = 8;
			
			num_leds = 0;
			for(i = 0; i < num_strips; i++)
			{
				num_leds += strip_lengths[i];
			}			

			leds = (CRGB*)malloc(sizeof(CRGB*) * num_leds);
			
			for(i = 0; i < num_leds; i++)
			{
				leds[i] = CRGB(0, 0, 0);
			}
			
			// There needs to be a line here for each strip in the panel
			FastLED.addLeds<WS2812, 2, GRB>(leds, num_leds);
			
			break;
		case 21: // Lower row, first panel
		case 22: // Lower row, second panel
		case 23: // Lower row, third panel
		case 24: // Lower row, fourth panel
		case 25: // Lower row, fifth panel
			num_strips = 9; // set panel strip count to 9
			strip_lengths = (short*)malloc(sizeof(short) * num_strips);
			strip_lengths[0] = 16;
			strip_lengths[1] = 22;
			strip_lengths[2] = 27;
			strip_lengths[3] = 29;
			strip_lengths[4] = 29;
			strip_lengths[5] = 29;
			strip_lengths[6] = 27;
			strip_lengths[7] = 22;
			strip_lengths[8] = 16;
				
			longest_strip_length = 29;
			
			// Each column (sub strip) may be of a different length (as described in strip_lengths)
			// And, thus, to establish a coherent grid, we need to know where each strip starts relative to the others.
			// Specifically, this is how far each strip starts *from the bottom*
			// Offset of 0 is for the longest column(s) as those take up the entire vertical height of the coordinate grid
			strip_start_addresses = (short*)malloc(sizeof(short) * num_strips); 
			strip_start_addresses[0] = 6;
			strip_start_addresses[1] = 2;
			strip_start_addresses[2] = 0;
			strip_start_addresses[3] = 0;
			strip_start_addresses[4] = 0;
			strip_start_addresses[5] = 0;
			strip_start_addresses[6] = 0;
			strip_start_addresses[7] = 2;
			strip_start_addresses[8] = 6;
			
			num_leds = 0;
			for(i = 0; i < num_strips; i++)
			{
				num_leds += strip_lengths[i];
			}			

			leds = (CRGB*)malloc(sizeof(CRGB*) * num_leds);
			
			for(i = 0; i < num_leds; i++)
			{
				leds[i] = CRGB(0, 0, 0);
			}
			
			// There needs to be a line here for each strip in the panel
			FastLED.addLeds<WS2812, 36, GRB>(leds, num_leds);
			
			break;
	}
	for(int k = 0; k < 50; k++)
	{
		status_buffer[k] = -1;
	}
}

// Return a reference to the cell in the main led array indicated by x and y
// This will need to adjust for the fact that the strips start at different indices, are different lengths
// and are wired as a zig-zag
// If the desired LED is outside the usable bounds, return NULL.  Make sure to always check for nullness
CRGB* LEDPanel::GetLED(short x, short y)
{
	short column_max = strip_lengths[x] + strip_start_addresses[x];
	short column_start = 0;
	short true_y = y - strip_start_addresses[x];

	bool is_even = x % 2; // The first column is coordinate 0, and is thus even. Figure that.
	
	if(y < strip_start_addresses[x] || y >= column_max)
		return NULL;
	
	for(int i = 0; i < x; i++)
		column_start += strip_lengths[i];
	
	short led_index = 0;
	if(is_even)
		led_index = (column_start + strip_lengths[x] - 1) - (y - strip_start_addresses[x]);
	else
		led_index = column_start + (y - strip_start_addresses[x]);

	
	return &leds[led_index];
}

void LEDPanel::ResetStatus()
{
	int i;
	for(i = 0; i < 5; i++)
		status_buffer[i] = -1;
}

// Does what it says on the tin, really.
void LEDPanel::SetColor(short target_r, short target_g, short target_b)
{
	short x, y;
	
	for(x = 0; x < num_strips; x++)
	{
		for(y = 0; y < longest_strip_length; y++)
		{
			CRGB *current_led = GetLED(x, y);
			
			(*current_led) = CRGB(target_r, target_g, target_b);
		}
	}
}

void LEDPanel::StaticVerticalGradient(short start_r, short start_g, short start_b, short target_r, short target_g, short target_b)
{
	short step_r = ceil((((double)start_r - (double)target_r)) / (longest_strip_length / 2));
	short step_g = ceil((((double)start_g - (double)target_g)) / (longest_strip_length / 2));
	short step_b = ceil((((double)start_b - (double)target_b)) / (longest_strip_length / 2));
	
	short x, y;
	short half_length = longest_strip_length / 2;
	for(x = 0; x < num_strips; x++)
	{
		for(y = 0; y < longest_strip_length; y++)
		{
			short dist_from_center = abs(y - half_length);
			
			CRGB *current_led = GetLED(x, y);
			
			short new_r = start_r - (dist_from_center * step_r);
			short new_g = start_g - (dist_from_center * step_g);
			short new_b = start_b - (dist_from_center * step_b);
			
			//Serial.println((String)" R " + new_r + "  G " + new_g + "  B " + new_b);
			
			(*current_led) = CRGB(new_r, new_g, new_b);
		}
	}
}

// Fade from whatever the current color of each pixel in the whole panel to the target r, g, back
// Do so in approximately duration seconds.  Assumes system framerate of ~60fps (delay of 16ms between frames.  This is actually about 62fps)
// Return true when ALL current r g b values = target r g b values
bool LEDPanel::FadeToColor(short target_r, short target_g, short target_b, double duration, short buffer0)
{
	short x, y;
	bool done = true; // if ANY led is encountered that isn't at the target rgb, this will be set to false

	// Initialization, if we're just getting started
	if(status_buffer[buffer0] == -1)
	{
		CRGB *current_led = GetLED(0, 0);
		
		status_buffer[buffer0] = current_led->r;
		status_buffer[buffer0+1] = current_led->g;
		status_buffer[buffer0+2] = current_led->b;
	}

	for(x = 0; x < num_strips; x++)
	{
		for(y = 0; y < longest_strip_length; y++)
		{
			CRGB *current_led = GetLED(x, y);
			
			if(current_led != NULL)
			{
				short r_origin = status_buffer[buffer0];
				short g_origin = status_buffer[buffer0+1];
				short b_origin = status_buffer[buffer0+2];
				
				short r_dist = r_origin - target_r;
				short g_dist = g_origin - target_g;
				short b_dist = b_origin - target_b;
								
				short r_step = ceil((double)r_dist / (30.0 * duration));
				short g_step = ceil((double)g_dist / (30.0 * duration));
				short b_step = ceil((double)b_dist / (30.0 * duration));
				//Serial.println((String)" " + r_step + "   " + g_step + "   " + b_step);

				// These conditions will prevent overshooting the target
				if((short)current_led->r - r_step > 255 || (short)current_led->r - r_step < 0)
				{
					r_step = current_led->r - target_r;
				}
				if((short)current_led->g - g_step > 255 || (short)current_led->g - g_step < 0)
				{
					g_step = current_led->g - target_g;
				}
				if((short)current_led->b - b_step > 255 || (short)current_led->b - b_step < 0)
				{
					b_step = current_led->b - target_b;
				}
				//Serial.println((String)" " + r_step + "   " + g_step + "   " + b_step);
			
				if(r_step != 0 || g_step != 0 || b_step != 0) // This LED isn't done fading
				{
					done = false;
					(*current_led) = CRGB(current_led->r - r_step, current_led->g - g_step, current_led->b - b_step);
				}
			}
		}
	}
	
	if(done)
	{
		// Reset the buffers
		status_buffer[buffer0] = -1;
		status_buffer[buffer0+1] = -1;
		status_buffer[buffer0+2] = -1;
	}
	return done;
}

bool LEDPanel::WipeVertical(short target_r, short target_g, short target_b, bool go_up, double duration, short buffer0)
{
	short x, y, y_step, frame_offset;
	bool done = true; // if ANY led is encountered that isn't at the target rgb, this will be set to false
	
	y_step = ceil((double)longest_strip_length / (30.0 * duration));
	if(status_buffer[buffer0] == -1) // If we just got started
	{
		status_buffer[buffer0] = 0;
	}
	
	// Initialize
	if(go_up)
	{
		y = longest_strip_length - status_buffer[buffer0];
	}
	else
	{
		y = status_buffer[buffer0];
	}
	frame_offset = 0;
	
	
	for(frame_offset = 0; frame_offset < y_step; frame_offset++)
	{
		for(x = 0; x < num_strips; x++)
		{
			CRGB *current_led = GetLED(x, y);
			(*current_led) = CRGB(target_r, target_g, target_b);
		}
	
		status_buffer[buffer0] += 1;
		if(go_up)
		{
			y = longest_strip_length - status_buffer[buffer0];
		}
		else
		{
			y = status_buffer[buffer0];
		}
	}
	
	// If we're not done yet
	if((go_up && y >= 0) || (!go_up  && y < longest_strip_length))
	{
		done = false;
	}
	else // If we are, in fact, done
	{
		// Reset the buffer
		status_buffer[buffer0] = -1;
	}
	
	//Serial.println((String)" " + y_step + "   " + status_buffer[buffer0] + "   " + y);

	return done;
}

bool LEDPanel::WipeHorizontal(short target_r, short target_g, short target_b, bool go_right, double duration, short buffer0)
{
	short x, y, frame_number, x_limit, x_offset;
	double x_step;
	bool done = true; // if ANY led is encountered that isn't at the target rgb, this will be set to false
	
	// For this function, status buffer contains our frame number.
	
	x_step = (double)num_strips / (30.0 * duration);
	if(status_buffer[buffer0] == -1) // If we just got started
	{
		status_buffer[buffer0] = 0;
	}
	
	frame_number = status_buffer[buffer0];
	
	x_limit = ceil((double)frame_number * x_step);
	
	for(x_offset = 0; x_offset <= x_limit; x_offset++)
	{
		if(go_right)
			x = x_offset;
		else
			x = num_strips - x_offset;
		
		for(y = 0; y < longest_strip_length; y++)
		{
			CRGB *current_led = GetLED(x, y);
			(*current_led) = CRGB(target_r, target_g, target_b);
			//Serial.println((String)"X: " + x + "   Y:" + y + "   STEP: " + x_step + "   LIMIT: " + x_limit + "  FRAME: " + frame_number);
		}
	}
	
	// If we're not done yet
	if((go_right && x <= num_strips) || (!go_right && x >= 0))
	{
		done = false;
		status_buffer[buffer0] = frame_number + 1;

	}
	else // If we are, in fact, done
	{
		// Reset the buffer
		status_buffer[buffer0] = -1;
	}
	
	//Serial.println((String)" DONE: " + done);

	return done;
}

bool LEDPanel::Explosion(short target_r, short target_g, short target_b, bool go_out, double duration, short buffer0)
{
	short x, y, inverse_x, inverse_y, frame_number, x_offset, y_offset, x_limit, y_limit;
	double x_step, y_step;
	bool done = true; // if ANY led is encountered that isn't at the target rgb, this will be set to false
	
	// For this function, status buffer contains our frame number.
	
	x_step = (double)num_strips / (30.0 * duration * 2.0);
	y_step = (double)longest_strip_length / (30.0 * duration * 2.0);
	if(status_buffer[buffer0] == -1) // If we just got started
	{
		status_buffer[buffer0] = 0;
	}
	
	frame_number = status_buffer[buffer0];
	
	x_limit = ceil((double)frame_number * x_step);
	y_limit = ceil((double)frame_number * y_step);
	
	for(x_offset = 0; x_offset <= x_limit; x_offset++)
	{
		if(go_out)
		{
			x = (num_strips / 2) + x_offset;
			inverse_x = (num_strips / 2) - x_offset;
		}
		else
		{
			x = num_strips - x_offset;
			inverse_x = x_offset;
		}
		
		for(y_offset = 0; y_offset <= y_limit; y_offset++)
		{
			if(go_out)
			{
				y = (longest_strip_length / 2) + y_offset;
				inverse_y = (longest_strip_length / 2) - y_offset;
			}
			else
			{
				y = longest_strip_length - y_offset;
				inverse_y = y_offset;
			}

			CRGB *current_led = GetLED(x, y);
			(*current_led) = CRGB(target_r, target_g, target_b);
			current_led = GetLED(inverse_x, y);
			(*current_led) = CRGB(target_r, target_g, target_b);
			current_led = GetLED(x, inverse_y);
			(*current_led) = CRGB(target_r, target_g, target_b);
			current_led = GetLED(inverse_x, inverse_y);
			(*current_led) = CRGB(target_r, target_g, target_b);
			//Serial.println((String)"X: " + x + "   Y:" + y + "   STEP: " + x_step + "   LIMIT: " + x_limit + "  FRAME: " + frame_number);
		}
	}
	
	// If we're not done yet
	if(y_offset <= (longest_strip_length / 2))
	{
		done = false;
		status_buffer[buffer0] = frame_number + 1;

	}
	else // If we are, in fact, done
	{
		// Reset the buffer
		status_buffer[buffer0] = -1;
	}
	
	//Serial.println((String)" DONE: " + done);

	return done;
}

void LEDPanel::PrintGridToSerial()
{
	/*
	Scan through leds (using grid coords), and print line by line over serial
	Each led is to be represented by RRR|GGG|BBB where RRR GGG and BBB are all 0-255 values
	*/
	
	int x, y;
	Serial.println("PANELDUMP");
	for(y = 0; y < longest_strip_length; y++)
	{
		String line;
		for(x = 0; x < num_strips; x++)
		{
			CRGB *current_led = GetLED(x, y);
			if(x > 0)
				line += " ";
			
			if(current_led != NULL)
				line += (String)current_led->r + "|" + (String)current_led->g + "|" + (String)current_led->b;
			else
				line += "000|000|000";
		}
		Serial.println(line);
	}
	Serial.println("PANELDUMPCOMPLETE");
}