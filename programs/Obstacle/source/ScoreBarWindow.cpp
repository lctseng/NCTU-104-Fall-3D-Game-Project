#include "ScoreBarWindow.h"
#include "TutorialApplication.h"
#include <sstream>
#include <iostream>

using namespace NCTU;
using namespace std;

ScoreBarWindow::ScoreBarWindow():
GUIWindow("ScoreBar.layout")
{

}
void ScoreBarWindow::setup(){
	GUIWindow::setup();
	mScoreValue = mWindow->getChild("ScoreValue");
	mTimeValue = mWindow->getChild("TimeValue");
	drawScore(0);
	drawTime(0.0);
}
void ScoreBarWindow::drawScore(int score)
{
	std::stringstream ss;
	ss << setfill('0') << setw(10) << score;
	mScoreValue->setText(ss.str());
}
void ScoreBarWindow::drawTime(double seconds)
{
	std::stringstream ss;
	int m = seconds / 60;
	double s = seconds - m * 60;
	ss << setfill('0') << setw(2) <<  m << ':'<<  setfill('0') << setw(6)  << setprecision(3) << fixed  <<  s;
	mTimeValue->setText(ss.str());
}
void ScoreBarWindow::reset(){
	drawScore(0);
	drawTime(0.0);
}