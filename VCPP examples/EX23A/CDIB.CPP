#include "stdafx.h"
#include "resource.h"
#include "cdib.h"
#include <windowsx.h>  // for GlobalAllocPtr

IMPLEMENT_SERIAL(CDib, CObject, 0)

///////////////////////////////////////////////////////////////////
CDib::CDib()
{
    m_dwLength = 0L;
    m_nBits    = 0;
    m_lpBuf    = NULL;
}
    
///////////////////////////////////////////////////////////////////
CDib::CDib(CDC* pDC, int nBt, BOOL bCompr)
// pDC is memory DC ptr
// nBt is color bits per pixel (default = 0)
// bCompr is compression (default = TRUE)
{
// constructs a DIB from the contents of a bitmap
    BITMAP bm;
    int    nPaletteSize;

    CBitmap* pEmptyBitmap = new CBitmap;
    pEmptyBitmap->CreateCompatibleBitmap(pDC, 0, 0);
    CBitmap* pBitmap = (CBitmap*) (pDC->SelectObject(pEmptyBitmap));
    pBitmap->GetObject(sizeof(bm), &bm);
    if ((nBt == 1) || (nBt == 4) || (nBt == 8) || (nBt == 24)) {
        m_nBits = nBt;
    }
    else {   // nBt = 0
        m_nBits = bm.bmPlanes * bm.bmBitsPixel; // color bits per pixel
    }
    if (m_nBits == 1) {
        nPaletteSize = 2;
    }
    else {
        if (m_nBits == 4) {
            nPaletteSize = 16;
        }
        else {
            if (m_nBits == 8) {
                nPaletteSize = 256;
            }
            else {
                nPaletteSize = 0; // no palette for 24-bit display
            } 
        }
    }
    // fills out row to 4-byte boundary
    DWORD dwBytes = ((DWORD) bm.bmWidth * m_nBits) / 32;
    if (((DWORD) bm.bmWidth * m_nBits) % 32) {
        dwBytes ++;
    }
    dwBytes *= 4;

    m_dwLength = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                 sizeof(RGBQUAD) * nPaletteSize;
    if (!AllocateMemory()) return;
    
    m_lpBMIH->biSize = sizeof(BITMAPINFOHEADER);
    m_lpBMIH->biWidth = bm.bmWidth;
    m_lpBMIH->biHeight = bm.bmHeight;
    m_lpBMIH->biPlanes = 1;
    m_lpBMIH->biBitCount = m_nBits; // 1, 4, 8, or 24
    if (bCompr && (m_nBits == 4)) {
        m_lpBMIH->biCompression = BI_RLE4;
    }
    else {
        if (bCompr && (m_nBits == 8)) { 
            m_lpBMIH->biCompression = BI_RLE8;
        }
        else {
            m_lpBMIH->biCompression = BI_RGB;
        } 
    }
    m_lpBMIH->biSizeImage = 0;
    m_lpBMIH->biXPelsPerMeter = 0;
    m_lpBMIH->biYPelsPerMeter = 0;
    m_lpBMIH->biClrUsed = 0;
    m_lpBMIH->biClrImportant = 0;

    // calls GetDIBits with null data pointer to get size of DIB
    ::GetDIBits(pDC->GetSafeHdc(), (HBITMAP) pBitmap->GetSafeHandle(),
                0, (WORD) bm.bmHeight, NULL, m_lpBMI, DIB_RGB_COLORS);

    if (m_lpBMIH->biSizeImage == 0) {
        m_dwLength += dwBytes * bm.bmHeight;
        m_lpBMIH->biCompression = BI_RGB;
        // escape route for device drivers that don't do compression
        TRACE("Can't do compression\n");
    }
    else {
        m_dwLength += m_lpBMIH->biSizeImage;
    }
    if (!AllocateMemory(TRUE)) {
        return;
    }
    m_lpData = (LPSTR) m_lpBMIH + sizeof(BITMAPINFOHEADER) +
               sizeof(RGBQUAD) * nPaletteSize;
    m_lpBMFH->bfType = 0x4d42; // 'BM'
    m_lpBMFH->bfSize = m_dwLength;
    m_lpBMFH->bfReserved1 = 0;
    m_lpBMFH->bfReserved2 = 0;
    m_lpBMFH->bfOffBits = (char huge*) m_lpData - m_lpBuf;

    // second GetDIBits call to make DIB
    if (!::GetDIBits(pDC->GetSafeHdc(), (HBITMAP)
        pBitmap->GetSafeHandle(), 0, (WORD) bm.bmHeight, m_lpData,
        m_lpBMI, DIB_RGB_COLORS)) {
        m_dwLength = 0L;
    }
    delete pDC->SelectObject(pBitmap); // delete pEmptyBitmap
}

