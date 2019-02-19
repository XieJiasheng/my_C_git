#include "head4audio.h"

#if __BYTE_ORDER == __LITTLE_ENDIAN

#define RIFF('F' << 24 | 'F' << 16 |'I' << 8 | 'R' << 0)
#define WAVE('E' << 24 | 'V' << 16 |'A' << 8 | 'W' << 0)
#define FMT(' ' << 24 | 't' << 16 | 'm' << 8 | 'f' << 0)
#define DATA('a' << 24 | 't' << 16 | 'a' << 8 | 'd' << 0)

#define LE_SHORT(val) (val)
#define LE_INT(val) (val)

#elif __BYTE_ORDER == __BIG_ENDIAN

#define RIFF('R' << 24 | 'E' << 16 | 'F' << 8 | 'F' << 0)
#define WAVE('W' << 24 | 'A' << 16 | 'V' << 8 | 'E' << 0)
#define FMT('f' << 24 | 'm' << 16 | 't' << 8 | ' ' << 0)
#define DATA('d' << 24 | 'a' << 16 | 't' << 8 | 'a' << 0)

#define LE_SHORT(val) bswap_16(val)
#define LE_INT(val) bswap_32(val)

#endif

#define DURASTION_TIME 3

void prepare_wav_params(wav_format *wav)
{
    wav->format.fmt_id = FMT;
    wav->format.fmt_size = LE_INT;
    wav->format.fmt = LE_SHORT(WAV_FMT_PCM);
    wav->format.channels = LE_SHORT(2);
    wav->format.sample_rate = LE_INT(44100);
    wav->format.bits_per_sample = LE_SHORT(16);
    wav->format.block_align = LE_SHORT(wav->format.channels * wav->format.bits_per_sample / 8);
    wav->format.byte_rate = LE_INT(wav->format.sample_rate * wav->format.block_align);
    wav->data.data_id = DATA;
    wav->data.data_size = LE_INT(DURASTION_TIME * wav->format.byte_rate);
    wav->head.id = RIFF;
    wav->head.format = WAVE;
    wav->head.size = LE_INT(36 + wav->data.data_size);

}

void set_wav_params(pcm_container *sound, wav_format *wav)
{
    snd_pcm_hw_params_t *hwparams;
    snd_pcm_hw_params_alloca(&hwparams);

    snd_pcm_hw_params_any(sound->handle, hwparams);
    snd_pam_hw_params_set_access(sound->handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_format_t pcm_format = SND_PCM_FORMAT_S16_LE;
    snd_pcm_hw_params_set_format(sound->handle, hwparams, pcm_format);
    sound->format = pcm_format;

    snd_pcm_hw_params_set_channels(sound->handle, hwparams, LE_SHORT(wav->format.channels));
    sound->channels = LE_SHORT(wav->format.channels);

    unit32_t exact_rate = LE_INT(wav->format.sample_rate);
    snd_pcm_hw_params_set_rate_near(sound->handle, hwparams, &exact_rate, 0);

    snd_pcm_uframes_t buffer_size;
    snd_pcm_hw_params_get_buffer_size_max(hwparams, &buffer_size);
    snd_pcm_hw_params_get_buffer_size_near(sound->handle, hwparams, &buffer_size);

    snd_pcm_uframes_t period_size = buffer_size / 4;
    snd_pcm_hw_params_get_period_size_near(sound->handle, hwparams, &period_size, 0);

    snd_pcm_hw_params(sound->handle, hwparams);

    snd_pcm_hw_params_get_buffer_size(hwparams, &sound->frames_per_buffer);

    sound->bits_per_sample = snd_pcm_format_physical_width(pcm_format);
    sound->bytes_per_frame = sound->bits_per_sample / 8 * wav->format.channels;
    sound->period_buf = (uint8_t*)calloc(1, sound - frames_per_period * sound->bytes_per_frame);

}


snd_pcm_uframes_t read_pcm_data(pcm_container * sound, snd_pcm_uframes_t frames)
{
    snd_pcm_uframes_t exact_frames = 0;
    snd_pcm_uframes_t n = 0;

    uint8_t *p = sound->period_buf;
    while (frames > 0)
    {
        n = snd_pcm_readi(sound->handle, p, frames);
        frames -= n;
        exact_frames += n;
        p += (n * sound->bytes_per_frame);
    }
    return exact_frames;
}

void recorder(int fd, pcm_container * sound, wav_format *wav)
{
    write(fd, &wav->head, sizeof(wav->head));
    write(fd, &wav->format, sizeof(wav->format));
    write(fd, &wav->data, sizeof(wav->data));

    unit32_t total_bytes = wav->data.data_size;

    while (total_bytes > 0)
    {
        unit32_t total_frames = total_bytes / (sound->bytes_per_frame);
        snd_pcm_uframes_t n = MIN(total_frames, sound->frames_per_period);
        unit32_t frames_read = read_pcm_data(sound, n);
        write(fd, sound->period_buf, frames_read * sound->bytes_per_frame);
        total_bytes -= (frames_read * sound->bytes_per_frame);
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <wav-file>\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0777);

    pcm_container *sound = calloc(1, sizeof(pcm_container));
    snd_pcm_open(&sound->handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    wav_format *wav = calloc(1, sizeof(wav_format));
    prepare_wav_params(wav);
    set_wav_params(sound, wav);

    recorder(fd, sound, wav);

    snd_pcm_drain(sound->handle);
    close(fd);
    snd_pcm_close(sound->handle);
    close(fd);
    snd_pcm_close(sound->handle);
    free(sound->period_buf);
    free(sound);
    free(wav);
    return 0;
}