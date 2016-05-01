#include "NCTUAudio.h"
#include "stdio.h"
#include "stdlib.h"

using namespace std;

void NCTU::playFile (const string& fileName)
{
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

void NCTU::playSE (const string& fileName){
	playFile("Audio/SE/" + fileName);
}
void NCTU::playBGM (const string& fileName){
	playFile("Audio/BGM/" + fileName);
}

void NCTU::playHello(){
	ALuint helloBuffer, helloSource;
	helloBuffer = alutCreateBufferHelloWorld ();
	alGenSources (1, &helloSource);
	alSourcei (helloSource, AL_BUFFER, helloBuffer);
	alSourcePlay (helloSource);
	alutSleep (1);
}