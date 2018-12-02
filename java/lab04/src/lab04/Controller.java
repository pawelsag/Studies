package lab04;

import javax.swing.DefaultListModel;

public class Controller {
	QuestionManager qManager;
	TestManager tManager;
	TestGroupManager tGManager;
	Controller(QuestionManager _qManager, TestManager _tManager, TestGroupManager _tGroupManager ) {
		qManager = _qManager;
		tManager = _tManager;
		tGManager = _tGroupManager;
		
	}
	
	DefaultListModel<Question> getQestionModel() {
		return this.qManager.getlistModel();
	}
	
	DefaultListModel<Test> getTestModel(){
		return this.tManager.getTestModel();
	} 
	
}
