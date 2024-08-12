// ex07avw.h : interface of the CEx07aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx07aDialog;

class CEx07aView : public CView
{
private:
    CEx07aDialog* m_pDlg;
protected: // create from serialization only
    CEx07aView();
    DECLARE_DYNCREATE(CEx07aView)

// Attributes
public:
    CEx07aDoc* GetDocument();
    long OnGoodbye(UINT wParam, LONG lParam);

// Operations
public:

// Implementation
public:
    virtual ~CEx07aView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
    //{{AFX_MSG(CEx07aView)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex07avw.cpp
inline CEx07aDoc* CEx07aView::GetDocument()
   { return (CEx07aDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
