#pragma once
#include <string>
#include <fstream>

//header defining the class and function headers as described by soundboard stuff/rendering a stream

class AudioSource {
public:
	HRESULT LoadData(UINT32, BYTE*, DWORD*);
	HRESULT SetFormat(WAVEFORMATEX*);
	//have constructors for empty and from shell thing
	AudioSource(std::wstring);
	AudioSource();
	~AudioSource();

private:
	std::ifstream file;
};