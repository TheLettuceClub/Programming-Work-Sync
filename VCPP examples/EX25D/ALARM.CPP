// alarm.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "alarm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarm

//IMPLEMENT_DYNCREATE(CAlarm, CCmdTarget)

// no default ctor
CAlarm::CAlarm(const VARIANT FAR& time) : m_time(time) 
{
	TRACE("Entering CAlarm ctor -- time = %f\n", time.dblVal);
	EnableAutomation();
}

CAlarm::~CAlarm()
{
	TRACE("Entering CAlarm dtor\n");
}

void CAlarm::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.
	TRACE("Entering CAlarm::OnFinalRelease\n");
	delete this;
}

BEGIN_MESSAGE_MAP(CAlarm, CCmdTarget)
	//{{AFX_MSG_MAP(CAlarm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAlarm, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CAlarm)
	DISP_PROPERTY(CAlarm, "Time", m_time, VT_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarm message handlers

