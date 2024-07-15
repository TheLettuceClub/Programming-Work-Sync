#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <windowsx.h>
#include <wchar.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "basewin.h"

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class MainWindow : public BaseWindow<MainWindow>
{
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBrush;
    D2D1_ELLIPSE            ellipse;
    D2D1_POINT_2F ptMouse;
    //MouseTrackEvents mouseTrack;

    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void OnLButtonUp();
    void OnMouseMove(int pixelX, int pixelY, DWORD flags);

public:
    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL), ellipse(D2D1::Ellipse(D2D1::Point2F(),0,0)), ptMouse(D2D1::Point2F())
    {
    }

    PCWSTR  ClassName() const { return L"Circle Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class DPIScale {
    static float scale;
public:
    static void Initialize(HWND hwnd) {
        float dpi = GetDpiForWindow(hwnd);
        scale = dpi / 96.0f;
    }

    template<typename T>
    static D2D1_POINT_2F PixelsToDips(T x, T y) {
        return D2D1::Point2F(static_cast<float>(x) / scale, static_cast<float>(y) / scale);
    }
};

//class MouseTrackEvents
//{
//    bool m_bMouseTracking;
//
//public:
//    MouseTrackEvents() : m_bMouseTracking(false)
//    {
//    }
//
//    void OnMouseMove(HWND hwnd)
//    {
//        if (!m_bMouseTracking)
//        {
//            // Enable mouse tracking.
//            TRACKMOUSEEVENT tme;
//            tme.cbSize = sizeof(tme);
//            tme.hwndTrack = hwnd;
//            tme.dwFlags = TME_HOVER | TME_LEAVE;
//            tme.dwHoverTime = HOVER_DEFAULT;
//            TrackMouseEvent(&tme);
//            m_bMouseTracking = true;
//        }
//    }
//    void Reset(HWND hwnd)
//    {
//        m_bMouseTracking = false;
//    }
//};

float DPIScale::scale = 1.0f;

// Recalculate drawing layout when the size of the window changes.

void MainWindow::CalculateLayout() {

}

HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &pRenderTarget);

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
            
            if (SUCCEEDED(hr))
            {
                CalculateLayout();
            }
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}

void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
        pRenderTarget->FillEllipse(ellipse, pBrush);

        hr = pRenderTarget->EndDraw();
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
        //pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        CalculateLayout();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(L"Circle with User Input", WS_OVERLAPPEDWINDOW))
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
    wchar_t msg[32];
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        DPIScale::Initialize(m_hwnd);
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_SIZE:
        Resize();
        return 0;

    case WM_LBUTTONDOWN:
        OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;

    case WM_LBUTTONUP:
        OnLButtonUp();
        return 0;

    case WM_MOUSEMOVE:
        //mouseTrack.OnMouseMove(m_hwnd);
        OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);

    case WM_MOUSELEAVE:
        //other stuff
        //mouseTrack.Reset(m_hwnd);

    case WM_MOUSEHOVER:
        //other stuff
        //mouseTrack.Reset(m_hwnd);

    case WM_MOUSEWHEEL:
        //int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        //do something with this, >120 is considered an action. should accumulate between messages somehow

    case WM_SYSKEYDOWN: //don't use these without good reason
        swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_SYSCHAR:
        swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);
        break;

    case WM_SYSKEYUP:
        swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_KEYDOWN: //shouldn't really need these except when using keyboard shortcuts, but acclerator tables are better for that
        swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_KEYUP:
        swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_CHAR: //actually used to get input from keyboard, will always come after some keydown messages for stuff like shifted or ctrl chars
        swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);
        break;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags) {
    SetCapture(m_hwnd);
    ellipse.point = ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);
    ellipse.radiusX = ellipse.radiusY = 1.0f;
    InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnLButtonUp() {
    ReleaseCapture();
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags) {
    if (flags & MK_LBUTTON) { //checking if left button held
        const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);
        const float width = (dips.x - ptMouse.x) / 2;
        const float height = (dips.y - ptMouse.y) / 2;
        const float x1 = ptMouse.x + width;
        const float y1 = ptMouse.y + height;

        ellipse = D2D1::Ellipse(D2D1::Point2F(x1, y1), width, height);
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}