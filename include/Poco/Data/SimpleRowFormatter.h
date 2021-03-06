//
// RowFormatter.h
//
// $Id: //poco/Main/Data/include/Poco/Data/SimpleRowFormatter.h#1 $
//
// Library: Data
// Package: DataCore
// Module:  SimpleRowFormatter
//
// Definition of the RowFormatter class.
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


#ifndef Data_SimpleRowFormatter_INCLUDED
#define Data_SimpleRowFormatter_INCLUDED


#include "Poco/Data/Data.h"
#include "Poco/Data/RowFormatter.h"


namespace Poco {
namespace Data {


class Data_API SimpleRowFormatter: public RowFormatter
	/// A simple row formatting class.
{
public:
	//typedef RowFormatter::NameVec    NameVec;
	//typedef RowFormatter::NameVecPtr NameVecPtr;
	//typedef RowFormatter::ValueVec   ValueVec;

	static const int DEFAULT_COLUMN_WIDTH = 16;

	SimpleRowFormatter(std::streamsize columnWidth = DEFAULT_COLUMN_WIDTH);
		/// Creates the SimpleRowFormatter and sets the column width to specified value.

	SimpleRowFormatter(const SimpleRowFormatter& other);
		/// Creates the copy of the supplied SimpleRowFormatter.

	SimpleRowFormatter& operator = (const SimpleRowFormatter& row);
		/// Assignment operator.

	~SimpleRowFormatter();
		/// Destroys the SimpleRowFormatter.

	void swap(SimpleRowFormatter& other);
		/// Swaps the row formatter with another one.

	std::string& formatNames(const NameVecPtr pNames, std::string& formattedNames) const;
		/// Formats the row field names.

	std::string& formatValues(const ValueVec& vals, std::string& formattedValues) const;
		/// Formats the row values.

	void setColumnWidth(std::streamsize width);
		/// Sets the column width.

	std::streamsize getColumnWidth() const;
		/// Returns the column width.

private:
	std::streamsize _colWidth;
};


///
/// inlines
///


inline void SimpleRowFormatter::setColumnWidth(std::streamsize columnWidth)
{
	_colWidth = columnWidth;
}


inline std::streamsize SimpleRowFormatter::getColumnWidth() const
{
	return _colWidth;
}


} } // namespace Poco::Data


namespace std
{
	template<>
	inline void swap<Poco::Data::SimpleRowFormatter>(Poco::Data::SimpleRowFormatter& s1, 
		Poco::Data::SimpleRowFormatter& s2)
		/// Full template specalization of std:::swap for SimpleRowFormatter
	{
		s1.swap(s2);
	}
}


#endif // Data_SimpleRowFormatter_INCLUDED
