// ex17bvw.h : interface of the CEx17bView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx17bView : public CView
{
protected: // create from serialization only
	CEx17bView();
	DECLARE_DYNCREATE(CEx17bView)

// Attributes
public:
	CEx17bDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CEx17bView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CEx17bView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in ex17bvw.cpp
inline CEx17bDoc* CEx17bView::GetDocument()
   { return (CEx17bDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
