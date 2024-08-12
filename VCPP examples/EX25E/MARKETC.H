// marketc.h

/////////////////////////////////////////////////////////////////////////////
// CMarketControl wrapper class

class CMarketControl : public COleDispatchDriver
{
// Attributes
public:
	enum { DID_ZERO, DID_GETAVERAGE };
	short GetIndustrialsAverage(const VARIANT& propVal);
};

