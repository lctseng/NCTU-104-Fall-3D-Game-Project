#include "NCTUAudio.h"
#include "stdio.h"
#include "stdlib.h"

using namespace std;

extern bool NCTU::Audio::hasInit;

void NCTU::Audio::playFile (const string& fileName)
{
	if(!hasInit){
		return;
	}
	ALuint buffer;
	ALuint source;
	ALenum error;
	ALint status;

	/* Create an AL buffer from the given sound file. */
	buffer = alutCreateBufferFromFile (fileName.c_str());
	if (buffer == AL_NONE)
	{
		error = alutGetError ();
		fprintf (stderr, "Error loading file: '%s'\n",
			alutGetErrorString (error));
		alutExit ();
		exit (EXIT_FAILURE);
	}

	/* Generate a single source, attach the buffer to it and start playing. */
	alGenSources (1, &source);
	alSourcei (source, AL_BUFFER, buffer);
	alSourcePlay (source);

	/* Normally nothing should go wrong above, but one never knows... */
	error = alGetError ();
	if (error != ALUT_ERROR_NO_ERROR)
	{
		fprintf (stderr, "%s\n", alGetString (error));
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
	*/
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