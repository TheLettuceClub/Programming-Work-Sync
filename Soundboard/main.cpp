#ifndef UNICODE
#define UNICODE
#endif
#define WIN32_LEAN_AND_MEAN
#include <d2d1.h>
#include <Windows.h>
#include <Windowsx.h>
#pragma comment(lib, "d2d1")
#include <shobjidl.h>
#include <array>
#include <memory>
//#include <string>
#include <wil/registry.h> //see https://github.com/microsoft/wil/wiki/Registry-Helpers later
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include "resource.h"
#include "basewin.h"
#include "AudioSource.h"

#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}

using namespace std;

class MainWindow : public BaseWindow<MainWindow>
{
	//semi-global member vars
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	HBITMAP hbm;
	array<wstring, 6> paths; //string paths to each item, retrieved from registry on launch, flushed to registry on close
	const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
	const IID IID_IAudioClient = __uuidof(IAudioClient);
	const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

	//available functions
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    OnPaint();
	void    Resize();
	HRESULT LoadPaths();
	HRESULT SavePaths();
	void InitButtons();
	HRESULT LoadNewFile(int);
	HRESULT PlaySound(int);
	AudioSource* getASfromShell(int);

public:
	//var initalization
	MainWindow()
	{
		pFactory = NULL;
		pRenderTarget = NULL;
		hbm = NULL;
	}

	//don't ever need to touch these, change the string to whatever seems right
	PCWSTR  ClassName() const { return L"Soundboard"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	MainWindow win;

	if (!win.Create(L"Soundboard by Dan", WS_OVERLAPPEDWINDOW, 0, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1))))
	{
		return -1;
	}
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	if (hAccel == NULL) {
		return -1;
	}
	ShowWindow(win.Window(), nCmdShow);

	// Run the message loop.
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(win.Window(), hAccel, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		DiscardGraphicsResources();
		SafeRelease(&pFactory);
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
		{
			return -1;  // Fail CreateWindowEx.
		}
		InitButtons();
		return 0;

	case WM_PAINT:
		OnPaint();
		return 0;

	case WM_SIZE:
		Resize();
		return 0;

	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED) {
			wchar_t text[2]{ 0 };
			HWND hButton = (HWND)lParam;
			Button_GetText(hButton, text, 2);
			switch (text[0]) {
			case '0':
				//play first sound
				break;

				//repeat
			}
			//determine the sound associated with the button and play it
		}
		switch (LOWORD(wParam)) {
		case ID_ACCELERATOR40001:
			//play the sound
			break;
			//replicate for 40001 through 40006

		case ID_FILE_SETSOUNDFORBUTTON1:
			OutputDebugString(L"menu item 1\r\n");
			LoadNewFile(0);
			break;
		}
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

//my stuff
void MainWindow::InitButtons() {
	hbm = LoadBitmap((HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDB_BITMAP1));
	for (int i = 0; i < 6; i++) {
		HWND hwndButton = CreateWindowEx(0L, L"BUTTON", L"0"/*(const wchar_t*)i*/, WS_VISIBLE | WS_CHILD | BS_BITMAP, 40 + (55 * i), 40, 50, 50, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
		SendMessage(hwndButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);
	}
}

HRESULT MainWindow::LoadNewFile(int whichButton) {
	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) {
		return E_FAIL;
	}
	IFileOpenDialog* pFileOpen;
	if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen)))) { //actually create it
		if (SUCCEEDED(pFileOpen->Show(NULL))) { //tell the dialog to show, with no owner
			IShellItem* pItem;
			if (SUCCEEDED(pFileOpen->GetResult(&pItem))) { //get the item the user selects?
				PWSTR pszFilePath;
				if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath))) { //get path of file
					paths[whichButton] = *pszFilePath;
					//MessageBox(NULL, pszFilePath, L"File Path", MB_OK); //display to user
					CoTaskMemFree(pszFilePath); //free vars
				}
				pItem->Release();
			}
		}
		pFileOpen->Release();
	}
	CoUninitialize();
}

