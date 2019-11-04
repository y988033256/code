#define DSBCAPS_CTRLDEFAULT 0x000000E0

#include "mysoundengine.h"
#include "errorlogger.h"


MySoundEngine* MySoundEngine::instance=nullptr;

MySoundEngine::MySoundEngine(HWND hwnd)
{
	m_NextSoundIndex = 1;

	MySound temp;
	temp.lpSoundBuffer=nullptr;
	temp.m_sourceFileName=L"Unknown sound";
	m_MySoundList.insert(std::pair<SoundIndex, MySound>(0, temp));

	HRESULT err;
	if (FAILED(DirectSoundCreate8(&DSDEVID_DefaultPlayback, &lpds, NULL)))
	{
		ErrorLogger::Writeln(L"Failed to create sound player");
		lpds=nullptr;
	}

	// Set cooperative level and check for error
	err=lpds->SetCooperativeLevel(hwnd, DSSCL_NORMAL);

	if (FAILED(err))	// If failed to set cooperative level
	{
		ErrorLogger::Writeln(L"Failed to set cooperative level\n");
		lpds->Release();
		lpds=nullptr;
		ErrorLogger::Writeln(ErrorString(err));
	}
}

MySoundEngine::~MySoundEngine()
{
	// Unload and release sound buffers
	UnloadAllSounds();
	// Release DirectSound
	Release();
}

ErrorType MySoundEngine::Release()
{
	if (lpds)			
	{
		lpds->Release();
		lpds=nullptr;
		return SUCCESS;
	}
	return FAILURE;
}

MySoundEngine* MySoundEngine::Start(HWND hwnd)
{
	if(instance)
	{
		instance->Terminate();
	}
	instance = new MySoundEngine(hwnd);
	return instance;
}

MySoundEngine* MySoundEngine::GetInstance()
{
	return instance;
}

ErrorType MySoundEngine::Terminate()
{
	if(instance)
	{
		delete instance;
		instance=nullptr;
		return SUCCESS;
	}
	else
		return FAILURE;
}

const wchar_t* MySoundEngine::ErrorString(HRESULT err)
{
	// Returns an error string from DirectX
	return ERRORSTRING(err);
}

MySoundEngine::MySound& MySoundEngine::FindSound(SoundIndex sound)
{
	// Find a sound in the map
	std::map<SoundIndex, MySound>::iterator it = m_MySoundList.find(sound);
	if(it  == m_MySoundList.end())			// Not found
	{
		ErrorLogger::Writeln(L"SoundIndex not found");
		// Return the sound at position 0 - has an empty sound buffer
		return m_MySoundList[0];
	}
	return it->second;
}

