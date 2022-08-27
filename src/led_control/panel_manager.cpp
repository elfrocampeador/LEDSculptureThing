#include "panel_manager.h"
#include "src/led_control/led_control.h"

PanelManager::PanelManager(short rows, short columns)
{
	num_rows = rows;
	num_columns = columns;
	num_panels = rows * columns;
	
	panels = new LEDPanel[num_rows][num_columns];
	current_step = 0;
	
	int x, y;
	// Initialize all panels.
	for(x = 0; x < num_rows; x++)
	{
		for(y = 0; y < num_columns; y++)
		{
			panels[x][y] = LEDPanel(y + 1, x + 1);
		}
	}
}

// Turn a string with multiple tokens into an array of strings.  ONLY COMPATIBLE WITH STRINGS WITH 7 TOKENS.
String* PanelManager::Tokenize(String in, char delimiter)
{
	String tokens[7];
	char *token;
	int num = 1;
	
	token = strtok(in, delimiter);
	tokens[0] = token;
	
	while(token != NULL)
	{
		token = strtok(NULL, delimiter)
		tokens[i] = token;
		i += 1;
	}
	
	return tokens;
}

bool PanelManager::RunAnimation(short column, short row, String instruction)
{
	char *instruction_tokens = Tokenize(instruction);
	bool done = False;
	
	if(instruction_tokens[0] == "VWIPE")
	{
		short red = (short)instruction_tokens[1];
		short green = (short)instruction_tokens[2];
		short blue = (short)instruction_tokens[3];
		bool up = (bool)instruction_tokens[4];
		double duration = (double)instruction_tokens[5];
		short buffer0 = (short)instruction_tokens[6];
		
		done = panels[column][row].WipeVertical(red, green, blue, up, duration, buffer0);
	}
	else if(instruction_tokens[0] == "HWIPE")
	{
		short red = (short)instruction_tokens[1];
		short green = (short)instruction_tokens[2];
		short blue = (short)instruction_tokens[3];
		bool right = (bool)instruction_tokens[4];
		double duration = (double)instruction_tokens[5];
		short buffer0 = (short)instruction_tokens[6];
		
		done = panels[column][row].WipeHorizontal(red, green, blue, right, duration, buffer0);
	}
	else if(instruction_tokens[0] == "FADE")
	{
		short red = (short)instruction_tokens[1];
		short green = (short)instruction_tokens[2];
		short blue = (short)instruction_tokens[3];
		double duration = (double)instruction_tokens[4];
		short buffer0 = (short)instruction_tokens[5];
		
		done = panels[column][row].FadeToColor(red, green, blue, duration, buffer0);
	}
	else if(instruction_tokens[0] == "BOOM")
	{
		short red = (short)instruction_tokens[1];
		short green = (short)instruction_tokens[2];
		short blue = (short)instruction_tokens[3];
		bool out = (bool)instruction_tokens[4];
		double duration = (double)instruction_tokens[5];
		short buffer0 = (short)instruction_tokens[6];
		
		done = panels[column][row].WipeVertical(red, green, blue, out, duration, buffer0);
	}
	
	return done;
}

void PanelManager::CoordinateEffects()
{
	// Loop over the effects array and instruct each panel to run the effect specified for it.
	// If any panel's RunAnimation call returns true, move on to next step
	
	short panel_num;
	short panel_index;
	short panel_row;
	short panel_column;
	bool done;
	
	for(panel_index = 0; panel_index < num_panels; panel_index++)
	{
		panel_num = (short)effects[panel_index][0];
		if(panel_num > 20)
		{
			panel_row = 2;
			panel_column = panel_num - 20;
		}
		else
		{
			panel_row = 1;
			panel_column - 10;
		}
		
		String encoded_instruction = effects[panel_index][current_step];
		done = RunAnimation(panel_column, panel_row, encoded_instruction);
		
		if(done)
		{
			if(current_step < num_steps)
				current_step += 1;
			else
				current_step = 1;
				
			// Reset all status stuff for each panel, so we don't inadvertently start in the middle of a effect or something
			for(panel_index = 0; panel_index < num_panels; panel_index++)
			{
				panel_num = (short)effects[panel_index][0];
				if(panel_num > 20)
				{
					panel_row = 2;
					panel_column = panel_num - 20;
				}
				else
				{
					panel_row = 1;
					panel_column - 10;
				}
				
				panels[panel_column][panel_row].ResetStatus();
			}
		}
	}
}