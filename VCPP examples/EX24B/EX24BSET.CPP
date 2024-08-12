// ex24bset.cpp : implementation file
//

#include "stdafx.h"
#include "ex24b.h"
#include "ex24bset.h"
#include "columnst.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24bSet

IMPLEMENT_DYNAMIC(CEx24bSet, CRecordset)

CEx24bSet::CEx24bSet(CDatabase* pdb)
    : CRecordset(pdb)
{
}

void CEx24bSet::Initialize(const char* pchTableName)
{
// second construction phase

    void* pVar = NULL;

    m_nFields = 0;
    CColumns columns(m_pDatabase);  // closed on destruction
    columns.m_strTableNameParam = pchTableName;
    columns.Open();
    while (!columns.IsEOF()) {
      m_arrayName.Add(columns.m_strColumnName);
      m_nColWidth[m_nFields] = max(((int) columns.m_lLength + 2),
                            columns.m_strColumnName.GetLength());
      // data types defined in sql.h and sqlext.h
      m_nDatType[m_nFields] = columns.m_nDataType;
      switch (columns.m_nDataType) {
      case SQL_BIT:
          pVar = new BOOL;
          break;
      case SQL_TINYINT:
          pVar = new BYTE;
          break;
      case SQL_SMALLINT:
          pVar = new int;
          break;
      case SQL_INTEGER:
          pVar = new long;
          break;
      case SQL_REAL:
          pVar = new float;
          break;
      case SQL_FLOAT:
      case SQL_DOUBLE:
          pVar = new double;
          break;
      case SQL_DATE:
      case SQL_TIME:
      case SQL_TIMESTAMP:
          pVar = new CTime;
          break;
      case SQL_BINARY:
      case SQL_VARBINARY:
          pVar = new CByteArray;
          break;
      case SQL_DECIMAL:
      case SQL_NUMERIC:
      case SQL_CHAR:
      case SQL_VARCHAR:
          pVar = new CString;
          break;
      case SQL_LONGVARCHAR:
      case SQL_LONGVARBINARY:
          pVar = new CLongBinary;
          break;
      default:
          ASSERT(FALSE);
      }
      m_arrayValue.Add(pVar);
      columns.MoveNext();
      m_nFields++;
    }
}

CEx24bSet::~CEx24bSet()
{
    for (int i = 0; i < (int) m_nFields; i++) {
      switch (m_nDatType[i]) {
      case SQL_DECIMAL:
      case SQL_NUMERIC:
      case SQL_CHAR:
      case SQL_VARCHAR:
          delete (CString*) m_arrayValue[i];
          break;
      case SQL_BINARY:
      case SQL_VARBINARY:
          delete (CByteArray*) m_arrayValue[i];
          break;
      case SQL_LONGVARCHAR:
      case SQL_LONGVARBINARY:
          delete (CLongBinary*) m_arrayValue[i];
      default:        
          delete m_arrayValue[i];
      }
    }
}

CString CEx24bSet::GetDefaultSQL()
{
    // necessary because it's pure virtual
    return "";
}

void CEx24bSet::DoFieldExchange(CFieldExchange* pFX)
{
    pFX->SetFieldType(CFieldExchange::outputColumn);
    for (int i = 0; i < (int) m_nFields; i++) {
      switch (m_nDatType[i]) {
      case SQL_BIT:
          RFX_Bool(pFX, m_arrayName[i],
                 *((BOOL*) m_arrayValue[i]));
          break;
      case SQL_TINYINT:
          RFX_Byte(pFX, m_arrayName[i],
                 *((BYTE*) m_arrayValue[i]));
          break;
      case SQL_SMALLINT:
          RFX_Int(pFX,  m_arrayName[i],
                *((int*) m_arrayValue[i]));
          break;
      case SQL_INTEGER:
          RFX_Long(pFX,  m_arrayName[i],
                 *((long*) m_arrayValue[i]));
          break;
      case SQL_REAL:
          RFX_Single(pFX,  m_arrayName[i],
                   *((float*) m_arrayValue[i]));
          break;
      case SQL_FLOAT:
      case SQL_DOUBLE:
          RFX_Double(pFX, m_arrayName[i],
                   *((double*) m_arrayValue[i]));
          break;
      case SQL_DATE:
      case SQL_TIME:
      case SQL_TIMESTAMP:
          RFX_Date(pFX,  m_arrayName[i],
                 *((CTime*) m_arrayValue[i]));
          break;
      case SQL_BINARY:
      case SQL_VARBINARY:
          RFX_Binary(pFX,  m_arrayName[i],
                   *((CByteArray*) m_arrayValue[i]));
          break;
      case SQL_DECIMAL:
      case SQL_NUMERIC:
      case SQL_CHAR:
      case SQL_VARCHAR:
          RFX_Text(pFX, m_arrayName[i],
           *((CString*) m_arrayValue[i]));
          break;
      case SQL_LONGVARCHAR:
      case SQL_LONGVARBINARY:
          RFX_LongBinary(pFX, m_arrayName[i],
             *((CLongBinary*) m_arrayValue[i]));
          break;
      default:
          ASSERT(FALSE);
      }
    }   
}