SoundIndex MySoundEngine::LoadWav(wchar_t* filename)
// CAUTION - Multiple early returns
{
	if(!lpds)
	{
		ErrorLogger::Writeln(L"Cannot load a sound wave - No pointer to DirectSound.");
		return 0;			// Early return  **
	}

	MySound temp;

	temp.lpSoundBuffer=nullptr;
	temp.m_sourceFileName = filename;

	DSBUFFERDESC dsbd;			// "Order form" for the sound
	WAVEFORMATEX formatdesc;	// Description of the format	
	HMMIO hWaveFile;		// Handle to the wave file
	MMCKINFO parent;		// A parent chunk (wav file data chunks)
	MMCKINFO child;			// A child chunk (wav file data chunks)

	UCHAR *tempBuffer;		// Pointer to a buffer to temporarily store sound
	UCHAR *tempPtr1;		// Pointer to first part of sound buffer
	UCHAR *tempPtr2;		// Pointer to second part of sound buffer
	DWORD length1;			// Length of first part of sound buffer
	DWORD length2;			// Length of second part of sound buffer


	parent.ckid			= (FOURCC)0;
	parent.cksize		= 0;
	parent.fccType		= (FOURCC)0;
	parent.dwDataOffset	= 0;
	parent.dwFlags		= 0;

	child=parent;

	// Open the wav file

	hWaveFile = mmioOpen(filename, NULL, MMIO_READ|MMIO_ALLOCBUF);	

	if (!hWaveFile)			// If file could not open
	{
		ErrorLogger::Write(L"Failed to open sound file ");
		ErrorLogger::Writeln(filename);
		return 0;			// Early return  **
	}

	parent.fccType=mmioFOURCC('W','A','V','E');

	if (mmioDescend(hWaveFile, &parent, NULL, MMIO_FINDRIFF))
	{
		ErrorLogger::Write(L"Couldn't find wave section in wave file ");
		ErrorLogger::Writeln(filename);

		mmioClose(hWaveFile,0);			// Error - close the wave file
		return 0;			// Early return  **
	}

	// Find the format section
	child.ckid=mmioFOURCC('f','m','t',' ');
	if (mmioDescend(hWaveFile, &child,&parent, 0)!=MMSYSERR_NOERROR)
	{
		ErrorLogger::Write(L"Couldn't find format section in wave file ");
		ErrorLogger::Writeln(filename);

		mmioClose(hWaveFile,0);			// Error - close the wave file
		return 0;			// Early return  **
	}

	// Read out the format data
	if (mmioRead(hWaveFile, (char *)&formatdesc, sizeof(formatdesc))!=sizeof(formatdesc))
	{
		ErrorLogger::Write(L"Error in wave format of ");
		ErrorLogger::Writeln(filename);

		mmioClose(hWaveFile,0);
		return 0;			// Early return  **
	}

	if (formatdesc.wFormatTag!=WAVE_FORMAT_PCM)
	{
		ErrorLogger::Write(L"Error in wave format of ");
		ErrorLogger::Writeln(filename);

		mmioClose(hWaveFile,0);
		return 0;			// Early return  **
	}

	if (mmioAscend(hWaveFile, &child, 0)!=MMSYSERR_NOERROR )
	{
		ErrorLogger::Write(L"Couldn't ascend to data chunk of ");
		ErrorLogger::Writeln(filename);

		mmioClose(hWaveFile,0);
		return 0;			// Early return  **
	}

	// Now drop into data chunk
	child.ckid=mmioFOURCC('d','a','t','a');

	if (mmioDescend(hWaveFile, &child,&parent, MMIO_FINDCHUNK)!=MMSYSERR_NOERROR)
	{
		ErrorLogger::Write(L"Couldn't find data section in wave file ");
		ErrorLogger::Writeln(filename);

		mmioClose(hWaveFile,0);			// Error - close the wave file
		return 0;			// Early return  **
	}


	

	memset(&dsbd,0,sizeof(dsbd));
	dsbd.dwSize=sizeof(dsbd);
	dsbd.dwFlags = DSBCAPS_CTRLDEFAULT;				// Default features
	dsbd.dwBufferBytes=child.cksize;				// Set bytes needed to store
	dsbd.lpwfxFormat=&formatdesc;					// The format descriptor (got earlier from the file)

	HRESULT err = lpds->CreateSoundBuffer(&dsbd,&(temp.lpSoundBuffer),NULL);
	if (FAILED(err))
	{
		temp.lpSoundBuffer=nullptr;
		ErrorLogger::Writeln(L"Could not create a sound buffer");
		ErrorLogger::Writeln(MySoundEngine::ErrorString(err));
		return 0;			// Early return  **
	}

	
	tempBuffer = (UCHAR *)malloc(child.cksize);
	mmioRead(hWaveFile, (char*)tempBuffer, child.cksize);

	// Close the file
	mmioClose(hWaveFile,0);

	// Locking the Dsound buffer

	err = temp.lpSoundBuffer->Lock(0, child.cksize, (void**) &tempPtr1,
							&length1, (void**) &tempPtr2,
							&length2, DSBLOCK_FROMWRITECURSOR);
	if(FAILED(err))
	{
		ErrorLogger::Writeln(L"Couldn't lock the sound buffer.");
		ErrorLogger::Writeln(MySoundEngine::ErrorString(err));
		free(tempBuffer);
		temp.lpSoundBuffer->Release();
		temp.lpSoundBuffer=nullptr;
		return 0;			// Early return  **
	}

	// Copy the two bits of the buffer
	memcpy(tempPtr1, tempBuffer, length1);
	memcpy(tempPtr2, tempBuffer+length1, length2);

	// Unlock the Dsound buffer
	err = temp.lpSoundBuffer->Unlock(tempPtr1,
							length1, tempPtr2,
							length2);
	if(FAILED(err))
	{
		ErrorLogger::Writeln(L"Couldn't unlock the sound buffer.");
		ErrorLogger::Writeln(MySoundEngine::ErrorString(err));
		free(tempBuffer);
		temp.lpSoundBuffer->Release();
		temp.lpSoundBuffer=nullptr;
		return 0;			// Early return  **
	}

	free(tempBuffer);

	m_MySoundList.insert(std::pair<SoundIndex, MySound>(m_NextSoundIndex, temp));

	return m_NextSoundIndex++;
}

