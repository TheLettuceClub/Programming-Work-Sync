// student.h
class CStudent : public CObject
{
    DECLARE_SERIAL(CStudent)
public:
    CString m_name;
    LONG    m_lGrade;

    CStudent() {
        m_lGrade = 0;
    }

    CStudent(char* szName, int lGrade) {
        m_name = szName;
        m_lGrade = lGrade;
    }
    virtual void Serialize(CArchive& ar);
#ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
#endif
};
