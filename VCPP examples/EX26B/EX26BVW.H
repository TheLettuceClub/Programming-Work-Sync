// ex26bvw.h : interface of the ex26bview class  (student list view)
//
// Class CRowView implements a generic row-based scroll view.
// This derived class, CEx26bView, implements the details specific
// to the student list application.
/////////////////////////////////////////////////////////////////////////////

// Format of Student View line 1:
#define STUDENT_NAME_COL	0
#define STUDENT_NAME_LEN	20
#define STUDENT_GRADE_COL	(STUDENT_NAME_COL + STUDENT_NAME_LEN + 1)
#define STUDENT_GRADE_LEN	4
#define ROW_WIDTH	(STUDENT_GRADE_COL + STUDENT_GRADE_LEN)


class CEx26bView : public CRowView
{
	DECLARE_DYNCREATE(CEx26bView)
public:
	int m_nSelectedStudent;
public:
	CEx26bView();

// Attributes
public:
	CEx26bDoc* GetDocument()
		{
			ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx26bDoc)));
			return (CEx26bDoc*) m_pDocument;
		}

// Overrides of CView
	void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);

// Overrides of CRowView
	void OnDrawRow(CDC* pDC, int nRowNo, int y, BOOL bSelected);
	void GetRowWidthHeight(CDC* pDC, int& nRowWidth, 
		int& nRowHeight, int& nCharWidth);
	int GetActiveRow();
	int GetRowCount();
	void ChangeSelectionNextRow(BOOL bNext);
	void ChangeSelectionToRow(int nRow);

// Implementation
protected:
	virtual ~CEx26bView() {}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// Generated message map functions
protected:
	//{{AFX_MSG(CEx26bView)
	afx_msg void OnLButtonDblClk(UINT, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
