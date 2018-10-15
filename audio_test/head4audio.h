#ifndef _HEAD4AUDIO_H_
#define _HEAD4AUDIO_H_

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <locale.h>
#include <sys/unistd.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <alsa/asoundlib.h>

#define WAV_FMT_PCM     0x0001

#define MIN(a, b)\
    ({\
        typeof(a) _a = a;\
        typeof(b) _b = b;\
        (void)(_a == _b);\
        _a < _b ? _a : _b;\
    })

typedef long long  off64_t;

// ================RIFF block======================
struct wav_header
{
    unit32_t id;
    unit32_t size;
    unit32_t format;
};

// ================fmt block=======================
struct wav_fmt
{
    unit32_t fmt_id;
    unit32_t fmt_size;
    unit16_t channels;
    unit32_t sample_rate;
    unit32_t byte_rate;
    unit16_t block_align;
    unit16_t bits_per_sample;
};

// ================data block======================
struct wav_data
{
    unit32_t data_id;
    unit32_t data_size;
};

// =================container======================
typedef struct
{
    struct wav_header head;
    struct wav_fmt format;
    struct wav_data data;
}wav_format;

// =================================================
typedef struct 
{
    snd_pcm_t *headle;
    snd_pcm_format_t format;

    unit16_t channels;
    size_t bits_per_sample;
    size_t bytes_per_frame;

    snd_pcm_uframes_t frames_per_period;
    snd_pcm_uframes_t frames_per_buffer;

    unit8_t *period_buf;
}pcm_container;

#endif