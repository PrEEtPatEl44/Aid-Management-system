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
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds {
	class Menu {
	private:
		char *m_menuContent;
		int countTab(const char* mContent)const;
		void setEmpty();
	public:
		Menu();
		~Menu();
		Menu(const char* mContent);
		unsigned int run(int size=33)const;
		void printUserSelection(unsigned int userSelection);
	};
}


#endif