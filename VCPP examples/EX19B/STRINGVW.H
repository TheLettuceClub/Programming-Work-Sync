// ex18avw.h : interface of the CStringView class
//
/////////////////////////////////////////////////////////////////////////////

class CStringView : public CScrollView
{
protected: // create from serialization only
	CStringView();
	DECLARE_DYNCREATE(CStringView)

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
	virtual ~CStringView();
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
	//{{AFX_MSG(CStringView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
