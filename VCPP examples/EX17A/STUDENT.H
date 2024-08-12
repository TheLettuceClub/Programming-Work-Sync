// student.h
class CStudent : public CObject
{
    DECLARE_SERIAL(CStudent)
public:
    CString m_name;
    LONG m_lGrade;
    CStudent() {
        m_lGrade = 0;
    }
    CStudent(const char* szName, int lGrade) : m_name(szName) {
        m_lGrade = lGrade;
    }

    CStudent(const CStudent& s) : m_name(s.m_name) {
        m_lGrade = s.m_lGrade;
    }

    const CStudent& operator =(const CStudent& s)
    {
        m_name = s.m_name;
        m_lGrade = s.m_lGrade;
        return *this;
    }

    BOOL operator ==(const CStudent& s) const
    {
        if((m_name == s.m_name) && (m_lGrade == s.m_lGrade)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }

    BOOL operator !=(const CStudent& s) const
    {
        // let's make use of the operator we just defined
        return !(*this == s);
    }

    virtual void Serialize(CArchive& ar);
#ifdef _DEBUG
    void Dump(CDumpContext& dc) const;
#endif
};
