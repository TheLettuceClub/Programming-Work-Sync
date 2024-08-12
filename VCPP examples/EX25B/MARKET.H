// market.h : header file
//

#define IMPLEMENT_OLECREATE2(class_name, external_name, \
    l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    static const char BASED_CODE _szProgID_##class_name[] = external_name; \
    COleObjectFactory NEAR class_name::factory(class_name::guid, \
        RUNTIME_CLASS(class_name), TRUE, _szProgID_##class_name); \
    const GUID CDECL BASED_CODE class_name::guid = \
        { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };


/////////////////////////////////////////////////////////////////////////////
// CMarket command target

class CMarket : public CCmdTarget
{   
    DECLARE_DYNCREATE(CMarket)
protected:
    CMarket();          // protected constructor used by
                        //  dynamic creation

// Attributes
public:

// Operations
public:

// Implementation
public:
    virtual ~CMarket();
    virtual void OnFinalRelease();

protected:
    // Generated message map functions
    //{{AFX_MSG(CMarket)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DECLARE_OLECREATE(CMarket)

    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CMarket)
    afx_msg short GetIndustrialsAverage(const VARIANT FAR& Date);
    //}}AFX_DISPATCH
    DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////
