#ifndef __NCTU_AUDIO_h_
#define __NCTU_AUDIO_h_

#include <AL/alut.h>
#include <string>

using std::string;

namespace NCTU{
	namespace Audio{
		static bool hasInit = false;
		void playFile (const string& fileName);
		void playSE (const string& fileName);
		void playBGM (const string& fileName);
		void playHello();
		void init(int argc, char *argv[]);
		void cleanUp();
	};
};

#endif