// menu.cpp : Defines the entry point for the console application.
//

#include<conio.h>
#include<string>
#include<iostream>
#include "table.h"
#include "list.h"
#include "binary_heap.h"
#include "red_black_tree.h"
#include "container_test.h"

using namespace std;

void displayMenu(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
	cout << "7.Wyczysc wszystko" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void displayTestMenu()
{
	cout << endl;
	cout << "1.Test tablicy" << endl;
	cout << "2.Test listy" << endl;
	cout << "3.Test kopca" << endl;
	cout << "4.Test drzewa" << endl;
	cout << "5.Testuj wszystko" << endl;
	cout << "Podaj opcje:";
}


void menu_table()
{
	char opt;
	string fileName;
	int index, value;
	
	table myTab;

	do{
		displayMenu("--- TABLICA ---");
		opt = getche();
		cout << endl;
		switch (opt){
		case '1': 
			cout << " Podaj nazwê zbioru:";
			cin >> fileName;
			myTab.load_from_file(fileName);
			myTab.display();
			break;

		case '2': 
			cout << " podaj index:";
			cin >> index;
			myTab.remove(index);
			myTab.display();
			break;

		case '3': 
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartosc:";
			cin >> value;

			myTab.insert(index,value);
			myTab.display();			
			break;

		case '4': 
			cout << " podaj wartosc:";
			cin >> value;
			if (myTab.find(value) == true)
				cout << "poadana wartosc jest w tablicy";
			else
				cout << "poadanej wartosci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			myTab.generate_data(value);
			myTab.display();
			break;
		case '6':  //tutaj wyœwietlanie tablicy
			myTab.display();
			break;
		case '7':
			myTab.clear();
			myTab.display();
			break;			
		}

	} while (opt != '0');
}

void menu_list()
{
	char opt;
	string fileName;
	int index, value;
	
	list my_list;

	do{
		displayMenu("--- LISTA ---");
		opt = getche();
		cout << endl;
		switch (opt){
		case '1': 
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			my_list.load_from_file(fileName);
			my_list.display();
			break;

		case '2': 
			cout << " podaj wartosc:";
			cin >> value;
			my_list.remove(value);
			my_list.display();
			break;

		case '3': 
			cout << " podaj index:";
			cin >> index;
			cout << " podaj wartosc:";
			cin >> value;
			my_list.insert(index,value);
			my_list.display();			
			break;

		case '4': 
			cout << " podaj wartosc:";
			cin >> value;
			if (my_list.find(value) == true)
				cout << "poadana wartosc jest w tablicy";
			else
				cout << "poadanej wartosci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			my_list.generate_data(value);
			my_list.display();
			break;
		case '6':  //tutaj wyœwietlanie tablicy
			my_list.display();
			break;
		case '7':
			my_list.clear();
			my_list.display();
			break;		
		}

	} while (opt != '0');
}

void menu_heap()
{
	char opt;
	string fileName;
	int value;
	
	binary_heap my_heap;

	do{
		displayMenu("--- HEAP ---");
		opt = getche();
		cout << endl;
		switch (opt){
		case '1': 
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			my_heap.load_from_file(fileName);
			my_heap.display();
			break;

		case '2': 
			cout << " podaj wartosc:";
			cin >> value;
			my_heap.remove(value);
			my_heap.display();
			break;

		case '3':
			cout << " podaj wartosc:";
			cin >> value;
			my_heap.insert(value);
			my_heap.display();			
			break;

		case '4': 
			cout << " podaj wartosc:";
			cin >> value;
			if (my_heap.find(value) == true)
				cout << "poadana wartosc jest w tablicy";
			else
				cout << "poadanej wartosci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			my_heap.generate_data(value);
			my_heap.display();
			break;
		case '6':  //tutaj wyœwietlanie tablicy
			my_heap.display();
			break;
		case '7':
			my_heap.clear();
			my_heap.display();
			break;		
		}

	} while (opt != '0');
}

void menu_tree()
{
	char opt;
	string fileName;
	int value;
	
	red_black_tree my_tree;
	
	do{
		displayMenu("--- READ BLACK TREE ---");
		opt = getche();
		cout << endl;
		switch (opt){
		case '1': 
			cout << " Podaj nazwe zbioru:";
			cin >> fileName;
			my_tree.load_from_file(fileName);
			my_tree.display();
			break;

		case '2': 
			cout << " podaj wartosc:";
			cin >> value;
			my_tree.remove(value);
			my_tree.display();
			break;

		case '3':
			cout << " podaj wartosc:";
			cin >> value;
			my_tree.insert(value);
			my_tree.display();			
			break;

		case '4': 
			cout << " podaj wartosc:";
			cin >> value;
			if (my_tree.find(value) == true)
				cout << "poadana wartosc jest w tablicy";
			else
				cout << "poadanej wartosci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc elementów tablicy:";
			cin >> value;
			my_tree.generate_data(value);
			my_tree.display();
			break;
		case '6':  //tutaj wyœwietlanie tablicy
			my_tree.display();
			break;
		case '7':
			my_tree.clear();
			my_tree.display();
			break;		
		}

	} while (opt != '0');
}

int main([[maybe_unused]]int argc,[[maybe_unused]] char* argv[])
{

	char option;
	do{
		cout << endl;
		cout << "==== MENU GLOWNE ===" << endl;
		cout << "1.Tablica" << endl;
		cout << "2.Lista" << endl;
		cout << "3.Kopiec" << endl;
		cout << "4.Red-Black tree" << endl;
		cout << "5.Przeprowadz testy" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";		
		option = getche();
		cout << endl;

		switch (option){
		case '1':
			menu_table();
			break;

		case '2':
			menu_list();
			break;

		case '3':
			menu_heap();
			break;
		case '4':
			menu_tree();
			break;
		case '5':
			displayTestMenu();
			option = getche();

			meassure::perform_test(meassure::convert_to_TEST_TYPE(option),
								   meassure::convert_to_TEST_NAME(option));
			break;

		}

	} while (option != '0');
	

	return 0;
}

