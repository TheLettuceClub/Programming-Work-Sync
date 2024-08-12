// matvw1.h : interface of the CListView class
//
// Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

class CListView : public CView
{
/****************************************************************/
private:
	CListBox* m_pListBox;
	CMatplanDialog* m_pDialog;
	CPiece* m_pPiece; // currently selected element
	int m_xChar, m_yChar; // character width and height
	CSize m_drawOffset;
	CFont* m_pPrintFont;
	int m_nPage, m_nLinesPerPage;
/****************************************************************/
protected: // create from serialization only
	CListView();
	DECLARE_DYNCREATE(CListView)

// Attributes
public:
	CMatplanDoc* GetDocument()
		{
			ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatplanDoc)));
			return (CMatplanDoc*) m_pDocument;
		}

// Operations
public:

// Implementation
public:
	virtual ~CListView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
/****************************************************************/
private:
	void StartNewList();
	void PrintPageHeader(CDC* pDC);
	void PrintPageFooter(CDC* pDC);
	void UpdatePlanDocument();
/****************************************************************/
protected:
/****************************************************************/
	virtual	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
/****************************************************************/
	//{{AFX_MSG(CListView)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnListBoxDblClk();
		afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
