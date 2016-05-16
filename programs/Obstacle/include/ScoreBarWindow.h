#ifndef NCTU_GUI_SCORE_BAR_WINDOW_h_
#define NCTU_GUI_SCORE_BAR_WINDOW_h_

#include "NCTUGUIWindow.h"

namespace NCTU{
	class ScoreBarWindow : public GUIWindow
	{
	public:
		ScoreBarWindow();           
		virtual void drawScore(int score);
		virtual void drawTime(double seconds);
		virtual void setup();
		virtual void reset();
	protected:
		CEGUI::Window *mScoreValue;
		CEGUI::Window *mTimeValue;
	};
};
#endif
