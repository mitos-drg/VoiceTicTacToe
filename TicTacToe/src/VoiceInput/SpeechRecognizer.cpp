#include "SpeechRecognizer.h"

#include <pocketsphinx/pocketsphinx.h>
#include <sphinxbase/ad.h>

#include <cstdio>

SpeechRecognizer::SpeechRecognizer()
{
    m_Config = cmd_ln_init(NULL, ps_args(), TRUE,
        "-hmm", "./res/lang/en-us",
        "-kws", "./res/lang/commands.kws",
        "-dict", "./res/lang/commands.dict",
        "-bestpath", "1",
        "-logfn", "null",
        NULL);

    ps_default_search_args(m_Config);
    m_Decoder = ps_init(m_Config);

    m_AudioDevice = ad_open();

    m_nextTime = 0;
    m_currentTime = 0;
    m_bufferRead = 0;
}

SpeechRecognizer::~SpeechRecognizer()
{
    ps_free(m_Decoder);
    cmd_ln_free_r(m_Config);
    ad_close(m_AudioDevice);
}

void SpeechRecognizer::StartListening()
{
    ad_start_rec(m_AudioDevice);

    ps_start_utt(m_Decoder);
    m_uttStarted = false;
    m_inSpeech = false;

    m_currentTime = 0;
    m_nextTime = 100;

    m_result = new char[2048];
}

void SpeechRecognizer::StopListening()
{
    ad_stop_rec(m_AudioDevice);
    delete m_result;
}

void SpeechRecognizer::ProcessSpeech(int deltaTime)
{
    if (!m_speechCompleted)
        m_currentTime += deltaTime;

    m_speechCompleted = false;
    if (m_currentTime >= m_nextTime)
    {
        m_bufferRead = ad_read(m_AudioDevice, m_AudioBuffer, 2048);

        ps_process_raw(m_Decoder, m_AudioBuffer, m_bufferRead, FALSE, FALSE);

        m_inSpeech = ps_get_in_speech(m_Decoder);
        if (m_inSpeech && !m_uttStarted) {
            m_uttStarted = true;
        }

        if (!m_inSpeech && m_uttStarted) {
            /* speech -> silence transition, time to start new utterance  */
            ps_end_utt(m_Decoder);
            m_hypothesis = ps_get_hyp(m_Decoder, NULL);
            
            m_speechCompleted = true;
            if (m_hypothesis)
                strcpy(m_result, m_hypothesis);

            ps_start_utt(m_Decoder);
            m_uttStarted = false;
        }
        m_nextTime += 100;
    }
}

char* SpeechRecognizer::GetHypothesis(bool& speechReturned)
{
    speechReturned = m_speechCompleted && m_result;

    if (speechReturned)
        printf("%s\n", m_result);

    return m_result;
}

/*

static ps_decoder_t* psDecoder;
static cmd_ln_t* config;

{
    config = cmd_ln_init(NULL, ps_args(), TRUE,
        "-hmm", "../res/lang2/en-us",
        "-lm", "../res/lang2/1074.lm.bin",
        "-dict", "../res/lang2/1074.dic",
        "-bestpath", "1",
        "-logfn", "null",
        NULL);

    ps_default_search_args(config);
    psDecoder = ps_init(config);
}

void ProcessSpeech(bool* isRunning, bool* recognized, const char* hypothesis)
{
    ad_rec_t* audioDevice;
    int16_t audioBuffer[2048];
    bool uttStarted, inSpeech;
    int k;

    audioDevice = ad_open();
    ad_start_rec(audioDevice);

    ps_start_utt(psDecoder);
    uttStarted = false;

    while (*isRunning)
    {
        k = ad_read(audioDevice, audioBuffer, 2048);

        ps_process_raw(psDecoder, audioBuffer, k, FALSE, FALSE);

        inSpeech = ps_get_in_speech(psDecoder);
        if (inSpeech && !uttStarted) {
            uttStarted = true;
        }

        if (!inSpeech && uttStarted) {
            /* speech -> silence transition, time to start new utterance  */
/*ps_end_utt(psDecoder);
hypothesis = ps_get_hyp(psDecoder, NULL);
        }
        Sleep(100);
    }

    ad_close(audioDevice);
}*/