///////////////////////////////////////////////////////////////////
CDib::~CDib()
{
    if (m_lpBuf) {
        GlobalFreePtr(m_lpBuf);  // free the DIB memory
    }
}

///////////////////////////////////////////////////////////////////
void CDib::Serialize(CArchive& ar)
{
    ar.Flush();
    if (ar.IsStoring()) {
      Write(ar.GetFile());
    }
    else {
      Read(ar.GetFile());
    }
}

///////////////////////////////////////////////////////////////////
BOOL CDib::Read(CFile* pFile)
{
    // file assumed to be open
    ASSERT(m_dwLength == 0L); // DIB must be empty
    m_dwLength = pFile->GetLength();
    if (!AllocateMemory()) {
        return FALSE;       
    }
    DWORD dwCount = pFile->ReadHuge(m_lpBuf, m_dwLength);
    if (dwCount != m_dwLength) {
        AfxMessageBox("Read error");
        return FALSE;
    }
    if (m_lpBMFH->bfType != 0x4d42) {
        AfxMessageBox("Invalid bitmap file");
        return FALSE;
    }
    ASSERT((m_lpBMIH->biBitCount == 1) || (m_lpBMIH->biBitCount == 4) ||
           (m_lpBMIH->biBitCount == 8) || (m_lpBMIH->biBitCount == 24));
    m_lpData = (LPSTR) m_lpBMFH + m_lpBMFH->bfOffBits;
    m_nBits = m_lpBMIH->biBitCount;
    return TRUE;
}

///////////////////////////////////////////////////////////////////
BOOL CDib::Write(CFile* pFile)
{
    TRY {
        pFile->WriteHuge(m_lpBuf, m_dwLength);
    }
    CATCH (CException, e) {
        AfxMessageBox("Write error--possible disk full condition");
        return FALSE;
    }
    END_CATCH
    return TRUE;
}

///////////////////////////////////////////////////////////////////
CBitmap* CDib::MakeBitmap(CDC* pDC, CSize& bmSize)
{
    // replaces the DC's existing bitmap with a new one from the DIB
    // returns the old one
    BITMAP bm;
    DWORD  dwFore, dwBack;
    // checks to see whether DIB buffer is properly loaded
    if (m_dwLength == 0L) {
        bmSize.cx = bmSize.cy = 0;
        return NULL;
    }

    // this code conditions the DC for mono or color
    int nPlanes = pDC->GetDeviceCaps(PLANES);
    int nBitsPixel = pDC->GetDeviceCaps(BITSPIXEL);
    CBitmap* pConfigBitmap = new CBitmap;
    char bits[100];
    if (m_lpBMIH->biBitCount == 1) {
        pConfigBitmap->CreateBitmap(1, 1, 1, 1, bits);
    }
    else {
        pConfigBitmap->CreateBitmap(1, 1, nPlanes, nBitsPixel, bits);
    }
    CBitmap* pOriginalBitmap =
        (CBitmap*) pDC->SelectObject(pConfigBitmap);

// CreateDIBitmap "switches bits" for mono bitmaps, depending on colors,
//  so we'll fool it
    if (GetMonoColors(dwFore, dwBack)) {
        SetMonoColors(0L, 0xFFFFFFL);
    }
    
#ifdef _WIN32
    HBITMAP hBitmap = ::CreateDIBitmap(pDC->GetSafeHdc(), m_lpBMIH,
            CBM_INIT, (CONST BYTE*) (m_lpBuf + m_lpBMFH->bfOffBits),
            m_lpBMI, DIB_RGB_COLORS);
#else
    HBITMAP hBitmap = ::CreateDIBitmap(pDC->GetSafeHdc(), m_lpBMIH,
            CBM_INIT, (LPSTR) (m_lpBuf + m_lpBMFH->bfOffBits),
            m_lpBMI, DIB_RGB_COLORS);
#endif
    if (hBitmap == NULL) {
        TRACE("null bitmap\n");  
        delete pDC->SelectObject(pOriginalBitmap); // delete config bitmap
        return NULL; // untested error logic
    }
    
    SetMonoColors(dwFore, dwBack);
    
    // Can't use CBitmap::FromHandle here because we need to
    //  delete the object later
    CBitmap* pBitmap = new CBitmap;
    pBitmap->Attach(hBitmap);
    pBitmap->GetObject(sizeof(bm), &bm);
    bmSize.cx = bm.bmWidth;
    bmSize.cy = bm.bmHeight;
    delete pDC->SelectObject(pBitmap); // delete configuration bitmap
    return pOriginalBitmap;
}

