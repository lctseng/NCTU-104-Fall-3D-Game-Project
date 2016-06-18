#ifndef NCTU_GUI_GAME_CONSOLE_WINDOW_h_
#define NCTU_GUI_GAME_CONSOLE_WINDOW_h_

#include "NCTUGUIWindow.h"


namespace NCTU{
	/*! 
	\brief GUI window fro CEGUI demo, not used in game
	*/
	class GameConsoleWindow : public GUIWindow
	{
	public:
		/*! 
		\brief constructor
		*/
		GameConsoleWindow();                   // Constructor
	protected:
		/*! 
		\brief Register our handler functions
		*/
		virtual void registerHandlers();                              // Register our handler functions
		/*! 
		\brief Handle when we press Enter after typing
		*/
		bool Handle_TextSubmitted(const CEGUI::EventArgs &e);      // Handle when we press Enter after typing
		/*! 
		\brief Handle when we press the Send button         
		*/
		bool Handle_SendButtonPressed(const CEGUI::EventArgs &e);  // Handle when we press the Send button         
		/*! 
		\brief Parse the text the user submitted.
		*/
		void ParseText(CEGUI::String inMsg);                       // Parse the text the user submitted.
		/*! 
		\brief Post the message to the ChatHistory listbox.
		*/
		void OutputText(CEGUI::String inMsg,                       // Post the message to the ChatHistory listbox.
			CEGUI::Colour colour = CEGUI::Colour( 0xFFFFFFFF)); //   with a white color default

	};
};
#endif