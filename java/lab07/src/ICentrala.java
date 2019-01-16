package lab07;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ICentrala extends Remote {
    int register(IBoard s) throws RemoteException; // zwraca numer przypisany do zarejestrowanej tablicy lub 0, je�li operacja si� nie uda�a
    int unregister(int id) throws RemoteException; // zwraca numer wyrejestrowanej tablicy lub 0, je�li operacja si� nie uda�a
}