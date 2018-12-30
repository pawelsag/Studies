package lab06;

public class CourierDescriptor extends HostDescription{
	enum State{
		BUSY,
		FREE
	}
	
	public String category;
	private State status = State.FREE;
	
	public CourierDescriptor(String host, int port ) {
		super( host, port );
		String category = getCategor();
		this.category = category; 
	}
	
	private String getCategor() {
		// TODO Auto-generated method stub
		return null;
	}
	
	public State getStatus() {
		return this.status;
	}
	public void deliverPackage(Package p) {
		this.status = State.BUSY;
	
	}
	

}
