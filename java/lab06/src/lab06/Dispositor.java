package lab06;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JTextPane;
import javax.swing.SwingConstants;

public class Dispositor extends JFrame {

	private JPanel contentPane;
	private JTextField Port;
	private JButton ConnectServer;
	private JButton NewClient;
	private JButton NewCourier;
	private JLabel label;
	private JTextPane messages;
	// server components
	private int currentPort = 0;
	ServerSocket serverSocket =null;
	// accepted clients descriptors
	ArrayList<ClientDescriptor> clientArray = new ArrayList<>();
	// accepted couriers descriptors
	ArrayList<CourierDescriptor> courierArray = new ArrayList<>();
	// warehouse
	ArrayList<Package> warehouse = new ArrayList<>();
	int warehouseLimit = 1;
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Dispositor frame = new Dispositor();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public Dispositor() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{0, 0, 0, 0, 0};
		gbl_contentPane.rowHeights = new int[]{0, 0, 0, 0, 0, 0};
		gbl_contentPane.columnWeights = new double[]{0.0, 1.0, 0.0, 1.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		contentPane.setLayout(gbl_contentPane);
		
		JLabel lblPort = new JLabel("Port");
		GridBagConstraints gbc_lblPort = new GridBagConstraints();
		gbc_lblPort.insets = new Insets(0, 0, 5, 5);
		gbc_lblPort.anchor = GridBagConstraints.EAST;
		gbc_lblPort.gridx = 0;
		gbc_lblPort.gridy = 0;
		contentPane.add(lblPort, gbc_lblPort);
		
		Port = new JTextField();
		GridBagConstraints gbc_Port = new GridBagConstraints();
		gbc_Port.insets = new Insets(0, 0, 5, 5);
		gbc_Port.fill = GridBagConstraints.HORIZONTAL;
		gbc_Port.gridx = 1;
		gbc_Port.gridy = 0;
		contentPane.add(Port, gbc_Port);
		Port.setColumns(10);
		
		ConnectServer = new JButton("Create dispatcher");
		GridBagConstraints gbc_ConnectServer = new GridBagConstraints();
		gbc_ConnectServer.insets = new Insets(0, 0, 5, 5);
		gbc_ConnectServer.gridx = 2;
		gbc_ConnectServer.gridy = 0;
		ConnectServer.addActionListener( new ConnectServerEvent() );
		contentPane.add(ConnectServer, gbc_ConnectServer);
		
		NewClient = new JButton("New Client");
		GridBagConstraints gbc_NewClient = new GridBagConstraints();
		gbc_NewClient.insets = new Insets(0, 0, 5, 5);
		gbc_NewClient.gridx = 1;
		gbc_NewClient.gridy = 1;
		NewClient.addActionListener( new CreateNewClientObjEvent() );
		contentPane.add(NewClient, gbc_NewClient);
		
		NewCourier = new JButton("New Courier ");
		GridBagConstraints gbc_NewCourier = new GridBagConstraints();
		gbc_NewCourier.insets = new Insets(0, 0, 5, 5);
		gbc_NewCourier.gridx = 1;
		gbc_NewCourier.gridy = 2;
		NewCourier.addActionListener( new CreateNewCourierObjEvent() );
		contentPane.add(NewCourier, gbc_NewCourier);
		
		JLabel lblWarehauseSpace = new JLabel("Warehouse space:");
		GridBagConstraints gbc_lblWarehauseSpace = new GridBagConstraints();
		gbc_lblWarehauseSpace.insets = new Insets(0, 0, 5, 5);
		gbc_lblWarehauseSpace.gridx = 1;
		gbc_lblWarehauseSpace.gridy = 3;
		contentPane.add(lblWarehauseSpace, gbc_lblWarehauseSpace);
		
		label = new JLabel("50");
		label.setHorizontalAlignment(SwingConstants.LEFT);
		GridBagConstraints gbc_label = new GridBagConstraints();
		gbc_label.insets = new Insets(0, 0, 5, 5);
		gbc_label.gridx = 2;
		gbc_label.gridy = 3;
		contentPane.add(label, gbc_label);
		
		messages = new JTextPane();
		messages.setEditable(false);
		GridBagConstraints gbc_messages = new GridBagConstraints();
		gbc_messages.gridwidth = 2;
		gbc_messages.insets = new Insets(0, 0, 0, 5);
		gbc_messages.fill = GridBagConstraints.BOTH;
		gbc_messages.gridx = 1;
		gbc_messages.gridy = 4;
		contentPane.add(messages, gbc_messages);
	}
	
