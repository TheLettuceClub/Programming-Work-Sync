// ex24bvw.h : interface of the CEx24bView class
//
/////////////////////////////////////////////////////////////////////////////
class CEx24bSet;

class CEx24bView : public CRowView
{
private:
	int m_nSelectedRow;
	CEx24bSet* m_pSet;
protected: // create from serialization only
	CEx24bView();
	DECLARE_DYNCREATE(CEx24bView)

// Attributes
public:
	CEx24bDoc* GetDocument();
	void CEx24bView::OnUpdate(CView*, LPARAM lHint, CObject* pHint);


// Overrides of CRowView
	void OnDrawRow(CDC* pDC, int nRowNo, int y, BOOL bSelected);
	void GetRowWidthHeight(CDC* pDC, int& nRowWidth, 
		int& nRowHeight, int& nCharWidth);
	int GetActiveRow();
	int GetRowCount();
	void ChangeSelectionNextRow(BOOL bNext);
	void ChangeSelectionToRow(int nRow);

// Implementation
public:
	virtual ~CEx24bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	void DrawDataRow(CDC* pDC, int y);

// Generated message map functions
protected:
	//{{AFX_MSG(CEx24bView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex24bvw.cpp
inline CEx24bDoc* CEx24bView::GetDocument()
   { return (CEx24bDoc*) m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////
