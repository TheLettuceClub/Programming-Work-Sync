#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <list>
#include <memory>
using namespace std;

#include "basewin.h"
#include "resource.h"

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

struct MyEllipse
{
    D2D1_ELLIPSE    ellipse;
    D2D1_COLOR_F    color;

    void Draw(ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush) const
    {
        pBrush->SetColor(color);
        pRT->FillEllipse(ellipse, pBrush);
        pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
        pRT->DrawEllipse(ellipse, pBrush, 1.0f);
    }

    BOOL HitTest(float x, float y) const
    {
        const float a = ellipse.radiusX;
        const float b = ellipse.radiusY;
        const float x1 = x - ellipse.point.x;
        const float y1 = y - ellipse.point.y;
        const float d = ((x1 * x1) / (a * a)) + ((y1 * y1) / (b * b));
        return d <= 1.0f;
    }
};
D2D1::ColorF::Enum colors[] = { D2D1::ColorF::Yellow, D2D1::ColorF::Salmon, D2D1::ColorF::LimeGreen };


class MainWindow : public BaseWindow<MainWindow>
{
    enum Mode {
        DrawMode, SelectMode, DragMode
    };

    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBrush;
    D2D1_POINT_2F ptMouse;
    HCURSOR hCursor;
    Mode mode;
    size_t nextColor;
    list<shared_ptr<MyEllipse>> ellipses;
    list<shared_ptr<MyEllipse>>::iterator selection;

    shared_ptr<MyEllipse> Selection() {
        if (selection == ellipses.end()) {
            return nullptr;
        }
        else {
            return (*selection);
        }
    }

    void ClearSelection() { selection = ellipses.end(); }

    HRESULT InsertEllipse(float x, float y);
    void SetMode(Mode m);
    BOOL HitTest(float x, float y);
    void MoveSelection(float x, float y);
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void OnLButtonUp();
    void OnMouseMove(int pixelX, int pixelY, DWORD flags);
    void OnKeyDown(UINT vkey);

public:
    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL), nextColor(0), selection(ellipses.end()), ptMouse(D2D1::Point2F())
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
float DPIScale::scale = 1.0f;


HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &pRenderTarget);

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
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
        for (auto i = ellipses.begin(); i != ellipses.end(); ++i) {
            (*i)->Draw(pRenderTarget, pBrush);
        }
        if (Selection()) {
            pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
            pRenderTarget->DrawEllipse(Selection()->ellipse, pBrush, 2.0f);
        }
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
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    MainWindow win;
    if (!win.Create(L"Circle Drawing", WS_OVERLAPPEDWINDOW))
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

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        DPIScale::Initialize(m_hwnd);
        SetMode(DrawMode);
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
        OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;
    
    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT) {
            SetCursor(hCursor);
            return TRUE;
        }
        break;

    case WM_KEYDOWN:
        OnKeyDown(wParam);
        return 0;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ACCELERATOR40002:
            SetMode(DrawMode);
            break;
        case ID_ACCELERATOR40003:
            SetMode(SelectMode);
            break;
        case ID_ACCELERATOR40001:
            if (mode == DrawMode) {
                SetMode(SelectMode);
            }
            else {
                SetMode(DrawMode);
            }
            break;
        }
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags) {
    const D2D1_POINT_2F dip = DPIScale::PixelsToDips(pixelX, pixelY);
    if (mode == DrawMode) {
        POINT pt = { pixelX, pixelY };
        if (DragDetect(m_hwnd, pt)) {
            SetCapture(m_hwnd);
            InsertEllipse(dip.x, dip.y);
        }
    }
    else {
        ClearSelection();
        if (HitTest(dip.x, dip.y)) {
            SetCapture(m_hwnd);
            ptMouse = Selection()->ellipse.point;
            ptMouse.x -= dip.x;
            ptMouse.y -= dip.y;
            SetMode(DragMode);
        }
    }
    InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnLButtonUp() {
    if (mode == DrawMode && Selection()) {
        ClearSelection();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
    else if (mode == DragMode) {
        SetMode(SelectMode);
    }
    ReleaseCapture();
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags) {
    const D2D1_POINT_2F dip = DPIScale::PixelsToDips(pixelX, pixelY);
    if ((flags & MK_LBUTTON) && Selection()) {
        if (mode == DrawMode) {
            const float width = (dip.x - ptMouse.x) / 2;
            const float height = (dip.y - ptMouse.y) / 2;
            const float x1 = ptMouse.x + width;
            const float y1 = ptMouse.y + height;
            Selection()->ellipse = D2D1::Ellipse(D2D1::Point2F(x1, y1), width, height);
        }
        else if (mode == DragMode) {
            Selection()->ellipse.point.x = dip.x + ptMouse.x;
            Selection()->ellipse.point.y = dip.y + ptMouse.y;
        }
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

void MainWindow::OnKeyDown(UINT vkey) {
    switch (vkey) {
    case VK_BACK:
    case VK_DELETE:
        if ((mode == SelectMode) && Selection()) {
            ellipses.erase(selection);
            ClearSelection();
            SetMode(SelectMode);
            InvalidateRect(m_hwnd, NULL, FALSE);
        }
        break;
    case VK_LEFT:
        MoveSelection(-1, 0);
        break;

    case VK_UP:
        MoveSelection(0, -1);
        break;

    case VK_RIGHT:
        MoveSelection(1, 0);
        break;

    case VK_DOWN:
        MoveSelection(0,1);
        break;
    }
}

HRESULT MainWindow::InsertEllipse(float x, float y) {
    try {
        selection = ellipses.insert(ellipses.end(), shared_ptr<MyEllipse>(new MyEllipse()));
        auto select = Selection();
        select->ellipse.point = ptMouse = D2D1::Point2F(x, y);
        select->ellipse.radiusX = select->ellipse.radiusY = 2.0f;
        select->color = D2D1::ColorF(colors[nextColor]);
        nextColor = (nextColor + 1) % ARRAYSIZE(colors);
    }
    catch (bad_alloc) {
        return E_OUTOFMEMORY;
    }
    return S_OK;
}

BOOL MainWindow::HitTest(float x, float y) {
    for (auto i = ellipses.rbegin(); i != ellipses.rend(); ++i) {
        if ((*i)->HitTest(x, y)) {
            selection = (++i).base();
            return TRUE;
        }
    }
    return FALSE;
}

void MainWindow::MoveSelection(float x, float y) {
    auto select = Selection();
    if (mode == SelectMode && select) {
        select->ellipse.point.x += x;
        select->ellipse.point.y += y;
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

void MainWindow::SetMode(Mode m) {
    mode = m;
    LPWSTR cursor{};
    switch (mode) {
    case DrawMode:
        cursor = IDC_CROSS;
        break;
    case SelectMode:
        cursor = IDC_HAND;
        break;
    case DragMode:
        cursor = IDC_SIZEALL;
        break;
    }
    hCursor = LoadCursor(NULL, cursor);
    SetCursor(hCursor);
}