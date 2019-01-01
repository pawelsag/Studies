package lab06;

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
import javax.swing.JComboBox;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.Font;
import java.awt.Color;

public class Client extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private JTextField PckgName;
	private JTextField Host;
	private JTextField Port;
	private JComboBox<String> Categorybox;
	private JTextArea messages;
	private JButton InstructButton;
	private JButton CreateServerButton;
	private JLabel lblNewLabel_1;
	private JTextField serverPort;
	private JLabel lblNewLabel_2;
	ServerSocket serverSocket =null;
	private JLabel activeLabel;
	
	/**
	 * Launch the application.
	 */

	/**
	 * Create the frame.
	 */
	public Client() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{0, 0, 0, 0};
		gbl_contentPane.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_contentPane.columnWeights = new double[]{1.0, 1.0, 0.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, Double.MIN_VALUE};
		contentPane.setLayout(gbl_contentPane);
		
		lblNewLabel_1 = new JLabel("Client");
		lblNewLabel_1.setFont(new Font("Dialog", Font.BOLD, 16));
		GridBagConstraints gbc_lblNewLabel_1 = new GridBagConstraints();
		gbc_lblNewLabel_1.gridwidth = 2;
		gbc_lblNewLabel_1.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_1.gridx = 0;
		gbc_lblNewLabel_1.gridy = 0;
		contentPane.add(lblNewLabel_1, gbc_lblNewLabel_1);
		
		JLabel PortinfoLabel = new JLabel("Port:");
		GridBagConstraints gbc_PortinfoLabel = new GridBagConstraints();
		gbc_PortinfoLabel.anchor = GridBagConstraints.EAST;
		gbc_PortinfoLabel.insets = new Insets(0, 0, 5, 5);
		gbc_PortinfoLabel.gridx = 0;
		gbc_PortinfoLabel.gridy = 1;
		contentPane.add(PortinfoLabel, gbc_PortinfoLabel);
		
		Port = new JTextField();
		Port.setText("1234");
		GridBagConstraints gbc_Port = new GridBagConstraints();
		gbc_Port.insets = new Insets(0, 0, 5, 5);
		gbc_Port.fill = GridBagConstraints.HORIZONTAL;
		gbc_Port.gridx = 1;
		gbc_Port.gridy = 1;
		contentPane.add(Port, gbc_Port);
		Port.setColumns(10);
		
		JLabel HostInfoLabel = new JLabel("Host:");
		GridBagConstraints gbc_HostInfoLabel = new GridBagConstraints();
		gbc_HostInfoLabel.anchor = GridBagConstraints.EAST;
		gbc_HostInfoLabel.insets = new Insets(0, 0, 5, 5);
		gbc_HostInfoLabel.gridx = 0;
		gbc_HostInfoLabel.gridy = 2;
		contentPane.add(HostInfoLabel, gbc_HostInfoLabel);
		
		Host = new JTextField();
		Host.setText("localhost");
		GridBagConstraints gbc_Host = new GridBagConstraints();
		gbc_Host.insets = new Insets(0, 0, 5, 5);
		gbc_Host.fill = GridBagConstraints.HORIZONTAL;
		gbc_Host.gridx = 1;
		gbc_Host.gridy = 2;
		contentPane.add(Host, gbc_Host);
		Host.setColumns(10);
		
		JLabel lblNewLabel = new JLabel("Package name:");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.anchor = GridBagConstraints.EAST;
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel.gridx = 0;
		gbc_lblNewLabel.gridy = 3;
		contentPane.add(lblNewLabel, gbc_lblNewLabel);
		
		PckgName = new JTextField();
		PckgName.setText("klocuszki");
		GridBagConstraints gbc_PckgName = new GridBagConstraints();
		gbc_PckgName.insets = new Insets(0, 0, 5, 5);
		gbc_PckgName.fill = GridBagConstraints.HORIZONTAL;
		gbc_PckgName.gridx = 1;
		gbc_PckgName.gridy = 3;
		contentPane.add(PckgName, gbc_PckgName);
		PckgName.setColumns(10);
		
		JLabel lblCategory = new JLabel("Category:");
		GridBagConstraints gbc_lblCategory = new GridBagConstraints();
		gbc_lblCategory.anchor = GridBagConstraints.EAST;
		gbc_lblCategory.insets = new Insets(0, 0, 5, 5);
		gbc_lblCategory.gridx = 0;
		gbc_lblCategory.gridy = 4;
		contentPane.add(lblCategory, gbc_lblCategory);
		
		Categorybox = new JComboBox<>();
		GridBagConstraints gbc_Categorybox = new GridBagConstraints();
		gbc_Categorybox.insets = new Insets(0, 0, 5, 5);
		gbc_Categorybox.fill = GridBagConstraints.HORIZONTAL;
		gbc_Categorybox.gridx = 1;
		gbc_Categorybox.gridy = 4;
		Categorybox.addItem(new String("Toys") );
		Categorybox.addItem(new String("Clothes") );
		Categorybox.addItem(new String("Jewelry") );
		
		contentPane.add(Categorybox, gbc_Categorybox);
		
		InstructButton = new JButton("Instruct task");
		GridBagConstraints gbc_InstructButton = new GridBagConstraints();
		gbc_InstructButton.insets = new Insets(0, 0, 5, 0);
		gbc_InstructButton.gridx = 2;
		gbc_InstructButton.gridy = 4;
		InstructButton.addActionListener(new SendRequestEvent() );
		contentPane.add(InstructButton, gbc_InstructButton);
		
		activeLabel = new JLabel("Active");
		activeLabel.setForeground(Color.RED);
		GridBagConstraints gbc_activeLabel = new GridBagConstraints();
		gbc_activeLabel.insets = new Insets(0, 0, 5, 5);
		gbc_activeLabel.gridx = 0;
		gbc_activeLabel.gridy = 5;
		contentPane.add(activeLabel, gbc_activeLabel);
		
		JLabel lblComunicates = new JLabel("Announcements:");
		GridBagConstraints gbc_lblComunicates = new GridBagConstraints();
		gbc_lblComunicates.insets = new Insets(0, 0, 5, 5);
		gbc_lblComunicates.gridx = 1;
		gbc_lblComunicates.gridy = 5;
		contentPane.add(lblComunicates, gbc_lblComunicates);
		
		CreateServerButton = new JButton("Create server");
		GridBagConstraints gbc_CreateServerButton = new GridBagConstraints();
		gbc_CreateServerButton.insets = new Insets(0, 0, 5, 5);
		gbc_CreateServerButton.gridx = 0;
		gbc_CreateServerButton.gridy = 6;
		CreateServerButton.addActionListener(new ConnectServerEvent());
		contentPane.add(CreateServerButton, gbc_CreateServerButton);
		
		messages = new JTextArea();
		messages.setEditable(false);
		GridBagConstraints gbc_messages = new GridBagConstraints();
		gbc_messages.gridheight = 3;
		gbc_messages.gridwidth = 2;
		gbc_messages.fill = GridBagConstraints.BOTH;
		gbc_messages.gridx = 1;
		gbc_messages.gridy = 6;
		contentPane.add(messages, gbc_messages);
		
		lblNewLabel_2 = new JLabel("Port");
		GridBagConstraints gbc_lblNewLabel_2 = new GridBagConstraints();
		gbc_lblNewLabel_2.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_2.gridx = 0;
		gbc_lblNewLabel_2.gridy = 7;
		contentPane.add(lblNewLabel_2, gbc_lblNewLabel_2);
		
		serverPort = new JTextField();
		serverPort.setText("5678");
		GridBagConstraints gbc_serverPort = new GridBagConstraints();
		gbc_serverPort.insets = new Insets(0, 0, 0, 5);
		gbc_serverPort.fill = GridBagConstraints.HORIZONTAL;
		gbc_serverPort.gridx = 0;
		gbc_serverPort.gridy = 8;
		contentPane.add(serverPort, gbc_serverPort);
		serverPort.setColumns(10);
	}
		
