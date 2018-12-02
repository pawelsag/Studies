package lab04;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

import java.awt.GridBagLayout;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Random;

import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class TestManager extends JPanel {

	private static final long serialVersionUID = 1L;
	private Controller controller;
	private DefaultListModel<Question> qestionModel = new DefaultListModel<Question>();
	private DefaultListModel<Test> tModel = new DefaultListModel<Test>();
	private JList<Question> questionList;
	private JList<Test> testList;
	private JButton btnAddTest;
	private JButton btnRemoveTest;
	private JTextField testName;
	private JLabel lblTestName;
	
	public TestManager() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{1.0, 0.0, 1.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 1.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		btnAddTest= new JButton("Add Test");
		GridBagConstraints gbc_btnAddTest = new GridBagConstraints();
		gbc_btnAddTest.insets = new Insets(0, 0, 5, 5);
		gbc_btnAddTest.gridx = 0;
		gbc_btnAddTest.gridy = 0;
		add(btnAddTest, gbc_btnAddTest);
		
		btnRemoveTest = new JButton("Remove Test");
		GridBagConstraints gbc_btnRemoveTest = new GridBagConstraints();
		gbc_btnRemoveTest.insets = new Insets(0, 0, 5, 0);
		gbc_btnRemoveTest.gridx = 2;
		gbc_btnRemoveTest.gridy = 0;
		add(btnRemoveTest, gbc_btnRemoveTest);
		
		lblTestName = new JLabel("Test name:");
		GridBagConstraints gbc_lblTestName = new GridBagConstraints();
		gbc_lblTestName.insets = new Insets(0, 0, 5, 5);
		gbc_lblTestName.anchor = GridBagConstraints.EAST;
		gbc_lblTestName.gridx = 0;
		gbc_lblTestName.gridy = 1;
		add(lblTestName, gbc_lblTestName);
		
		testName = new JTextField();
		GridBagConstraints gbc_testName = new GridBagConstraints();
		gbc_testName.insets = new Insets(0, 0, 5, 5);
		gbc_testName.fill = GridBagConstraints.HORIZONTAL;
		gbc_testName.gridx = 1;
		gbc_testName.gridy = 1;
		add(testName, gbc_testName);
		testName.setColumns(10);
		
		questionList = new JList<Question>(qestionModel);
		GridBagConstraints gbc_questionList = new GridBagConstraints();
		gbc_questionList.gridwidth = 2;
		gbc_questionList.insets = new Insets(0, 0, 0, 5);
		gbc_questionList.fill = GridBagConstraints.BOTH;
		gbc_questionList.gridx = 0;
		gbc_questionList.gridy = 2;
		add(new JScrollPane(questionList), gbc_questionList);
		
		testList = new JList<Test>(tModel);
		GridBagConstraints gbc_testList = new GridBagConstraints();
		gbc_testList.fill = GridBagConstraints.BOTH;
		gbc_testList.gridx = 2;
		gbc_testList.gridy = 2;
		add(new JScrollPane(testList), gbc_testList);
		AddTestListener AddTestEvent = new AddTestListener();
		this.btnAddTest.addActionListener(AddTestEvent);
		RemoveTestListener removetestEvent = new RemoveTestListener();
		this.btnRemoveTest.addActionListener(removetestEvent);
		

	}
	
	void setController(Controller c) {
		this.controller = c;
		questionList.setModel(c.getQestionModel());
		qestionModel = (DefaultListModel<Question>) questionList.getModel();
		// after init do test
		this.testTestManger();
	}
	
	DefaultListModel<Test> getTestModel(){
		return this.tModel;
	}
	
	private class AddTestListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			if(questionList.getSelectedIndex() == -1)
			{
				JOptionPane.showMessageDialog(null, "Select question than add test", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			ArrayList<Question> qList= new ArrayList<Question>( (ArrayList<Question>) questionList.getSelectedValuesList());
			String name = testName.getText();
			if(name.length() == 0) {
				JOptionPane.showMessageDialog(null, "Type name for test", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			questionList.clearSelection();
			tModel.addElement( new Test(name,qList) );
		}
		
	}
	
	private class RemoveTestListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			int idx = testList.getSelectedIndex();
			if(idx == -1) {
				JOptionPane.showMessageDialog(null, "Select question to remove, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			tModel.removeElementAt(idx);
		}
	}
	
	private void testTestManger() {
		String name = "Test ";
		Random rand = new Random();
		int n;
		for(int i =1 ; i<= 4; i++) {
			ArrayList<Question> qList = new ArrayList<>();
			for(int j =0 ; j < 3; j++) {
				n = rand.nextInt( this.qestionModel.size() );
				qList.add(this.qestionModel.get(n));
			}
			tModel.addElement( new Test(name + i,qList) );
		}
	}
}
