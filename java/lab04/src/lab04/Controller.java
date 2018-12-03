package lab04;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Enumeration;

import javax.swing.DefaultListModel;
import javax.swing.JOptionPane;

public class Controller {
	QuestionManager qManager;
	TestManager tManager;
	TestGroupManager tGManager;
	Settings settings;
	TestHandler testhandler;
	String folderBaseName = "./DB/";
	// variable necessary to export/import data from database
	String fileName;
	Controller(QuestionManager _qManager, TestManager _tManager, TestGroupManager _tGroupManager,TestHandler _testhandler, Settings _settings ) {
		qManager = _qManager;
		tManager = _tManager;
		tGManager = _tGroupManager;
		settings = _settings;
		testhandler = _testhandler;
		new File( folderBaseName ).mkdirs();
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
	void refreshAvailabaleTests(Enumeration<Test> tests) {
		testhandler.fillActiveTests(tests);
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
				qManager.exportToDatabase(folderBaseName + name + "_Q.txt");
				// export tests
				tManager.exportToDatabase(folderBaseName + name +"_T.txt");
				// export groups
				tGManager.exportToDatabase(folderBaseName + name + "_TG.txt");
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				JOptionPane.showMessageDialog(null, "Exporting file can't be performed", "InfoBox: ", JOptionPane.ERROR_MESSAGE);
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
			int dialogButton = JOptionPane.YES_NO_OPTION;
			int dialogResult = JOptionPane.showConfirmDialog (null, "All current progres will be removed. Continue?","Warning",dialogButton);
			
			if(dialogResult == JOptionPane.NO_OPTION)
			  return;
			
			String name = fileName.split("\\.")[0];
			try {
				// export questions
				qManager.importFromDatabase(folderBaseName + name + "_Q.txt");
				// export tests
				tManager.importFromDatabase(folderBaseName + name +"_T.txt");
				// export groups
				tGManager.importFromDatabase(folderBaseName + name + "_TG.txt");
				
			} catch (NumberFormatException | IOException e) {
				// TODO Auto-generated catch block
				JOptionPane.showMessageDialog(null, "Can't open file", "InfoBox: ", JOptionPane.ERROR_MESSAGE);
			}
			
		}
	}
}
