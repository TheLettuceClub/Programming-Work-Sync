#include "AudioSource.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Audioclient.h>
#include <mfmediaengine.h>
#include <mfapi.h>

//actully make the functions defined in the header
using namespace std;

//writes a set number of audio frames to a buffer
//if able to write at least 1 frame of data, puts 0 in flags
//else, write AUDCLNT_BUFFERFLAGS_SILENT
HRESULT AudioSource::LoadData(UINT32 numFrames, BYTE* buf, DWORD* flags)
{
	return E_NOTIMPL;
}

//specifies format for loaddata to use
HRESULT AudioSource::SetFormat(WAVEFORMATEX* format)
{
	return E_NOTIMPL;
}

AudioSource::AudioSource(wstring path)
{
	file.open(path, ifstream::beg|ifstream::binary|ifstream::in);
}

AudioSource::AudioSource()
{
	MFStartup(MF_VERSION);
	IMFAttributes* thingy = NULL;
	MFCreateAttributes(&thingy, 1);
	thingy->
	IMFMediaEngineClassFactory::CreateInstance(MF_MEDIA_ENGINE_AUDIOONLY, );
}

AudioSource::~AudioSource() {
	file.close();
	MFShutdown();
}
