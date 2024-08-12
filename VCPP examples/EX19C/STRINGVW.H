// stringvw.h : interface of the CStringView class
//
/////////////////////////////////////////////////////////////////////////////

class CStringView : public CScrollView
{
protected: // create from serialization only
    CStringView();
    DECLARE_DYNCREATE(CStringView)

// Attributes
public:
    CPoemDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CStringView();
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
    virtual void OnInitialUpdate();
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL );

// Generated message map functions
protected:
    //{{AFX_MSG(CStringView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
   	void SetScrollInfo();  // helper for logical twips srolling
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in stringvw.cpp
inline CPoemDoc* CStringView::GetDocument()
   { return (CPoemDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
