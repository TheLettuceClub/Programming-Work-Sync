// stuview.h : interface of the CStudentView class

class CStudentView : public CFormView
{
    DECLARE_DYNCREATE(CStudentView)
protected: // create from serialization only
    CStudentView();
// Form data
public:
    //{{AFX_DATA(CStudentView)
    enum { IDD = IDD_STUDENT };
    CString m_name;
    long    m_lGrade;
    //}}AFX_DATA

// Attributes
public:
    CStudentDoc* GetDocument()
    {
        ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentDoc)));
        return (CStudentDoc*) m_pDocument;
    }

// Operations
public:

// Implementation
protected:
    POSITION m_position; // current position in document list
    CObList* m_pList;    // copied from document
public:
    virtual ~CStudentView();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV
                                                        //  support
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Printing support
protected:
    virtual void OnInitialUpdate();
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Generated message map functions
protected:
    //{{AFX_MSG(CStudentView)
    afx_msg void OnCommandHome();
    afx_msg void OnUpdateCommandHome(CCmdUI* pCmdUI);
    afx_msg void OnCommandEnd();
    afx_msg void OnUpdateCommandEnd(CCmdUI* pCmdUI);
    afx_msg void OnCommandPrev();
    afx_msg void OnUpdateCommandPrev(CCmdUI* pCmdUI);
    afx_msg void OnCommandNext();
    afx_msg void OnUpdateCommandNext(CCmdUI* pCmdUI);
    afx_msg void OnCommandDel();
    afx_msg void OnUpdateCommandDel(CCmdUI* pCmdUI);
    afx_msg void OnCommandIns();
    afx_msg void OnClickedClear();
    //}}AFX_MSG
protected:
    virtual void GetEntry(POSITION position);
    virtual void InsertEntry(POSITION position);
    virtual void ClearEntry();

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
