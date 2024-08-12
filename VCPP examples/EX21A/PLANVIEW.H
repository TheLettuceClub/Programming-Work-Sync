// matvw2.h : interface of the CPlanView class
//				(included by the main MATPLAN.H file)
//
// Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

class CPlanView : public CScrollView
{
	DECLARE_DYNCREATE(CPlanView)
/*************************************************************/
private:
	int m_xChar, m_yChar; // character width and height
	CPoint m_mousePoint; // in logical coordinates
	CPiece* m_pPiece; // most recently captured piece
	BOOL m_bCaptured;
	CDC* m_pMemDC;
	HBITMAP m_hOldBitmap;
/*************************************************************/
protected: // create from serialization only
	CPlanView();

// Attributes
public:
	CMatplanDoc* GetDocument()
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatplanDoc)));
		return (CMatplanDoc*) m_pDocument;
	}

// Operations
/*************************************************************/
private:
	void ShowOverlap();
	void SafeScrollTo(CPoint posDev);
	void DrawBackground(CDC* pDC);
/*************************************************************/

// Implementation
public:
	virtual ~CPlanView();
	virtual void OnDraw(CDC* pDC);		// overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
	//{{AFX_MSG(CPlanView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
