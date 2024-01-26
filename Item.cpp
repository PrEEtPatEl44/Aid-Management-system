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

#include "Item.h"
#include "Utils.h"

namespace sdds {

	Item::Item(): state("Empty") {
		m_price = 0.0;
		m_qty = 0;
		m_neededQty = 0;
		m_desc = nullptr;
		m_flag = false;
        m_code = 0;
	}
    //Rule of three
    Item::Item(const Item& other) {
        (*this) = other;//using assignment operator
    }

	bool Item::linear() const
	{
		return m_flag;
	}
    Item::~Item() {
        delete[] m_desc;
        state.clear();
    }

    Item& Item::operator=(const Item& other) {

        m_price = other.m_price;
        m_qty = other.m_qty;
        m_neededQty = other.m_neededQty;
        delete[] m_desc;
        ut.alocpy(m_desc, other.m_desc);
        m_flag = other.m_flag;
        state = other.state;
        m_code = other.m_code;
        return *this;
    }

    int Item::qtyNeeded() const {
        return m_neededQty;
    }

    int Item::qty() const {
        return m_qty;
    }

    Item::operator double() const {
        return m_price;
    }

    Item::operator bool() const {
        return state;
    }

    int Item::operator-=(int qty) {
        return m_qty -= qty;
    }

    int Item::operator+=(int qty) {
        return m_qty += qty;
    }

    void Item::linear(bool isLinear) {
        m_flag = isLinear;
    }

    void Item::clear() {
        state.clear();
    }

    bool Item::operator==(int code) const {
        return m_code == code;
    }

    bool Item::operator==(const char* description) const {
        if (m_desc && description) {
            return std::strstr(m_desc, description) != nullptr;
        }
        return false;
    }
    std::ofstream& Item::save(std::ofstream& ofstr) const {
        if (state) {
            ofstr << m_code << '\t' << m_desc << '\t'<< m_qty << '\t' << m_neededQty << '\t'<< std::fixed << std::setprecision(2) << m_price;
        }
        return ofstr;
    }
    std::ifstream& Item::load(std::ifstream& ifstr) {
        delete[] m_desc;
        m_desc = nullptr;

        ifstr >> m_code;
        ifstr.ignore();
        char temp[1000]{};
        ifstr.getline(temp, 1000, '\t');
        ut.alocpy(m_desc, temp);


        ifstr >> m_qty;
        ifstr.ignore();
        ifstr >> m_neededQty;
        ifstr.ignore();
        ifstr>> m_price;
        ifstr.ignore();

        if (ifstr.fail()) {
            state = "Input file stream read failed!";
            delete[] m_desc;
            m_desc = nullptr;
        }
        else {
            state.clear();
        }
        return ifstr;
    }
    std::ostream& Item::display(std::ostream& ostr) const {
        if (state) {
            if (linear()) {
                char buffer[36]{ '\0' };

                ostr << std::setw(5) << std::setfill('0') << m_code << " | ";

                if (m_desc) {
                    std::strncpy(buffer, m_desc, 35);
                    buffer[35] = '\0';
                    ostr << std::setw(35) << std::left << std::setfill(' ') << buffer << " | ";
                }

                ostr << std::setw(4) << std::right << m_qty << " | "
                    << std::setw(4) << m_neededQty << " | "
                    << std::setw(7) << std::fixed << std::setprecision(2) << m_price << " |";
            }
            else {
                ostr << "AMA Item:" << std::endl;
                ostr << m_code << ": " << m_desc << std::endl;
                ostr << "Quantity Needed: " << m_neededQty << std::endl;
                ostr << "Quantity Available: " << m_qty << std::endl;
                ostr << "Unit Price: $" << std::fixed << std::setprecision(2) << m_price << std::endl;
                ostr << "Needed Purchase Fund: $" << std::fixed << std::setprecision(2) << (m_price * (m_neededQty - m_qty)) << std::endl;
            }
        } 
        else {
            ostr << state;
        }
        return ostr;
    }
    int Item::readSku(std::istream& istr) {
        m_code = ut.getint(40000, 99999, "SKU: ");
        return m_code;
    }
    std::istream& Item::read(std::istream& istr) {
        std::cout << "AMA Item:" << std::endl;
        std::cout << "SKU: " << m_code << std::endl;

        delete[] m_desc;
        m_desc = nullptr;
        char temp[1000]{ '\0' };
        std::cout << "Description: ";
        istr.clear();
        istr.ignore(1000, '\n');
        istr.getline(temp, 1000, '\n');
        ut.alocpy(m_desc, temp);

        m_neededQty = ut.getint(1, 9999, "Quantity Needed: ");
        m_qty = ut.getint(0, m_neededQty, "Quantity On Hand: ");
        m_price = ut.getdouble(0.0, 9999.0, "Unit Price: $");
        

        return istr;
    }

    bool Item::subString(const char* sub) const {
        return std::strstr(m_desc, sub) != nullptr;
    }
}