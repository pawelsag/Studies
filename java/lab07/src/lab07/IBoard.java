package lab07;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IBoard extends Remote {
    boolean register(ISensor s, char category) throws RemoteException; 
    boolean unregister(ISensor s) throws RemoteException;
    void toggle() throws RemoteException; // prze³¹cznik w³¹cz/wy³¹cz zbierania i wyœwietlania danych na tablicy
    void setUpdateInterval(long milisec) throws RemoteException;
    BoardData getBoardData()  throws RemoteException;
}