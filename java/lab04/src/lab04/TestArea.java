package lab04;

import javax.swing.JPanel;
import javax.swing.JRadioButton;

import java.awt.GridBagLayout;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;
import java.util.NoSuchElementException;

import javax.swing.AbstractButton;
import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JButton;

public class TestArea extends JPanel {

	private static final long serialVersionUID = 1L;
	MainWindow parentInstance;
	int qnumber = 0, correctAnsNum =0;
	boolean testover = false;

	Test activetest;
	JLabel QTitle;
	JRadioButton BoxA;
	JRadioButton BoxB;
	JRadioButton BoxC;
	JRadioButton BoxD;
	JLabel correctCount;
	JLabel TestNumber;
	JButton btnCheck;
	JButton btnNext;
	JButton btnFinish;
	ButtonGroup checkBoxGroup = new ButtonGroup();
	
			 
	public TestArea(MainWindow parent) {
		// set reference to parent
		this.parentInstance = parent;
		
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		QTitle = new JLabel("QuestionTitle");
		GridBagConstraints gbc_QTitle = new GridBagConstraints();
		gbc_QTitle.gridwidth = 4;
		gbc_QTitle.insets = new Insets(0, 0, 5, 5);
		gbc_QTitle.gridx = 3;
		gbc_QTitle.gridy = 0;
		add(QTitle, gbc_QTitle);
		
		JLabel label = new JLabel("");
		GridBagConstraints gbc_label = new GridBagConstraints();
		gbc_label.insets = new Insets(0, 0, 5, 5);
		gbc_label.gridx = 2;
		gbc_label.gridy = 2;
		add(label, gbc_label);
		
		BoxA = new JRadioButton("A");
		GridBagConstraints gbc_BoxA = new GridBagConstraints();
		gbc_BoxA.insets = new Insets(0, 0, 5, 5);
		gbc_BoxA.gridx = 3;
		gbc_BoxA.gridy = 3;
		add(BoxA, gbc_BoxA);
		BoxA.setBorderPainted(true);
		
		 BoxB = new JRadioButton("B");
		GridBagConstraints gbc_BoxB = new GridBagConstraints();
		gbc_BoxB.insets = new Insets(0, 0, 5, 5);
		gbc_BoxB.gridx = 3;
		gbc_BoxB.gridy = 4;
		add(BoxB, gbc_BoxB);
		BoxB.setBorderPainted(true);
		
		 BoxC = new JRadioButton("C");
		GridBagConstraints gbc_BoxC = new GridBagConstraints();
		gbc_BoxC.insets = new Insets(0, 0, 5, 5);
		gbc_BoxC.gridx = 3;
		gbc_BoxC.gridy = 5;
		add(BoxC, gbc_BoxC);
		BoxC.setBorderPainted(true);
		
		 BoxD = new JRadioButton("D");
		GridBagConstraints gbc_BoxD = new GridBagConstraints();
		gbc_BoxD.insets = new Insets(0, 0, 5, 5);
		gbc_BoxD.gridx = 3;
		gbc_BoxD.gridy = 6;
		add(BoxD, gbc_BoxD);
		BoxD.setBorderPainted(true);
		
		checkBoxGroup.add(BoxA);
		checkBoxGroup.add(BoxB);
		checkBoxGroup.add(BoxC);
		checkBoxGroup.add(BoxD);
		
		JLabel lblNewLabel = new JLabel("Correct Answer:");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel.gridx = 10;
		gbc_lblNewLabel.gridy = 7;
		add(lblNewLabel, gbc_lblNewLabel);
		
		correctCount = new JLabel("0");
		GridBagConstraints gbc_correctCount = new GridBagConstraints();
		gbc_correctCount.insets = new Insets(0, 0, 5, 5);
		gbc_correctCount.gridx = 11;
		gbc_correctCount.gridy = 7;
		add(correctCount, gbc_correctCount);
		
		JLabel QLabel = new JLabel("Question:");
		GridBagConstraints gbc_QLabel = new GridBagConstraints();
		gbc_QLabel.insets = new Insets(0, 0, 5, 5);
		gbc_QLabel.gridx = 10;
		gbc_QLabel.gridy = 8;
		add(QLabel, gbc_QLabel);
		
		TestNumber = new JLabel("0/X");
		GridBagConstraints gbc_TestNumber = new GridBagConstraints();
		gbc_TestNumber.insets = new Insets(0, 0, 5, 5);
		gbc_TestNumber.gridx = 11;
		gbc_TestNumber.gridy = 8;
		add(TestNumber, gbc_TestNumber);
		setEmptyCheckBoxBorder();
		btnCheck = new JButton("Check");
		CheckAnswerListener checkevent = new CheckAnswerListener();
		btnCheck.addActionListener(checkevent);
		
		GridBagConstraints gbc_btnCheck = new GridBagConstraints();
		gbc_btnCheck.insets = new Insets(0, 0, 0, 5);
		gbc_btnCheck.gridx = 5;
		gbc_btnCheck.gridy = 11;
		add(btnCheck, gbc_btnCheck);
		
		btnNext = new JButton("Next");
		NextQListsner nextEvent = new NextQListsner();
		btnNext.addActionListener(nextEvent);
		btnNext.setEnabled(false);
		GridBagConstraints gbc_btnNext = new GridBagConstraints();
		gbc_btnNext.insets = new Insets(0, 0, 0, 5);
		gbc_btnNext.gridx = 6;
		gbc_btnNext.gridy = 11;
		add(btnNext, gbc_btnNext);
		
		btnFinish = new JButton("Finish");
		btnFinish.addActionListener( parentInstance.new finishTest() );
		btnFinish.setEnabled(false);
		GridBagConstraints gbc_btnFinish = new GridBagConstraints();
		gbc_btnFinish.insets = new Insets(0, 0, 0, 5);
		gbc_btnFinish.gridx = 7;
		gbc_btnFinish.gridy = 11;
		add(btnFinish, gbc_btnFinish);
		
	}
	
