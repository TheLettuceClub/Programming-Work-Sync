// ex05avw.h : interface of the CEx05aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx05aView : public CView
{
private:
    void ShowFont(CDC* pDC, int& nPos, int nPoints);
protected:
    void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected: // create from serialization only
    CEx05aView();
    DECLARE_DYNCREATE(CEx05aView)

// Attributes
public:
    CEx05aDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx05aView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Printing support
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
    //{{AFX_MSG(CEx05aView)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex05avw.cpp
inline CEx05aDoc* CEx05aView::GetDocument()
   { return (CEx05aDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
