package lab06;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.JButton;
import javax.swing.JComboBox;
import java.awt.Font;
import java.awt.Color;

public class Courier extends JFrame {

	private JPanel contentPane;
	private JTextArea messages;
	private JComboBox<String> CatrgoryBox;
	private JTextField Host;
	private JTextField Port;
	private JButton getPackage;
	private JLabel lblNewLabel_3;
	private JButton CreateServer;
	private JTextField ServerPort;
	private JLabel lblServer;
	private JButton Resign;
	ServerSocket serverSocket = null;
	String foreignHost;
	int foreignPort;
	int localPort;
	// variable check if courier has been created
	// cause new courier can be created only when old one 
	// resign
	boolean oldCorierStatus = true;
	// id of the taken package by courier
	// Necessary to inform dispacher class
	// about finished task
	String currentPackageid;
	private JLabel activeLabel;
	/**
	 * Create the frame.
	 */
	public Courier() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{0, 0, 0, 0};
		gbl_contentPane.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_contentPane.columnWeights = new double[]{1.0, 1.0, 0.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		contentPane.setLayout(gbl_contentPane);
		
		lblNewLabel_3 = new JLabel("Courier");
		lblNewLabel_3.setFont(new Font("Dialog", Font.BOLD, 16));
		GridBagConstraints gbc_lblNewLabel_3 = new GridBagConstraints();
		gbc_lblNewLabel_3.gridwidth = 2;
		gbc_lblNewLabel_3.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_3.gridx = 0;
		gbc_lblNewLabel_3.gridy = 0;
		contentPane.add(lblNewLabel_3, gbc_lblNewLabel_3);
		
		getPackage = new JButton("Get task");
		GridBagConstraints gbc_getPackage = new GridBagConstraints();
		gbc_getPackage.insets = new Insets(0, 0, 5, 0);
		gbc_getPackage.gridx = 2;
		gbc_getPackage.gridy = 1;
		getPackage.addActionListener( new SendRequestEvent());
		getPackage.addActionListener(new SendRequestEvent() );
		
		JLabel lblNewLabel_1 = new JLabel("Port:");
		GridBagConstraints gbc_lblNewLabel_1 = new GridBagConstraints();
		gbc_lblNewLabel_1.anchor = GridBagConstraints.EAST;
		gbc_lblNewLabel_1.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_1.gridx = 0;
		gbc_lblNewLabel_1.gridy = 1;
		contentPane.add(lblNewLabel_1, gbc_lblNewLabel_1);
		
		Port = new JTextField();
		Port.setText("1234");
		GridBagConstraints gbc_Port = new GridBagConstraints();
		gbc_Port.insets = new Insets(0, 0, 5, 5);
		gbc_Port.fill = GridBagConstraints.HORIZONTAL;
		gbc_Port.gridx = 1;
		gbc_Port.gridy = 1;
		contentPane.add(Port, gbc_Port);
		Port.setColumns(10);
		contentPane.add(getPackage, gbc_getPackage);
		
		JLabel lblNewLabel = new JLabel("Host:");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.anchor = GridBagConstraints.EAST;
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel.gridx = 0;
		gbc_lblNewLabel.gridy = 2;
		contentPane.add(lblNewLabel, gbc_lblNewLabel);
		
		Host = new JTextField();
		Host.setText("localhost");
		GridBagConstraints gbc_Host = new GridBagConstraints();
		gbc_Host.insets = new Insets(0, 0, 5, 5);
		gbc_Host.fill = GridBagConstraints.HORIZONTAL;
		gbc_Host.gridx = 1;
		gbc_Host.gridy = 2;
		contentPane.add(Host, gbc_Host);
		Host.setColumns(10);
		
		JLabel CategoryBoxLabel = new JLabel("Category:");
		GridBagConstraints gbc_CategoryBoxLabel = new GridBagConstraints();
		gbc_CategoryBoxLabel.anchor = GridBagConstraints.EAST;
		gbc_CategoryBoxLabel.insets = new Insets(0, 0, 5, 5);
		gbc_CategoryBoxLabel.gridx = 0;
		gbc_CategoryBoxLabel.gridy = 3;
		contentPane.add(CategoryBoxLabel, gbc_CategoryBoxLabel);
		
		CatrgoryBox = new JComboBox<>();
		GridBagConstraints gbc_CatrgoryBox = new GridBagConstraints();
		gbc_CatrgoryBox.insets = new Insets(0, 0, 5, 5);
		gbc_CatrgoryBox.fill = GridBagConstraints.HORIZONTAL;
		gbc_CatrgoryBox.gridx = 1;
		gbc_CatrgoryBox.gridy = 3;
		CatrgoryBox.addItem(new String("Toys") );
		CatrgoryBox.addItem(new String("Clothes") );
		CatrgoryBox.addItem(new String("Jewelry") );
		
		contentPane.add(CatrgoryBox, gbc_CatrgoryBox);
		
		JLabel lblNewLabel_2 = new JLabel("Announcements:");
		GridBagConstraints gbc_lblNewLabel_2 = new GridBagConstraints();
		gbc_lblNewLabel_2.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_2.gridx = 1;
		gbc_lblNewLabel_2.gridy = 4;
		contentPane.add(lblNewLabel_2, gbc_lblNewLabel_2);
		
		Resign = new JButton("Resign");
		GridBagConstraints gbc_Resign = new GridBagConstraints();
		gbc_Resign.insets = new Insets(0, 0, 5, 5);
		gbc_Resign.gridx = 0;
		gbc_Resign.gridy = 6;
		Resign.addActionListener(new ResignRequest() );
		
		activeLabel = new JLabel("Active");
		activeLabel.setForeground(Color.RED);
		GridBagConstraints gbc_activeLabel = new GridBagConstraints();
		gbc_activeLabel.insets = new Insets(0, 0, 5, 5);
		gbc_activeLabel.gridx = 0;
		gbc_activeLabel.gridy = 5;
		contentPane.add(activeLabel, gbc_activeLabel);
		contentPane.add(Resign, gbc_Resign);
		
		CreateServer = new JButton("Create server");
		GridBagConstraints gbc_CreateServer = new GridBagConstraints();
		gbc_CreateServer.insets = new Insets(0, 0, 5, 5);
		gbc_CreateServer.gridx = 0;
		gbc_CreateServer.gridy = 7;
		CreateServer.addActionListener( new ConnectServerEvent());
		contentPane.add(CreateServer, gbc_CreateServer);
		
		lblServer = new JLabel("Port");
		GridBagConstraints gbc_lblServer = new GridBagConstraints();
		gbc_lblServer.insets = new Insets(0, 0, 5, 5);
		gbc_lblServer.gridx = 0;
		gbc_lblServer.gridy = 8;
		contentPane.add(lblServer, gbc_lblServer);
		
		ServerPort = new JTextField();
		ServerPort.setText("8956");
		GridBagConstraints gbc_ServerPort = new GridBagConstraints();
		gbc_ServerPort.anchor = GridBagConstraints.WEST;
		gbc_ServerPort.insets = new Insets(0, 0, 0, 5);
		gbc_ServerPort.gridx = 0;
		gbc_ServerPort.gridy = 9;
		contentPane.add(ServerPort, gbc_ServerPort);
		ServerPort.setColumns(10);
		
		messages = new JTextArea();
		messages.setEditable(false);
		GridBagConstraints gbc_messages = new GridBagConstraints();
		gbc_messages.gridheight = 5;
		gbc_messages.gridwidth = 2;
		gbc_messages.fill = GridBagConstraints.BOTH;
		gbc_messages.gridx = 1;
		gbc_messages.gridy = 5;
		contentPane.add(messages, gbc_messages);
	}
	
