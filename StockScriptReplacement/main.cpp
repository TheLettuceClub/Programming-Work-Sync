#ifndef UNICODE
#define UNICODE
#endif
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "json.hpp"
#include <codecvt>
#include <d2d1.h>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <Windows.h>
#pragma comment(lib, "d2d1")

#include "basewin.h"
#include "AVW_StockTimeSeries.h"

using namespace std;
using json = nlohmann::json;

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}

struct Holding {
	string ticker;
	int amount = 1;

	Holding(string t, int a) {
		ticker = t;
		if (a != 1) {
			amount = a;
		}
	}
};

class MainWindow : public BaseWindow<MainWindow>
{
	//semi-global member vars
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	//HWND testOutput;
	HWND editButton;
	HWND displayButton;
	fstream holdingsFile;
	list<HWND> textList;
	list<shared_ptr<Holding>> holdingsList;

	//available functions
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    OnPaint();
	void    Resize();
	void OnEditClick();
	void ParseDataFile();
	void OnDisplayClick();
	string ParseAV(string, int);
	void InitTextBoxes();

public:
	//var initalization
	MainWindow()
	{
		pFactory = NULL;
		pRenderTarget = NULL;
		//testOutput = NULL;
		editButton = NULL;
		displayButton = NULL;
	}

	//don't ever need to touch these, change the string to whatever seems right
	PCWSTR  ClassName() const { return L"StockViewer"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	MainWindow win;

	if (!win.Create(L"Stock Data Viewer", WS_OVERLAPPEDWINDOW))
	{
		return -1;
	}

	ShowWindow(win.Window(), nCmdShow);

	// Run the message loop.
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
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
		editButton = CreateWindow(L"BUTTON", L"Edit Holdings", WS_VISIBLE | WS_CHILD, 20, 20, 100, 25, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
		displayButton = CreateWindow(L"BUTTON", L"Display Stock Info", WS_VISIBLE | WS_CHILD, 125, 20, 150, 25, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
		ParseDataFile();
		InitTextBoxes();
		return 0;

	case WM_PAINT:
		OnPaint();
		return 0;

	case WM_SIZE:
		Resize();
		return 0;

	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			HWND hButton = (HWND)lParam;
			if (hButton == editButton) {
				OnEditClick();
				return 0;
			}
			else if (hButton == displayButton) {
				OnDisplayClick();
				return 0;
			}
		}
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

//stuff here
static wstring utf8_to_wstring(const string& str) {
	//this relies on deprecated shit but there really isn't a better way to do this
	wstring_convert<codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}

static string wstring_to_utf8(const wstring& str) {
	wstring_convert<codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

static HWND get(list<HWND> _list, int _i) {
	list<HWND>::iterator it = _list.begin();
	for (int i = 0; i < _i; i++) {
		++it;
	}
	return *it;
}

static shared_ptr<Holding> get(list<shared_ptr<Holding>> _list, int _i) {
	list<shared_ptr<Holding>>::iterator it = _list.begin();
	for (int i = 0; i < _i; i++) {
		++it;
	}
	return *it;
}

void MainWindow::OnDisplayClick() {
	//take each holding, run it through AV, parse the output to what we want, then display it on the relevant text static
	for (auto i = 0; i < textList.size(); i++) {
		HWND text = get(textList, i);
		shared_ptr<Holding> h = get(holdingsList, i);
		string out = ParseAV(wstring_to_utf8(AVW::TimeSeries(AVW::Daily, utf8_to_wstring(h->ticker))), h->amount);
		SetWindowText(text, wstring(out.begin(), out.end()).c_str()); //i hate windows sometimes man, why can't we all just use the same types for strings
	}
}

void MainWindow::OnEditClick() {
	//TODO: open notepad to the relevant file, detect when it closes and parse the new contents
	wchar_t cli[]{ L"notepad.exe holdings.txt" };
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess(NULL, cli, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		OutputDebugString(L"Creating notepad process failed\r\n");
	}
	else {
		// Wait until child process exits.
		WaitForSingleObject(pi.hProcess, INFINITE);
	}
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	ParseDataFile();
	InitTextBoxes();
}

string MainWindow::ParseAV(string in, int amt) {
	//parses the JSON output of AV to the data we want
	//what we want: symbol, last?, close, numShares, total value
	string symbol = "";
	float close = 0;
	float value = 0;
	try {
		json j;
		if (false) {
			ifstream is;
			is.open("example.json", fstream::in);
			j = json::parse(is);
			is.close();
		}
		else {
			j = json::parse(in);
		}
		symbol = j.at("Meta Data").at("2. Symbol");
		string tclose = j.at("Time Series (Daily)").back().at("4. close"); //causes error unless this shit
		close = stof(tclose);
		value = amt * close;
	}
	catch (exception e) {
		wchar_t msg[121];
		swprintf_s(msg, L"Error in JSON parse! Toggle canAPI!, what: %hs\r\n", e.what()); //won't print right but at least its only a warn
		OutputDebugString(msg);
	}
	char msg[81];
	sprintf_s(msg, "%s\t           %.2f\t      %d\t                %.2f", symbol.c_str(), close, amt, value); //seems like the \t's do nothing so I have to manually space this, looks better anyway
	return msg;
}

void MainWindow::ParseDataFile() {
	//parse the data file for stocks
	try {
		holdingsFile.open("holdings.txt", fstream::out | fstream::in);
	}
	catch (exception e) {
		OutputDebugString(L"Something went wrong opening the datafile!\r\n");
		return;
	}
	if (!holdingsFile) {
		OutputDebugString(L"File creation and/or aquisition failed!!\r\n");
		return;
	}
	holdingsList.clear();
	char isInit;
	holdingsFile.get(isInit);
	holdingsFile.seekg(0);
	if (isInit != '#') {
		// initialize the file, as it is empty
		try {
			holdingsFile.clear();
			holdingsFile << "# This is the holdings file, the standard format is <stock ticker>,<amount held>, blank lines are permitted, comments start with \"#\"" << endl;
			holdingsFile << endl;
		}
		catch (exception e) {
			OutputDebugString(L"Something went wrong writing to the datafile!\r\n");
			return;
		}
	}
	else {
		// file exists, parse it
		char line[257];
		while (holdingsFile.eof() == false) {
			holdingsFile.getline(line, 256);
			string line2 = line;
			if (line2.empty()) {
				continue;
			}
			else if (line2.at(0) == '#') {
				continue;
			}
			else {
				size_t comma = line2.find(',');
				if (comma != string::npos) {
					string ticker = line2.substr(0, comma);
					int amt = stoi(line2.substr(comma + 1));
					holdingsList.emplace_back(new Holding(ticker, amt));
				}
			}
		}
	}
	holdingsFile.close();
}

void MainWindow::InitTextBoxes() {
	CreateWindow(L"STATIC", L"Symbol      close       Nshares      value", WS_VISIBLE | WS_CHILD | SS_SIMPLE | SS_GRAYFRAME, 20, 50, 2000, 50, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
	size_t number = holdingsList.size();
	textList.clear();
	for (int i = 0; i < number; i++) {
		textList.emplace_back(CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD | SS_SIMPLE | SS_GRAYFRAME, 20, 70 + (i * 30), 2000, 50, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL));
	}
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
		///wstring out = AVW::TimeSeries(AVW::Intraday, L"NVDA");
		///SetWindowText(testOutput, out.c_str());
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
