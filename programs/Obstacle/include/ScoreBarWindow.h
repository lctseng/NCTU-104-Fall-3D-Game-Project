#ifndef NCTU_GUI_SCORE_BAR_WINDOW_h_
#define NCTU_GUI_SCORE_BAR_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	/*! 
	\brief GUI window for score bar
	*/
	class ScoreBarWindow : public GUIWindow
	{
	public:
		/*! 
		\brief constructor
		*/
		ScoreBarWindow(); 
		/*! 
		\brief draw score on window
		*/
		virtual void drawScore(int score);
		/*! 
		\brief draw time on window
		*/
		virtual void drawTime(double seconds);
		/*! 
		\brief setup everything
		*/
		virtual void setup();
		/*! 
		\brief reset the window
		*/
		virtual void reset();
	protected:
		/*! 
		\brief pointer to the score value sub-window
		*/
		CEGUI::Window *mScoreValue;
		/*! 
		\brief pointer to the time value sub-window
		*/
		CEGUI::Window *mTimeValue;
	};
};
#endif
