package lab06;

public class Package {
	static int uniqueID =0;
	private String packageId;
	private String clientId;
	public String name;
	public String Category; 
	Package(String id, String name,String Category){
		this.clientId = id;
		this.name = name;
		this.Category = Category;
		this.packageId = this.clientId + uniqueID;
		uniqueID++;
	}
	public Package(Package p) {
		if (p ==null)
			return;
		this.clientId = p.clientId;
		this.packageId = p.packageId;
		this.name = p.name;
		this.Category = p.Category;

	}
	
	String getclientId() {
		return this.clientId;
	}
	String getpckgId() {
		return this.packageId;
	}
}
