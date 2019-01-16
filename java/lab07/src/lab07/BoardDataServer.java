package lab07;

import java.awt.EventQueue;
import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Color;
import javax.swing.JTextField;
import javax.swing.JButton;

public class BoardDataServer extends JFrame{

	private JPanel contentPane;
	private JTextField localPort;
	BoardData board;
	private JLabel windState;
	private JLabel windValue;
	private JLabel tempState;
	private JLabel tempValue;
	private JLabel rainState;
	private JLabel rainValue;
	private JTextField centralPort;
	private JButton registerBoard;
	private JButton unregisterBoard;
	boolean isActive = false;
	int localPortValue;
	ArrayList<stubRegister> stubArray = new ArrayList<>();
	private JLabel lblId;
	private JLabel remoteId;
	
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					BoardDataServer frame = new BoardDataServer();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	
	
	public BoardDataServer() {
		try {board = new BoardData(this);} catch (RemoteException e) {}
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 631, 139);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_contentPane.rowHeights = new int[]{0, 0, 0, 0, 0, 0};
		gbl_contentPane.columnWeights = new double[]{0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		contentPane.setLayout(gbl_contentPane);
		
		lblId = new JLabel("ID");
		GridBagConstraints gbc_lblId = new GridBagConstraints();
		gbc_lblId.insets = new Insets(0, 0, 5, 5);
		gbc_lblId.gridx = 0;
		gbc_lblId.gridy = 0;
		contentPane.add(lblId, gbc_lblId);
		
		JLabel lblWindStrength = new JLabel("Wind strength");
		lblWindStrength.setForeground(Color.BLUE);
		GridBagConstraints gbc_lblWindStrength = new GridBagConstraints();
		gbc_lblWindStrength.gridwidth = 3;
		gbc_lblWindStrength.insets = new Insets(0, 0, 5, 5);
		gbc_lblWindStrength.gridx = 1;
		gbc_lblWindStrength.gridy = 0;
		contentPane.add(lblWindStrength, gbc_lblWindStrength);
		
		JLabel lblTemperature = new JLabel("Temperature");
		lblTemperature.setForeground(Color.BLUE);
		GridBagConstraints gbc_lblTemperature = new GridBagConstraints();
		gbc_lblTemperature.gridwidth = 3;
		gbc_lblTemperature.insets = new Insets(0, 0, 5, 5);
		gbc_lblTemperature.gridx = 5;
		gbc_lblTemperature.gridy = 0;
		contentPane.add(lblTemperature, gbc_lblTemperature);
		
		JLabel lblRainfall = new JLabel("Rainfall");
		lblRainfall.setForeground(Color.BLUE);
		GridBagConstraints gbc_lblRainfall = new GridBagConstraints();
		gbc_lblRainfall.insets = new Insets(0, 0, 5, 0);
		gbc_lblRainfall.gridx = 9;
		gbc_lblRainfall.gridy = 0;
		contentPane.add(lblRainfall, gbc_lblRainfall);
		
		remoteId = new JLabel("None");
		GridBagConstraints gbc_remoteId = new GridBagConstraints();
		gbc_remoteId.insets = new Insets(0, 0, 5, 5);
		gbc_remoteId.gridx = 0;
		gbc_remoteId.gridy = 1;
		contentPane.add(remoteId, gbc_remoteId);
		
		windState = new JLabel("Inactive");
		windState.setForeground(Color.RED);
		GridBagConstraints gbc_windState = new GridBagConstraints();
		gbc_windState.gridwidth = 3;
		gbc_windState.insets = new Insets(0, 0, 5, 5);
		gbc_windState.gridx = 1;
		gbc_windState.gridy = 1;
		contentPane.add(windState, gbc_windState);
		
		tempState = new JLabel("Incactive");
		tempState.setForeground(Color.RED);
		GridBagConstraints gbc_tempState = new GridBagConstraints();
		gbc_tempState.gridwidth = 3;
		gbc_tempState.insets = new Insets(0, 0, 5, 5);
		gbc_tempState.gridx = 5;
		gbc_tempState.gridy = 1;
		contentPane.add(tempState, gbc_tempState);
		
		rainState = new JLabel("Inactive");
		rainState.setForeground(Color.RED);
		GridBagConstraints gbc_rainState = new GridBagConstraints();
		gbc_rainState.insets = new Insets(0, 0, 5, 0);
		gbc_rainState.gridx = 9;
		gbc_rainState.gridy = 1;
		contentPane.add(rainState, gbc_rainState);
		
		JLabel label = new JLabel("");
		GridBagConstraints gbc_label = new GridBagConstraints();
		gbc_label.insets = new Insets(0, 0, 5, 5);
		gbc_label.gridx = 1;
		gbc_label.gridy = 2;
		contentPane.add(label, gbc_label);
		
		JLabel lblValue = new JLabel("Value:");
		GridBagConstraints gbc_lblValue = new GridBagConstraints();
		gbc_lblValue.insets = new Insets(0, 0, 5, 5);
		gbc_lblValue.gridx = 0;
		gbc_lblValue.gridy = 3;
		contentPane.add(lblValue, gbc_lblValue);
		
		windValue = new JLabel("0.0");
		GridBagConstraints gbc_windValue = new GridBagConstraints();
		gbc_windValue.gridwidth = 3;
		gbc_windValue.insets = new Insets(0, 0, 5, 5);
		gbc_windValue.gridx = 1;
		gbc_windValue.gridy = 3;
		contentPane.add(windValue, gbc_windValue);
		
		JLabel label_4 = new JLabel("Value:");
		GridBagConstraints gbc_label_4 = new GridBagConstraints();
		gbc_label_4.insets = new Insets(0, 0, 5, 5);
		gbc_label_4.gridx = 4;
		gbc_label_4.gridy = 3;
		contentPane.add(label_4, gbc_label_4);
		
		tempValue = new JLabel("0.0");
		GridBagConstraints gbc_tempValue = new GridBagConstraints();
		gbc_tempValue.gridwidth = 3;
		gbc_tempValue.insets = new Insets(0, 0, 5, 5);
		gbc_tempValue.gridx = 5;
		gbc_tempValue.gridy = 3;
		contentPane.add(tempValue, gbc_tempValue);
		
		JLabel label_5 = new JLabel("Value:");
		GridBagConstraints gbc_label_5 = new GridBagConstraints();
		gbc_label_5.insets = new Insets(0, 0, 5, 5);
		gbc_label_5.gridx = 8;
		gbc_label_5.gridy = 3;
		contentPane.add(label_5, gbc_label_5);
		
		rainValue = new JLabel("0.0");
		GridBagConstraints gbc_rainValue = new GridBagConstraints();
		gbc_rainValue.insets = new Insets(0, 0, 5, 0);
		gbc_rainValue.gridx = 9;
		gbc_rainValue.gridy = 3;
		contentPane.add(rainValue, gbc_rainValue);
		
		JLabel lblPort = new JLabel("Port");
		GridBagConstraints gbc_lblPort = new GridBagConstraints();
		gbc_lblPort.anchor = GridBagConstraints.EAST;
		gbc_lblPort.insets = new Insets(0, 0, 0, 5);
		gbc_lblPort.gridx = 0;
		gbc_lblPort.gridy = 4;
		contentPane.add(lblPort, gbc_lblPort);
		
		localPort = new JTextField();
		localPort.setText("1111");
		GridBagConstraints gbc_localPort = new GridBagConstraints();
		gbc_localPort.gridwidth = 2;
		gbc_localPort.insets = new Insets(0, 0, 0, 5);
		gbc_localPort.fill = GridBagConstraints.HORIZONTAL;
		gbc_localPort.gridx = 1;
		gbc_localPort.gridy = 4;
		contentPane.add(localPort, gbc_localPort);
		localPort.setColumns(10);
		
		JButton btnRegister = new JButton("Create");
		GridBagConstraints gbc_btnRegister = new GridBagConstraints();
		gbc_btnRegister.insets = new Insets(0, 0, 0, 5);
		gbc_btnRegister.gridx = 3;
		gbc_btnRegister.gridy = 4;
		btnRegister.addActionListener(new RegisterServer() );
		contentPane.add(btnRegister, gbc_btnRegister);
		
		JLabel lblPort_1 = new JLabel("Port");
		GridBagConstraints gbc_lblPort_1 = new GridBagConstraints();
		gbc_lblPort_1.insets = new Insets(0, 0, 0, 5);
		gbc_lblPort_1.anchor = GridBagConstraints.EAST;
		gbc_lblPort_1.gridx = 4;
		gbc_lblPort_1.gridy = 4;
		contentPane.add(lblPort_1, gbc_lblPort_1);
		
		centralPort = new JTextField();
		centralPort.setText("1282");
		GridBagConstraints gbc_centralPort = new GridBagConstraints();
		gbc_centralPort.gridwidth = 2;
		gbc_centralPort.insets = new Insets(0, 0, 0, 5);
		gbc_centralPort.fill = GridBagConstraints.HORIZONTAL;
		gbc_centralPort.gridx = 5;
		gbc_centralPort.gridy = 4;
		contentPane.add(centralPort, gbc_centralPort);
		centralPort.setColumns(10);
		
		registerBoard = new JButton("Register");
		GridBagConstraints gbc_registerBoard = new GridBagConstraints();
		gbc_registerBoard.anchor = GridBagConstraints.WEST;
		gbc_registerBoard.insets = new Insets(0, 0, 0, 5);
		gbc_registerBoard.gridx = 7;
		gbc_registerBoard.gridy = 4;
		registerBoard.addActionListener( new Register());
		contentPane.add(registerBoard, gbc_registerBoard);
		
		unregisterBoard = new JButton("Unregister");
		GridBagConstraints gbc_unregisterBoard = new GridBagConstraints();
		gbc_unregisterBoard.insets = new Insets(0, 0, 0, 5);
		gbc_unregisterBoard.gridx = 8;
		gbc_unregisterBoard.gridy = 4;
		unregisterBoard.addActionListener(new Unregister() );
		contentPane.add(unregisterBoard, gbc_unregisterBoard);
		
		
		
	}
	void changeIfaceState(char category, boolean action) {
		// if action == false unregister event happened
		// otherwise register event happened
		switch(category) {
		case 't':
			if(action) {
				this.tempState.setText("Active");
				this.tempState.setForeground(Color.GREEN);
			}else {
				this.tempState.setText("InActive");
				this.tempState.setForeground(Color.RED);
				this.tempValue.setText("0.0");
			}	
			break;
		case 'w':
			if(action) {
				this.windState.setText("Active");
				this.windState.setForeground(Color.GREEN);
			}else {
				this.windState.setText("InActive");
				this.windState.setForeground(Color.RED);
				this.windValue.setText("0.0");
			}
			break;
		case 'p':
			if(action) {
				this.rainState.setText("Active");
				this.rainState.setForeground(Color.GREEN);
			}else {
				this.rainState.setText("InActive");
				this.rainState.setForeground(Color.RED);
				this.rainValue.setText("0.0");
			}
			break;
		}
		
	}
	
