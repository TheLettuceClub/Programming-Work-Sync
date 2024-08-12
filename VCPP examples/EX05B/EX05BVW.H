// ex05bvw.h : interface of the CEx05bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx05bView : public CView
{
private:
    void TraceMetrics(CDC* pDC);
protected:
    void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected: // create from serialization only
	CEx05bView();
	DECLARE_DYNCREATE(CEx05bView)

// Attributes
public:
	CEx05bDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx05bView();
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
	//{{AFX_MSG(CEx05bView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex05bvw.cpp
inline CEx05bDoc* CEx05bView::GetDocument()
   { return (CEx05bDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
