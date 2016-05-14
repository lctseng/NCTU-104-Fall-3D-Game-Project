#ifndef NCTU_GUI_GAME_CONSOLE_WINDOW_h_
#define NCTU_GUI_GAME_CONSOLE_WINDOW_h_

#include "NCTUGUIWindow.h"


namespace NCTU{
	class GameConsoleWindow : public GUIWindow
	{
	public:
		GameConsoleWindow();                   // Constructor
	protected:
		virtual void registerHandlers();                              // Register our handler functions
		bool Handle_TextSubmitted(const CEGUI::EventArgs &e);      // Handle when we press Enter after typing
		bool Handle_SendButtonPressed(const CEGUI::EventArgs &e);  // Handle when we press the Send button         
		void ParseText(CEGUI::String inMsg);                       // Parse the text the user submitted.
		void OutputText(CEGUI::String inMsg,                       // Post the message to the ChatHistory listbox.
			CEGUI::Colour colour = CEGUI::Colour( 0xFFFFFFFF)); //   with a white color default

	};
};
#endif