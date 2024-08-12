// student.cpp
#include "stdafx.h"
#include "student.h"

IMPLEMENT_DYNAMIC(CStudent, CObject)

#ifdef _DEBUG
    void CStudent::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
        dc << "\nm_name = " << m_name << "\nm_lGrade = " << m_lGrade;
    }
#endif
