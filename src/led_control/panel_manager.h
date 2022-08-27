#include <FastLED.h>

#ifndef panel_man_h
#define panel_man_h

#include "Arduino.h"
#include "src/led_control/led_control.h"

class PanelManager
{
	public:
		PanelManager(short rows, short columns);
		String* Tokenize(String in, char delimiter);
		bool RunAnimation(short column, short row, String instruction);
		
	private:
		short num_panels;
		short num_rows;
		short num_columns;
		
		LEDPanel *panels;
		short num_steps = 12;
		short current_step = 1;
		
		String effects[10][10] = 
		{
			// EFFECTS ENCODED AS "NAME ARG1 ARG2 ARG3..."
			// FOR NOW, ALL STRINGS MUST HAVE 7 TOKENS. ELSE THINGS WILL GET WEIRD
			// IE HWIPE 255 0 0 1 2.0 0
			// ROW 0 JUST CONTAINS EACH PANEL'S NUMBER
			{"11", "12", "13", "14", "15", "21", "22", "23", "24", "25"},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""},
			{"", "", "", "", "", "", "", "", "", ""}
		};
		
};

#endif
