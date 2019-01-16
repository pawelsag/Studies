package lab07;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

public class BoardData  implements IBoard, Serializable  {
	 public float temperature;
	 public float wind;
	 public float precipation;
	 
	 private boolean boardActive =false;
	 private long interval =1;
	 private BoardDataServer parent;
	 ArrayList<SensorManager> sensors = new ArrayList<>(); 
	
	protected BoardData(BoardDataServer p) throws RemoteException {
		super();
		this.parent = p;
		boardActive = true;
	}
	BoardData(float temperature2, float wind2, float precipation2) throws RemoteException {
		this.temperature =temperature2;
		this.wind = wind2;
		this.precipation = precipation2;	
	}
	@Override
	public boolean register(ISensor s, char category) throws RemoteException {
		if(sensors.size() >= 3)
			return false;
		if( checkSensor(category)== true ) return false;
		SensorManager instance = new SensorManager(s,category);
		sensors.add(instance);
		instance.start();
		
		this.parent.changeIfaceState( category, true);
		System.out.println("Registered");
		
		return true;
	}

	@Override
	public boolean unregister(ISensor s) throws RemoteException {
		for (SensorManager sm :sensors)
			if( sm.iface.equals(s) ) {
				sm.setActive(false);
				// wake board to escape from while loop
				boardActive = true;
				sensors.remove(sm);
				this.parent.changeIfaceState(sm.category, false);
				
				return true;
			}
		return false;
	}

	@Override
	public void toggle() throws RemoteException {
		if(this.boardActive) this.boardActive =false;
		else this.boardActive =true;
	}

	@Override
	public void setUpdateInterval(long milisec) throws RemoteException {
		this.interval = milisec;
	}
	
	@Override
	public BoardData getBoardData() throws RemoteException {
		try {return new BoardData(this.temperature, this.wind, this.precipation);}
		catch (RemoteException e) {return null;}
	}
	
	private boolean checkSensor(char category){
		for (SensorManager sm :sensors)
			if(sm.category == category)
				return true;
		return false;
	}
	
	private class SensorManager extends Thread{
		public ISensor iface;
		public char category;
		private boolean active =false;
		
		SensorManager(ISensor s, char c){
			this.iface = s;
			this.category = c;
			this.active =true;
		}
		
		void setActive(boolean state) {
			this.active =state;
		}
		
		@Override	
		public void run() {
			while(active) {			
				try {
					SensorReadings obj = iface.getSensorReadings();
					switch(category) {
						case 'w':
							wind =obj.value;
							parent.windReadings(wind);
							break;
						case 't':
							temperature =obj.value;
							parent.tempReadings(temperature);
							break;
						case 'p':
							parent.precipationReadings(precipation);
							precipation =obj.value;
							break;
					}
					
					
				} catch (RemoteException e1) {
					// if we get here probably our sensor has crushed
					try {unregister(iface);}
					catch (RemoteException e) {System.out.println(e1.getMessage());}
				}
				
				try { Thread.sleep( interval *1000 );} catch (InterruptedException e) {}			
				// if central turn off board with reading values, wait for wake up signal
				while(!boardActive) try { Thread.sleep( 0 );} catch (InterruptedException e) {}
			}
		}	
	}
	
}