private class ListenForConnections extends Thread{
		
		public void run() {
			String line;
			
			while(true) {
				try {
					// accept socket
	                Socket socket = serverSocket.accept();
	                // catch stream for income requests
	                BufferedReader in = new BufferedReader(
	                    new InputStreamReader( socket.getInputStream()) );
					line = in.readLine();
					messages.setText(messages.getText() + line +"\n" );
					socket.close();
				
				} catch (IOException e) {
	                System.out.println("I/O error: " + e);
	            }
			}
		}
	}
	
	public
	class ConnectServerEvent implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent unused) {
			String portText = serverPort.getText();
		
			if( portText.length() == 0 )
				return;
			int currentPort = Integer.parseInt( portText );
			
			if( serverSocket != null && !serverSocket.isClosed() )
				return;
			try {
				serverSocket = new ServerSocket( currentPort );
				System.out.println( "Client's Server created" );
				new ListenForConnections().start();
				activeLabel.setForeground(Color.GREEN);
			} catch (IOException e) {
				System.out.print("Can't open server");
				e.printStackTrace();		
			}
		}
	}
	
	public
	class SendRequestEvent implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent unused) {
			String portText = Port.getText();
			String host = Host.getText();
			String pckgName = PckgName.getText();
			if( portText.length() == 0 || pckgName.length() == 0 || host.length() == 0 )
				return;
			
			if( serverSocket == null || serverSocket.isClosed() )
				return;
			
			try (
				    Socket clientSocket = new Socket( host,Integer.valueOf( Port.getText()) );
				    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
				){
				// send credits to dispositor including package request
				// class id | server port for incoming replays | category | pckgName
				out.println("0");
				out.println("0;" + serverPort.getText() + ";" + Categorybox.getSelectedItem().toString()+";" + pckgName );
				clientSocket.close();
				
			} catch (IOException e) {
				System.out.print("Can't open server");
				e.printStackTrace();
					
			}
		}
	}

}
