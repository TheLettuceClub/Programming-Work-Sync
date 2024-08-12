// ex14avw.h : interface of the CEx14aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx14aView : public CView
{
protected: // create from serialization only
	CEx14aView();
	DECLARE_DYNCREATE(CEx14aView)

// Attributes
public:
	CEx14aDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx14aView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CEx14aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex14avw.cpp
inline CEx14aDoc* CEx14aView::GetDocument()
   { return (CEx14aDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
