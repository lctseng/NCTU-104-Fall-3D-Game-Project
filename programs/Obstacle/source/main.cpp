

#include "TutorialApplication.h"

int main(int argc, char *argv[]) {
	alutInit (&argc, argv); // AL
	BasicTutorial_00 app;
	NCTU::playBGM("Scene6.wav");
	app.go();  
	alutExit (); // AL
	return 0;
}


