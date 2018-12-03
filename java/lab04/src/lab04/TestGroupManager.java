package lab04;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

import java.awt.GridBagLayout;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JLabel;
import javax.swing.ListSelectionModel;

public class TestGroupManager extends JPanel {

	private static final long serialVersionUID = 1L;
	private JTextField groupName;
	private JList<Test> testList;
	private JList<TestGroup> groupList;
	private JList<Test> t_InGroupsList;
	private Controller controller;
	DefaultListModel<Test> testModel = new DefaultListModel<Test>();
	DefaultListModel<TestGroup> groupModel = new DefaultListModel<TestGroup>();
	DefaultListModel<Test> connectedGroupModel = new DefaultListModel<Test>();
	
	/**
	 * Create the panel.
	 */
	public TestGroupManager() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{1.0, 0.0, 1.0, 1.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		JButton AddGroup = new JButton("Add Group");
		GridBagConstraints gbc_AddGroup = new GridBagConstraints();
		gbc_AddGroup.insets = new Insets(0, 0, 5, 5);
		gbc_AddGroup.gridx = 0;
		gbc_AddGroup.gridy = 0;
		add(AddGroup, gbc_AddGroup);
		
		JLabel lblGroupname = new JLabel("GroupName");
		GridBagConstraints gbc_lblGroupname = new GridBagConstraints();
		gbc_lblGroupname.insets = new Insets(0, 0, 5, 5);
		gbc_lblGroupname.anchor = GridBagConstraints.EAST;
		gbc_lblGroupname.gridx = 1;
		gbc_lblGroupname.gridy = 0;
		add(lblGroupname, gbc_lblGroupname);
		
		groupName = new JTextField();
		GridBagConstraints gbc_groupName = new GridBagConstraints();
		gbc_groupName.insets = new Insets(0, 0, 5, 5);
		gbc_groupName.fill = GridBagConstraints.HORIZONTAL;
		gbc_groupName.gridx = 2;
		gbc_groupName.gridy = 0;
		add(groupName, gbc_groupName);
		groupName.setColumns(10);
		
		JButton AssignTest = new JButton("Assign Test");
		GridBagConstraints gbc_AssignTest = new GridBagConstraints();
		gbc_AssignTest.insets = new Insets(0, 0, 5, 0);
		gbc_AssignTest.gridx = 3;
		gbc_AssignTest.gridy = 0;
		add(AssignTest, gbc_AssignTest);
		
		JButton RemoveGroup = new JButton("Remove Group");
		GridBagConstraints gbc_RemoveGroup = new GridBagConstraints();
		gbc_RemoveGroup.insets = new Insets(0, 0, 5, 5);
		gbc_RemoveGroup.gridx = 0;
		gbc_RemoveGroup.gridy = 1;
		add(RemoveGroup, gbc_RemoveGroup);
		
		JButton RemoveTest = new JButton("Remove Test");
		GridBagConstraints gbc_RemoveTest = new GridBagConstraints();
		gbc_RemoveTest.insets = new Insets(0, 0, 5, 0);
		gbc_RemoveTest.gridx = 3;
		gbc_RemoveTest.gridy = 1;
		add(RemoveTest, gbc_RemoveTest);
		
		JLabel lblQuestions = new JLabel("Tests");
		GridBagConstraints gbc_lblQuestions = new GridBagConstraints();
		gbc_lblQuestions.insets = new Insets(0, 0, 5, 5);
		gbc_lblQuestions.gridx = 0;
		gbc_lblQuestions.gridy = 2;
		add(lblQuestions, gbc_lblQuestions);
		
		JLabel lblGroups = new JLabel("Groups");
		GridBagConstraints gbc_lblGroups = new GridBagConstraints();
		gbc_lblGroups.gridwidth = 2;
		gbc_lblGroups.insets = new Insets(0, 0, 5, 5);
		gbc_lblGroups.gridx = 1;
		gbc_lblGroups.gridy = 2;
		add(lblGroups, gbc_lblGroups);
		
		JLabel lblQInGroup = new JLabel("T in Group");
		GridBagConstraints gbc_lblQInGroup = new GridBagConstraints();
		gbc_lblQInGroup.insets = new Insets(0, 0, 5, 0);
		gbc_lblQInGroup.gridx = 3;
		gbc_lblQInGroup.gridy = 2;
		add(lblQInGroup, gbc_lblQInGroup);
		
		testList = new JList<Test>();
		GridBagConstraints gbc_testList = new GridBagConstraints();
		gbc_testList.insets = new Insets(0, 0, 0, 5);
		gbc_testList.fill = GridBagConstraints.BOTH;
		gbc_testList.gridx = 0;
		gbc_testList.gridy = 3;
		add(new JScrollPane(testList), gbc_testList);
		
		groupList = new JList<TestGroup>(groupModel);
		groupList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		GridBagConstraints gbc_groupList = new GridBagConstraints();
		gbc_groupList.gridwidth = 2;
		gbc_groupList.insets = new Insets(0, 0, 0, 5);
		gbc_groupList.fill = GridBagConstraints.BOTH;
		gbc_groupList.gridx = 1;
		gbc_groupList.gridy = 3;
		add( new JScrollPane(groupList), gbc_groupList);
	
		t_InGroupsList = new JList<Test>(connectedGroupModel);
		
		GridBagConstraints gbc_t_InGroupsList = new GridBagConstraints();
		gbc_t_InGroupsList.fill = GridBagConstraints.BOTH;
		gbc_t_InGroupsList.gridx = 3;
		gbc_t_InGroupsList.gridy = 3;
		add(new JScrollPane(t_InGroupsList), gbc_t_InGroupsList);
		// add group button listener
		AddGroupListener groupAddEvent = new AddGroupListener();
		AddGroup.addActionListener(groupAddEvent);
		// remove group button listener
		RemoveGroupListener groupRemoveEvent = new RemoveGroupListener();
		RemoveGroup.addActionListener(groupRemoveEvent);
		// assign test to group button listener
		AddTestToGroupListener TestToGroupEvent = new AddTestToGroupListener();
		AssignTest.addActionListener(TestToGroupEvent);
		// remove test from group button listener
		RemoveTestInGroupListener TestFromGroupEvent = new RemoveTestInGroupListener();
		RemoveTest.addActionListener(TestFromGroupEvent);
		// handle mouse button click on group -> print all test in group
		MouseListsenr mouseEvent = new MouseListsenr();
		groupList.addMouseListener(mouseEvent);
		
	}
	
