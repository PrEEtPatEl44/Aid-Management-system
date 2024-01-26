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
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

#include "Perishable.h"
#include "Utils.h"

namespace sdds {
	//Rule of three
	Perishable::Perishable(const Perishable& other) {
		(*this) = other;//using assignment operator
	}

	Perishable::~Perishable() {
		
		delete[] m_instructions;
	}

	Perishable& Perishable::operator=(const Perishable& other)
	{
		Item::operator= (other);
		m_expDate = other.m_expDate;
		delete[] m_instructions;
		ut.alocpy(m_instructions, other.m_instructions);
		return *this;
	}

	const Date& Perishable::expiry() const {
		return m_expDate;
	}

	int Perishable::readSku(std::istream& istr) {
		m_code = ut.getint(10000, 39999, "SKU: ");
		
		return m_code;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const {
		if (Item::operator bool()) {
			Item::save(ofstr) << '\t';
			if (m_instructions && strlen(m_instructions)) ofstr << m_instructions;
			const_cast<Date&>(m_expDate).formatted(false);
			ofstr << '\t' << m_expDate;
		}
		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr){
		Item::load(ifstr);

		delete[] m_instructions;
		m_instructions = nullptr;

		char temp[1000]{};
		ifstr.getline(temp, 1000, '\t');
		ut.alocpy(m_instructions, temp);


		ifstr >> m_expDate;
		ifstr.ignore();


		if (ifstr.fail()) {
			state = "Input file stream read (perishable) failed!";
			delete[] m_instructions;
			m_instructions = nullptr;
		}
		else {
			state.clear();
		}

		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const {
		if (state) {
			const_cast<Date&>(m_expDate).formatted(true);
			if (linear()) {
				Item::display(ostr) << ((m_instructions && strlen(m_instructions)) ? "*" : " ") << m_expDate;
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: " << m_expDate << std::endl;
				if (m_instructions && strlen(m_instructions)) {
					ostr << "Handling Instructions: " << m_instructions << std::endl;
				}
			}
		}
		else {
			ostr << state;
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		delete[] m_instructions;
		m_instructions = nullptr;
		
		std::cout << "Expiry date (YYMMDD): ";
		istr >> m_expDate;
		istr.clear();
		istr.ignore();

		std::cout << "Handling Instructions, ENTER to skip: "<<std::endl;
		if (istr.peek() != '\n') {
			char temp[1000]{ '\0' };
			istr.getline(temp, 1000, '\n');
			ut.alocpy(m_instructions, temp);
		}

		if (istr.fail()) { 
			Item::state = "Perishable console date entry failed!"; 
		}
		else {
			Item::state.clear(); 
		}

		return istr;
	}




}