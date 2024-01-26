/*/////////////////////////////////////////////////////////////////////////
                          Milestone: 2
Full Name  : Preet Bhagyesh Patel
Student ID#: 132603226
Email      : pbpatel48@myseneca.ca
Date       : 15 November 2023

Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
///////////////////////////////////////////////////////////////////////*/
#define _CRT_SECURE_NO_WARNINGS

#include "AidMan.h"
#include "Utils.h"
#include"Menu.h"
#include"Date.h"
#include "Perishable.h"

#include <iostream>
#include<iomanip>
#include <cstring>

using namespace std;
namespace sdds {
    AidMan::AidMan(const char* FName) : mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
        ut.alocpy(this->m_FName, FName);
    }


    AidMan::~AidMan() {
        if (m_FName)
            deallocate();
        delete[] m_FName;
        m_FName = nullptr;
    }


    void AidMan::run() {
        unsigned int selectionByUser;
        do {
            selectionByUser = menu();
            if (m_FName) {
                mainMenu.printUserSelection(selectionByUser);
                cin.ignore();
                switch (selectionByUser) {
                case 1:

                    listItems();
                    break;
                case 2:

                    addItem();
                    break;

                case 3:
                    removeItem();
                    break;
                case 4:
                    updateQuantity();
                    break;
                case 5:
                    sort();
                    break;
                case 6:
                    shipItem();
                    break;
                case 7:
                    cout << endl << "****New/Open Aid Database****" << endl << endl;
                    break;
                case 0:
                    cout << "Exiting Program!" << endl;
                    break;

                }
            }
            else {
                mainMenu.printUserSelection(7);
                load();
            }

        } while (selectionByUser != 0);
    }
    void AidMan::listItems() {
        if (list()) {
            cout << "Enter row number to display details or <ENTER> to continue:" << endl << "> ";

            if (cin.peek() != '\n') {
                int row = ut.getint();
                m_items[row - 1]->linear(false);
                m_items[row - 1]->display(cout) << endl;
            }
            else {
                cout << endl;
                cin.ignore();
            }
        }
    }

    unsigned int AidMan::menu()const {
        cout << "Aid Management System" << endl;
        cout << "Date: " << Date() << endl;
        if (m_FName)
        {
            cout << "Data file: " << m_FName << endl;
        }
        else
        {
            cout << "Data file: No file" << endl;
        }
        cout << "---------------------------------" << endl;


        unsigned int val = this->mainMenu.run();
        return val;
    }
    void AidMan::save() {
        if (m_FName) {
            ofstream file(m_FName);

            int i = 0;
            while (i < m_noOfItems) {
                m_items[i]->save(file) << endl;
                i++;
            }
            file.close();
        }

    }
    void AidMan::deallocate() {
        save();

        int i = 0;
        while (i < m_noOfItems) {
            delete m_items[i];
            m_items[i] = nullptr;
            i++;
        }
        m_noOfItems = 0;
    }
    bool AidMan::load() {
        save();
        deallocate();
        cin.ignore();



        if (m_FName) {
            ifstream file(m_FName);
            if (file.is_open()) {
                cout << "Failed to open " << m_FName << " for reading!" << endl;
                cout << "Would you like to create a new data file?" << endl;
                Menu menu("1- Yes!");
                if (menu.run()) {
                    char temp[1000]{ '\0' };
                    cin.getline(temp, 1000, '\n');
                    delete[] m_FName;
                    m_FName = nullptr;
                    ut.alocpy(m_FName, temp);
                    ofstream outputFile(m_FName);
                    outputFile << "";
                    outputFile.close();
                }
                else cout << "Exiting Program!" << endl;
            }
            file.close();
        }
        else {
            cout << "Enter file name: ";
            char temp[1000]{ '\0' };
            cin.getline(temp, 1000, '\n');
            ut.alocpy(m_FName, temp);
        }



        ifstream file(m_FName);
        int i;
        for (i = 0; i < sdds_max_num_items; i++) {
            int peek = file.peek();

            if (peek >= 49 && peek <= 51) {
                m_items[i] = new Perishable;
                if (m_items[i]->load(file)) { m_noOfItems++; }
                else {
                    if (m_items[i] != nullptr) {
                        delete m_items[i];
                        m_items[i] = nullptr;
                    }
                }
            }
            else if (peek >= 52 && peek <= 57) {
                m_items[i] = new Item;
                if (m_items[i]->load(file)) m_noOfItems++;
                else {
                    delete m_items[i];
                    m_items[i] = nullptr;
                }
            }
            else file.setstate(std::ios::failbit);
        }
        cout << m_noOfItems << " records loaded!" << endl << endl;
        file.close();
        return m_noOfItems;
    }
    int AidMan::list(const char* sub_desc) {
        int count{ 0 };
        cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        int i = 0;
        while (i < m_noOfItems)
        {
            if (!sub_desc) {
                m_items[i]->linear(true);
                cout << std::setw(4) << std::setfill(' ') << std::right << (i + 1) << " | ";
                m_items[i]->display(cout) << endl;
                count++;
            }
            else {
                if (m_items[i]->subString(sub_desc)) {
                    m_items[i]->linear(true);
                    cout << std::setw(4) << std::setfill(' ') << std::right << (i + 1) << " | ";
                    m_items[i]->display(cout) << endl;
                    count++;
                }
            }
            i++;
        }
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        return count;
    }
    int AidMan::search(int sku) const
    {
        int i = 0;
        int idx = -1;
        while (i < m_noOfItems)
        {
            if (*m_items[i] == sku) {
                idx = i;
            }
            i++;
        }
        return idx;
    }
    void AidMan::addItem() {
        if (m_noOfItems >= sdds_max_num_items) { cout << "Database full!" << endl; }
        else {
            Menu menu("Perishable\tNon-Perishable");
            int selection = menu.run(17);
            if (selection) {
                switch (selection) {
                case 0:
                    cout << "Aborted!" << endl;
                    break;
                case 1:
                    m_items[m_noOfItems] = new Perishable;
                    break;
                case 2:
                    m_items[m_noOfItems] = new Item;
                    break;

                }
                if (selection == 1 || selection == 2) {
                    int sku = m_items[m_noOfItems]->readSku(cin);
                    if (search(sku) !=-1) {
                        cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl<<endl;
                        delete m_items[m_noOfItems];
                        m_items[m_noOfItems] = nullptr;
                    }
                    else {
                        m_items[m_noOfItems]->read(cin);
                        m_noOfItems++;
                    }
                }
            }
        }
    }

    void AidMan::remove(int index) {
        
        delete m_items[index];
        m_items[index] = nullptr;
        for (int i = index; i < m_noOfItems - 1; i++) {
            m_items[i] = m_items[i + 1];
        }
        m_items[--m_noOfItems] = nullptr;
    }

    void AidMan::removeItem() {
        cout << "Item description: ";
        char input[1000]{ '\0' };
        cin.getline(input, 1000, '\n'); 
        if (list(input)) {
            int sku = ut.getint("Enter SKU: ");
            int index = search(sku); 
            if (index >= 0) {
                cout << "Following item will be removed: " << endl;
                m_items[index]->linear(false);
                m_items[index]->display(cout) << endl;

                cout << "Are you sure?" << endl;
                Menu menu("Yes!");
                if (menu.run(0)) {
                    remove(index); 
                    save();
                    cout << "Item removed!" << endl<<endl;
                }
                else cout << "Aborted!" << endl;
            }
            else cout << "SKU not found!" << endl;
        }
        else cout << "No matches found!" << endl;
    }

    void AidMan::updateQuantity() {
        cout << "Item description: ";
        char selection[1000]{ '\0' };
        cin.getline(selection, 1000, '\n');		 
        if (list(selection)) {
            int sku = ut.getint("Enter SKU: ");
            int index = search(sku);	 
            if (index >= 0) {
                Menu menu("Add\tReduce");
                switch (menu.run(0)) {
                case 1:
                    if (m_items[index]->qty() == m_items[index]->qtyNeeded()) {		
                        cout << "Quantity Needed already fulfilled!" << endl<<endl;
                    }
                    else {
                        int add = ut.getint(1, m_items[index]->qtyNeeded(), "Quantity to add: ");	 
                        m_items[index]->operator+= (add);		
                        cout << add << " items added!" << endl<<endl;
                        save();
                    }
                    break;
                case 2:
                    if (m_items[index]->qty() == 0) {	
                        cout << "There are no Items to reduce!" << endl;
                    }
                    else {
                        int reduced = ut.getint(1, m_items[index]->qty(), "Quantity to reduce: ");  
                        m_items[index]->operator-= (reduced);	
                        cout << reduced << " items removed!" << endl<<endl;
                        save();
                    }
                    break;
                case 0:
                default:
                    cout << "Aborted!" << endl<<endl;
                    break;
                }
            }
            else cout << "SKU not found!" << endl;
        }
        else cout << "No matches found!" << endl;
    }

    void AidMan::sort() {
        for (int i = 0; i < m_noOfItems - 1; ++i) {
            for (int j = 0; j < m_noOfItems - i - 1; ++j) {
                
                if (m_items[j]->qtyNeeded() - m_items[j] -> qty() < m_items[j + 1]->qtyNeeded() - m_items[j + 1] -> qty()) {
                   
                    iProduct* temp = m_items[j];	
                    m_items[j] = m_items[j+1];	
                    m_items[j+1] = temp;
                }
            }
        }
        save();
        cout << "Sort completed!" << endl<<endl;
    }

    void AidMan::shipItem() {
        ofstream ofstr("shippingOrder.txt");
        Date date{};
        date.formatted(true);
        ofstr << "Shipping Order, Date: " << date << endl;
        ofstr << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
        ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        int count{ 0 };
        for (int i = 0; i < m_noOfItems; i++) {
            if (m_items[i]->qty() == m_items[i]->qtyNeeded()) {
                m_items[i]->linear(true);
                ofstr << std::setw(4) << std::setfill(' ') << std::right << (++count) << " | ";	
                m_items[i]->display(ofstr) << endl;	
                remove(i); 
                i--;	
            }
        }
        ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        save();
        cout << "Shipping Order for " << count << " times saved!" << endl<<endl;
    }

}