	void setController(Controller c) {
		this.controller = c;
		testModel = controller.getTestModel();
		this.testList.setModel(testModel);
		// do some tests
		doTestGroup();
	}
	
	private class MouseListsenr implements MouseListener{

		@Override
		public void mouseClicked(MouseEvent arg0) {
			connectedGroupModel = new DefaultListModel<Test>();
			int idx  = groupList.getSelectedIndex();
		
			groupModel.get(idx).gettests().forEach( (test)->{
				connectedGroupModel.addElement(test);
			});
			
			t_InGroupsList.setModel(connectedGroupModel);	
			
		}
		@Override
		public void mouseEntered(MouseEvent arg0) {}

		@Override
		public void mouseExited(MouseEvent arg0) {}

		@Override
		public void mousePressed(MouseEvent arg0) {}

		@Override
		public void mouseReleased(MouseEvent arg0) {}
		
	}
	private class AddGroupListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			String g_name = groupName.getText();
			if(g_name.length() == 0) {
				JOptionPane.showMessageDialog(null, "Type group name", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			groupModel.addElement( new TestGroup(g_name) );
			groupName.setText("");
		}
		
	}
	
	private class RemoveGroupListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			int idx = groupList.getSelectedIndex();
			if(idx == -1) {
				JOptionPane.showMessageDialog(null, "Select group to remove, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			groupModel.removeElementAt(idx);
		
		}	
	}
	
	private class AddTestToGroupListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			// get index of group
			int idx = groupList.getSelectedIndex();
			if(idx == -1) {
				JOptionPane.showMessageDialog(null, "Select group, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			//get indexes of tests
			if(testList.getSelectedIndex() == -1)
			{
				JOptionPane.showMessageDialog(null, "Select tests, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			ArrayList<Test> tList= new ArrayList<Test>( (ArrayList<Test>) testList.getSelectedValuesList());
			// assign test to group
			groupModel.getElementAt(idx).addTest(tList);
			testList.clearSelection();
			groupList.clearSelection();
		}	
	}
	
	
	private class RemoveTestInGroupListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			// get index of group
			// don't have to check for indexes, cause there is no possibility to print
			// tests in group without selecting group
			// so tests selection index validate both groupSelection and testsSelection 
			int idx = groupList.getSelectedIndex();
			
			//get indexes of tests
			if(t_InGroupsList.getSelectedIndex() == -1)
			{
				JOptionPane.showMessageDialog(null, "Select tests to remove, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			// remove test from group
			
			int[] selectedIx = t_InGroupsList.getSelectedIndices();
			int removedItems = 0; 
			for(int testIdx : selectedIx) {
				((DefaultListModel)t_InGroupsList.getModel()).remove(testIdx -removedItems );
				groupModel.get(idx).removeTest(testIdx - removedItems);
				removedItems++;
			}
			
		}	
	}
	
	private void doTestGroup() {
		String g_name = "G";
		for(int i =1; i <= 3 ;i++) {
			groupModel.addElement( new TestGroup(g_name + i) );
			for(int j = i-1; j <= i; j++)
				groupModel.getElementAt(i-1).addTest(testModel.getElementAt(j));
		}
	}

	void exportToDatabase(String fileName) throws IOException {
		BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
		String fmt =  TestGroup.getuniqueId() + "\n" ;
		for(int i = 0; i <this.groupModel.size(); i++) {
			fmt += groupModel.getElementAt(i).toDatabaseFormat() + "\n" ;
		}
		writer.write(fmt);
		writer.close();
	}
	
	void importFromDatabase(String fileName) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader(fileName));
		// clear old values
		groupModel.clear();
		// restore available tests
		testModel = controller.getTestModel();
		this.testList.setModel(testModel);
		// get uniqueId of our tests
		int uid  = Integer.valueOf(reader.readLine());
		String line;
		String []args;
		ArrayList<Test> availableTests;
		while( (line = reader.readLine()) != null ) {
			args = line.split(",");
			// read id of test
			int id = Integer.valueOf(args[0]);
			// read all questions
			availableTests = new ArrayList<Test>();
			for(int i = 1; i < args.length - 1; i++) {
				Test q = this.controller.getTestFromDataBase( Integer.valueOf(args[i]) );
				if(  q != null );
				availableTests.add(q);
			}
			// after reading questions and validation add new te
			this.groupModel.addElement(new TestGroup(id, args[args.length - 1], availableTests ) );
		}
		
		// restore uniqueID
		TestGroup.setuniqueId(uid);
		reader.close();
	}
}
