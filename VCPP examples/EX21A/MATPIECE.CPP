// matpiece.cpp

#include "stdafx.h"
#include "matpiece.h"

IMPLEMENT_SERIAL(CPiece, CObject, 0)

/////////////////////////////////////////////////////////////////////////////
CPiece::CPiece() // required for serialization
{
    m_length = m_width = 0.0;
    m_sheet = m_x = m_y = m_bOverlap = 0;
}

/////////////////////////////////////////////////////////////////////////////
void CPiece::Draw(CDC* pDC, int yChar)
{
    CRect rect;
    GetRect(rect);

    pDC->SelectStockObject(BLACK_PEN);
    if (m_bOverlap) {
        pDC->SelectStockObject(BLACK_BRUSH);
    }
    else {
        pDC->SelectStockObject(GRAY_BRUSH);
    }
    pDC->Rectangle(rect);
    int hdcSave = pDC->SaveDC();
// the next two statements don't work with some printers
    pDC->SetTextColor((COLORREF) 0x00FFFFFF); // white
    pDC->SetBkMode(TRANSPARENT);

    pDC->IntersectClipRect(rect);  // restricts text to piece rectangle
    pDC->TextOut(rect.left, rect.bottom + yChar + 2, m_desc);
    pDC->RestoreDC(hdcSave);
}

/////////////////////////////////////////////////////////////////////////////
void CPiece::PrintLine(CDC* pDC, CPoint point)
{
    char temp[100];

    pDC->SetTextColor((COLORREF) 0x00000000); // black
    sprintf(temp, "%6.2f %6.2f %-30.30s%5ld%5ld%5ld",
            m_length, m_width, (const char*) m_desc, m_sheet, m_x, m_y);
    pDC->TextOut(point.x, point.y, temp);
}

/////////////////////////////////////////////////////////////////////////////
void CPiece::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        ar << m_length << m_width << m_desc << m_sheet << m_x << m_y;
    }
    else {
        ar >> m_length >> m_width >> m_desc >> m_sheet >> m_x >> m_y;
    }
}

/////////////////////////////////////////////////////////////////////////////
void CPiece::InsertInList(CListBox* pListBox, int index)
{ // copies data from this CPiece object into a list box entry
    char temp[100];

    sprintf(temp, "%6.2f %6.2f %-30.30s%5ld%5ld%5ld",
            m_length, m_width, (const char*) m_desc, m_sheet, m_x, m_y);
    pListBox->InsertString(index, temp);
}

/////////////////////////////////////////////////////////////////////////////
void CPiece::ExtractFromList(CListBox* pListBox, int index)
{   // copies data from a list box entry into a CPiece object
    char temp1[100], temp2[100];

    // sscanf won't work here because the description can
    //  contain embedded spaces
    pListBox->GetText(index, temp1);
    strncpy(temp2, temp1, 6); temp2[6] = '\0';
    m_length = atof(temp2);
    strncpy(temp2, temp1+7, 6); temp2[6] = '\0';
    m_width= atof(temp2);
    strncpy(temp2, temp1+14, 30); temp2[30] = '\0';
    m_desc = temp2;
    strncpy(temp2, temp1+44, 5); temp2[5] = '\0';
    m_sheet = atol(temp2);
    strncpy(temp2, temp1+49, 5); temp2[5] = '\0';
    m_x = atol(temp2);
    strncpy(temp2, temp1+54, 5); temp2[5] = '\0';
    m_y = atol(temp2);
}

/////////////////////////////////////////////////////////////////////////////
void CPiece::GetRect(CRect& r)
{ // converts piece to rectangle in logical coordinates
    r.top = (int) m_y;
    r.bottom = (int) (m_y - (LONG) (m_width / .24));
    r.left = (int) m_x;
    r.right = (int) (m_x + (LONG) (m_length / .24));
}

