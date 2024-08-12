// ex25caut.h : header file
//
#include "cvariant.h"

/////////////////////////////////////////////////////////////////////////////
// CEx25cAuto command target

class CEx25cAuto : public CCmdTarget
{   
	DECLARE_DYNCREATE(CEx25cAuto)
protected:
	CEx25cAuto();			// protected constructor used by dynamic creation

// Implementation
public:
	virtual ~CEx25cAuto();
	virtual void OnFinalRelease();

protected:
	// Generated message map functions
	//{{AFX_MSG(CEx25cAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	DECLARE_OLECREATE(CEx25cAuto)

	CVariant m_textData; // moved here to keep ClassWizard happy
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CEx25cAuto)
	long m_longData;
	afx_msg BOOL DisplayDialog();
//	afx_msg BOOL DisplayDialog(long hwndParent);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

