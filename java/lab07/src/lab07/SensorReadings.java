package lab07;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class SensorReadings implements ISensor, Serializable {
	public char category = 'w'; // 't' - temperature, 'w' - wind, 'p' - precipitation
	public float value=(float) 0.0; // wartoœæ, której jednostka zale¿y od kategorii
	protected SensorReadings() throws RemoteException {
		super();
	}
	SensorReadings(char c, float v) throws RemoteException{
		super();
		this.category = c;
		this.value =v;
	}
	
	@Override
	public SensorReadings getSensorReadings() throws RemoteException {
		return new SensorReadings(this.category,this.value);
	}
	

}
