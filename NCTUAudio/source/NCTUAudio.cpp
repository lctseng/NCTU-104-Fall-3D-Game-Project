#include "NCTUAudio.h"
#include "stdio.h"
#include "stdlib.h"

using namespace std;

extern bool NCTU::Audio::hasInit;


bool NCTU::Audio::SoundSlot::usable(){
	if(!used){
		return true;
	}
	// check status
	alGetSourcei (source, AL_SOURCE_STATE, &status);
	if(status == AL_PLAYING){
		return false;
	}
	alSourcei(source,AL_BUFFER,0);
    alDeleteSources(1,&source);
	alDeleteBuffers(1,&buffer);
	used = false;
	return true;
}

void NCTU::Audio::playFileInSlot (const string& fileName, SoundSlot& slot){
	if(!hasInit){
		return;
	}
	slot.used = true;
	/* Create an AL buffer from the given sound file. */
	slot.buffer = alutCreateBufferFromFile (fileName.c_str());
	if (slot.buffer == AL_NONE)
	{
		slot.error = alutGetError ();
		fprintf (stderr, "Error loading file: '%s'\n",
			alutGetErrorString (slot.error));
		alutExit ();
		exit (EXIT_FAILURE);
	}

	/* Generate a single source, attach the buffer to it and start playing. */
	alGenSources (1, &slot.source);
	alSourcei (slot.source, AL_BUFFER, slot.buffer);
	alSourcePlay (slot.source);


	/* Normally nothing should go wrong above, but one never knows... */
	slot.error = alGetError ();
	if (slot.error != ALUT_ERROR_NO_ERROR)
	{
		fprintf (stderr, "%s\n", alGetString (slot.error));
		alutExit ();
		exit (EXIT_FAILURE);
	}


	/* Check every 0.1 seconds if the sound is still playing. */
	/*
	do
	{
	alutSleep (0.1f);
	alGetSourcei (source, AL_SOURCE_STATE, &status);
	}
	while (status == AL_PLAYING);

	alSourcei(source,AL_BUFFER,0);
    alDeleteSources(1,&source);
	alDeleteBuffers(1,&buffer);
	*/
}

void NCTU::Audio::playFile (const string& fileName)
{
	if(!hasInit){
		return;
	}
	// find a slot
	int i,slotIndex = -1;
	for(i=0;i<soundSlots.size();i++){
		if(soundSlots[i].usable()){
			slotIndex = i;
			break;
		}
	}
	if(slotIndex < 0 && soundSlots.size() < maxSlotsAllow){
		slotIndex = soundSlots.size();
		soundSlots.push_back(SoundSlot());
	}
	if(slotIndex >= 0){
		playFileInSlot(fileName,soundSlots[slotIndex]);
	}
	else{
		//fprintf (stderr, "Not Enough Sound Slot\n");
	}
	
}

void NCTU::Audio::playSE (const string& fileName){
	playFile("Audio/SE/" + fileName);
}
void NCTU::Audio::playBGM (const string& fileName){
	playFile("Audio/BGM/" + fileName);
}

void NCTU::Audio::playHello(){
	if(!hasInit){
		return;
	}
	ALuint helloBuffer, helloSource;
	helloBuffer = alutCreateBufferHelloWorld ();
	alGenSources (1, &helloSource);
	alSourcei (helloSource, AL_BUFFER, helloBuffer);
	alSourcePlay (helloSource);
	alutSleep (1);
}

void NCTU::Audio::init(int argc, char *argv[]){
	alutInit (&argc, argv);
	hasInit = true;
}
void NCTU::Audio::cleanUp(){
	if(!hasInit){
		return;
	}
	alutExit (); 
	hasInit = false;
}