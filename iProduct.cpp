
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
#include "iProduct.h"

std::ostream& sdds::operator<<(std::ostream& ostr, const iProduct& other)
{
	return other.display(ostr);
}

std::istream& sdds::operator>>(std::istream& istr, iProduct& other)
{
	return other.read(istr);
}
