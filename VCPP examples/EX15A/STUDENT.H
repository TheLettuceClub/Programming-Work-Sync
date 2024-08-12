// student.h
class CStudent : public CObject
{
    DECLARE_DYNAMIC(CStudent)
public:
    CString m_name;
    LONG    m_lGrade;

    CStudent() {
        m_lGrade = 0L;
    }

    CStudent(const char* szName, long lGrade) : m_name(szName) {
        m_lGrade = lGrade;
    }

    CStudent(const CStudent& s) : m_name(s.m_name) { // copy constructor
        m_lGrade = s.m_lGrade;
    }

    const CStudent& operator =(const CStudent& s) {
        m_name   = s.m_name;
        m_lGrade = s.m_lGrade;
        return *this;
    }

    BOOL operator ==(const CStudent& s) const
    {
        if ((m_name == s.m_name) && (m_lGrade == s.m_lGrade)) {
          return TRUE;
        }
        else {
          return FALSE;
        }
    }

    BOOL operator !=(const CStudent& s) const
    {
        // Let's make use of the operator we just defined!
        return !(*this == s);
    }

#ifdef _DEBUG
    void Dump(CDumpContext& dc) const;
#endif
};

