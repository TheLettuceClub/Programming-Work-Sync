// ex25dvw.h : interface of the CEx25dView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx25dView : public CView
{
private:
	static const int nX[60];
	static const int nY[60];
	CFont m_font;

protected: // create from serialization only
	CEx25dView();
	DECLARE_DYNCREATE(CEx25dView)

// Attributes
public:
	CEx25dDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx25dView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx25dView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex25dvw.cpp
inline CEx25dDoc* CEx25dView::GetDocument()
   { return (CEx25dDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
