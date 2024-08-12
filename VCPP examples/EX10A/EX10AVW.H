// ex10avw.h : interface of the CEx10aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx10aView : public CScrollView
{
private:
    CDC*    m_pDisplayMemDC;
    HBITMAP m_hOldDisplayBitmap;
    int     m_nSWidth, m_nSHeight, m_nDWidth, m_nDHeight;
protected: // create from serialization only
    CEx10aView();
    DECLARE_DYNCREATE(CEx10aView)

// Attributes
public:
    CEx10aDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx10aView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual void OnInitialUpdate(); // called first time after construct

    // Printing support
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
    //{{AFX_MSG(CEx10aView)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex10avw.cpp
inline CEx10aDoc* CEx10aView::GetDocument()
   { return (CEx10aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
