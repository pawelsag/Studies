package lab07;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IBoard extends Remote {
    boolean register(ISensor s, char category) throws RemoteException; 
    boolean unregister(ISensor s) throws RemoteException;
    void toggle() throws RemoteException; // prze��cznik w��cz/wy��cz zbierania i wy�wietlania danych na tablicy
    void setUpdateInterval(long milisec) throws RemoteException;
    BoardData getBoardData()  throws RemoteException;
}