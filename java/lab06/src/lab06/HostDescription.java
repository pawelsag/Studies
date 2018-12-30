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
		String text = host + port;
		MessageDigest digest ;
		try {
			digest = MessageDigest.getInstance("SHA-256");
			byte[] hash = digest.digest(text.getBytes(StandardCharsets.UTF_8));
			this.uniqueId =hash.toString();
			
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}		
	}
	
}
