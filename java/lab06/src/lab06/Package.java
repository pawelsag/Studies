package lab06;

public class Package {
	
	private String clientId;
	public String name;
	public String Category; 
	Package(String id, String name,String Category){
		this.clientId = id;
		this.name = name;
		this.Category = Category;
	}
	public Package(Package p) {
		if (p ==null)
			return;
		this.clientId = p.clientId;
		this.name = p.name;
		this.Category = p.Category;
	}
	
	String getclientId() {
		return this.clientId;
	}
}
