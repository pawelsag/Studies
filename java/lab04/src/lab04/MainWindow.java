package lab04;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JTabbedPane;

public class MainWindow extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private TestHandler testhandler;
	QuestionManager questionmanager;
	TestManager testmanager;
	TestGroupManager groupmanager;
	Statistic statistics;
	Settings settings;
	Controller controller;
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
		testhandler = new TestHandler();
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
		
		controller = new Controller(questionmanager,testmanager,groupmanager,settings);
		testmanager.setController(controller);
		groupmanager.setController(controller);
		settings.setController(controller);
		
		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		testhandler.setPreferredSize( this.getSize() );
		
		tabbedPane.add("Play test", testhandler);
		tabbedPane.add("Manage questions",questionmanager);
		tabbedPane.add("Manage tests",testmanager);
		tabbedPane.add("Manage test groups",groupmanager);
		tabbedPane.add("Statistics",statistics);
		tabbedPane.add("Settings",settings);
		
		contentPane.add(tabbedPane, BorderLayout.NORTH);
	}
	
	
	
}
