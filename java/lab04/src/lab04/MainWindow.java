package lab04;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JTabbedPane;

public class MainWindow extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	JTabbedPane tabbedPane;
	private TestHandler testhandler;
	QuestionManager questionmanager;
	TestManager testmanager;
	TestGroupManager groupmanager;
	Statistic statistics;
	Settings settings;
	Controller controller;
	//create test tab where user will do test
	TestArea testarea;
	/**
	 * Launch the application.
	 */
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainWindow frame = new MainWindow();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	
	public MainWindow() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 807, 569);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		contentPane.setSize(this.getWidth(),this.getHeight() );
		setContentPane(contentPane);
		// do new test 
		testhandler = new TestHandler( this );
		// handle questions (add/remove questions)
		questionmanager = new QuestionManager();
		// handle tests (create/remove test)
		testmanager = new TestManager();
		// create/remove group test, assign test to group
		groupmanager = new TestGroupManager();
		// generate statistics(average result inside specific tests,
		// specific test result in regard to specific average of tests,
		// average  users result inside test groups )
		statistics = new Statistic();
		// settings tab
		settings = new Settings();
		// create test tab
		testarea = new TestArea(this);
		controller = new Controller(questionmanager,testmanager,groupmanager,testhandler,statistics,settings);
		testmanager.setController(controller);
		groupmanager.setController(controller);
		settings.setController(controller);
		
		tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		testhandler.setPreferredSize( this.getSize() );
		
		tabbedPane.add("Play test", testhandler);
		tabbedPane.add("Manage questions",questionmanager);
		tabbedPane.add("Manage tests",testmanager);
		tabbedPane.add("Manage test groups",groupmanager);
		tabbedPane.add("Statistics",statistics);
		tabbedPane.add("Settings",settings);
		
		contentPane.add(tabbedPane, BorderLayout.NORTH);
		
	}
	
	class playTest implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			if( !testhandler.canTestBeStarted() ) {
				JOptionPane.showMessageDialog(null, "Type nickname, than press button again", "InfoBox: ", JOptionPane.INFORMATION_MESSAGE);
				return;
			}
			
			testarea.initTest( testhandler.getActiveTest() );;
			
			tabbedPane.setComponentAt( 0,testarea );
			
		}	
	}
	
	
	class finishTest implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			tabbedPane.setComponentAt( 0,testhandler );
			String nickName = testhandler.getnickName();
			int result = testarea.getcorrectAnsNum();
			int testId = testhandler.getActiveTest().getId();
			testhandler.getActiveTest().testPerformedCount++;
			Result r = statistics.isUserExists(nickName);
			if(r != null) {
				r.AddPoints(testId, result);
			}else {
				statistics.addResult(new Result(nickName, result,testId));
			}
				
			
		}
	}
	
}
