//
// Extractor.h
//
// $Id: //poco/Main/Data/SQLite/include/Poco/Data/SQLite/Extractor.h#4 $
//
// Library: SQLite
// Package: SQLite
// Module:  Extractor
//
// Definition of the Extractor class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Data_SQLite_Extractor_INCLUDED
#define Data_SQLite_Extractor_INCLUDED


#include "Poco/Data/SQLite/SQLite.h"
#include "Poco/Data/SQLite/Utility.h"
#include "Poco/Data/AbstractExtractor.h"
#include "Poco/Data/MetaColumn.h"
#include "Poco/Data/DataException.h"
#include "Poco/Data/Constants.h"
#include "Poco/Any.h"
#include "Poco/DynamicAny.h"
#include <vector>
#include <utility>


struct sqlite3_stmt;


namespace Poco {
namespace Data {
namespace SQLite {


class SQLite_API Extractor: public Poco::Data::AbstractExtractor
	/// Extracts and converts data values form the result row returned by SQLite.
	/// If NULL is received, the incoming val value is not changed and false is returned
{
public:
	typedef std::vector<std::pair<bool, bool> > NullIndVec;
		/// Type for null indicators container.

	Extractor(sqlite3_stmt* pStmt);
		/// Creates the Extractor.

	~Extractor();
		/// Destroys the Extractor.

	bool extract(std::size_t pos, Poco::Int8& val);
		/// Extracts an Int8.

	bool extract(std::size_t pos, Poco::UInt8& val);
		/// Extracts an UInt8.

	bool extract(std::size_t pos, Poco::Int16& val);
		/// Extracts an Int16.

	bool extract(std::size_t pos, Poco::UInt16& val);
		/// Extracts an UInt16.

	bool extract(std::size_t pos, Poco::Int32& val);
		/// Extracts an Int32.

	bool extract(std::size_t pos, Poco::UInt32& val);
		/// Extracts an UInt32.

	bool extract(std::size_t pos, Poco::Int64& val);
		/// Extracts an Int64.

	bool extract(std::size_t pos, Poco::UInt64& val);
		/// Extracts an UInt64.

#ifndef POCO_LONG_IS_64_BIT
	bool extract(std::size_t pos, long& val);
		/// Extracts a long.
#endif

	bool extract(std::size_t pos, bool& val);
		/// Extracts a boolean.

	bool extract(std::size_t pos, float& val);
		/// Extracts a float.

	bool extract(std::size_t pos, double& val);
		/// Extracts a double.

	bool extract(std::size_t pos, char& val);
		/// Extracts a single character.

	bool extract(std::size_t pos, std::string& val);
		/// Extracts a string.

	bool extract(std::size_t pos, Poco::Data::BLOB& val);
		/// Extracts a BLOB.

	bool extract(std::size_t pos, Poco::Data::Date& val);
		/// Extracts a Date.

	bool extract(std::size_t pos, Poco::Data::Time& val);
		/// Extracts a Time.

	bool extract(std::size_t pos, Poco::DateTime& val);
		/// Extracts a DateTime.

	bool extract(std::size_t pos, Poco::Any& val);
		/// Extracts an Any.

	bool extract(std::size_t pos, Poco::DynamicAny& val);
		/// Extracts a DynamicAny.

	bool isNull(std::size_t pos, std::size_t row = POCO_DATA_INVALID_ROW);
		/// Returns true if the current row value at pos column is null.
		/// Because of the loss of information about null-ness of the 
		/// underlying database values due to the nature of SQLite engine, 
		/// (once null value is converted to default value, SQLite API 
		/// treats it  as non-null), a null indicator container member
		/// variable is used to cache the indicators of the underlying nulls 
		/// thus rendering this function idempotent. 
		/// The container is a vector of [bool, bool] pairs.
		/// The vector index corresponds to the column position, the first
		/// bool value in the pair is true if the null indicator has 
		/// been set and the second bool value in the pair is true if
		/// the column is actually null.
		/// The row argument, needed for connectors with bulk capabilities,
		/// is ignored in this implementation.

	void reset();
		/// Clears the cached nulls indicator vector.

private:
	template <typename T>
	bool extractImpl(std::size_t pos, T& val)
		/// Utility function for extraction of Any and DynamicAny.
	{
		if (isNull(pos)) return false;

		bool ret = false;

		switch (Utility::getColumnType(_pStmt, pos))
		{
		case MetaColumn::FDT_BOOL:
		{
			bool i = false;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_INT8:
		{
			Poco::Int8 i = 0;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_UINT8:
		{
			Poco::UInt8 i = 0;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_INT16:
		{
			Poco::Int16 i = 0;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_UINT16:
		{
			Poco::UInt16 i = 0;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_INT32:
		{
			Poco::Int32 i = 0;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_UINT32:
		{
			Poco::UInt32 i = 0;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_INT64:
		{
			Poco::Int64 i = 0;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_UINT64:
		{
			Poco::UInt64 i = 0;
			ret = extract(pos, i); 
			val = i;
			break;
		}
		case MetaColumn::FDT_STRING:
		{
			std::string s;
			ret = extract(pos, s); 
			val = s;
			break;
		}
		case MetaColumn::FDT_DOUBLE:
		{
			double d(0.0);
			ret = extract(pos, d); 
			val = d;
			break;
		}
		case MetaColumn::FDT_FLOAT:
		{
			float f(0.0);
			ret = extract(pos, f); 
			val = f;
			break;
		}
		case MetaColumn::FDT_BLOB:
		{
			BLOB b;
			ret = extract(pos, b); 
			val = b;
			break;
		}
		case MetaColumn::FDT_DATE:
		{
			Date d;
			ret = extract(pos, d); 
			val = d;
			break;
		}
		case MetaColumn::FDT_TIME:
		{
			Time t;
			ret = extract(pos, t); 
			val = t;
			break;
		}
		case MetaColumn::FDT_TIMESTAMP:
		{
			DateTime dt;
			ret = extract(pos, dt); 
			val = dt;
			break;
		}
		default:
			throw Poco::Data::UnknownTypeException("Unknown type during extraction");
		}

		return ret;
	}

	sqlite3_stmt* _pStmt;
	NullIndVec    _nulls;
};


///
/// inlines
///
inline void Extractor::reset()
{
	_nulls.clear();
}


} } } // namespace Poco::Data::SQLite


#endif // Data_SQLite_Extractor_INCLUDED
