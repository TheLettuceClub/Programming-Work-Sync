#include "pch.h"
#include "CompositionHost.h"

#define MAX_TIME 300000
#define MIN_TIME 1500

// Global Variables:
HINSTANCE hInst; // current instance
HWND hwnd;
CompositionHost* compHost = CompositionHost::GetInstance();
int scrnWidth;
int scrnHeight;

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    // TODO: Place code here.

    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASS wc = { 0 };
    wc.style = CS_NOCLOSE | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"ScrnSav";

    return RegisterClass(&wc);
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   if (GetSystemMetrics(SM_CMONITORS) > 1) {
       //spawn another more on other monitors
       //can add screen width to mi.rcMonitor.left and will work, so do that somehow, use nccreate?
   }
   HMONITOR hmon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
   MONITORINFO mi = { sizeof(mi) };
   if (!GetMonitorInfo(hmon, &mi)) return NULL;
   hwnd = CreateWindowEx(WS_EX_TOPMOST, L"ScrnSav", L"ScreenSaver", WS_POPUP | WS_VISIBLE,
       mi.rcMonitor.left,
       mi.rcMonitor.top,
       mi.rcMonitor.right - mi.rcMonitor.left,
       mi.rcMonitor.bottom - mi.rcMonitor.top, nullptr, nullptr, hInstance, nullptr);
   scrnHeight = mi.rcMonitor.bottom;
   scrnWidth = mi.rcMonitor.right;

   if (!hwnd)
   {
      return FALSE;
   }
   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_DESTROY:
        for (int i = 1; i < 5; i++) {
            KillTimer(hWnd, i);
        }
        compHost->~CompositionHost();
        PostQuitMessage(0);
        break;

    /*case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MOUSEMOVE:
    case WM_MOUSELEAVE:
    case WM_MOUSEHOVER:
    case WM_MOUSEWHEEL:*/
    case WM_SYSKEYDOWN:
    case WM_SYSCHAR:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_CHAR:
        SendMessage(hWnd, WM_DESTROY, 0, 0);
        break;

    case WM_CREATE:
        compHost->Initialize(hWnd);
        srand(time(nullptr));
        //make timers
        for (int i = 1; i < 5; i++) {
            SetTimer(hWnd, i, rand() % (MAX_TIME - MIN_TIME + 1) + MIN_TIME, NULL);
        }
        SetTimer(hWnd, 77, MAX_TIME, NULL);
        break;

    case WM_TIMER: {
        if (wParam == 77) {
            compHost->ClearScreen();
            break;
        }
        double size = (double)(rand() % 150 + 50);
        double x = (double)(rand() % scrnWidth);
        double y = (double)(rand() % scrnHeight);
        compHost->AddElement(2/*(rand() % (2 - 1 + 1) + 1)*/, size, x, y);
        break;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

