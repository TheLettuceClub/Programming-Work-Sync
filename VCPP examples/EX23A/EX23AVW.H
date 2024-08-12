// ex23avw.h : interface of the CEx23aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx23aView : public CScrollView
{
public:
	CDC* m_pDisplayMemDC;
	HBITMAP m_hOldDisplayBitmap;
	CSize m_bmSize; // bitmap size
	CSize m_totalSize;  // document size
	BOOL m_bShrinkToFit;
protected: // create from serialization only
	CEx23aView();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	DECLARE_DYNCREATE(CEx23aView)
public:
	CEx23aDoc* GetDocument();
public:
	virtual ~CEx23aView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnInitialUpdate();
	// Printing support
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CEx23aView)
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditPasteFrom();
	afx_msg void OnEditCopyTo();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnViewShrink();
	afx_msg void OnUpdateViewShrink(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline CEx23aDoc* CEx23aView::GetDocument()
   { return (CEx23aDoc*) m_pDocument; }
 