ErrorType MySoundEngine::Unload(SoundIndex sound)
{
	std::map<SoundIndex, MySound>::iterator it = m_MySoundList.find(sound);
	MySound& sb = it->second;

	if (sb.lpSoundBuffer)				// If lpSoundBuffer is not null
	{
		sb.lpSoundBuffer->Release();	// Attempt to release it

		sb.lpSoundBuffer=nullptr;

		m_MySoundList.erase(it);

		return SUCCESS;
	}
	return FAILURE;
}

ErrorType MySoundEngine::UnloadAllSounds()
{
	ErrorType answer = SUCCESS;
	std::map<SoundIndex, MySound>::iterator it = m_MySoundList.begin();
	for(;it!= m_MySoundList.end();it++ )
	{
		MySound& sb = it->second;

		if (sb.lpSoundBuffer)				// If lpSoundBuffer is not null
		{
			sb.lpSoundBuffer->Release();	// Attempt to release it

			sb.lpSoundBuffer=nullptr;
		}
	}

	
	it = m_MySoundList.begin();
	it++;
	m_MySoundList.erase(it, m_MySoundList.end());
	return answer;
}

ErrorType MySoundEngine::SetVolume(SoundIndex sound, int volume)
{
	MySound& sb = FindSound(sound);
	if(!sb.lpSoundBuffer)
	{
		ErrorLogger::Writeln(L"Sound not found.");
		return FAILURE;
	}
	HRESULT err = sb.lpSoundBuffer->SetVolume(volume);
	if (FAILED(err))
	{
		ErrorLogger::Write(L"Failed to set volume for a sound:");
		ErrorLogger::Writeln(sb.m_sourceFileName.c_str());
		ErrorLogger::Writeln(MySoundEngine::ErrorString(err));
		return FAILURE;
	}
	return SUCCESS;
}

ErrorType MySoundEngine::SetFrequency(SoundIndex sound, int frequency)
{
	MySound& sb = FindSound(sound);

	if(!sb.lpSoundBuffer)
	{
		ErrorLogger::Writeln(L"Sound not found in SetFrequency.");
		return FAILURE;
	}
	HRESULT err = sb.lpSoundBuffer->SetFrequency(frequency);
	if (FAILED(err))
	{
		ErrorLogger::Write(L"Failed to set frequency for a sound: ");
		ErrorLogger::Writeln(sb.m_sourceFileName.c_str());
		ErrorLogger::Writeln(MySoundEngine::ErrorString(err));
		return FAILURE;
	}
	return SUCCESS;
}

ErrorType MySoundEngine::SetPan(SoundIndex sound, int pan)
{
	MySound& sb = FindSound(sound);
	if(!sb.lpSoundBuffer)
	{
		ErrorLogger::Writeln(L"Sound buffer not created.");
		return FAILURE;
	}
	HRESULT err = sb.lpSoundBuffer->SetPan(pan);
	if (FAILED(err))
	{
		ErrorLogger::Write(L"Failed to pan a sound:");
		ErrorLogger::Writeln(sb.m_sourceFileName.c_str());
		ErrorLogger::Writeln(MySoundEngine::ErrorString(err));
		return FAILURE;
	}
	return SUCCESS;
}

ErrorType MySoundEngine::Play(SoundIndex sound, bool looping)
{

	MySound& sb = FindSound(sound);

	if(!sb.lpSoundBuffer)
	{
		ErrorLogger::Writeln(L"Sound buffer not created.");
	}
	else
	{

		DWORD flag =0;
		if(looping)
		{
			flag = DSBPLAY_LOOPING;
		}
		HRESULT err = sb.lpSoundBuffer->Play(0,0, flag);
		if (FAILED(err))
		{
			ErrorLogger::Write(L"Failed to play a sound: ");
			ErrorLogger::Writeln(sb.m_sourceFileName.c_str());
			ErrorLogger::Writeln(MySoundEngine::ErrorString(err));
			return FAILURE;	
		}
		return SUCCESS;
	}	// if lpSoundBuffer not NULL
	return FAILURE;	
}

ErrorType MySoundEngine::Stop(SoundIndex sound)
{
	MySound& sb = FindSound(sound);
	if(!sb.lpSoundBuffer)
	{
		ErrorLogger::Writeln(L"Sound buffer not created.");
		return FAILURE;
	}

	HRESULT err = sb.lpSoundBuffer->Stop();
	if (FAILED(err))
	{
		ErrorLogger::Write(L"Failed to stop a sound: ");
		ErrorLogger::Writeln(sb.m_sourceFileName.c_str());
		ErrorLogger::Writeln(MySoundEngine::ErrorString(err));
		return FAILURE;
	}

	return SUCCESS;
}

