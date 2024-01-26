

#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
#include <cstring>

#include "Status.h"
#include "Utils.h"

using namespace std;
namespace sdds {

	Status::Status(const char* desc) {
		m_code = 0;

		m_desc = nullptr;

		if (desc) ut.alocpy(m_desc, desc);
		
	}
	Status::~Status() {
		clear();
	}
	Status& Status::operator=(const Status& other)
	{
		if (this != &other)
		{
			clear();
			m_code = other.m_code;
			ut.alocpy(m_desc, other.m_desc);
		}

		return *this;
	}
	Status& Status::operator=(const char* desc) {
		delete[] m_desc;
		m_desc = nullptr;
		ut.alocpy(m_desc, desc);
		return *this;
	}
	Status& Status::operator=(int code) {
		m_code = code;
		return *this;
	}
	Status::operator int() const {
		return m_code;
	}
	Status::operator const char* () const {
		return m_desc;
	}
	Status::operator bool() const {
		return !m_desc;
	}
	Status& Status::clear() {
		delete[] m_desc;
		m_desc = nullptr;
		m_code = 0;
		return *this;
	}
	std::ostream& operator<<(std::ostream& ostr, const Status& status)
	{
		if (!status) {
			if ((int)status) {
				ostr << "ERR#" << (int)status << ": ";
			}
			ostr << (const char*)status;
		}
		return ostr;
	}
}


