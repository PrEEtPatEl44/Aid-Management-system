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
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>

#include "Item.h"
#include "Date.h"

namespace sdds {
	class Perishable : public Item {
		Date m_expDate{};
		char* m_instructions{};

	public:
		Perishable() = default;
		Perishable(const Perishable& src);
		~Perishable();
		Perishable& operator =(const Perishable& src);
		const Date& expiry() const;
		virtual int readSku(std::istream& istr) override;
		virtual std::ofstream& save(std::ofstream& ofstr) const override;
		virtual std::ifstream& load(std::ifstream& ifstr) override;
		virtual std::ostream& display(std::ostream& ostr) const override;
		virtual std::istream& read(std::istream& istr) override;
	};
}

#endif // !SDDS_PERISHABLR_H
