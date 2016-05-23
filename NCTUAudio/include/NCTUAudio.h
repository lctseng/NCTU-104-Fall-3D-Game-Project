#ifndef __NCTU_AUDIO_h_
#define __NCTU_AUDIO_h_

#include <AL/alut.h>
#include <string>

#include <deque>


using std::string;

namespace NCTU{
	namespace Audio{

		struct SoundSlot{
			ALuint buffer;
			ALuint source;
			ALenum error;
			ALint status;
			bool used;
			SoundSlot():used(false){}
			bool usable();
		};
		static int maxSlotsAllow = 100;
		static std::deque<SoundSlot> soundSlots;
		static SoundSlot bgmSlot;
		static bool hasInit = false;
		void clearSlot(SoundSlot&);
		void playFile (const string& fileName);
		void playFileInSlot (const string& fileName, SoundSlot&);
		void playSE (const string& fileName);
		void playBGM (const string& fileName);
		void stopBGM ();
		void pauseBGM ();
		void resumeBGM ();
		void playHello();
		void init(int argc, char *argv[]);
		void cleanUp();
	};
};

#endif