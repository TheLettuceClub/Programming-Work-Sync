// ex18avw.h : interface of the CHexView class
//
/////////////////////////////////////////////////////////////////////////////

class CHexView : public CScrollView
{
protected: // create from serialization only
	CHexView();
	DECLARE_DYNCREATE(CHexView)

// Attributes
public:
	CPoemDoc* GetDocument()
		{
			ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoemDoc)));
			return (CPoemDoc*) m_pDocument;
		}

// Operations
public:

// Implementation
public:
	virtual ~CHexView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Printing support
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CHexView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
