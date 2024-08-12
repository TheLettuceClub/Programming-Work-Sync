// ex03avw.h : interface of the CEx03aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx03aView : public CView
{
protected: // create from serialization only
	CEx03aView();
	DECLARE_DYNCREATE(CEx03aView)

// Attributes
public:
	CEx03aDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx03aView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CEx03aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex03avw.cpp
inline CEx03aDoc* CEx03aView::GetDocument()
   { return (CEx03aDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
