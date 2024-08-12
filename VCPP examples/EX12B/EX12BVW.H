// ex12bvw.h : interface of the CEx12bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx12bView : public CEditView
{
private:
    CFont* m_pFont;
protected: // create from serialization only
    CEx12bView();
    DECLARE_DYNCREATE(CEx12bView)

// Attributes
public:
    CEx12bDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx12bView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CEx12bView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    afx_msg BOOL OnCommandSize(UINT nID);
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex12bvw.cpp
inline CEx12bDoc* CEx12bView::GetDocument()
   { return (CEx12bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
