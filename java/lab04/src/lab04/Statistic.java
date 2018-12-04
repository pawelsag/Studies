package lab04;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.NoSuchElementException;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import javax.swing.JComboBox;
import java.awt.Insets;
import javax.swing.JList;

public class Statistic extends JPanel {

	private static final long serialVersionUID = 1L;
	ArrayList<Result> results = new ArrayList<>();
	private final JLabel lblAvergeForE = new JLabel("Averge for every test in group");
	private JComboBox<Test> testList;
	private JComboBox<Result> userList;
	private JComboBox<Test> TestList_2;
	private JLabel avgUsers;
	private JLabel avgtest;
	private JComboBox<TestGroup> testGroups;
	private JLabel lblNewLabel;
	private JLabel lblNewLabel_1;
	public Statistic() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		JLabel lblUserAveragePoints = new JLabel("User average points in test ");
		GridBagConstraints gbc_lblUserAveragePoints = new GridBagConstraints();
		gbc_lblUserAveragePoints.insets = new Insets(0, 0, 5, 5);
		gbc_lblUserAveragePoints.gridx = 1;
		gbc_lblUserAveragePoints.gridy = 0;
		add(lblUserAveragePoints, gbc_lblUserAveragePoints);
		
		testList = new JComboBox<Test>();
		GridBagConstraints gbc_testList = new GridBagConstraints();
		gbc_testList.insets = new Insets(0, 0, 5, 5);
		gbc_testList.fill = GridBagConstraints.HORIZONTAL;
		gbc_testList.gridx = 1;
		gbc_testList.gridy = 1;
		add(testList, gbc_testList);
		
		userList = new JComboBox<Result>();
		GridBagConstraints gbc_userList = new GridBagConstraints();
		gbc_userList.insets = new Insets(0, 0, 5, 5);
		gbc_userList.fill = GridBagConstraints.HORIZONTAL;
		gbc_userList.gridx = 2;
		gbc_userList.gridy = 1;
		add(userList, gbc_userList);
		
		JLabel lblAveragePoints = new JLabel("Average : ");
		GridBagConstraints gbc_lblAveragePoints = new GridBagConstraints();
		gbc_lblAveragePoints.insets = new Insets(0, 0, 5, 5);
		gbc_lblAveragePoints.gridx = 3;
		gbc_lblAveragePoints.gridy = 1;
		add(lblAveragePoints, gbc_lblAveragePoints);
		
		avgUsers = new JLabel("0");
		GridBagConstraints gbc_avgUsers = new GridBagConstraints();
		gbc_avgUsers.insets = new Insets(0, 0, 5, 5);
		gbc_avgUsers.gridx = 4;
		gbc_avgUsers.gridy = 1;
		add(avgUsers, gbc_avgUsers);
		
		JLabel lblTestResultAverage = new JLabel("Test result average in regard to other tests");
		GridBagConstraints gbc_lblTestResultAverage = new GridBagConstraints();
		gbc_lblTestResultAverage.insets = new Insets(0, 0, 5, 5);
		gbc_lblTestResultAverage.gridx = 1;
		gbc_lblTestResultAverage.gridy = 2;
		add(lblTestResultAverage, gbc_lblTestResultAverage);
		
		TestList_2 = new JComboBox<Test>();
		GridBagConstraints gbc_TestList_2 = new GridBagConstraints();
		gbc_TestList_2.gridwidth = 2;
		gbc_TestList_2.insets = new Insets(0, 0, 5, 5);
		gbc_TestList_2.fill = GridBagConstraints.HORIZONTAL;
		gbc_TestList_2.gridx = 1;
		gbc_TestList_2.gridy = 3;
		add(TestList_2, gbc_TestList_2);
		
		JLabel lblAverage = new JLabel("Average :");
		GridBagConstraints gbc_lblAverage = new GridBagConstraints();
		gbc_lblAverage.insets = new Insets(0, 0, 5, 5);
		gbc_lblAverage.gridx = 3;
		gbc_lblAverage.gridy = 3;
		add(lblAverage, gbc_lblAverage);
		
		avgtest = new JLabel("0");
		GridBagConstraints gbc_avgtest = new GridBagConstraints();
		gbc_avgtest.insets = new Insets(0, 0, 5, 5);
		gbc_avgtest.gridx = 4;
		gbc_avgtest.gridy = 3;
		add(avgtest, gbc_avgtest);
		GridBagConstraints gbc_lblAvergeForE = new GridBagConstraints();
		gbc_lblAvergeForE.insets = new Insets(0, 0, 5, 5);
		gbc_lblAvergeForE.gridx = 1;
		gbc_lblAvergeForE.gridy = 5;
		add(lblAvergeForE, gbc_lblAvergeForE);
		
		testGroups = new JComboBox<TestGroup>();
		GridBagConstraints gbc_testGroups = new GridBagConstraints();
		gbc_testGroups.gridwidth = 2;
		gbc_testGroups.insets = new Insets(0, 0, 5, 5);
		gbc_testGroups.fill = GridBagConstraints.HORIZONTAL;
		gbc_testGroups.gridx = 1;
		gbc_testGroups.gridy = 6;
		add(testGroups, gbc_testGroups);
		
		lblNewLabel = new JLabel("Average");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel.gridx = 3;
		gbc_lblNewLabel.gridy = 6;
		add(lblNewLabel, gbc_lblNewLabel);
		
		lblNewLabel_1 = new JLabel("0");
		GridBagConstraints gbc_lblNewLabel_1 = new GridBagConstraints();
		gbc_lblNewLabel_1.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_1.gridx = 4;
		gbc_lblNewLabel_1.gridy = 6;
		add(lblNewLabel_1, gbc_lblNewLabel_1);
		GridBagConstraints gbc_list = new GridBagConstraints();
		gbc_list.gridwidth = 7;
		gbc_list.fill = GridBagConstraints.BOTH;
		gbc_list.gridx = 0;
		gbc_list.gridy = 7;
		add(new JScrollPane(), gbc_list);	
	}
	
	void addResult(Result r) {
		results.add(r);
		userList.addItem(r);
	}
	
	Result isUserExists(String _nickName) {
		for(Result res : results) {
			if( res.getnickName().equals(_nickName) )
				return res;
		}
		return null;
	}
	
	void exportToDatabase(String fileName) throws IOException {
		
		BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
		String fmt =  Result.getuniqueId() + "\n" ;
		for(Result r : results) {
			fmt += r.toDataBaseFormat() + "\n" ;
		}
		writer.write(fmt);
		writer.close();
	}
	
	void importFromDatabase(String fileName) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader(fileName));
		results.clear();
		
		// get uniqueId of our tests
		int uid  = Integer.valueOf(reader.readLine());
		String line;
		int i= 0;
		
		while( (line = reader.readLine() ) != null ) {
			results.add(new Result());
			results.get(i).fromDatabaseFmt(line);
			i++;
		}
		
		reader.close();
		Result.setuniqueId(uid);
	}
	void clearTests() {
		testList.removeAll();
		TestList_2.removeAll();
	}
	
	void addActiveTest(Test test) {
		testList.addItem(test);
		TestList_2.addItem(test);		
	}
	
	void cleatTestGroups() {
		testGroups.removeAll();
	}
	
	void addAvtiveGroup(TestGroup tg) {
		testGroups.addItem(tg);
	}
	
	// generate some statistics
	void generateStatistic() {
		// average points in distinct test
		
		// average results for distinct test in regard to other tests
		
		// average result in test group for every test
		
	}
	
}
