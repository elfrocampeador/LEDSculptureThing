#include <FastLED.h>
#include "Arduino.h"
#include "led_control.h"

#ifndef panel_man_h
#define panel_man_h

#define ROWS 2
#define COLUMNS 5

class PanelManager
{
	public:
		PanelManager();
		LEDPanel* GetPanel(short x, short y);
		String* Tokenize(String in, char delimiter);
		bool RunAnimation(short column, short row, String instruction);
		void CoordinateEffects();
		
	private:
		short num_panels;
		short num_rows;
		short num_columns;
		
		LEDPanel* panels[ROWS * COLUMNS];
		short num_steps = 12;
		short current_step = 1;
		
		String effects[10][10] = 
		{
			// EFFECTS ENCODED AS "NAME ARG1 ARG2 ARG3..."
			// FOR NOW, ALL STRINGS MUST HAVE 7 TOKENS. ELSE THINGS WILL GET WEIRD
			// IE HWIPE 255 0 0 1 2.0 0
			// ROW 0 JUST CONTAINS EACH PANEL'S NUMBER
			{"11", "12", "13", "14", "15", "21", "22", "23", "24", "25"},
			{"HWIPE 255 0 0 1 2.0 0", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"},
			{"VWIPE 0 255 0 1 2.0 0", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"},
			{"BOOM 0 0 255 1 2.0 0", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"},
			{"FADE 255 255 255 2.0 0", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"},
			{"NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"},
			{"NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"},
			{"NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"},
			{"NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"},
			{"NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp", "NoOp"}
		};
		
};

#endif