///////////////////////////////////////////////////////////////////
BOOL CDib::Display(CDC* pDC, CPoint origin)
{
    // direct to device--bypass the GDI bitmap
    if (!m_lpBuf) {
        return FALSE; // nothing to display
    }
    if (!::SetDIBitsToDevice(pDC->GetSafeHdc(), origin.x, origin.y,
       (WORD) m_lpBMIH->biWidth, (WORD) m_lpBMIH->biHeight, 0, 0, 0,
       (WORD) m_lpBMIH->biHeight, m_lpData, m_lpBMI,
       DIB_RGB_COLORS)) {
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////
BOOL CDib::Stretch(CDC* pDC, CPoint origin, CSize size)
{
    // direct to device--bypass the GDI bitmap
    if (!m_lpBuf) {
        return FALSE; // nothing to display
    }
    if (!::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y,
        size.cx, size.cy, 0, 0, (WORD) m_lpBMIH->biWidth,
        (WORD) m_lpBMIH->biHeight, m_lpData, m_lpBMI,
        DIB_RGB_COLORS, SRCCOPY)) {
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////
int CDib::GetColorBits()
{
    return m_nBits;
}

///////////////////////////////////////////////////////////////////
DWORD CDib::GetLength()
{
    return m_dwLength;
}

CSize CDib::GetSize()
{
    return CSize((int) m_lpBMIH->biWidth, (int) m_lpBMIH->biHeight);
}

///////////////////////////////////////////////////////////////////
void CDib::SetMonoColors(DWORD dwForeground, DWORD dwBackground)
{
    if (m_nBits != 1) {
        return;
    }
    unsigned long far* pPalette = (unsigned long far*)
                       ((LPSTR) m_lpBMIH + sizeof(BITMAPINFOHEADER));
    *pPalette = dwForeground;
    *(++pPalette) = dwBackground;
    return;
}

///////////////////////////////////////////////////////////////////
BOOL CDib::GetMonoColors(DWORD& dwForeground, DWORD& dwBackground)
{
    if (m_nBits != 1) {
        return FALSE;
    }
    unsigned long far* pPalette = (unsigned long far*)
                       ((LPSTR) m_lpBMIH + sizeof(BITMAPINFOHEADER));
    dwForeground = *pPalette;
    dwBackground = *(++pPalette);
    return TRUE;
}

///////////////////////////////////////////////////////////////////
BOOL CDib::AllocateMemory(BOOL bRealloc) // bRealloc default = FALSE
{
    if (bRealloc) {  
        m_lpBuf = (char huge*) GlobalReAllocPtr(m_lpBuf,
                                                m_dwLength, GHND);
    }
    else {
        m_lpBuf = (char huge*) GlobalAllocPtr(GHND, m_dwLength);
    }
    if (!m_lpBuf) {
        AfxMessageBox("Unable to allocate DIB memory");
        m_dwLength = 0L;
        m_nBits = 0;
        return FALSE;
    }
    m_lpBMFH = (LPBITMAPFILEHEADER) m_lpBuf;
    m_lpBMIH = (LPBITMAPINFOHEADER) (m_lpBuf + sizeof(BITMAPFILEHEADER));
    m_lpBMI = (LPBITMAPINFO) m_lpBMIH;
    return TRUE;
}