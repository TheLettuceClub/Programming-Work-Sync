// cdib.h
class CDib : public CObject
{
    DECLARE_SERIAL(CDib)
private:
    char huge* m_lpBuf;    // DIB data buffer
    DWORD      m_dwLength; // total buffer length, including file header
    int        m_nBits;    // number of color bits per pixel
    //pointers for internal use
    LPBITMAPFILEHEADER m_lpBMFH;
    LPBITMAPINFOHEADER m_lpBMIH;
    LPBITMAPINFO       m_lpBMI;
    LPSTR              m_lpData; 
public:
    CDib();
    CDib(CDC* pDC, int nBt = 0, BOOL bCompr = FALSE);
    // nBt = 0 means use default bits/pixel
    ~CDib();
    virtual void Serialize(CArchive &ar);
    BOOL Read(CFile* pFile);
    BOOL Write(CFile* pFile);
    CBitmap* MakeBitmap(CDC* pDC, CSize& bmSize); // bmsize returned
    BOOL Display(CDC*, CPoint origin);
    BOOL Stretch(CDC*, CPoint origin, CSize size);
    int GetColorBits();  // bits per pixel
    DWORD GetLength();
    CSize GetSize();
    void SetMonoColors(DWORD dwForeground, DWORD dwBackground);
    BOOL GetMonoColors(DWORD& dwForeground, DWORD& dwBackground);
private:
    BOOL AllocateMemory(BOOL bRealloc = FALSE);
};
