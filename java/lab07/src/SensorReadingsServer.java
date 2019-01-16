package lab07;

import java.awt.Color;
import java.awt.EventQueue;
import java.rmi.AccessException;
import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Random;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JButton;
import javax.swing.JSlider;

public class SensorReadingsServer extends JFrame{

	private JPanel contentPane;
	private JTextField sensorPort;
	private JTextField boardPort;
	private JLabel sensorValueDisplay;
	private JComboBox<String> sensorCategory;
	private JSlider freqSlider;
	private JButton register;
	private JButton unregister;
	private JButton sensorToggle;
	private JLabel stateDisplay;
	private JLabel freqValue;
	int speed = 1;
	int registeredCount =0;
	String sName = "wind";
	int localPort, foreignPort;
	boolean isActive = false, onceActivated = false;
	Meassurments meassuremntsObject;
	SensorReadings sensor;
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					SensorReadingsServer frame = new SensorReadingsServer();
					frame.setVisible(true);	
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	public SensorReadingsServer() {
		try {
			this.sensor  = new SensorReadings();
		} catch (RemoteException e1) {
		}
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{0, 0, 0, 0, 0, 0, 0};
		gbl_contentPane.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0};
		gbl_contentPane.columnWeights = new double[]{0.0, 0.0, 1.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		contentPane.setLayout(gbl_contentPane);
		
	
		
		JLabel lblState = new JLabel("State");
		GridBagConstraints gbc_lblState = new GridBagConstraints();
		gbc_lblState.insets = new Insets(0, 0, 5, 0);
		gbc_lblState.gridx = 5;
		gbc_lblState.gridy = 0;
		contentPane.add(lblState, gbc_lblState);
		
		JLabel lblSensorPort = new JLabel("Sensor port :");
		GridBagConstraints gbc_lblSensorPort = new GridBagConstraints();
		gbc_lblSensorPort.anchor = GridBagConstraints.EAST;
		gbc_lblSensorPort.insets = new Insets(0, 0, 5, 5);
		gbc_lblSensorPort.gridx = 1;
		gbc_lblSensorPort.gridy = 1;
		contentPane.add(lblSensorPort, gbc_lblSensorPort);
		
		sensorPort = new JTextField();
		sensorPort.setText("1234");
		GridBagConstraints gbc_sensorPort = new GridBagConstraints();
		gbc_sensorPort.fill = GridBagConstraints.HORIZONTAL;
		gbc_sensorPort.insets = new Insets(0, 0, 5, 5);
		gbc_sensorPort.gridx = 2;
		gbc_sensorPort.gridy = 1;
		contentPane.add(sensorPort, gbc_sensorPort);
		sensorPort.setColumns(10);
		
		stateDisplay = new JLabel("Inactive");
		GridBagConstraints gbc_stateDisplay = new GridBagConstraints();
		gbc_stateDisplay.insets = new Insets(0, 0, 5, 0);
		gbc_stateDisplay.gridx = 5;
		gbc_stateDisplay.gridy = 1;
		stateDisplay.setForeground(Color.RED);
		contentPane.add(stateDisplay, gbc_stateDisplay);
		
		JLabel lblSensorCategory = new JLabel("Sensor category:");
		GridBagConstraints gbc_lblSensorCategory = new GridBagConstraints();
		gbc_lblSensorCategory.insets = new Insets(0, 0, 5, 5);
		gbc_lblSensorCategory.anchor = GridBagConstraints.EAST;
		gbc_lblSensorCategory.gridx = 1;
		gbc_lblSensorCategory.gridy = 2;
		contentPane.add(lblSensorCategory, gbc_lblSensorCategory);
		
		sensorCategory = new JComboBox<>();
		GridBagConstraints gbc_sensorCategory = new GridBagConstraints();
		gbc_sensorCategory.fill = GridBagConstraints.HORIZONTAL;
		gbc_sensorCategory.insets = new Insets(0, 0, 5, 5);
		gbc_sensorCategory.gridx = 2;
		gbc_sensorCategory.gridy = 2;
		sensorCategory.addItem("Wind strength");
		sensorCategory.addItem("Temperature");
		sensorCategory.addItem("Precipitation");
		sensorCategory.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int c = sensorCategory.getSelectedIndex();
				if(c == 0) {
					sName = "wind";
					sensor.category = 'w';
				}else if(c == 1) {
					sName = "temp";
					sensor.category='t';
				}else {
					sName = "rain";
					sensor.category = 'p';
				}
			}		
		});
		contentPane.add(sensorCategory, gbc_sensorCategory);
		
		sensorToggle = new JButton("Toggle State");
		GridBagConstraints gbc_sensorToggle = new GridBagConstraints();
		gbc_sensorToggle.insets = new Insets(0, 0, 5, 0);
		gbc_sensorToggle.gridx = 5;
		gbc_sensorToggle.gridy = 2;
		sensorToggle.addActionListener(new ToggleEvent() );
		contentPane.add(sensorToggle, gbc_sensorToggle);
		
		JLabel lblCurrentReading = new JLabel("Current reading:");
		GridBagConstraints gbc_lblCurrentReading = new GridBagConstraints();
		gbc_lblCurrentReading.insets = new Insets(0, 0, 5, 5);
		gbc_lblCurrentReading.gridx = 1;
		gbc_lblCurrentReading.gridy = 3;
		contentPane.add(lblCurrentReading, gbc_lblCurrentReading);
		
		sensorValueDisplay = new JLabel("0.0");
		GridBagConstraints gbc_sensorValueDisplay = new GridBagConstraints();
		gbc_sensorValueDisplay.insets = new Insets(0, 0, 5, 5);
		gbc_sensorValueDisplay.anchor = GridBagConstraints.WEST;
		gbc_sensorValueDisplay.gridx = 2;
		gbc_sensorValueDisplay.gridy = 3;
		contentPane.add(sensorValueDisplay, gbc_sensorValueDisplay);
		
		JLabel lblNewLabel = new JLabel("Frequency in [s] :");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel.gridx = 1;
		gbc_lblNewLabel.gridy = 4;
		contentPane.add(lblNewLabel, gbc_lblNewLabel);
		
		freqSlider = new JSlider();
		freqSlider.setMaximum(20);
		freqSlider.setMinimum(1);
		freqSlider.setValue(1);
		GridBagConstraints gbc_freqSlider = new GridBagConstraints();
		gbc_freqSlider.fill = GridBagConstraints.HORIZONTAL;
		gbc_freqSlider.insets = new Insets(0, 0, 5, 5);
		gbc_freqSlider.gridx = 2;
		gbc_freqSlider.gridy = 4;
		
		freqSlider.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent arg0) {
				speed = freqSlider.getValue();
				freqValue.setText( String.valueOf(speed) ); 
			}
		});
		
		contentPane.add(freqSlider, gbc_freqSlider);
		
		freqValue = new JLabel("0");
		GridBagConstraints gbc_freqValue = new GridBagConstraints();
		gbc_freqValue.insets = new Insets(0, 0, 5, 5);
		gbc_freqValue.gridx = 3;
		gbc_freqValue.gridy = 4;
		contentPane.add(freqValue, gbc_freqValue);
		
		JLabel lblBoardPort = new JLabel("Board port :");
		GridBagConstraints gbc_lblBoardPort = new GridBagConstraints();
		gbc_lblBoardPort.anchor = GridBagConstraints.EAST;
		gbc_lblBoardPort.insets = new Insets(0, 0, 0, 5);
		gbc_lblBoardPort.gridx = 1;
		gbc_lblBoardPort.gridy = 6;
		contentPane.add(lblBoardPort, gbc_lblBoardPort);
		
		boardPort = new JTextField();
		boardPort.setText("1111");
		GridBagConstraints gbc_boardPort = new GridBagConstraints();
		gbc_boardPort.fill = GridBagConstraints.HORIZONTAL;
		gbc_boardPort.insets = new Insets(0, 0, 0, 5);
		gbc_boardPort.gridx = 2;
		gbc_boardPort.gridy = 6;
		contentPane.add(boardPort, gbc_boardPort);
		boardPort.setColumns(10);
		
		register = new JButton("Register");
		GridBagConstraints gbc_register = new GridBagConstraints();
		gbc_register.insets = new Insets(0, 0, 0, 5);
		gbc_register.gridwidth = 2;
		gbc_register.gridx = 3;
		gbc_register.gridy = 6;
		register.addActionListener(new Register() );
		contentPane.add(register, gbc_register);
		
		unregister = new JButton("Unregister");
		GridBagConstraints gbc_unregister = new GridBagConstraints();
		gbc_unregister.gridx = 5;
		gbc_unregister.gridy = 6;
		unregister.addActionListener(new Unregister() );
		contentPane.add(unregister, gbc_unregister);
 
		this.freqValue.setText( ""+this.freqSlider.getValue() );
		
	}
	
	class ToggleEvent implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			
			if( sensorPort.getText().length() == 0 ) {
				return;
			}
			
			try{localPort = Integer.valueOf(sensorPort.getText());}catch(Exception e) {return;};
								
			
			if(isActive == false) {
				Registry registry;
				try {
					if(onceActivated == false) {
						registry = LocateRegistry.createRegistry(localPort);
						
						onceActivated = true;
					}else
						registry = LocateRegistry.getRegistry(localPort);
					// Bind the remote object's stub in the registry
					ISensor stub = (ISensor) UnicastRemoteObject.exportObject(sensor, 0);
					registry.bind(sName, stub);
				} catch (RemoteException e1) {
					System.err.println("Sensor creation error: " + e1.toString());
					return;
				} catch (AlreadyBoundException e) {
					System.err.println("Sensor already bounded: " + e.toString());
					return;
				}
				
				stateDisplay.setText("Active");
				isActive = true;
				stateDisplay.setForeground(Color.GREEN);
				meassuremntsObject = new Meassurments();
				meassuremntsObject.start();
				sensorCategory.setEnabled(false);
				sensorPort.setEnabled(false);
			}else {
				if(registeredCount >0) return;
				try {
					LocateRegistry.getRegistry(localPort).unbind(sName);
					UnicastRemoteObject.unexportObject(sensor, true);
				} catch (AccessException e1) {
					System.err.println("Can't access register" + e1.toString());
				} catch (RemoteException e1) {
					System.err.println("Remote exception: " + e1.toString());
				} catch (NotBoundException e1) {
					System.err.println("Sensor hasn't been bounded " + e1.toString());
				}
				
				isActive = false;
				stateDisplay.setText("InActive");
				stateDisplay.setForeground(Color.RED);
				try {meassuremntsObject.join();} catch (InterruptedException e) {System.out.println(" can\'t join ");}
				System.out.println("Joined");
				sensorCategory.setEnabled(true);
				sensorPort.setEnabled(true);
				sensorValueDisplay.setText("0.0");
			}
		}
	}
	
	private class Register implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			if(isActive == false) return;
			int remotePort;
			try{ remotePort = Integer.valueOf(boardPort.getText()); }catch(Exception e1) {return;};
			
			try {
	            Registry registry = LocateRegistry.getRegistry(remotePort);
	            IBoard stub = (IBoard) registry.lookup("board");
	            
	            boolean response = stub.register((ISensor)LocateRegistry.getRegistry(localPort).lookup(sName), sensor.category );
	            if(response ==true) {
	            	System.out.println("Registration correct");
	            	registeredCount++;
	            }
	        } catch (Exception e2) {
	            System.err.println("Error during sensor registration: " + e2.toString());
	        }			
		}
	}
	
	private class Unregister implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			if(isActive == false) return;
			int remotePort;
			try{ remotePort = Integer.valueOf(boardPort.getText()); }catch(Exception e1) {return;};
			
			try {
	            Registry registry = LocateRegistry.getRegistry(remotePort);
	            IBoard stub = (IBoard) registry.lookup("board");
	            boolean response = stub.unregister((ISensor)LocateRegistry.getRegistry(localPort).lookup(sName));
	            if(response == true) {
	            	System.out.println("Unregistration correct");
	            	registeredCount--;
	            }
	            
	        } catch (Exception e2) {
	            System.err.println("Error during sensor unregistration: " + e2.toString());
	       
	        }			
		}
	}
	
	
	private class Meassurments extends Thread{
		@Override
		public void run() {
			Random rand = new Random();
			while(isActive) {
				sensor.value = rand.nextFloat();
				sensor.value = (float) (Math.round(sensor.value *1000)/100.0);
				sensorValueDisplay.setText(String.valueOf(sensor.value));
				try{Thread.sleep( speed *1000 );}catch(Exception e) { System.out.println("Sleep error" + e.getMessage() );}
			}
		}
	}

	
}
