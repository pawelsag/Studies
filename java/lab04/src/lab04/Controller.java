package lab04;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.DefaultListModel;
import javax.swing.JOptionPane;

public class Controller {
	QuestionManager qManager;
	TestManager tManager;
	TestGroupManager tGManager;
	Settings settings;
	// variable necessary to export/import data from database
	String fileName;
	Controller(QuestionManager _qManager, TestManager _tManager, TestGroupManager _tGroupManager,Settings _settings ) {
		qManager = _qManager;
		tManager = _tManager;
		tGManager = _tGroupManager;
		settings = _settings;
		
	}
	
	DefaultListModel<Question> getQestionModel() {
		return this.qManager.getlistModel();
	}
	
	DefaultListModel<Test> getTestModel(){
		return this.tManager.getTestModel();
	}
	Question getQuestionFromDatabse(int id) {
		return this.qManager.getQuestionById(id);
	}
	Test getTestFromDataBase(int id) {
		return this.tManager.getTestByIndex(id);
	}
	
	void setfileName(String fName) {
		this.fileName = fName;
	}
	public class ExportEventListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			fileName = settings.getFileName();
			if(fileName.length() == 0)
			{
				JOptionPane.showMessageDialog(null, "Type file name, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			String name = fileName.split("\\.")[0];
			try {
				
				// export questions
				qManager.exportToDatabase(name + "_Q.txt");
				// export tests
				tManager.exportToDatabase(name +"_T.txt");
				// export groups
				tGManager.exportToDatabase(name + "_TG.txt");
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
	}
	public class ImportEventListener implements  ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			fileName = settings.getFileName();
			if(fileName.length() == 0)
			{
				JOptionPane.showMessageDialog(null, "Type file name, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			String name = fileName.split("\\.")[0];
			try {
				// export questions
				qManager.importFromDatabase(name + "_Q.txt");
				// export tests
				tManager.importFromDatabase(name +"_T.txt");
				// export groups
				tGManager.importFromDatabase(name + "_TG.txt");
				
			} catch (NumberFormatException | IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
	}
}
