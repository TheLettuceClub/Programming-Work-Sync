// student.cpp
#include "stdafx.h"
#include "student.h"

IMPLEMENT_SERIAL(CStudent, CObject, 0)

void CStudent::Serialize(CArchive& ar)
{
    TRACE("Entering CStudent::Serialize\n");
    if (ar.IsStoring()) {
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
