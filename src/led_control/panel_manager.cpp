#include "panel_manager.h"
#include "led_control.h"

PanelManager::PanelManager()
{
	num_rows = rows;
	num_columns = columns;
	num_panels = rows * columns;
	
	Serial.begin(57600);
	Serial.println((String)" TEST");
	//Serial.println((String)" PANEL " + sizeof(LEDPanel*) + "  R " + num_rows + "  C " + num_columns);
	
	return;
	current_step = 0;
	
	short x, y;
	
	// Initialize all panels.
	for(y = 0; y < num_columns; y++)
	{
		for(x = 0; x < num_rows; x++)
		{
			Serial.println((String)" X " + x + "  Y " + y);
			panels[(num_columns * y) + x] = LEDPanel(y + 1, x + 1);
		}
	}
}

LEDPanel* PanelManager::GetPanel(short x, short y)
{
	short panel_index = (num_columns * (y-1)) + (x-1);
	return &panels[panel_index];
}

// Turn a string with multiple tokens into an array of strings.  ONLY COMPATIBLE WITH STRINGS WITH 7 TOKENS.
String* PanelManager::Tokenize(String in, char delimiter)
{
	String tokens[7];
	char *token;
	const char* inner_delimiter = (const char*)delimiter;
	
	int i = 0;
	
	token = strtok((char*)in.c_str(), inner_delimiter);
	tokens[0] = token;
	
	while(token != NULL)
	{
		token = strtok(NULL, inner_delimiter);
		tokens[i] = token;
		i += 1;
	}
	
	return tokens;
}

bool PanelManager::RunAnimation(short column, short row, String instruction)
{
	String *instruction_tokens = Tokenize(instruction, ' ');
	bool done = false;
	
	Serial.println((String)" E " + instruction_tokens[0]);
	
	if(instruction_tokens[0] == "VWIPE")
	{
		short red = (short)instruction_tokens[1].toInt();
		short green = (short)instruction_tokens[2].toInt();
		short blue = (short)instruction_tokens[3].toInt();
		bool up = (bool)instruction_tokens[4].toInt();
		double duration = (double)instruction_tokens[5].toFloat();
		short buffer0 = (short)instruction_tokens[6].toInt();
		
		LEDPanel* current_panel = GetPanel(column, row);
		done = current_panel->WipeVertical(red, green, blue, up, duration, buffer0);
	}
	else if(instruction_tokens[0] == "HWIPE")
	{
		short red = (short)instruction_tokens[1].toInt();
		short green = (short)instruction_tokens[2].toInt();
		short blue = (short)instruction_tokens[3].toInt();
		bool right = (bool)instruction_tokens[4].toInt();
		double duration = (double)instruction_tokens[5].toFloat();
		short buffer0 = (short)instruction_tokens[6].toInt();
		
		LEDPanel* current_panel = GetPanel(column, row);
		done = current_panel->WipeHorizontal(red, green, blue, right, duration, buffer0);
	}
	else if(instruction_tokens[0] == "FADE")
	{
		short red = (short)instruction_tokens[1].toInt();
		short green = (short)instruction_tokens[2].toInt();
		short blue = (short)instruction_tokens[3].toInt();
		double duration = (double)instruction_tokens[4].toFloat();
		short buffer0 = (short)instruction_tokens[5].toInt();
		
		LEDPanel* current_panel = GetPanel(column, row);
		done = current_panel->FadeToColor(red, green, blue, duration, buffer0);
	}
	else if(instruction_tokens[0] == "BOOM")
	{
		short red = (short)instruction_tokens[1].toInt();
		short green = (short)instruction_tokens[2].toInt();
		short blue = (short)instruction_tokens[3].toInt();
		bool out = (bool)instruction_tokens[4].toInt();
		double duration = (double)instruction_tokens[5].toFloat();
		short buffer0 = (short)instruction_tokens[6].toInt();
		
		LEDPanel* current_panel = GetPanel(column, row);
		done = current_panel->WipeVertical(red, green, blue, out, duration, buffer0);
	}
	else if(instruction_tokens[0] == "NoOp")
	{
		// Do Nothing!
		done = false;
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
		panel_num = (short)effects[panel_index][0].toInt();
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
				panel_num = (short)effects[panel_index][0].toInt();
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
				
				LEDPanel* current_panel = GetPanel(panel_column, panel_row);
				current_panel->ResetStatus();
			}
		}
	}
}