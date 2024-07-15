#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>
#include <wincodec.h>
#include <list>
#include <memory>
#include <strsafe.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "basewin.h"
#include "resource.h"
#define ID_EDITCHILD 100

using namespace std;

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT) {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

struct MyKeyCommand {
    WPARAM virtCode = 0;
    int repeatCount = 0;
    WORD scanCode = 0; //not sure how to use this!

};

class MainWindow : public BaseWindow<MainWindow>
{
    //semi-global member vars
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    IWICImagingFactory* pIWICFactory;
    ID2D1Bitmap* pBitmap;
    list<shared_ptr<MyKeyCommand>> keysHeldDown;
    list<shared_ptr<MyKeyCommand>>::iterator selection;
    HWND hwEdit;

    //available functions
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    HRESULT LoadResourceBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap);
    void OnKeyDown(WPARAM wParam, LPARAM lParam);
    void OnKeyUp(WPARAM wParam, LPARAM lParam);

    shared_ptr<MyKeyCommand> Selection() {
        if (selection == keysHeldDown.end()) {
            return nullptr;
        }
        else {
            return (*selection);
        }
    }

public:
    //var initalization
    MainWindow()
    {
        pFactory = NULL;
        pRenderTarget = NULL;
        pIWICFactory = NULL;
        pBitmap = NULL;
        hwEdit = NULL;
    }
    
    //don't ever need to touch these, change the string to whatever seems right
    PCWSTR  ClassName() const { return L"KMviewer"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    MainWindow win;

    if (!win.Create(L"Keyboard and Mouse Viewer", WS_OVERLAPPEDWINDOW))
    {
        return -1;
    }
    ShowWindow(win.Window(), nCmdShow);
    if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))) {
        return -1;
    }
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    CoUninitialize();
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
        hwEdit = CreateWindowEx(
            0, L"EDIT",   // predefined class 
            NULL,         // no window title 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
            0, 0, 0, 0,   // set size in WM_SIZE message 
            m_hwnd,         // parent window 
            (HMENU)ID_EDITCHILD,   // edit control ID 
            (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
            NULL);
        SendMessage(hwEdit, EM_SETLIMITTEXT, 0, 0);
        return 0;

    /*case WM_SETFOCUS:
        SetFocus(hwEdit);
        return 0;*/

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

    case WM_SYSKEYDOWN:
        swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
        OnKeyDown(wParam, lParam);
        OutputDebugString(msg);
        break;

    case WM_SYSKEYUP:
        swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
        OnKeyUp(wParam, lParam);
        OutputDebugString(msg);
        break;

    case WM_KEYDOWN:
        swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
        OnKeyDown(wParam, lParam);
        OutputDebugString(msg);
        break;

    case WM_KEYUP:
        swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
        OnKeyUp(wParam, lParam);
        OutputDebugString(msg);
        break;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::OnKeyDown(WPARAM wParam, LPARAM lParam) {
    //check if wParam matches any in keysHeldDown
    // if so: add 1 to repeat count
    // else: add a new MyKeyCommand to the list
    BOOL repeated = FALSE;
    for (auto i = keysHeldDown.begin(); i != keysHeldDown.end(); ++i) {
        if ((*i)->virtCode == wParam) {
            (*i)->repeatCount++;
            repeated = TRUE;
        }
    }
    if (!repeated) {
        try {
            selection = keysHeldDown.insert(keysHeldDown.end(), shared_ptr<MyKeyCommand>(new MyKeyCommand()));
            auto select = Selection();
            select->virtCode = wParam;
            select->scanCode = LOBYTE(HIWORD(lParam)); //TODO: I don't think this is getting the right bits, but not sure how to fix for now
            select->repeatCount = LOWORD(lParam);
        }
        catch (bad_alloc) {
            return;
        }
    }
    //invalidaterect to trigger a repaint to get the data onto the UI
    InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnKeyUp(WPARAM wParam, LPARAM lParam) {
    //remove current key/keys to keysHeldDown
    for (auto i = keysHeldDown.begin(); i != keysHeldDown.end(); ++i) {
        if ((*i)->virtCode == wParam) {
            keysHeldDown.erase(i);
            break;
        }
    }
    //invalidaterect to trigger a repaint to get the data onto the UI
    InvalidateRect(m_hwnd, NULL, FALSE);
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
        if (SUCCEEDED(hr)) {
            hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pIWICFactory);
}

void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        
        BeginPaint(m_hwnd, &ps);
        pRenderTarget->BeginDraw();
        pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        //determine which chars are being held
        wchar_t keys[1000]{};
        for (auto i = keysHeldDown.begin(); i != keysHeldDown.end(); ++i) {
            wchar_t msg[58]{};
            swprintf_s(msg, 55, L"   %c: is being pressed %d times from scancode %x\r\n", (wchar_t)(*i)->virtCode, (*i)->repeatCount, (*i)->scanCode);
            StringCchCat(keys, 1000, msg);
        }
        //display that info in a textbox
        SetWindowText(hwEdit, keys);
        //if possible, show images of keys
        hr = LoadResourceBitmap(pRenderTarget, pIWICFactory, MAKEINTRESOURCE(IDB_BITMAP1), RT_BITMAP, 100, 100, &pBitmap); //if bitmap: RT_BITMAP, else: use name from resource viewer
        if (SUCCEEDED(hr)) {
            D2D1_SIZE_F size = pBitmap->GetSize();
            D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(100.f, 10.f);
            // Draw a bitmap. will need to modify later to have all the potential keys in place
            pRenderTarget->DrawBitmap(
                pBitmap,
                D2D1::RectF(
                    upperLeftCorner.x,
                    upperLeftCorner.y,
                    upperLeftCorner.x + size.width,
                    upperLeftCorner.y + size.height));
        }
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
    RECT rc;
    GetClientRect(m_hwnd, &rc);
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
        pRenderTarget->Resize(size);
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
    MoveWindow(hwEdit,
        0, rc.bottom / 2,                  // starting x- and y-coordinates 
        rc.right,        // width of client area 
        rc.bottom / 5,        // height of client area 
        TRUE);
}

HRESULT MainWindow::LoadResourceBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;
    IWICBitmapScaler* pScaler = NULL;

    HRSRC imageResHandle = NULL;
    HGLOBAL imageResDataHandle = NULL;
    void* pImageFile = NULL;
    DWORD imageFileSize = 0;

    // Locate the resource.
    imageResHandle = FindResource(NULL, resourceName, resourceType);
    HRESULT hr = imageResHandle ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
        // Load the resource.
        imageResDataHandle = LoadResource(NULL, imageResHandle);

        hr = imageResDataHandle ? S_OK : E_FAIL;
    }
    if (SUCCEEDED(hr))
    {
        // Lock it to get a system memory pointer.
        pImageFile = LockResource(imageResDataHandle);

        hr = pImageFile ? S_OK : E_FAIL;
    }
    if (SUCCEEDED(hr))
    {
        // Calculate the size.
        imageFileSize = SizeofResource(NULL, imageResHandle);

        hr = imageFileSize ? S_OK : E_FAIL;

    }
    if (SUCCEEDED(hr))
    {
        // Create a WIC stream to map onto the memory.
        hr = pIWICFactory->CreateStream(&pStream);
    }
    if (SUCCEEDED(hr))
    {
        // Initialize the stream with the memory pointer and size.
        if (resourceType == RT_BITMAP) {
            // if bitmap, apparently loading it as a resouces chops off the header and now it's being added back on
            BITMAPFILEHEADER header;
            header.bfType = 0x4D42; // 'BM'
            header.bfSize = imageFileSize + 14; // resource data size + 14 bytes header
            header.bfReserved1 = 0;
            header.bfReserved2 = 0;
            header.bfOffBits = 14 + 40; // details in bitmap format
            BYTE* buffer = new BYTE[header.bfSize];
            memcpy(buffer, &header, 14);
            memcpy(buffer + 14, pImageFile, imageFileSize);
            hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(buffer), header.bfSize);
        }
        else {
            //if not bitmap
            hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(pImageFile), imageFileSize);
        }
    }
    if (SUCCEEDED(hr))
    {
        // Create a decoder for the stream.
        hr = pIWICFactory->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnLoad, &pDecoder);
    }
    if (SUCCEEDED(hr))
    {
        // Create the initial frame.
        hr = pDecoder->GetFrame(0, &pSource);
    }
    if (SUCCEEDED(hr))
    {
        // Convert the image format to 32bppPBGRA
        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
        hr = pIWICFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pSource,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.f,
            WICBitmapPaletteTypeMedianCut
        );
        if (SUCCEEDED(hr))
        {
            //create a Direct2D bitmap from the WIC bitmap.
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );

        }
    }
    SafeRelease(&pDecoder);
    SafeRelease(&pSource);
    SafeRelease(&pStream);
    SafeRelease(&pConverter);
    SafeRelease(&pScaler);

    return hr;
}

