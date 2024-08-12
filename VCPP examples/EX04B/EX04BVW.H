// ex04bvw.h : interface of the CEx04bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx04bView : public CView
{
private:
    CRect  m_ellipseRect;
    CPoint m_mousePos;
    BOOL   m_bCaptured;
protected: // create from serialization only
    CEx04bView();
    DECLARE_DYNCREATE(CEx04bView)

// Attributes
public:
    CEx04bDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx04bView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CEx04bView)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex04bvw.cpp
inline CEx04bDoc* CEx04bView::GetDocument()
   { return (CEx04bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
