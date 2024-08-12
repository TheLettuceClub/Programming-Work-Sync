// ex05cvw.h : interface of the CEx05cView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx05cView : public CScrollView
{
private:
    CRect  m_ellipseRect;
    CPoint m_mousePos;
    BOOL   m_bCaptured;
protected: // create from serialization only
    CEx05cView();
    DECLARE_DYNCREATE(CEx05cView)

// Attributes
public:
    CEx05cDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx05cView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual void OnInitialUpdate(); // called first time after construct

// Generated message map functions
protected:
    //{{AFX_MSG(CEx05cView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex05cvw.cpp
inline CEx05cDoc* CEx05cView::GetDocument()
   { return (CEx05cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
