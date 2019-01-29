package lab07;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.DefaultCellEditor;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JScrollBar;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.JScrollPane;
import javax.swing.JSlider;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.JTextField;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;

public class Central extends JFrame implements ICentrala {

	private JPanel contentPane;
	private JTable table;
	// start count id from 1, because 0 is reserved for error id value 
	private int boardId = 1;
	private ArrayList<stubRegister> stubArray = new ArrayList<>();
	private boolean isActive =false;
	private static Registry registry;
	public static int centralPort = 1282;
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Central frame = new Central();
					frame.setVisible(true);
					
					registry = LocateRegistry.createRegistry(centralPort);
					ICentrala stub = (ICentrala) UnicastRemoteObject.exportObject( frame, 0);
					// Bind the remote object's stub in the registry
					registry.bind("central", frame);	
					
				}catch (RemoteException e1) {
					System.out.println("Remote exception " + e1.getMessage());
				}catch (AlreadyBoundException e) {
					System.out.println("obejct already bind " + e.getMessage());
				}catch (Exception e) {
					System.out.println(e.getMessage());
				}
				
			}
		});
	}


	public Central() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 1006, 439);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{0, 982, 0, 0};
		gbl_contentPane.rowHeights = new int[]{26, 339, 0, 0};
		gbl_contentPane.columnWeights = new double[]{0.0, 1.0, 0.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 0.0, Double.MIN_VALUE};
		contentPane.setLayout(gbl_contentPane);
		
		JLabel lblCentral = new JLabel("Central");
		lblCentral.setHorizontalAlignment(SwingConstants.CENTER);
		lblCentral.setFont(new Font("Tahoma", Font.BOLD, 21));
		lblCentral.setForeground(Color.BLACK);
		GridBagConstraints gbc_lblCentral = new GridBagConstraints();
		gbc_lblCentral.anchor = GridBagConstraints.NORTH;
		gbc_lblCentral.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblCentral.insets = new Insets(0, 0, 5, 5);
		gbc_lblCentral.gridx = 1;
		gbc_lblCentral.gridy = 0;
		contentPane.add(lblCentral, gbc_lblCentral);
		
		JScrollPane scrollPane = new JScrollPane();
		GridBagConstraints gbc_scrollPane = new GridBagConstraints();
		gbc_scrollPane.gridheight = 2;
		gbc_scrollPane.gridwidth = 3;
		gbc_scrollPane.insets = new Insets(0, 0, 5, 5);
		gbc_scrollPane.fill = GridBagConstraints.BOTH;
		gbc_scrollPane.gridx = 0;
		gbc_scrollPane.gridy = 1;
		contentPane.add(scrollPane, gbc_scrollPane);
		
		table = new JTable();
		
		scrollPane.setViewportView(table);
		table.setModel(new MyTableModel(
			new Object[][] {},
			new String[] {
				"ID", "Wind Readings", "Temp Readings", "Precipation Readings", "Toggle", "Interval"
			}) {
				private static final long serialVersionUID = -6997572805462762718L;
			Class[] columnTypes = new Class[] {
				Long.class, Float.class, Float.class, Float.class, Object.class, Object.class
			};
			public Class getColumnClass(int columnIndex) {
				return columnTypes[columnIndex];
			}
		});
		table.getColumnModel().getColumn(1).setPreferredWidth(116);
		table.getColumnModel().getColumn(2).setPreferredWidth(116);
		table.getColumnModel().getColumn(3).setPreferredWidth(116);
		table.getColumnModel().getColumn(4).setPreferredWidth(90);
		table.getColumnModel().getColumn(5).setPreferredWidth(104);
		
		table.getColumn("Toggle").setCellRenderer( new ButtonRenderer());
		table.getColumn("Toggle").setCellEditor( new ButtonEditor(new JCheckBox()) );
		table.getColumn("Interval").setCellRenderer( new SliderRenderer(JSlider.HORIZONTAL, 1, 20, 1));
		table.getColumn("Interval").setCellEditor( new SliderEditor(JSlider.HORIZONTAL, 1, 20, 1) );
		
	}
	
	
	@Override
	public int register(IBoard s) throws RemoteException {
		if(isStubExist(s) == true) return 0;
		
		BoardData board= s.getBoardData();
		if(board == null) return 0;
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		if(model == null) return 0;	
		model.addRow(new Object[]{boardId, board.wind, board.temperature,board.precipation,new JButton("Toggle"),new JSlider() });
		
		if(stubArray.add(new stubRegister(boardId, s)) ==false) return 0;
		registry.rebind("board_" + boardId, s);
		
		return boardId++;
	}
	

	@Override
	public int unregister(int id) throws RemoteException {
		
		DefaultTableModel model = (DefaultTableModel) table.getModel();
	
		int i = findRowById(id);
		if(i == -1) return 0;
		stubArray.get(i).reader.active = false;
		stubArray.remove(i);
		model.removeRow(i);
		
		try {registry.unbind( "board_" + id);} catch (NotBoundException e) {e.printStackTrace();}
		return id;
	}
	
	private int findRowById(int id) {
		int i =0;
		for(stubRegister s : stubArray) {
			if(s.id == id) 				
				return i;
			i++;
		}	
		return -1;
	}
	private boolean isStubExist(IBoard s) {
		for(stubRegister stub : stubArray )
			if(stub.stub.equals(s))
				return true;
		return false;
	}
	private class stubRegister{
		public int id;
		public IBoard stub;
		BoardManager reader = new BoardManager(this);
		stubRegister(int id, IBoard iface){
			this.id = id;
			this.stub = iface;
			reader.start();
		}
		
	}
	 private class BoardManager extends Thread{
			public stubRegister stubReference;
			public boolean active = false;
			
			BoardManager(stubRegister s){
				this.stubReference= s;
				this.active =true;
			}
			
			@Override	
			public void run() {
				
				while(active) {			
					try {
						BoardData board = stubReference.stub.getBoardData();
						int i = findRowById(stubReference.id);
						DefaultTableModel model = (DefaultTableModel) table.getModel();			
						model.setValueAt(board.wind, i, 1);
						model.setValueAt(board.temperature, i, 2);
						model.setValueAt(board.precipation, i, 3);
						
					} catch (RemoteException e1) {
						// if we get here probably our board has crushed
						
						try {unregister(stubReference.id);}catch (RemoteException e) {System.out.println(e.getMessage());}
					}	
					try { Thread.sleep( 1000 );} catch (InterruptedException e) {}
				}
			}	
		}
	
	
	public class MyTableModel extends DefaultTableModel {

	      public MyTableModel(Object[][] objects, String[] strings) {
			super(objects,strings);	
		}

		public boolean isCellEditable(int row, int column){ 

			if(column == 4 || column == 5) return true;
	          return false;  
	    }
	}
	
	class ButtonRenderer extends JButton implements TableCellRenderer {

		  public ButtonRenderer() {
		    setOpaque(true);
		  }

		  public Component getTableCellRendererComponent(JTable table, Object value,
		      boolean isSelected, boolean hasFocus, int row, int column) {
		    if (isSelected) {
		      setForeground(table.getSelectionForeground());
		      setBackground(table.getSelectionBackground());
		      
		    } else {
		      setForeground(table.getForeground());
		      setBackground(UIManager.getColor("Button.background"));
		    }
		    setText((value == null) ? "" : "Toggle");
		    return this;
		  }
		}


		class ButtonEditor extends DefaultCellEditor {
		  protected JButton button;

		  private String label;

		  private boolean isPushed;

		  public ButtonEditor(JCheckBox checkBox) {
		    super(checkBox);
		    button = new JButton();
		    button.setOpaque(true);
		    button.addActionListener(new ActionListener() {
		      public void actionPerformed(ActionEvent e) {
		    	  int selectedId = table.getSelectedRow() + 1;
		    	  for(stubRegister s : stubArray) {
		    		  if(s.id == selectedId) {
		    			  try {s.stub.toggle();} catch (RemoteException e1) {System.out.println(e1.getMessage());}
		    			  break;
		    		  }
		    	  }
		      }
		    });
		  }

		  public Component getTableCellEditorComponent(JTable table, Object value,
		      boolean isSelected, int row, int column) {
		    if (isSelected) {
		      button.setForeground(table.getSelectionForeground());
		      button.setBackground(table.getSelectionBackground());
		    } else {
		      button.setForeground(table.getForeground());
		      button.setBackground(table.getBackground());
		    }
		    label = (value == null) ? "" : "Toggle";
		    button.setText(label);
		    isPushed = true;
		    return button;
		  }

		  public Object getCellEditorValue() {
		    isPushed = false;
		    return new String(label);
		  }  
		}
		
		
		class SliderRenderer extends JSlider implements TableCellRenderer {

				public SliderRenderer(int orientation, int min, int max, int value) {
			      super(orientation, min, max, value);
			   }

			  public Component getTableCellRendererComponent(JTable table, Object value,
			      boolean isSelected, boolean hasFocus, int row, int column) {
			    if (isSelected) {
			      setForeground(table.getSelectionForeground());
			      setBackground(table.getSelectionBackground());
			    } else {
			      setForeground(table.getForeground());
			      setBackground(UIManager.getColor("Button.background"));
			      
			    }
			    if(value instanceof Integer)
			    	setValue(((Integer) value).intValue());
			    else
			    	setValue(((JSlider)value).getValue());
			    updateUI();
			    return this;
			  }
			  
			}
		
		class SliderEditor extends DefaultCellEditor {
			  protected JSlider slider;

			  public SliderEditor(int orientation, int min, int max, int value) {
			      super(new JCheckBox());
			      slider = new JSlider(orientation, min, max, value);     
			      slider.setOpaque(true);
			      slider.addMouseListener((new MouseListener() {
	
						@Override
						public void mouseClicked(MouseEvent arg0) {
							return;
						}

						@Override
						public void mouseEntered(MouseEvent arg0) {
							return;
						}

						@Override
						public void mouseExited(MouseEvent arg0) {
							return;
						}

						@Override
						public void mousePressed(MouseEvent arg0) {
							return;
						}
						
						@Override
						public void mouseReleased(MouseEvent arg0) {
							int selectedId = table.getSelectedRow() + 1;
							for(stubRegister s : stubArray) {
					    		  if(s.id == selectedId) {
					    			  try {s.stub.setUpdateInterval(slider.getValue());} catch (RemoteException e1) {System.out.println(e1.getMessage());}
					    			  break;
					    		  }
					    	}
						}
				    }));
			  }		 
			 
			  
			  public Component getTableCellEditorComponent(JTable table, Object value,
			      boolean isSelected, int row, int column) {
			    if (isSelected) {
			    	slider.setForeground(table.getSelectionForeground());
			    	slider.setBackground(table.getSelectionBackground());
			    	
			    } else {
			    	slider.setForeground(table.getForeground());
			    	slider.setBackground(table.getBackground());
			    	
			    }
			    if(value instanceof Integer)
			    	slider.setValue(((Integer) value).intValue());
			    else
			    	slider.setValue(((JSlider) value).getValue());
			    return slider;
			  }

			  public Object getCellEditorValue() {
			      return new Integer(slider.getValue());
			   }
			  
			   public boolean stopCellEditing() {
			      return super.stopCellEditing();
			   }
			  
			   protected void fireEditingStopped() {
			      super.fireEditingStopped();
			   }
			  
			}

			
	
}
