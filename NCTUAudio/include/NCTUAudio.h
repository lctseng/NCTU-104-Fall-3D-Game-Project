#ifndef __NCTU_AUDIO_h_
#define __NCTU_AUDIO_h_

#include <AL/alut.h>
#include <string>

#include <deque>


using std::string;

namespace NCTU{
	namespace Audio{
		/*! 
		\brief Store information for a single sound playback
		*/
		struct SoundSlot{
			/*! 
			\brief OpenAL buffer
			*/
			ALuint buffer;
			/*! 
			\brief OpenAL source
			*/
			ALuint source;
			/*! 
			\brief OpenAL error
			*/
			ALenum error;
			/*! 
			\brief OpenAL status code
			*/
			ALint status;
			/*! 
			\brief whether this sound clip is in use
			*/
			bool used;
			/*! 
			\brief constrcutor
			*/
			SoundSlot():used(false){}
			/*! 
			\brief determine this sound slot is usable?
			*/
			bool usable();
		};
		/*! 
		\brief maxinum number of sound clip in the same time
		*/
		static int maxSlotsAllow = 100;
		/*! 
		\brief store all sound slot objects
		*/
		static std::deque<SoundSlot> soundSlots;
		/*! 
		\brief dedicated slot for bgm
		*/
		static SoundSlot bgmSlot;
		/*! 
		\brief whether this module is initialized or not
		*/
		static bool hasInit = false;
		/*! 
		\brief clear a specific slot
		*/
		void clearSlot(SoundSlot&);
		/*! 
		\brief play sound from file
		*/
		void playFile (const string& fileName);
		/*! 
		\brief play sound from file and store it into a slot
		*/
		void playFileInSlot (const string& fileName, SoundSlot&);
		/*! 
		\brief play SE: sound effect
		*/
		void playSE (const string& fileName);
		/*! 
		\brief play BGM: background music
		*/
		void playBGM (const string& fileName);
		/*! 
		\brief stop playing bgm and rewind
		*/
		void stopBGM ();
		/*! 
		\brief pause bgm with rewind
		*/
		void pauseBGM ();
		/*! 
		\brief resume playing of bgm
		*/
		void resumeBGM ();
		/*! 
		\brief play a test hello sound
		*/
		void playHello();
		/*! 
		\brief initialize the module
		*/
		void init(int argc, char *argv[]);
		/*! 
		\brief module cleanup
		*/
		void cleanUp();
	};
};

#endif