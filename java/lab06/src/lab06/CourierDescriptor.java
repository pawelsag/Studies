package lab06;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class CourierDescriptor extends HostDescription{
	enum State{
		BUSY,
		FREE
	}
	boolean resignRequest = false;
	
	public String category;
	private State status = State.FREE;
	private CustomEvent packageDeiveredEvent = new CustomEvent();
	private CustomEvent newPackageAvailableEvent = new CustomEvent();
	private Dispositor parent;
	private Package packageToDeliver;
	
	public CourierDescriptor(String host, int port,String category, Dispositor instance ) {
		super( host.substring(1), port );
		this.category = category; 
		this.parent = instance;
	}
	
	Package getPackage() {
		return this.packageToDeliver;
	}
	
	@Override
	public void run() {
	
		while(!resignRequest) {
			
			// check for new packages
			Package p = parent.getPackage(this.category);
			
			// process new packages if there are some in warehouse		
			if(p == null) {
				// wait if there is no available packages in warehouse		
				newPackageAvailableEvent.lock();
				if(resignRequest)
					break;
				continue;
			}
			System.out.println(this.port + " PCKG taken");
			ClientDescriptor c = parent.findClientById(p.getclientId());
			c.respond(ClientDescriptor.PackageState.PACKAGE_PROCESS, p, "Courier took your packge ");
			this.deliverPackage(p);		
			// wait if there is no available packages in warehouse		
			System.out.println(this.port + " waiting");
			newPackageAvailableEvent.lock();
			// check again		
		}		
	}
	
	public void newPackageEvent() {
		if(this.status == State.BUSY)
			return;		
		this.newPackageAvailableEvent.unlockAll();
	}
	
	public State getStatus() {
		return this.status;
	}
	
	public Package packageDelivered() {
		
		this.status = State.FREE;
		this.packageDeiveredEvent.unlockAll();
		this.newPackageAvailableEvent.unlockAll();
		System.out.println(this.port + " delivered");
		return this.packageToDeliver;
	}
	// method to close communication with courier
	public void finishJob() {	
		resignRequest = true;
		if(this.status == State.BUSY)
			packageDeiveredEvent.lock();
		newPackageAvailableEvent.unlockAll();
	}
	
	public void deliverPackage(Package p) {
		
		if(this.status == State.BUSY)
			return;
		
		synchronized(packageDeiveredEvent) {
			this.status = State.BUSY;
			this.packageToDeliver = p;
			try (
				    Socket clientSocket = new Socket( this.host, this.port );
				    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
				){
				// forward package to courier
				out.println("3;" + p.getpckgId() + ";" + p.name);
				clientSocket.close();
				
			} catch (IOException e) {
				System.out.print("Can't send package to courier");
			}
		}	
	}		
}
