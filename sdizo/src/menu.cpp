// menu.cpp : Defines the entry point for the console application.
//


#include<conio.h>
#include<string>
#include<iostream>
#include "table.h"
#include "list.h"
#include "binary_heap.h"
#include "binary_tree.h"
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
	cout << "7.Test (pomiary)" << endl;
	cout << "8.Wyczysc wszystko" << endl;
	cout << "0.Powrot do menu" << endl;
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
			cout << " Podaj nazw� zbioru:";
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
				cout << "poadana warto�c jest w tablicy";
			else
				cout << "poadanej warto�ci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc element�w tablicy:";
			cin >> value;
			myTab.generate_data(value);
			myTab.display();
			break;
		case '6':  //tutaj wy�wietlanie tablicy
			myTab.display();
			break;
		case '7': 
				// pomiary
				
			break;
		case '8':
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
				cout << "poadana warto�c jest w tablicy";
			else
				cout << "poadanej warto�ci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc element�w tablicy:";
			cin >> value;
			my_list.generate_data(value);
			my_list.display();
			break;
		case '6':  //tutaj wy�wietlanie tablicy
			my_list.display();
			break;
		case '7': 
				// pomiary
			break;
		case '8':
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
				cout << "poadana warto�c jest w tablicy";
			else
				cout << "poadanej warto�ci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc element�w tablicy:";
			cin >> value;
			my_heap.generate_data(value);
			my_heap.display();
			break;
		case '6':  //tutaj wy�wietlanie tablicy
			my_heap.display();
			break;
		case '7': 
				// pomiary
			break;
		case '8':
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
	
	binary_tree my_tree;
	
	do{
		displayMenu("--- BINARY TREE ---");
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
				cout << "poadana warto�c jest w tablicy";
			else
				cout << "poadanej warto�ci NIE ma w tablicy";
			break;

		case '5':  //tutaj generowanie  tablicy
			cout << "Podaj ilosc element�w tablicy:";
			cin >> value;
			my_tree.generate_data(value);
			my_tree.display();
			break;
		case '6':  //tutaj wy�wietlanie tablicy
			my_tree.display();
			break;
		case '7': 
				// pomiary
			break;
		case '8':
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
		cout << "4.Binary search tree" << endl;
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
		}

	} while (option != '0');
	

	return 0;
}