HRESULT MainWindow::PlaySound(int whichButton) {
	HRESULT hr;
	REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
	REFERENCE_TIME hnsActualDuration;
	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioClient* pAudioClient = NULL;
	IAudioRenderClient* pRenderClient = NULL;
	WAVEFORMATEX* pwfx = NULL;
	UINT32 bufferFrameCount;
	UINT32 numFramesAvailable;
	UINT32 numFramesPadding;
	BYTE* pData;
	DWORD flags = 0;
	AudioSource* pMySource = new AudioSource(paths[whichButton]);

	hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		(void**)&pEnumerator);
	EXIT_ON_ERROR(hr)

		hr = pEnumerator->GetDefaultAudioEndpoint(
			eRender, eConsole, &pDevice);
	EXIT_ON_ERROR(hr)

		hr = pDevice->Activate(
			IID_IAudioClient, CLSCTX_ALL,
			NULL, (void**)&pAudioClient);
	EXIT_ON_ERROR(hr)

		hr = pAudioClient->GetMixFormat(&pwfx);
	EXIT_ON_ERROR(hr)

		hr = pAudioClient->Initialize(
			AUDCLNT_SHAREMODE_SHARED,
			0,
			hnsRequestedDuration,
			0,
			pwfx,
			NULL);
	EXIT_ON_ERROR(hr)

		// Tell the audio source which format to use.
		hr = pMySource->SetFormat(pwfx);
	EXIT_ON_ERROR(hr)

		// Get the actual size of the allocated buffer.
		hr = pAudioClient->GetBufferSize(&bufferFrameCount);
	EXIT_ON_ERROR(hr)

		hr = pAudioClient->GetService(
			IID_IAudioRenderClient,
			(void**)&pRenderClient);
	EXIT_ON_ERROR(hr)

		// Grab the entire buffer for the initial fill operation.
		hr = pRenderClient->GetBuffer(bufferFrameCount, &pData);
	EXIT_ON_ERROR(hr)

		// Load the initial data into the shared buffer.
		hr = pMySource->LoadData(bufferFrameCount, pData, &flags);
	EXIT_ON_ERROR(hr)

		hr = pRenderClient->ReleaseBuffer(bufferFrameCount, flags);
	EXIT_ON_ERROR(hr)

		// Calculate the actual duration of the allocated buffer.
		hnsActualDuration = (double)REFTIMES_PER_SEC *
		bufferFrameCount / pwfx->nSamplesPerSec;

	hr = pAudioClient->Start();  // Start playing.
	EXIT_ON_ERROR(hr)

		// Each loop fills about half of the shared buffer.
		while (flags != AUDCLNT_BUFFERFLAGS_SILENT)
		{
			// Sleep for half the buffer duration.
			Sleep((DWORD)(hnsActualDuration / REFTIMES_PER_MILLISEC / 2));

			// See how much buffer space is available.
			hr = pAudioClient->GetCurrentPadding(&numFramesPadding);
			EXIT_ON_ERROR(hr)

				numFramesAvailable = bufferFrameCount - numFramesPadding;

			// Grab all the available space in the shared buffer.
			hr = pRenderClient->GetBuffer(numFramesAvailable, &pData);
			EXIT_ON_ERROR(hr)

				// Get next 1/2-second of data from the audio source.
				hr = pMySource->LoadData(numFramesAvailable, pData, &flags);
			EXIT_ON_ERROR(hr)

				hr = pRenderClient->ReleaseBuffer(numFramesAvailable, flags);
			EXIT_ON_ERROR(hr)
		}

	// Wait for last data in buffer to play before stopping.
	Sleep((DWORD)(hnsActualDuration / REFTIMES_PER_MILLISEC / 2));

	hr = pAudioClient->Stop();  // Stop playing.
	EXIT_ON_ERROR(hr)

		Exit:
	CoTaskMemFree(pwfx);
	SAFE_RELEASE(pEnumerator)
		SAFE_RELEASE(pDevice)
		SAFE_RELEASE(pAudioClient)
		SAFE_RELEASE(pRenderClient)

		return hr;
}

AudioSource* MainWindow::getASfromShell(int which) {
	//convert shell to AudioSource by creating a pointer to a thing or fuckin whatever
	return NULL;
}

//necessary for painting
HRESULT MainWindow::CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &pRenderTarget);

	}
	return hr;
}

void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
}

void MainWindow::OnPaint()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);
		pRenderTarget->BeginDraw();
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		//other drawing
		pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(m_hwnd, &ps);
	}
}

void MainWindow::Resize()
{
	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		pRenderTarget->Resize(size);
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

