// ex12avw.h : interface of the CEx12aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx12aView : public CEditView
{
private:
    int m_nFont; // ID of currently selected stock font
protected: // create from serialization only
    CEx12aView();
    DECLARE_DYNCREATE(CEx12aView)

// Attributes
public:
    CEx12aDoc* GetDocument();

// Operations
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
    virtual ~CEx12aView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Printing support
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
    //{{AFX_MSG(CEx12aView)
    afx_msg void OnFontFixed();
    afx_msg void OnUpdateFontFixed(CCmdUI* pCmdUI);
    afx_msg void OnFontSystem();
    afx_msg void OnUpdateFontSystem(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex12avw.cpp
inline CEx12aDoc* CEx12aView::GetDocument()
   { return (CEx12aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
