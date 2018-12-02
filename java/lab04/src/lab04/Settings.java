package lab04;

import javax.swing.JPanel;
import java.awt.GridBagLayout;
import javax.swing.JTextField;
import java.awt.GridBagConstraints;
import javax.swing.JLabel;
import java.awt.Insets;
import javax.swing.JButton;

public class Settings extends JPanel {


	private static final long serialVersionUID = 1L;
	private JTextField textField;
	JButton btnExportSettings;
	JButton btnImportSettings;
	Controller controller;
	public Settings() {
		
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		JLabel lblFilename = new JLabel("FileName:");
		GridBagConstraints gbc_lblFilename = new GridBagConstraints();
		gbc_lblFilename.insets = new Insets(0, 0, 5, 5);
		gbc_lblFilename.gridx = 1;
		gbc_lblFilename.gridy = 0;
		add(lblFilename, gbc_lblFilename);
		
		textField = new JTextField();
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.insets = new Insets(0, 0, 5, 0);
		gbc_textField.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField.gridx = 3;
		gbc_textField.gridy = 0;
		add(textField, gbc_textField);
		textField.setColumns(10);
		
		btnExportSettings = new JButton("Export Settings");
		GridBagConstraints gbc_btnExportSettings = new GridBagConstraints();
		gbc_btnExportSettings.insets = new Insets(0, 0, 5, 0);
		gbc_btnExportSettings.gridx = 3;
		gbc_btnExportSettings.gridy = 1;
		add(btnExportSettings, gbc_btnExportSettings);
		
		btnImportSettings = new JButton("Import Settings");
		GridBagConstraints gbc_btnImportSettings = new GridBagConstraints();
		gbc_btnImportSettings.gridx = 3;
		gbc_btnImportSettings.gridy = 2;
		add(btnImportSettings, gbc_btnImportSettings);
		
	
	}
	
	void setController(Controller c) {
		controller = c;
		// set export event listener
		Controller.ExportEventListener exportEvent = controller.new ExportEventListener();
		btnExportSettings.addActionListener(exportEvent);
		// set import event listener 
		Controller.ImportEventListener importEvent = controller.new ImportEventListener();
		btnImportSettings.addActionListener(importEvent);
	}
	
	String getFileName() {
		return this.textField.getText();
	}
	

}
