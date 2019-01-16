package lab07;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ISensor extends Remote {
    SensorReadings getSensorReadings() throws RemoteException;;
}