	void setactiveTest(Test t) {
		this.activetest = t;
	}
	
	int getcorrectAnsNum() {
		return correctAnsNum;
	}
	
	void initTest(Test t) {
		this.activetest = t;
		Question q = this.activetest.getquestions().get(0);
		reloadQuestion(q);
		TestNumber.setText("1/"+String.valueOf(this.activetest.getquestions().size()));
		correctCount.setText("0");
		checkBoxGroup.clearSelection();
		btnFinish.setEnabled(false);
		btnCheck.setEnabled(true);
		btnNext.setEnabled(false);
		qnumber = 0;
		correctAnsNum=0;
		testover = false;
		setEmptyCheckBoxBorder();
	}
	
	void setCheckBoxBorder(int id, Color c) {
		if(id == 0 )
			BoxA.setBorder(BorderFactory.createLineBorder(c));
		else if(id ==1)
			BoxB.setBorder(BorderFactory.createLineBorder(c));
		else if(id ==2)
			BoxC.setBorder(BorderFactory.createLineBorder(c));
		else if(id ==3)
			BoxD.setBorder(BorderFactory.createLineBorder(c));
	}
	
	void setEmptyCheckBoxBorder() {
			BoxA.setBorder(BorderFactory.createEmptyBorder());
			BoxB.setBorder(BorderFactory.createEmptyBorder());
			BoxC.setBorder(BorderFactory.createEmptyBorder());
			BoxD.setBorder(BorderFactory.createEmptyBorder());
	}
	
	void reloadQuestion(Question q) {
		QTitle.setText(q.getQName());
		String[] ans = q.getAnserws(); 
		BoxA.setText(ans[0]);
		BoxB.setText(ans[1]);
		BoxC.setText(ans[2]);
		BoxD.setText(ans[3]);
		checkBoxGroup.clearSelection();
		enableRadioBox();
		btnNext.setEnabled(false);
	}
	
	void enableRadioBox() {
		BoxA.setEnabled(true);
		BoxB.setEnabled(true);
		BoxC.setEnabled(true);
		BoxD.setEnabled(true);
	}
	
	void disableRadioBox() {
		BoxA.setEnabled(false);
		BoxB.setEnabled(false);
		BoxC.setEnabled(false);
		BoxD.setEnabled(false);		
	}
	
	class CheckAnswerListener implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0) {
			
			boolean isSelectedSth = false;
			Question q = activetest.getquestions().get(qnumber);
			Enumeration<AbstractButton> chcBoxs = checkBoxGroup.getElements();
			int i = 0;
			while(true)
				try{
					JRadioButton ans = (JRadioButton) chcBoxs.nextElement();
					if( ans.isSelected() == true) {
						isSelectedSth =true;
						ans.setBorder(BorderFactory.createLineBorder(Color.RED));
						if(q.getCorrectAns() == i) {
							correctAnsNum++;
						}
						break;
					}
					i++;
				}catch(NoSuchElementException e) {
					break;
				}
			
			if(!isSelectedSth) {
				JOptionPane.showMessageDialog(null, "Select answer", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			setCheckBoxBorder(q.getCorrectAns(),Color.GREEN);
			correctCount.setText(String.valueOf(correctAnsNum));
			btnNext.setEnabled(true);
			btnCheck.setEnabled(false);
			if(qnumber >= activetest.getquestions().size() -1 ) {
				disableRadioBox();
				testover = true;
				btnCheck.setEnabled(false);
				btnNext.setEnabled(false);
				btnFinish.setEnabled(true);
			}
		}
		
	}
	
	class NextQListsner implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			
			Question q = activetest.getquestions().get(qnumber);
			// load next question
			reloadQuestion(q);
			btnCheck.setEnabled(true);
			qnumber++;
			TestNumber.setText(String.valueOf(qnumber+1)+"/"+String.valueOf(activetest.getquestions().size()));
			setEmptyCheckBoxBorder();
		}
		
	}

}