	public
	class SendRequestEvent implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent unused) {
			// if old courier hasn't fished his job yet
			// do not create new courier
			if(!oldCorierStatus) return;
			
			String portText = Port.getText();
			foreignHost = Host.getText();
						
			if( portText.length() == 0 || foreignHost.length() == 0 )
				return;
			
			if( serverSocket == null || serverSocket.isClosed() )
				return;
			
			foreignPort = Integer.valueOf( portText );
			
			try (
				    Socket clientSocket = new Socket( foreignHost,foreignPort );
				    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
				){
				// send credits to dispositor including package request
				// class id | server port for incoming replays | category | pckgName
				out.println( "0");
				out.println("1;" + ServerPort.getText() + ";" + CatrgoryBox.getSelectedItem().toString() );
				oldCorierStatus = false;
				clientSocket.close();
				
			} catch (IOException e) {
				System.out.print("Can't open server");
				e.printStackTrace();				
			}
		}
	}
	private class ResignRequest implements ActionListener {
		
		@Override
		public void actionPerformed(ActionEvent arg0) {
			
			if(oldCorierStatus) return;
			
			if( serverSocket == null || serverSocket.isClosed() )
				return;
			try (
				    Socket clientSocket = new Socket( foreignHost,foreignPort );
				    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
				){
				// send credits to dispositor including package request
				// send request id | port to identification
				out.println("2");
				out.println( ServerPort.getText() );
				clientSocket.close();
				serverSocket.close();
				oldCorierStatus = true;
				activeLabel.setForeground(Color.RED);
			} catch (IOException e) {
				System.out.print("Can't open server");
				e.printStackTrace();
			}			
		}
	}
	
	private class ListenForConnections extends Thread{
		
		public void run() {
			String[] line;
			int packetType;
			String packetName;
			while(true) {
				try {
					// accept socket
	                Socket socket = serverSocket.accept();
	                // catch stream for income requests
	                BufferedReader in = new BufferedReader(
	                    new InputStreamReader( socket.getInputStream()) );
					// get new task 
	                line = in.readLine().split(";");
					packetType = Integer.valueOf(line[0]);
					currentPackageid = line[1];
					packetName = line[2];
					messages.setText(messages.getText() + packetName + "<-- processing\n"   );
					doSomeJob();
					messages.setText(messages.getText() + packetName + "<-- task done\n"   );
					socket.close();		
				} catch (IOException e) {
	                System.out.println("I/O error: " + e);
	                break;
	            }
			}
		}
	}
	
	public void doSomeJob() {
		// simulate courier's job :)
		try {Thread.sleep(5000);} catch (InterruptedException e) {}
		finishTask();
	}
	
	public void finishTask() {		
		try (
			    Socket clientSocket = new Socket( foreignHost, foreignPort );
			    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
			)
		{
			// ping server, that courier fished his job
			out.println("1");
			out.println( currentPackageid );
			
			clientSocket.close();	
		} catch (IOException e) {
			System.out.print("Can't open server");
			e.printStackTrace();
		}		
	}
	
	public
	class ConnectServerEvent implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent unused) {
			String portText = ServerPort.getText();
		
			if( portText.length() == 0 )
				return;
			localPort = Integer.parseInt( portText );
			
			if( serverSocket != null && !serverSocket.isClosed() )
				return;
			try {
				serverSocket = new ServerSocket( localPort );
				System.out.println( "Courier's Server created" );
				new ListenForConnections().start();
				activeLabel.setForeground(Color.GREEN);
			} catch (IOException e) {
				System.out.print("Can't open server");
				e.printStackTrace();		
			}
		}
	}

}
