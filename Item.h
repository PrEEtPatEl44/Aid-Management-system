

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
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
#include <iostream>

#include "iProduct.h"
#include "Status.h"

namespace sdds {
	class Item : public iProduct {
		double m_price{};
		int m_qty{};
		int m_neededQty{};
		char* m_desc{};
		bool m_flag{};

	protected:
		Status state{};
		int m_code{};

		bool linear() const;

	public:
		Item();
		Item(const Item& other);
		~Item();

		Item& operator =(const Item& other);




		int qtyNeeded() const ;
		int qty() const;
		operator double() const ;
		operator bool() const ;
		int operator-=(int qty) ;
		int operator+=(int qty) ;
		void linear(bool isLinear) ;
		void clear();
		bool operator==(int sku) const ;
		bool operator==(const char* description) const ;
		bool subString(const char* sub) const override;

		virtual std::ofstream& save(std::ofstream& ofstr) const ;
		virtual std::ifstream& load(std::ifstream& ifstr) ;
		virtual std::ostream& display(std::ostream& ostr) const ;
		virtual int readSku(std::istream& istr) ;
		virtual std::istream& read(std::istream& istr) ;
	};
}

#endif // !SDDS_ITEM_H
