// ex10bvw.h : interface of the CEx10bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx10bView : public CScrollView
{
private:
    CRect    m_ellipseRect;
    CPoint   m_mousePos;
    BOOL     m_bCaptured;
    CDC*     m_pMemDC;
    CBitmap* m_pBitmap;
protected: // create from serialization only
    CEx10bView();
    DECLARE_DYNCREATE(CEx10bView)

// Attributes
public:
    CEx10bDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx10bView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual void OnInitialUpdate(); // called first time after construct

// Generated message map functions
protected:
    //{{AFX_MSG(CEx10bView)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex10bvw.cpp
inline CEx10bDoc* CEx10bView::GetDocument()
   { return (CEx10bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
