package lab06;


import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class HostDescription extends Thread{
	public String host;
	public int port;
	protected String uniqueId;
	
	public HostDescription(String host, int port) {
		this.host = host;
		this.port = port;
		this.uniqueId = calculateUniqueId(this.host,this.port);
	}
	
	String getuniqueId() {
		return this.uniqueId;
	}
	
	static String calculateUniqueId(String host, int port) {
		String token = host + port;
		MessageDigest digest ;
		String uniqueid = null;
		try {
			digest = MessageDigest.getInstance("SHA-256");
			byte[] hash = digest.digest(token.getBytes(StandardCharsets.UTF_8));
			uniqueid =hash.toString();
			
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		return uniqueid;
	}
	
}
