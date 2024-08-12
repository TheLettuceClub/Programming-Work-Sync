// student.cpp
#include "stdafx.h"

#include "student.h"

IMPLEMENT_SERIAL(CStudent, CObject, 0)

CStudent::CStudent()
{
	m_lGrade = 0;
}

CStudent::CStudent(const char* szName, long lGrade) : m_name(szName)
{
	m_lGrade = lGrade;
}

void CStudent::Serialize(CArchive& ar)
{
	TRACE("Entering CStudent::Serialize\n");
	CObject::Serialize(ar); // I can get by without this.  Why??
	if (ar.IsStoring())	{
		ar << m_name << m_lGrade;
	}
	else {
		ar >> m_name >> m_lGrade;
	}
}

#ifdef _DEBUG
	void CStudent::Dump(CDumpContext& dc) const {
		CObject::Dump(dc);
		dc << "\nm_name = " << m_name << "\nm_lGrade = " << m_lGrade;
	}
#endif
