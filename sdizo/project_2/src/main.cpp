// menu.cpp : Defines the entry point for the console application.
//

#include<conio.h>
#include<string>
#include<iostream>
#include "priority_queue.h"
#include "mst.h"
#include "list_template.h"
#include "common_struct.h"

using namespace std;

void displayMST(string info)
{
  cout << endl;
  cout << info << endl;
  cout << "1.Wczytaj z pliku" << endl;
  cout << "2.Algorytm Prima" << endl;
  cout << "3.Algorytm Kruskala" << endl;
  cout << "4.Utworz losowo" << endl;
  cout << "5.Wyswietl" << endl;
  cout << "0.Powrot do menu" << endl;
  cout << "Podaj opcje:";
}

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

void displayShortestPathMenu(string info)
{
  cout << endl;
  cout << info << endl;
  cout << "1.Wczytaj z pliku" << endl;
  cout << "2.Algorytm Dijsktry" << endl;
  cout << "3.Algorytm Forda Belmana" << endl;
  cout << "4.Utworz losowo" << endl;
  cout << "5.Wyswietl" << endl;
  cout << "0.Powrot do menu" << endl;
  cout << "Podaj opcje:";
}

void menu_MST()
{
  char opt;
  string fileName;
  int vertex_count, edge_count;
  
  MST my_mst;

  do{
    displayMST("--- MST ---");
    opt = getche();
    cout << endl;
    switch (opt){
    case '1': 
      cout << " Podaj nazwe zbioru:";
      cin >> fileName;
      my_mst.load_from_file(fileName);
      my_mst.display();
      break;
    case '2':
        my_mst.perform_prim();
        my_mst.display_result();
      break;
    case '3':
        my_mst.perform_kruskal();
        my_mst.display_result();
      break;
    case '4':  //tutaj generowanie  elementow do grafu
      cout << "Podaj ilosc wierzcholkow, a nastepnie ilosc krawedzi:";
      cin >> vertex_count >> edge_count;
      my_mst.generate_data(vertex_count, edge_count);
      my_mst.display();
      break;
    case '5':  //tutaj wyœwietlanie danych
      my_mst.display();
      break;   
    }
  }while (opt != '0');

}

void menu_heap()
{
  char opt;
  string fileName;
  N_list value;
  priority_queue<N_list> my_heap;

  do{
    displayMenu("--- HEAP ---");
    opt = getche();
    cout << endl;
    switch (opt){

    case '2': 
      cout << " podaj wartosc:";
      cin >> value.v;
      my_heap.remove(value);
      my_heap.display();
      break;

    case '3': 
      cout << " podaj vertex i waga:";
      cin >> value.v >> value.w ;
      my_heap.push_back(value);
      my_heap.display();      
      break;

    case '4': 
      cout << " podaj wartosc:";
      cin >> value.v;
      if (my_heap.find(value) == true)
        cout << "poadana wartosc jest w tablicy";
      else
        cout << "poadanej wartosci NIE ma w tablicy";
      break;

    case '6':  //tutaj wyœwietlanie tablicy
      my_heap.display();
      break;
    case '7':
      my_heap.clear();
      my_heap.display();
      break;    
    }

  } while (opt != '0');}

int main([[maybe_unused]]int argc,[[maybe_unused]] char* argv[])
{

  char option;
  do{
    cout << endl;
    cout << "==== MENU GLOWNE ===" << endl;
    cout << "1.Wyznaczanie minimalnego drzewa rozpinajacego" << endl;
    cout << "2.Wyznaczanie najkrotszej sciezki w grafie" << endl;
    cout << "Podaj opcje:";   
    option = getche();
    cout << endl;

    switch (option){
    case '1':
      menu_MST();
      break;
    case '2':
      menu_heap();
      break;

    }
    
  } while (option != '0');
  

  return 0;
}

