// ex18bvw.h : interface of the CEx18bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx18bView : public CView
{
protected: // create from serialization only
    CEx18bView();
    DECLARE_DYNCREATE(CEx18bView)

// Attributes
public:
    CEx18bDoc* GetDocument();

// Operations
public:

// Implementation
public:
	UINT m_nPage;
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
protected:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
private:
    void PrintPageHeader(CDC* pDC);
    void PrintPageFooter(CDC* pDC);

public:
    virtual ~CEx18bView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Printing support
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
    //{{AFX_MSG(CEx18bView)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex18bvw.cpp
inline CEx18bDoc* CEx18bView::GetDocument()
   { return (CEx18bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
