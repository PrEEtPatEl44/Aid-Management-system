/*/////////////////////////////////////////////////////////////////////////
						  Milestone: 4
Full Name  : Preet Bhagyesh Patel
Student ID#: 132603226
Email      : pbpatel48@myseneca.ca
Date       : 29 November 2023

Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include <iostream>
#include <fstream>

#include "Status.h"

namespace sdds {
	const int MAX_YEAR = 2030;
	const int MIN_YEAR = 2023;
	class Date {
		int m_year{};
		int m_month{};
		int m_day{};
		Status m_state{};
		bool m_formatted{true};

		bool validate();
		int uniqueDataValue() const;
		
	public:
		Date();
		~Date();
		Date(int year, int month, int day);
		bool operator ==(const Date ROp) const;
		bool operator !=(const Date ROp) const;
		bool operator <(const Date ROp) const;
		bool operator >(const Date ROp) const;
		bool operator <=(const Date ROp) const;
		bool operator >=(const Date ROp) const;
		const Status& state() const;
		Date& formatted(bool format);
		operator bool() const;
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		std::ifstream& read(std::ifstream& istr);
	};
	std::ostream& operator <<(std::ostream& ostr, const Date& other);
	std::istream& operator >>(std::istream& istr, Date& other);
	std::ifstream& operator >>(std::ifstream& istr, Date& other);
}
#endif // !SDDS_DATE_H
