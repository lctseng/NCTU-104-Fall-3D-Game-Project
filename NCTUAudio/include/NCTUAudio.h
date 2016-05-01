#ifndef __NCTU_AUDIO_h_
#define __NCTU_AUDIO_h_

#include <AL/alut.h>
#include <string>

using std::string;

namespace NCTU{
	void playFile (const string& fileName);
	void playSE (const string& fileName);
	void playBGM (const string& fileName);
	void playHello();
};

#endif