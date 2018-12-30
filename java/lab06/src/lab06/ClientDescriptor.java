package lab06;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientDescriptor extends HostDescription{
	
	enum PackageState {
		PACKAGE_PROCESS,
		PACKGAE_IN_WAREHOUSE,
		PACKAGE_DELIVERED,
		PACKAGE_REJECTED,
	}
	
	public ClientDescriptor(String host, int port) {
		super(host.substring(1), port);
	}
	
	Package createPackge(String pName, String pCategory) {
		return new Package(this.uniqueId,pName,pCategory);		
	}
	
	void respond(PackageState s, Package p, String info) {

		try (
			    Socket clientSocket = new Socket( this.host,Integer.valueOf( this.port ) );
			    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
			){
			// respond to client about current package status
			out.println( s.toString() +  " Package name: " + p.name + ", info: " + info );
			clientSocket.close();
			
		} catch (IOException e) {
			System.out.print("Can't open server");
			e.printStackTrace();
				
		}
	}

}
