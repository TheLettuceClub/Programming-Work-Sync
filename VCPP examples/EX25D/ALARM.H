// alarm.h : header file
//

#include "cvariant.h"

class CAlarm : public CCmdTarget
{   
public:
	CAlarm(const VARIANT FAR& time);

public:
	virtual ~CAlarm();
	virtual void OnFinalRelease();

protected:
	// Generated message map functions
	//{{AFX_MSG(CAlarm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CVariant m_time;  // ClassWizard wants a VARIANT
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAlarm)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////