	// hope java has generic so i can merge that two below methods
	public static void createClient() {
		
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Client frame = new Client();
					frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	public static void createCourier() {
			
			EventQueue.invokeLater(new Runnable() {
				public void run() {
					try {
						Courier frame = new Courier();
						frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
						frame.setVisible(true);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			});		
	}
	
	private class ListenForConnections extends Thread{
		
		public void run() {
			String[] request;
			int packetType;

			while(true) {
				try {
					// accept socket
	                Socket socket = serverSocket.accept();
	                // init readers and writers
	                BufferedReader in = new BufferedReader(
	                    new InputStreamReader( socket.getInputStream()) );
	                packetType = Integer.valueOf(in.readLine());
	                request = in.readLine().split(";");
	                manageRequest(socket, packetType,request);
				} catch (IOException e) {
	                System.out.println("I/O error: " + e);
	            }
			}
		}
	}
	
	void manageRequest(Socket s, int packetType, String[] args) {
		switch(packetType) {
			case 0x0:
				this.manageInitRequests(s.getInetAddress().toString(), args);
				break;
			case 0x1:
				break;
			case 0x2:
				break;
			case 0x3:
				break;
		}
	}
	// helper function to manage initializing tasks requests from client and courier
	void manageInitRequests(String host,String[] args) {
		int classType;
		int foreignPort;
		String pckgName, category;
		classType = Integer.valueOf(args[0]);
        foreignPort = Integer.valueOf(args[1]);
        category = args[2];
        // new thread for a client
        if(classType == 0x0) {
        	// create new client
        	ClientDescriptor client =  new ClientDescriptor( host,foreignPort);
        	ClientDescriptor result= findHost(clientArray,client);
        	if(result ==null)
        		clientArray.add( client );
        	
        	pckgName = args[3];
        	// create package
        	Package pckg = client.createPackge(pckgName, category);
        	// check if there is any courier available with given category
        	CourierDescriptor courier = findCourierByCategory(category); 
        	// if so hire courier to deliver package
        	if( courier != null ) {
        		client.respond(ClientDescriptor.PackageState.PACKAGE_PROCESS, pckg, " ");
        		courier.deliverPackage(pckg);
        		return;
        	}
        	// if there is no space in warehouse reject transaction  
        	else if(warehouse.size() >= warehouseLimit ){
        		client.respond(ClientDescriptor.PackageState.PACKAGE_REJECTED, pckg,"No avaliable courier and no space in warehouse");
        		return;
        	}
        	
        	// otherwise add package to warehouse and wait for courier
        	warehouse.add(pckg);
        	client.respond(ClientDescriptor.PackageState.PACKGAE_IN_WAREHOUSE, pckg, "Courier will take your package soon :)");
        	
		}else if(classType == 0x1) {
			
        	courierArray.add( new CourierDescriptor(host,foreignPort));
        	courierArray.get(courierArray.size()-1).start();
		}       
	}
	
	public static<T> T findHost(ArrayList<T> userArray, HostDescription user){
		String uniqueid= user.getuniqueId();
		for(T obj : userArray) {
			if(uniqueid.equals( ((HostDescription)obj).getuniqueId()) ){
				return ((T)obj);
			}
		}
		return null;
		
	}
	
	public CourierDescriptor findCourierByCategory(String category) {
		for(CourierDescriptor c : courierArray ) {
			if(c.category.equals(category) && c.getStatus() == CourierDescriptor.State.FREE )
				return c;
		}
		return null;
	}
	
	public
	class ConnectServerEvent implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent unused) {
			String portText = Port.getText();
			if( portText.length() == 0 )
				return;
			currentPort = Integer.parseInt( Port.getText() );
			
			if( serverSocket != null && !serverSocket.isClosed() )
				return;
			try {
				serverSocket = new ServerSocket( currentPort );
				System.out.println( "Dispositor Server created" );
				new ListenForConnections().start();
				
			} catch (IOException e) {
				System.out.print("Can't open server");
				e.printStackTrace();
			}
		}
	}
	
	class CreateNewClientObjEvent implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent unused) {
			createClient();
		}
	}
	
	class CreateNewCourierObjEvent implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent unused) {
			createCourier();
		}
	}
	
}
