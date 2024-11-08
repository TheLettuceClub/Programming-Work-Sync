#include "AVW_StockTimeSeries.h"
#include "GetFunctions.h"


std::wstring AVW::TimeSeries(Function inFunc, const std::wstring& inSymbol, Interval inInterval, OutputSize inOutputSize, DataType inDataType)
{
	std::wstring baseString = L"https://www.alphavantage.co/query?";
	
	//Function Switch
	switch (inFunc)
	{
	case AVW::Intraday:
		baseString.append(L"function=TIME_SERIES_INTRADAY");
		break;
	case AVW::Daily:
		baseString.append(L"function=TIME_SERIES_DAILY");
		break;
	case AVW::DailyAdjusted:
		baseString.append(L"function=TIME_SERIES_DAILY_ADJUSTED");
		break;
	case AVW::Weekly:
		baseString.append(L"function=TIME_SERIES_WEEKLY");
		break;
	case AVW::WeeklyAdjusted:
		baseString.append(L"function=TIME_SERIES_WEEKLY_ADJUSTED");
		break;
	case AVW::Monthly:
		baseString.append(L"function=TIME_SERIES_MONTHLY");
		break;
	case AVW::MonthlyAdjusted:
		baseString.append(L"function=TIME_SERIES_MONTHLY_ADJUSTED");
		break;
	case AVW::QuoteEndpoint:
		baseString.append(L"function=GLOBAL_QUOTE");
		break;
	default:
		inFunc = Intraday;
		baseString.append(L"function=TIME_SERIES_INTRADAY");
		break;
	}

	//Symbol
	baseString.append(L"&symbol=");
	baseString.append(inSymbol);

	//Interval
	if (inFunc == Intraday) {
		switch (inInterval)
		{
		case AVW::none:
			baseString.append(L"&interval=5min");
			break;
		case AVW::n_1min:
			baseString.append(L"&interval=1min");
			break;
		case AVW::n_5min:
			baseString.append(L"&interval=5min");
			break;
		case AVW::n_15min:
			baseString.append(L"&interval=15min");
			break;
		case AVW::n_30min:
			baseString.append(L"&interval=30min");
			break;
		case AVW::n_60min:
			baseString.append(L"&interval=60min");
			break;
		default:
			baseString.append(L"&interval=5min");
			break;
		}
	}

	//Output Size
	if (inOutputSize == full) {
		if (inFunc == Intraday || inFunc == Daily || inFunc == DailyAdjusted) {
			baseString.append(L"&outputsize=full");
		}
	}
	else {
		baseString.append(L"&outputsize=compact");
	}

	//Key
	baseString.append(L"&apikey=");
	baseString.append(GetKey());

	//DataType
	if (inDataType == csv) {
		baseString.append(L"&datatype=csv");
	}

	return GetToString(baseString);

}


//OVERLOADS-------------------------------------------------------------------------
//Quick TS Call
std::wstring AVW::TimeSeries(Function inFunc, const std::wstring & inSymbol)
{
	return TimeSeries(inFunc, inSymbol, none, compact, json);
}
//Quick TS Call with Intervals
std::wstring AVW::TimeSeries(Function inFunc, const std::wstring & inSymbol, Interval inInterval)
{
	return TimeSeries(inFunc, inSymbol, inInterval, compact, json);
}

std::wstring AVW::TimeSeries(Function inFunc, const std::wstring & inSymbol, Interval inInterval, OutputSize inOutputSize)
{
	return TimeSeries(inFunc, inSymbol, inInterval, inOutputSize, json);
}

std::wstring AVW::TimeSeries(Function inFunc, const std::wstring & inSymbol, Interval inInterval, DataType inDataType)
{
	return TimeSeries(inFunc, inSymbol, inInterval, compact, inDataType);
}
//Quick TS Call, no Intervals
std::wstring AVW::TimeSeries(Function inFunc, const std::wstring & inSymbol, OutputSize inOutputSize, DataType inDataType)
{
	return TimeSeries(inFunc, inSymbol, none, inOutputSize, inDataType);
}

std::wstring AVW::TimeSeries(Function inFunc, const std::wstring & inSymbol, OutputSize inOutputSize)
{
	return TimeSeries(inFunc, inSymbol, none, inOutputSize, json);
}

std::wstring AVW::TimeSeries(Function inFunc, const std::wstring & inSymbol, DataType inDataType)
{
	return TimeSeries(inFunc, inSymbol, none, compact, inDataType);
}



//Search Endpoint
std::wstring AVW::SearchEndpoint(const std::wstring inKeywords, DataType inDataType)
{
	std::wstring baseString = L"https://www.alphavantage.co/query?function=SYMBOL_SEARCH&keywords=";

	//Keywords
	baseString.append(inKeywords);

	//Key
	baseString.append(L"&apikey=");
	baseString.append(GetKey());

	//DataType
	if (inDataType == csv) {
		baseString.append(L"&datatype=csv");
	}

	return GetToString(baseString);
}

