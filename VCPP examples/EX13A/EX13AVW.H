// ex13avw.h : interface of the CEx13aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx13aView : public CView
{
private:
    CRect m_rect;
    BOOL  m_bCircle;
    BOOL  m_bPattern;
protected: // create from serialization only
    CEx13aView();
    DECLARE_DYNCREATE(CEx13aView)

// Attributes
public:
    CEx13aDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx13aView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CEx13aView)
    afx_msg void OnDrawCircle();
    afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
    afx_msg void OnDrawPattern();
    afx_msg void OnUpdateDrawPattern(CCmdUI* pCmdUI);
    afx_msg void OnDrawSquare();
    afx_msg void OnUpdateDrawSquare(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex13avw.cpp
inline CEx13aDoc* CEx13aView::GetDocument()
   { return (CEx13aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
