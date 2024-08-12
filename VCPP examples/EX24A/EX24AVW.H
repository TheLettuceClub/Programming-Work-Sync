// ex24avw.h : interface of the CEx24aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx24aView : public CScrollView
{
public:
	CEx24aSet* m_pSet;

protected: // create from serialization only
    CEx24aView();
    DECLARE_DYNCREATE(CEx24aView)

// Attributes
public:
    CEx24aDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx24aView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual void OnInitialUpdate(); // called first time after construct

    // Printing support
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
    //{{AFX_MSG(CEx24aView)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex24avw.cpp
inline CEx24aDoc* CEx24aView::GetDocument()
   { return (CEx24aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
