package lab04;

import javax.swing.JPanel;
import javax.swing.BoxLayout;
import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;
import javax.swing.JComboBox;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.awt.event.ActionEvent;

public class TestHandler extends JPanel {


	private static final long serialVersionUID = 1L;
	private JTextField textField;
	MainWindow parentInstance;
	JComboBox<Test> comboBox;
	/**
	 * Create the panel.
	 */
	public TestHandler(MainWindow parent) {
		this.parentInstance = parent;
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{0.0, 0.0, 1.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		JLabel lblNewLabel = new JLabel("Test Your Knowlage");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.gridwidth = 3;
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 0);
		gbc_lblNewLabel.gridx = 0;
		gbc_lblNewLabel.gridy = 0;
		add(lblNewLabel, gbc_lblNewLabel);
		
		JLabel lblNickname = new JLabel("Nickname: ");
		GridBagConstraints gbc_lblNickname = new GridBagConstraints();
		gbc_lblNickname.insets = new Insets(0, 0, 5, 5);
		gbc_lblNickname.anchor = GridBagConstraints.EAST;
		gbc_lblNickname.gridx = 1;
		gbc_lblNickname.gridy = 1;
		add(lblNickname, gbc_lblNickname);
		
		textField = new JTextField();
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.insets = new Insets(0, 0, 5, 0);
		gbc_textField.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField.gridx = 2;
		gbc_textField.gridy = 1;
		add(textField, gbc_textField);
		textField.setColumns(10);
		
		JLabel lblTestName = new JLabel("Test name:");
		GridBagConstraints gbc_lblTestName = new GridBagConstraints();
		gbc_lblTestName.anchor = GridBagConstraints.EAST;
		gbc_lblTestName.insets = new Insets(0, 0, 5, 5);
		gbc_lblTestName.gridx = 1;
		gbc_lblTestName.gridy = 2;
		add(lblTestName, gbc_lblTestName);
		
		comboBox = new JComboBox<Test>();
		GridBagConstraints gbc_comboBox = new GridBagConstraints();
		gbc_comboBox.insets = new Insets(0, 0, 5, 0);
		gbc_comboBox.fill = GridBagConstraints.HORIZONTAL;
		gbc_comboBox.gridx = 2;
		gbc_comboBox.gridy = 2;
		add(comboBox, gbc_comboBox);
		
		JButton btnPla = new JButton("Play");
		btnPla.addActionListener(parentInstance.new playTest());
		
		GridBagConstraints gbc_btnPla = new GridBagConstraints();
		gbc_btnPla.gridx = 2;
		gbc_btnPla.gridy = 3;
		add(btnPla, gbc_btnPla);
		
	}
	void clearTests() {
		comboBox.removeAllItems();
	}
	void addActiveTests(Test test) {
		comboBox.addItem(test);
	}
	
	Test getActiveTest() {
		return (Test) comboBox.getSelectedItem();
	}
	
	String getnickName() {
		return this.textField.getText();
	}
	
	boolean canTestBeStarted() {
		return (textField.getText().length() != 0);
	}
	
}
