

#include "TutorialApplication.h"

int main(int argc, char *argv[]) {
	NCTU::Audio::init(argc,argv);
	BasicTutorial_00 app;
	app.go();  
	NCTU::Audio::cleanUp();
	return 0;
}


