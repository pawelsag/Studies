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
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.JButton;
import javax.swing.JComboBox;
import java.awt.Font;

public class Courier extends JFrame {

	private JPanel contentPane;
	private JTextArea messages;
	private JComboBox<String> CatrgoryBox;
	private JTextField textField;
	private JTextField textField_1;
	private JButton getPackge;
	private JLabel lblNewLabel_3;
	private JButton CreateServer;
	private JTextField ServerPort;
	private JLabel lblServer;

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
		
		JLabel lblNewLabel = new JLabel("Host:");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.anchor = GridBagConstraints.EAST;
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel.gridx = 0;
		gbc_lblNewLabel.gridy = 1;
		contentPane.add(lblNewLabel, gbc_lblNewLabel);
		
		textField = new JTextField();
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.insets = new Insets(0, 0, 5, 5);
		gbc_textField.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField.gridx = 1;
		gbc_textField.gridy = 1;
		contentPane.add(textField, gbc_textField);
		textField.setColumns(10);
		
		getPackge = new JButton("Get task");
		GridBagConstraints gbc_getPackge = new GridBagConstraints();
		gbc_getPackge.insets = new Insets(0, 0, 5, 0);
		gbc_getPackge.gridx = 2;
		gbc_getPackge.gridy = 1;
		contentPane.add(getPackge, gbc_getPackge);
		
		JLabel lblNewLabel_1 = new JLabel("Port:");
		GridBagConstraints gbc_lblNewLabel_1 = new GridBagConstraints();
		gbc_lblNewLabel_1.anchor = GridBagConstraints.EAST;
		gbc_lblNewLabel_1.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_1.gridx = 0;
		gbc_lblNewLabel_1.gridy = 2;
		contentPane.add(lblNewLabel_1, gbc_lblNewLabel_1);
		
		textField_1 = new JTextField();
		GridBagConstraints gbc_textField_1 = new GridBagConstraints();
		gbc_textField_1.insets = new Insets(0, 0, 5, 5);
		gbc_textField_1.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_1.gridx = 1;
		gbc_textField_1.gridy = 2;
		contentPane.add(textField_1, gbc_textField_1);
		textField_1.setColumns(10);
		
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
		
		CreateServer = new JButton("Create server");
		GridBagConstraints gbc_CreateServer = new GridBagConstraints();
		gbc_CreateServer.insets = new Insets(0, 0, 5, 5);
		gbc_CreateServer.gridx = 0;
		gbc_CreateServer.gridy = 6;
		contentPane.add(CreateServer, gbc_CreateServer);
		
		lblServer = new JLabel("Port");
		GridBagConstraints gbc_lblServer = new GridBagConstraints();
		gbc_lblServer.insets = new Insets(0, 0, 5, 5);
		gbc_lblServer.gridx = 0;
		gbc_lblServer.gridy = 8;
		contentPane.add(lblServer, gbc_lblServer);
		
		ServerPort = new JTextField();
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

}
