// menu.cpp : Defines the entry point for the console application.
//

#include<conio.h>
#include<string>
#include<iostream>
#include "priority_queue.h"
#include "mst.h"
#include "list_template.h"
#include "common_struct.h"
#include "path_finding.h"
#include "test_module.h"

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
  int vertex_count;
  double edge_fill;
  
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
      break;
    case '3':
        my_mst.perform_kruskal();
      break;
    case '4':  //tutaj generowanie  elementow do grafu
      cout << "Podaj ilosc wierzcholkow, a nastepnie ilosc krawedzi w %:";
      cin >> vertex_count >> edge_fill;
      my_mst.generate_data(vertex_count, edge_fill);
      my_mst.display();
      break;
    case '5':  //tutaj wyœwietlanie danych
      my_mst.display();
      break;   
    }
  }while (opt != '0');

}

void menu_PATH()
{
  
  char opt;
  string fileName;
  int vertex_count, begin_vertex;
  double edge_fill;
  
  path_finding my_pf;

  do{
    displayShortestPathMenu("--- PATH FINDING PROBLEM ---");
    opt = getche();
    cout << endl;
    switch (opt){
    case '1': 
      cout << " Podaj nazwe zbioru:";
      cin >> fileName;
      my_pf.load_from_file(fileName);
      my_pf.display();
      break;
    case '2':
        my_pf.perform_dijkstry();
      break;
    case '3':
        my_pf.perform_ford_belman();
      break;
    case '4':  //tutaj generowanie  elementow do grafu
      cout << "Podaj ilosc wierzcholkow, a nastepnie ilosc krawedzi w [%] oraz wierzcholek poczatkowy:";
      cin >> vertex_count >> edge_fill >> begin_vertex;
      my_pf.generate_data(vertex_count, edge_fill, begin_vertex);
      my_pf.display();
      break;
    case '5':  //tutaj wyœwietlanie danych
      my_pf.display();
      break;   
    }
  }while (opt != '0');

}

int main([[maybe_unused]]int argc,[[maybe_unused]] char* argv[])
{
  graph_tester test;
  char option;
  do{
    cout << endl;
    cout << "==== MENU GLOWNE ===" << endl;
    cout << "1.Wyznaczanie minimalnego drzewa rozpinajacego" << endl;
    cout << "2.Wyznaczanie najkrotszej sciezki w grafie" << endl;
    cout << "3.Przeprowadz testy:"<<endl;
    cout << "Podaj opcje:";   
    option = getche();
    cout << endl;

    switch (option){
    case '1':
      menu_MST();
      break;
    case '2':
      menu_PATH();
      break;
    case '3':
      test.run_test();
      break;
    }
    
  } while (option != '0');
  

  return 0;
}

