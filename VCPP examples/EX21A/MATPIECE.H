// MATPIECE.H  all classes for MATPLAN piece classes
class CPiece : public CObject
{
    DECLARE_SERIAL(CPiece)
public:  // easier if they're not private
    double m_length;
    double m_width;
    CString m_desc;
    LONG m_sheet;    // sheet number
    LONG m_x;        // x position of lower left on sheet
    LONG m_y;        // y position of lower left on sheet
    BYTE m_bOverlap; // TRUE if piece overlaps
    BOOL m_bNewList; // non-serializing flag for dialog control
public:
    CPiece(); // required for serialization
    void GetRect(CRect& r);
    void InsertInList(CListBox* pListbox, int index);
    void ExtractFromList(CListBox* pListbox, int index);
    void Draw(CDC* pDC, int yChar);
    void PrintLine(CDC* pDC, CPoint point);

    virtual void Serialize(CArchive& ar);
};
