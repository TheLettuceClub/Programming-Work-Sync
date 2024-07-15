#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>
#include <windowsx.h>
#include <list>
#include <iostream>
#include <fstream>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "basewin.h"
#include "ComputerAI.h"
#include "resource.h"

using namespace std;

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT) {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

int currGreen;
int currYellow;
int currOrange;
bool currentPlayer = true; //true = human, false = computer
bool gameOver = false;

class MainWindow : public BaseWindow<MainWindow>
{
    //local member vars
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    int humanWins = 0;
    int computerWins = 0;
    ComputerAI cptr{};
    list<HWND> yellowButtons;
    list<HWND> orangeButtons;
    list<HWND> greenButtons;
    HWND confirmButton;
    HWND resetButton;
    wchar_t whichColorSelected = ' ';
    int howManySelected = 0;
    fstream saveData;
    bool isThinking = false;

    //locally available functions
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void OnButtonClick(HWND hButton);
    void InitButtons();
    void OnResetClick();
    void OnConfirmClick();
    void checkGame();
    void getSavedData();
    void saveTheData();

public:
    //var initalization
    MainWindow()
    {
        pFactory = NULL;
        pRenderTarget = NULL;
        confirmButton = NULL;
        resetButton = NULL;
    }
    
    //don't ever need to touch these, change the string to whatever seems right
    PCWSTR  ClassName() const { return L"Nim"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int nCmdShow) {
    MainWindow win;
    currGreen = maxGreen;
    currOrange = maxOrange;
    currYellow = maxYellow;
    if (!win.Create(L"Dan's NIM port", WS_OVERLAPPEDWINDOW))
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
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        InitButtons();
        getSavedData();
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        saveTheData();
        PostQuitMessage(0);
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
            if (hButton == resetButton) {
                OnResetClick();
            }
            else if (hButton == confirmButton) {
                OnConfirmClick();
            }
            else {
                OnButtonClick(hButton);
            }
        }
        return 0;

    }
    if (currentPlayer == false && !isThinking) {
        isThinking = true;
        cptr.doMove();
        OnResetClick();
        checkGame();
        isThinking = false;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::InitButtons() {
    HBITMAP yellow = LoadBitmap((HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(103));
    HBITMAP orange = LoadBitmap((HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(102));
    HBITMAP green = LoadBitmap((HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(104));
    for (int i = 0; i < maxYellow; i++) {
        HWND hwndButton = CreateWindowEx(0L, L"BUTTON", L"y", WS_VISIBLE | WS_CHILD | BS_BITMAP, 40 + (55 * i), 40, 50, 50, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
        SendMessage(hwndButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)yellow);
        yellowButtons.emplace_back(hwndButton);
    }
    for (int i = 0; i < maxGreen; i++) {
        HWND hwndButton = CreateWindowEx(0L, L"BUTTON", L"g", WS_VISIBLE | WS_CHILD | BS_BITMAP, 40 + (55 * i), 100, 50, 50, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
        SendMessage(hwndButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)orange);
        greenButtons.emplace_back(hwndButton);
    }
    for (int i = 0; i < maxOrange; i++) {
        HWND hwndButton = CreateWindowEx(0L, L"BUTTON", L"o", WS_VISIBLE | WS_CHILD | BS_BITMAP, 40 + (55 * i), 160, 50, 50, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
        SendMessage(hwndButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)green);
        orangeButtons.emplace_back(hwndButton);
    }
    resetButton = CreateWindowEx(0L, L"BUTTON", L"reset", WS_VISIBLE | WS_CHILD, 100, 250, 50, 25, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
    confirmButton = CreateWindowEx(0L, L"BUTTON", L"confirm", WS_VISIBLE | WS_CHILD, 40, 250, 50, 25, m_hwnd, NULL, (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE), NULL);
}

void MainWindow::OnButtonClick(HWND hButton) {
    wchar_t text[2]{ 0 };
    Button_GetText(hButton, text, 2);
    OutputDebugString(text);
    OutputDebugString(L"\r\n");

    if (whichColorSelected == text[0]) {
        //button known to be visible since disabled buttons don't send clicked messages, disable and increment howManySelected
        Button_Enable(hButton, FALSE);
        howManySelected++;
    }
    else if (whichColorSelected == ' ') {
        //set whichColorSelected to text[0], do avove stuff
        whichColorSelected = text[0];
        Button_Enable(hButton, FALSE);
        howManySelected++;
    }
    else {
        //player made invalid choice, do nothing. put text in window if available
        OutputDebugString(L"Invalid choice!\r\n");
    }
}

void MainWindow::OnResetClick() {
    //do reset stuff
    whichColorSelected = ' ';
    howManySelected = 0;
    //reenable all buttons once they're in a list
    int increments = 0;
    for (HWND i : yellowButtons) {
        Button_Enable(i, FALSE);
        if (increments < currYellow) {
            Button_Enable(i, TRUE);
            increments++;
        }
    }
    increments = 0;
    for (HWND i : orangeButtons) {
        Button_Enable(i, FALSE);
        if (increments < currOrange) {
            Button_Enable(i, TRUE);
            increments++;
        }
    }
    increments = 0;
    for (HWND i : greenButtons) {
        Button_Enable(i, FALSE);
        if (increments < currGreen) {
            Button_Enable(i, TRUE);
            increments++;
        }
    }
}

void MainWindow::OnConfirmClick() {
    //do confirm stuff
    if (howManySelected != 0) {
        switch (whichColorSelected) {
        case 'g':
            currGreen -= howManySelected;
            break;
        case 'y':
            currYellow -= howManySelected;
            break;
        case 'o':
            currOrange -= howManySelected;
            break;
        }
        whichColorSelected = ' ';
        howManySelected = 0;
        checkGame();
    }
}

void MainWindow::checkGame() {
    //see if either player has won the game, then pop up a window saying who won
    if ((currYellow <= 0) && (currGreen <= 0) && (currOrange <= 0)) {
        //announce winner
        wchar_t msg[151];
        if (currentPlayer) {
            //pop up window
            humanWins++;
            swprintf_s(msg, L"You win! Your lifetime score is: human: %d wins, computer: %d wins.\r\nWould you like to rematch?", humanWins, computerWins);
        }
        else {
            //pop up window
            computerWins++;
            swprintf_s(msg, L"You lose! Your lifetime score is: human: %d wins, computer: %d wins.\r\nWould you like to rematch?", humanWins, computerWins);
        }
        int msgbox = MessageBox(m_hwnd, msg, L"Game Over", MB_YESNO | MB_ICONEXCLAMATION);
        switch (msgbox) {
        case IDYES:
            //TODO: do something to reset the game here
            gameOver = true;
            break;

        case IDNO:
            SendMessage(m_hwnd, WM_CLOSE, NULL, NULL); //close the game
            break;
        }
    }
    currentPlayer = !currentPlayer;
}

void MainWindow::getSavedData() {
    try {
        saveData.open("data", fstream::in);
    }
    catch (exception e) {
        OutputDebugString(L"opening data file failed in read!\r\n");
        return;
    }
    saveData >> humanWins;
    saveData >> computerWins;
    saveData.close();
}

void MainWindow::saveTheData() {
    try {
        saveData.open("data", fstream::out);
    }
    catch (exception e) {
        OutputDebugString(L"opening data file failed in write!\r\n");
        return;
    }
    saveData << humanWins << endl;
    saveData << computerWins << endl;
    saveData.close();
}

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
