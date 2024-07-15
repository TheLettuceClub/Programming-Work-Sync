#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "basewin.h"
#include "json.hpp"
#include "MyObjects.h"

using namespace std;
using json = nlohmann::json;

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT) {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class MainWindow : public BaseWindow<MainWindow>
{
    //semi-global member vars
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    HWND gameSelector;
    HWND characterSelector;
    HWND moveSelector;
    Game* currentGame;

    //available functions
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void InitSubWindows();
    void InitData();

public:
    //var initalization
    MainWindow()
    {
        pFactory = NULL;
        pRenderTarget = NULL;
        gameSelector = NULL;
        characterSelector = NULL;
        moveSelector = NULL;
        currentGame = NULL;
    }
    
    //don't ever need to touch these, change the string to whatever seems right
    PCWSTR  ClassName() const { return L"DustloopViewer"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    MainWindow win;

    if (!win.Create(L"Dustloop Move Data Viewer", WS_OVERLAPPEDWINDOW))
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
        //SafeRelease(&currentGame);
        PostQuitMessage(0);
        return 0;

    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        InitSubWindows();
        InitData();
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_SIZE:
        Resize();
        return 0;

    case WM_COMMAND:
        switch (HIWORD(wParam)) {
        case LBN_SELCHANGE:
            HWND lp = (HWND)lParam;
            if (lp == gameSelector) {
                OutputDebugString(L"The handle and hwnd match for gameSelector\r\n");
            } else if (lp == characterSelector) {
                OutputDebugString(L"The handle and hwnd match for characterSelector\r\n");
            } else if (lp == moveSelector) {
                OutputDebugString(L"The handle and hwnd match for moveSelector\r\n");
            }
            else {
                OutputDebugString(L"The handle and hwnd do not match\r\n");
            }
        }
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

//my stuff
void MainWindow::InitSubWindows() {
    gameSelector = CreateWindow(L"LISTBOX", L"Game Selector", LBS_HASSTRINGS | LBS_NOTIFY | LBS_SORT | WS_CHILD | WS_VISIBLE, 20, 20, 150, 40, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
    wchar_t msg[]{ L"stuff" };
    SendMessage(gameSelector, LB_ADDSTRING, NULL, (LPARAM)&msg);
    wchar_t msg2[]{ L"stuff2" };
    SendMessage(gameSelector, LB_ADDSTRING, NULL, (LPARAM)&msg2);
}

void MainWindow::InitData() {
    //load json file, parse it using json.hpp into nested Game, Character and Move objects
    try {
        ifstream is;
        is.open("DustloopData.json", ifstream::in);
        json j = json::parse(is);
        is.close();
        string name = j.at("Game").at("Game Name");
        string dname = j.at("Game").at("Dustloop Name");
        const int numChars = j.at("Game").at("Number of Characters");
        currentGame = new Game(name, dname, numChars);
        vector<string> cnames;
        vector<string> cdnames;
        vector<int> cmoves;
        auto chars = j.at("Characters");
        for (auto& i : chars) {
            cnames.push_back(i.at("Name"));
            cdnames.push_back(i.at("Dustloop Name"));
            cmoves.push_back(i.at("Number of Moves"));
        }
        currentGame->InitChars(&cnames, &cdnames, &cmoves);
        int num = 0;
        for (auto& i : chars) {
            json moves = i.at("Moves");
            /*vector<string> test;
            for (int i = 0; i < cmoves[num]; i++) {
                test[i] = moves[i].template get<std::string>();
            }*/
            currentGame->InitCharMoves(num, moves);
            num++;
        }
    }
    catch (const json::exception& ex)
    {
        wchar_t msg[201];
        swprintf_s(msg, L"message: %hs, exception id: %d, byte position of error: %x\r\n", ex.what(), ex.id, ex.byte);
        OutputDebugString(msg);
    }

    //now refer to MSDN tutorial on how to fill in list boxes with the data
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
