// ex04avw.h : interface of the CEx04aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx04aView : public CView
{
private:
    CRect m_ellipseRect;
protected: // create from serialization only
    CEx04aView();
    DECLARE_DYNCREATE(CEx04aView)

// Attributes
public:
    CEx04aDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx04aView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CEx04aView)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex04avw.cpp
inline CEx04aDoc* CEx04aView::GetDocument()
   { return (CEx04aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
