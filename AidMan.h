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
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include"Menu.h"
#include "iProduct.h"
namespace sdds {
    const int sdds_max_num_items = 100;
	class AidMan {
    private:
        char* m_FName{};
        Menu mainMenu{ "List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database" };
        unsigned int menu()const;
        iProduct* m_items[sdds_max_num_items]{ nullptr };
        int m_noOfItems{ 0 };
        void save();
        void deallocate();
        bool load();
        int list(const char* sub_desc = nullptr);
    public:
        void listItems();
        AidMan() = default;
        AidMan(const char* FName);
        ~AidMan();
        void run();
        int search(int sku)const;
        void addItem();
        void removeItem();
        void remove(int index);
        void updateQuantity();
        void sort();
        void shipItem();
	};
}
#endif