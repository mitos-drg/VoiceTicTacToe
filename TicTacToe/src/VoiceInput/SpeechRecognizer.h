#pragma once

#include <pocketsphinx/pocketsphinx.h>
#include <sphinxbase/ad.h>

#include <cstdint>
#include <string>
#include <thread>

/*
	Speech recognizer abstracted from CMU Pocketsphinx library.
*/
class SpeechRecognizer
{
public:
	/* Speech recognizer constructor sets up all relevant pocketsphinx elements, but doesn't start recognition. */
	SpeechRecognizer();
	/* Cleans pocketsphinx objects. */
	~SpeechRecognizer();

	/* Start recognition */
	void StartListening();
    /* Start asynchronous recognition */
	void StartListeningAsync();
	/* Stop recognition */
	void StopListening();
    /* Stop asynchronous recognition */
	void StopListeningAsync();

	/*
		Speech processing function, the recognitions takes place here.
	*/
	void ProcessSpeech(int deltaTime);
    /*
		Asynchronous speech processing function, the recognitions takes place here.
	*/
	void ProcessSpeechAsync();
	/*
		Returns last recognized phrase.
		speechReturned - flag indicating whether in current frame new recognition result appeared.
	*/
	char* GetHypothesis(bool& speechReturned);

private:
	ps_decoder_t* m_Decoder;
	cmd_ln_t* m_Config;

    std::thread m_thread;

	ad_rec_t* m_AudioDevice;

	int16_t m_AudioBuffer[2048];
	char* m_result;
	const char* m_hypothesis;

	bool m_inSpeech = false;
	bool m_uttStarted = false;
	int m_bufferRead;

	bool m_speechCompleted = false;
    bool m_isRecognizing = false;

	int m_nextTime;
	int m_currentTime;
};