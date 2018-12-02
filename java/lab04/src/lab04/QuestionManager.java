package lab04;


import javax.swing.JPanel;
import java.awt.GridBagLayout;

import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;

import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;

public class QuestionManager extends JPanel {

	private static final long serialVersionUID = 1L;
	private JTextField AnsT;
	private JTextField AnsA;
	private JTextField AnsB;
	private JTextField AnsC;
	private JTextField AnsD;
	ButtonGroup radioGroup = new ButtonGroup();
	private JList<Question> questionList;
	DefaultListModel<Question> listModel = new DefaultListModel<>();
	public QuestionManager() {
		GridBagLayout gridBagLayout = new GridBagLayout();
		gridBagLayout.columnWidths = new int[]{0, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0};
		gridBagLayout.columnWeights = new double[]{0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gridBagLayout.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, Double.MIN_VALUE};
		setLayout(gridBagLayout);
		
		JButton AddQuestion = new JButton("Add Question");
		GridBagConstraints gbc_AddQuestion = new GridBagConstraints();
		gbc_AddQuestion.insets = new Insets(0, 0, 5, 5);
		gbc_AddQuestion.gridx = 0;
		gbc_AddQuestion.gridy = 0;
		add(AddQuestion, gbc_AddQuestion);
		
		JButton RemoveQuestion = new JButton("Remove Question");
		GridBagConstraints gbc_RemoveQuestion = new GridBagConstraints();
		gbc_RemoveQuestion.insets = new Insets(0, 0, 5, 5);
		gbc_RemoveQuestion.gridx = 1;
		gbc_RemoveQuestion.gridy = 0;
		add(RemoveQuestion, gbc_RemoveQuestion);
		
		JLabel lblQuestionTitle = new JLabel("Question title");
		GridBagConstraints gbc_lblQuestionTitle = new GridBagConstraints();
		gbc_lblQuestionTitle.anchor = GridBagConstraints.EAST;
		gbc_lblQuestionTitle.insets = new Insets(0, 0, 5, 5);
		gbc_lblQuestionTitle.gridx = 0;
		gbc_lblQuestionTitle.gridy = 1;
		add(lblQuestionTitle, gbc_lblQuestionTitle);
		
		AnsT = new JTextField();
		GridBagConstraints gbc_AnsT = new GridBagConstraints();
		gbc_AnsT.gridwidth = 4;
		gbc_AnsT.insets = new Insets(0, 0, 5, 5);
		gbc_AnsT.fill = GridBagConstraints.HORIZONTAL;
		gbc_AnsT.gridx = 1;
		gbc_AnsT.gridy = 1;
		add(AnsT, gbc_AnsT);
		AnsT.setColumns(10);
		
		JLabel lblAnswerA = new JLabel("Answer A");
		GridBagConstraints gbc_lblAnswerA = new GridBagConstraints();
		gbc_lblAnswerA.anchor = GridBagConstraints.EAST;
		gbc_lblAnswerA.insets = new Insets(0, 0, 5, 5);
		gbc_lblAnswerA.gridx = 0;
		gbc_lblAnswerA.gridy = 2;
		add(lblAnswerA, gbc_lblAnswerA);
		
		AnsA = new JTextField();
		GridBagConstraints gbc_AnsA = new GridBagConstraints();
		gbc_AnsA.gridwidth = 4;
		gbc_AnsA.insets = new Insets(0, 0, 5, 5);
		gbc_AnsA.fill = GridBagConstraints.HORIZONTAL;
		gbc_AnsA.gridx = 1;
		gbc_AnsA.gridy = 2;
		add(AnsA, gbc_AnsA);
		AnsA.setColumns(10);
		
		JLabel lblAnswerB = new JLabel("Answer B");
		GridBagConstraints gbc_lblAnswerB = new GridBagConstraints();
		gbc_lblAnswerB.anchor = GridBagConstraints.EAST;
		gbc_lblAnswerB.insets = new Insets(0, 0, 5, 5);
		gbc_lblAnswerB.gridx = 0;
		gbc_lblAnswerB.gridy = 3;
		add(lblAnswerB, gbc_lblAnswerB);
		
		AnsB = new JTextField();
		GridBagConstraints gbc_AnsB = new GridBagConstraints();
		gbc_AnsB.gridwidth = 4;
		gbc_AnsB.insets = new Insets(0, 0, 5, 5);
		gbc_AnsB.fill = GridBagConstraints.HORIZONTAL;
		gbc_AnsB.gridx = 1;
		gbc_AnsB.gridy = 3;
		add(AnsB, gbc_AnsB);
		AnsB.setColumns(10);
		
		JLabel lblAnswerC = new JLabel("Answer C");
		GridBagConstraints gbc_lblAnswerC = new GridBagConstraints();
		gbc_lblAnswerC.anchor = GridBagConstraints.EAST;
		gbc_lblAnswerC.insets = new Insets(0, 0, 5, 5);
		gbc_lblAnswerC.gridx = 0;
		gbc_lblAnswerC.gridy = 4;
		add(lblAnswerC, gbc_lblAnswerC);
		
		AnsC = new JTextField();
		GridBagConstraints gbc_AnsC = new GridBagConstraints();
		gbc_AnsC.gridwidth = 4;
		gbc_AnsC.insets = new Insets(0, 0, 5, 5);
		gbc_AnsC.fill = GridBagConstraints.HORIZONTAL;
		gbc_AnsC.gridx = 1;
		gbc_AnsC.gridy = 4;
		add(AnsC, gbc_AnsC);
		AnsC.setColumns(10);
		
		JLabel lblAnswerD = new JLabel("Answer D");
		GridBagConstraints gbc_lblAnswerD = new GridBagConstraints();
		gbc_lblAnswerD.anchor = GridBagConstraints.EAST;
		gbc_lblAnswerD.insets = new Insets(0, 0, 5, 5);
		gbc_lblAnswerD.gridx = 0;
		gbc_lblAnswerD.gridy = 5;
		add(lblAnswerD, gbc_lblAnswerD);
		
		AnsD = new JTextField();
		GridBagConstraints gbc_AnsD = new GridBagConstraints();
		gbc_AnsD.gridwidth = 4;
		gbc_AnsD.insets = new Insets(0, 0, 5, 5);
		gbc_AnsD.fill = GridBagConstraints.HORIZONTAL;
		gbc_AnsD.gridx = 1;
		gbc_AnsD.gridy = 5;
		add(AnsD, gbc_AnsD);
		AnsD.setColumns(10);
		
		JLabel lblCorrectAnswer = new JLabel("Correct Answer");
		GridBagConstraints gbc_lblCorrectAnswer = new GridBagConstraints();
		gbc_lblCorrectAnswer.insets = new Insets(0, 0, 5, 5);
		gbc_lblCorrectAnswer.gridx = 0;
		gbc_lblCorrectAnswer.gridy = 6;
		add(lblCorrectAnswer, gbc_lblCorrectAnswer);
		
		JRadioButton radioA = new JRadioButton("A");
		GridBagConstraints gbc_radioA = new GridBagConstraints();
		gbc_radioA.insets = new Insets(0, 0, 5, 5);
		gbc_radioA.gridx = 2;
		gbc_radioA.gridy = 6;
		add(radioA, gbc_radioA);
		
		JRadioButton radioB = new JRadioButton("B");
		GridBagConstraints gbc_radioB = new GridBagConstraints();
		gbc_radioB.insets = new Insets(0, 0, 5, 5);
		gbc_radioB.gridx = 3;
		gbc_radioB.gridy = 6;
		add(radioB, gbc_radioB);
		
		JRadioButton radioC = new JRadioButton("C");
		GridBagConstraints gbc_radioC = new GridBagConstraints();
		gbc_radioC.insets = new Insets(0, 0, 5, 5);
		gbc_radioC.gridx = 4;
		gbc_radioC.gridy = 6;
		add(radioC, gbc_radioC);
		
		JRadioButton radioD = new JRadioButton("D");
		GridBagConstraints gbc_radioD = new GridBagConstraints();
		gbc_radioD.insets = new Insets(0, 0, 5, 5);
		gbc_radioD.gridx = 5;
		gbc_radioD.gridy = 6;
		add(radioD, gbc_radioD);
		
		radioGroup.add(radioA);
		radioGroup.add(radioB);
		radioGroup.add(radioC);
		radioGroup.add(radioD);
		
		questionList = new JList<>(listModel);
		GridBagConstraints gbc_questionList = new GridBagConstraints();
		gbc_questionList.gridwidth = 7;
		gbc_questionList.fill = GridBagConstraints.BOTH;
		gbc_questionList.gridx = 0;
		gbc_questionList.gridy = 7;
		add(new JScrollPane(questionList), gbc_questionList);
		
		//implements add button listener
		AddButtonListener addEvent = new AddButtonListener();
		AddQuestion.addActionListener(addEvent);
		RemoveButtonListener removeEvent = new RemoveButtonListener();
		RemoveQuestion.addActionListener( removeEvent );
		this.testQuestions();
	}
	
