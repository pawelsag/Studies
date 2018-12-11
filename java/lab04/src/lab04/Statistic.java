package lab04;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.NoSuchElementException;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

import java.awt.GridBagLayout;
import javax.swing.JLabel;
import java.awt.GridBagConstraints;
import javax.swing.JComboBox;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Statistic extends JPanel {

	private static final long serialVersionUID = 1L;
	ArrayList<Result> results = new ArrayList<>();
	private JComboBox<Test> testList;
	private JComboBox<Result> userList;
	private JComboBox<Test> TestList_2;
	private JLabel avgUser;
	private JLabel avgtest;
	private JLabel otherTestAvg;
	private JLabel lblNewLabel_4;
	private JLabel lblChoosenTest;
	private DecimalFormat df = new DecimalFormat("#.##");
	public Statistic() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 187, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		JLabel lblUserAveragePoints = new JLabel("User average points in test ");
		GridBagConstraints gbc_lblUserAveragePoints = new GridBagConstraints();
		gbc_lblUserAveragePoints.insets = new Insets(0, 0, 5, 5);
		gbc_lblUserAveragePoints.gridx = 1;
		gbc_lblUserAveragePoints.gridy = 0;
		add(lblUserAveragePoints, gbc_lblUserAveragePoints);
		
		userList = new JComboBox<Result>();
		GridBagConstraints gbc_userList = new GridBagConstraints();
		gbc_userList.insets = new Insets(0, 0, 5, 5);
		gbc_userList.fill = GridBagConstraints.HORIZONTAL;
		gbc_userList.gridx = 1;
		gbc_userList.gridy = 2;
		add(userList, gbc_userList);
		userList.addActionListener(new userAvgListener());
		testList = new JComboBox<Test>();
		GridBagConstraints gbc_testList = new GridBagConstraints();
		gbc_testList.insets = new Insets(0, 0, 5, 5);
		gbc_testList.fill = GridBagConstraints.HORIZONTAL;
		gbc_testList.gridx = 2;
		gbc_testList.gridy = 2;
		add(testList, gbc_testList);
		testList.addActionListener(new userAvgListener());
		JLabel lblAveragePoints = new JLabel("Average : ");
		GridBagConstraints gbc_lblAveragePoints = new GridBagConstraints();
		gbc_lblAveragePoints.insets = new Insets(0, 0, 5, 5);
		gbc_lblAveragePoints.gridx = 5;
		gbc_lblAveragePoints.gridy = 2;
		add(lblAveragePoints, gbc_lblAveragePoints);
		
		avgUser = new JLabel("0");
		GridBagConstraints gbc_avgUser = new GridBagConstraints();
		gbc_avgUser.insets = new Insets(0, 0, 5, 5);
		gbc_avgUser.gridx = 6;
		gbc_avgUser.gridy = 2;
		add(avgUser, gbc_avgUser);
		
		JLabel lblTestResultAverage = new JLabel("Test result average in regard to other tests");
		GridBagConstraints gbc_lblTestResultAverage = new GridBagConstraints();
		gbc_lblTestResultAverage.insets = new Insets(0, 0, 5, 5);
		gbc_lblTestResultAverage.gridx = 1;
		gbc_lblTestResultAverage.gridy = 3;
		add(lblTestResultAverage, gbc_lblTestResultAverage);
		
		lblChoosenTest = new JLabel("chosen test");
		GridBagConstraints gbc_lblChoosenTest = new GridBagConstraints();
		gbc_lblChoosenTest.insets = new Insets(0, 0, 5, 5);
		gbc_lblChoosenTest.gridx = 6;
		gbc_lblChoosenTest.gridy = 3;
		add(lblChoosenTest, gbc_lblChoosenTest);
		
		lblNewLabel_4 = new JLabel("other tests");
		GridBagConstraints gbc_lblNewLabel_4 = new GridBagConstraints();
		gbc_lblNewLabel_4.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_4.gridx = 7;
		gbc_lblNewLabel_4.gridy = 3;
		add(lblNewLabel_4, gbc_lblNewLabel_4);
		
		TestList_2 = new JComboBox<Test>();
		GridBagConstraints gbc_TestList_2 = new GridBagConstraints();
		gbc_TestList_2.insets = new Insets(0, 0, 5, 5);
		gbc_TestList_2.fill = GridBagConstraints.HORIZONTAL;
		gbc_TestList_2.gridx = 1;
		gbc_TestList_2.gridy = 4;
		add(TestList_2, gbc_TestList_2);
		TestList_2.addActionListener(new testAvgListener() );
		JLabel lblAverage = new JLabel("Average :");
		GridBagConstraints gbc_lblAverage = new GridBagConstraints();
		gbc_lblAverage.insets = new Insets(0, 0, 5, 5);
		gbc_lblAverage.gridx = 5;
		gbc_lblAverage.gridy = 4;
		add(lblAverage, gbc_lblAverage);
		
		avgtest = new JLabel("0");
		GridBagConstraints gbc_avgtest = new GridBagConstraints();
		gbc_avgtest.insets = new Insets(0, 0, 5, 5);
		gbc_avgtest.gridx = 6;
		gbc_avgtest.gridy = 4;
		add(avgtest, gbc_avgtest);
		
		otherTestAvg = new JLabel("0");
		GridBagConstraints gbc_otherTestAvg = new GridBagConstraints();
		gbc_otherTestAvg.insets = new Insets(0, 0, 5, 5);
		gbc_otherTestAvg.gridx = 7;
		gbc_otherTestAvg.gridy = 4;
		add(otherTestAvg, gbc_otherTestAvg);
		GridBagConstraints gbc_list = new GridBagConstraints();
		gbc_list.gridwidth = 9;
		gbc_list.fill = GridBagConstraints.BOTH;
		gbc_list.gridx = 0;
		gbc_list.gridy = 8;
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
		userList.removeAllItems();
		// get uniqueId of our tests
		int uid  = Integer.valueOf(reader.readLine());
		String line;
		int i= 0;
		
		while( (line = reader.readLine() ) != null ) {
			results.add(new Result());
			results.get(i).fromDatabaseFmt(line);
			userList.addItem(results.get(i));
			i++;
		}
		reader.close();
		Result.setuniqueId(uid);
	}
	
	void clearTests() {
		TestList_2.removeAllItems();
		testList.removeAllItems();
	}
	
	void addActiveTest(Test test) {
		TestList_2.addItem(test);		
		testList.addItem(test);
	}	
	
	class userAvgListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			Result r = (Result)userList.getSelectedItem();
			Test t = ((Test)testList.getSelectedItem());
			if( t == null || r == null)
				return;
			double average = generateUserAvgFromTest( r ,t.getId());
			avgUser.setText(String.valueOf(average) );
		}
	}
	class testAvgListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			Test t = (Test)TestList_2.getSelectedItem();
			if(t == null)
				return;
			testAvg( t.getId());
		}
		
	}
	
	void testAvg(int testID) {
		double sumAvg =0.0;
		double chosenTestAvg =0.0;
		int divider =0, chosenTestDivider = 0;
		
		for(Result r : this.results) {
			// for each user get test results
			for(Result.ResultDescriptor testResults :  r.getuserResults() ) {
				if(testResults.gettestId() == testID) {
					chosenTestAvg += testResults.getSum();
					chosenTestDivider += testResults.getpoints().size();
				}
				sumAvg += testResults.getSum();
				divider += testResults.getpoints().size();
			}
		}
		
		if(divider != 0 && chosenTestDivider != 0) {
			this.avgtest.setText(String.valueOf( df.format(chosenTestAvg/chosenTestDivider) ));
			this.otherTestAvg.setText(String.valueOf(df.format(sumAvg/divider) ));
		}
		else{
			this.avgtest.setText(String.valueOf(0));
			this.otherTestAvg.setText(String.valueOf(0));	
		}
	}
	
	double generateUserAvgFromTest(Result user, int testID) {
		int avg = 0;
		Result.ResultDescriptor usrDescriptor = user.getTestDescriptorByID(testID);
		if(usrDescriptor == null)
			return 0;
		
		return usrDescriptor.getAvg();
	}
	
}
