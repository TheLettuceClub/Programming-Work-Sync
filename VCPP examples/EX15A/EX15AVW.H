// ex15avw.h : interface of the CEx15aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx15aView : public CFormView
{
protected:
    virtual void OnInitialUpdate();
private:
    void UpdateEntry();
protected: // create from serialization only
    CEx15aView();
    DECLARE_DYNCREATE(CEx15aView)

public:
    //{{AFX_DATA(CEx15aView)
    enum { IDD = IDD_EX15A_FORM };
    long    m_lGrade;
    CString m_name;
    //}}AFX_DATA

// Attributes
public:
    CEx15aDoc* GetDocument();

// Operations
public:

// Implementation
public:
    virtual ~CEx15aView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Generated message map functions
protected:
    //{{AFX_MSG(CEx15aView)
    afx_msg void OnEnter();
    afx_msg void OnEditClearall();
    afx_msg void OnUpdateEditClearall(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex15avw.cpp
inline CEx15aDoc* CEx15aView::GetDocument()
   { return (CEx15aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
