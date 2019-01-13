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
		// previously there was sha256 algorithm to calculate token 
		return token;
	}
	
}