	private class AddButtonListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			String title = AnsT.getText();
			String A = AnsA.getText();
			String B = AnsB.getText();
			String C = AnsC.getText();
			String D = AnsD.getText();
			
			if( title.isEmpty() || A.isEmpty() || B.isEmpty() || C.isEmpty() || D.isEmpty() )  {
				JOptionPane.showMessageDialog(null, "All fileds have to be filled", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			int radioIdx;
			Enumeration<AbstractButton> elments = radioGroup.getElements();
			boolean isChecked = false;
			for(radioIdx =0; radioIdx < radioGroup.getButtonCount(); radioIdx++) {
				
				if(elments.nextElement().isSelected()) {
					isChecked = true;
					break;
					
				}
					
			}
			if( !isChecked ) {
				JOptionPane.showMessageDialog(null, "Select correct answer", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}				
			
			listModel.addElement(new Question( title, A, B, C, D ,radioIdx ));
			AnsT.setText("");
			AnsA.setText("");
			AnsB.setText("");
			AnsC.setText("");
			AnsD.setText("");
			
		}
		
	}
	
	private class RemoveButtonListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			int idx = questionList.getSelectedIndex();
			if(idx == -1) {
				JOptionPane.showMessageDialog(null, "Select question to remov, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			listModel.removeElementAt(idx);
		
		}
		
	}
	
	DefaultListModel<Question> getlistModel() {
		return this.listModel;
	}
	
	void testQuestions() {
		int num = 1;
		for(int i =num ; i <= 10; i++)
			this.listModel.addElement(new Question( "Question " + i, "all "+ i, "None " + i, "Zupa " + i, "Kanpka " + i , 1 ));
	
	}

}