	void precipationReadings(float value) {
		this.rainValue.setText(String.valueOf(value));
	}
	
	void windReadings(float value) {
		this.windValue.setText(String.valueOf(value));	
	}
	
	void tempReadings(float value) {
		this.tempValue.setText(String.valueOf(value));
	}
	
	private class Register implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			if(isActive == false) return;
			int remotePort;
			try{ remotePort = Integer.valueOf(centralPort.getText()); }catch(Exception e1) {return;};
			
			try {
				
	            Registry registry = LocateRegistry.getRegistry(remotePort);	         
	            ICentrala stub = (ICentrala) registry.lookup("central");	         
	            int response = stub.register( (IBoard)LocateRegistry.getRegistry(localPortValue).lookup("board") );
	            if( response != 0 ) {
	            	// if stub was registered, add info about assign stub to port
	            	stubArray.add(new stubRegister(response,remotePort) );
	            	remoteId.setText(String.valueOf( response ));
	            }
	            
	        }catch (Exception e2) {
	            System.err.println("Registration failed " + e2.toString());
	        }
		}

		
	}
	
	
	private class Unregister implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			if(isActive == false) return;
			int remotePort;
			try{ remotePort = Integer.valueOf(centralPort.getText()); }catch(Exception e1) {return;};
			
			try {
	            Registry registry = LocateRegistry.getRegistry(remotePort);
	            ICentrala stub = (ICentrala) registry.lookup("central");
	            
	            stubRegister instance =findStub(remotePort);
	            if(instance == null )return;
	            int response = stub.unregister( instance.id );
	            if(response != 0) {
	            	stubArray.remove(instance);
	            	remoteId.setText("None");
	            }
	            
	        } catch (Exception e2) {
	            System.err.println("Unregistration failed " + e2.toString());
	            
	        }			
		}
	}
	
	public stubRegister findStub(int port) {
		for(stubRegister reg : stubArray)
			if(reg.port == port) return reg;
		
		return null;
	}
	
	private class RegisterServer implements ActionListener{
		
		@Override
		public void actionPerformed(ActionEvent arg0) {
			Registry registry;
			if(isActive == true) return;		
			try {
				
				try{localPortValue = Integer.valueOf(localPort.getText());}catch(Exception e) {return;};
				registry = LocateRegistry.createRegistry(localPortValue);
				IBoard stub = (IBoard) UnicastRemoteObject.exportObject(board, 0);
				// Bind the remote object's stub in the registry
				registry.bind("board", board);
				isActive =true;
			} catch (RemoteException e1) {
				System.out.println("Remote exception " + e1.getMessage());
			} catch (AlreadyBoundException e) {
				System.out.println("Obejct was already bound" + e.getMessage());
			}	
		}
	}
	
	private class stubRegister{
		int port, id;
		stubRegister(int id, int port){
			this.id = id;
			this.port = port;
		}
	}

}
