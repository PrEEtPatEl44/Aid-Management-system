/*/////////////////////////////////////////////////////////////////////////
						  Milestone: 2
Full Name  : Preet Bhagyesh Patel
Student ID#: 132603226
Email      : pbpatel48@myseneca.ca
Date       : 15 November 2023

Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "Utils.h"
#include <iostream>
using namespace std;
#include <cstring>
namespace sdds {
	int sdds::Menu::countTab(const char* mContent)const
	{
		int count = 0;
		unsigned int i;
		if (*mContent) {
			for (i = 0; i < strlen(mContent); i++) {
				if (mContent[i] == '\t') {
					count++;
				}
			}
		}
		return count;
		
	}
	void Menu::setEmpty()
	{
		m_menuContent = nullptr;
	}

	Menu::Menu()
	{
		setEmpty();
	}

	Menu::Menu(const char* mContent)
	{
		setEmpty();
		if (mContent && countTab(mContent) < 15) {
				ut.alocpy(m_menuContent, mContent);
		}
		else {
			m_menuContent = nullptr;
		}
	}

	Menu::~Menu()
	{
		if (m_menuContent) {
			delete[]m_menuContent;
		}
	}
	unsigned int Menu::run(int size) const {
		int selection{ 0 };
		if (m_menuContent) {
			int index{ 1 };
			cout << index << "- ";
			for (size_t i = 0; i < strlen(m_menuContent); i++) {
				if (m_menuContent[i] == '\t') {
					cout << endl;
					cout << ++index << "- ";
				}
				else cout << m_menuContent[i];
			}
			cout << endl;
			for (int i = 0; i < size; i++) cout << '-';
			(size) && (cout << endl);
			cout << "0- Exit" << endl << "> ";
			selection  = ut.getint(0, index);
		}
		else {
			cout << "Invalid Menu!" << endl;
		}
		return selection;
	}

	void Menu::printUserSelection(unsigned int userSelection) {
		if (userSelection != 0) {
			cout << endl << "****";
		}
		unsigned int counter{ 1 };
		for (size_t i = 0; i < strlen(m_menuContent); i++) {
			if (m_menuContent[i] == '\t') {
				counter++;
				i++;
			}
			if (counter == userSelection) cout << m_menuContent[i];
		}if (userSelection != 0) {
			cout << "****" << endl;
		}
	}

}
