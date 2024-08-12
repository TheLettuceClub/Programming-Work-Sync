// Machine generated IDispatch driver class(es) created with ClassWizard.

/////////////////////////////////////////////////////////////////////////////
// Workbooks wrapper class

class Workbooks : public COleDispatchDriver
{
// Attributes
public:
	short GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Template);
	LPDISPATCH Add();
	VARIANT Application();
	void Close();
	VARIANT Item(const VARIANT& Index);
	VARIANT Open(const VARIANT& Filename, const VARIANT& UpdateLinks, const VARIANT& ReadOnly, const VARIANT& Format, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& IgnoreReadOnlyRecommended, const VARIANT& Origin, 
		const VARIANT& Delimiter, const VARIANT& Editable, const VARIANT& Notify, const VARIANT& Converter);
	VARIANT OpenText(const VARIANT& Filename, const VARIANT& Origin, const VARIANT& StartRow, const VARIANT& DataType, const VARIANT& TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, 
		const VARIANT& Comma, const VARIANT& Space, const VARIANT& Other, const VARIANT& OtherChar, const VARIANT& FieldInfo);
};

