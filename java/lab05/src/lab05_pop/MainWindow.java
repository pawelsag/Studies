package lab05_pop;

import java.awt.EventQueue;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JSlider;
import javax.swing.JLabel;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.layout.RowSpec;
import com.jgoodies.forms.layout.FormSpecs;
import javax.swing.JButton;

public class MainWindow extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	// amount of positions for workers and available places in conveyor belt
	int positions = 20;
	PuttingRobot[] puttingRobots;
	TakingRobot[] takingRobots;
	Worker[] workers;
	ConveyorBelt forwardBelt;
	ConveyorBelt backwardBelt;
	
	private Panel WorkersPositions;
	private Panel ConveyorBackward;
	private Panel ConveyorForward;
	private JLabel R1_Item;
	private JLabel R2_Item;
	private JSlider workerSliderSpeed;
	private JSlider beltSliderSpeed;
	private JSlider robotsSliderSpeed;
	private Panel panel;
	private JButton Start;
	private JButton Stop;
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

	
	public MainWindow() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		setBounds(100, 100, 600, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new GridLayout(4, 3, 4, 4));
		
		panel = new Panel();
		contentPane.add(panel);
		panel.setLayout(new FormLayout(new ColumnSpec[] {
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,
				FormSpecs.RELATED_GAP_COLSPEC,
				FormSpecs.DEFAULT_COLSPEC,},
			new RowSpec[] {
				FormSpecs.RELATED_GAP_ROWSPEC,
				FormSpecs.DEFAULT_ROWSPEC,
				FormSpecs.RELATED_GAP_ROWSPEC,
				FormSpecs.DEFAULT_ROWSPEC,})
				);
		
		JLabel lblNewLabel = new JLabel("Workers Speed");
		panel.add(lblNewLabel, "4, 2");
		
		workerSliderSpeed = new JSlider();
		panel.add(workerSliderSpeed, "8, 2");
		workerSliderSpeed.addChangeListener( new WorkerSliderSpeedEvent() );
		
		JLabel lblNewLabel_1 = new JLabel("Robots Speed");
		panel.add(lblNewLabel_1, "10, 2");
	
		robotsSliderSpeed = new JSlider();
		panel.add(robotsSliderSpeed, "12, 2");
		robotsSliderSpeed.addChangeListener( new RobotSliderSpeedEvent() );
		Start = new JButton("Start");
		Start.addActionListener( new StartButtonPressed() );
		
		panel.add(Start, "14, 2");
		
		Stop = new JButton("Stop");
		Stop.addActionListener( new StopButtonPressed() );
		panel.add(Stop, "16, 2");
		
		JLabel lblNewLabel_2 = new JLabel("Belt Speed");
		panel.add(lblNewLabel_2, "4, 4");
		
		beltSliderSpeed = new JSlider();
		panel.add(beltSliderSpeed, "8, 4");
		beltSliderSpeed.addChangeListener( new BeltSliderSpeedEvent() );
		
		
		JLabel robot1 = new JLabel("Robot 1 : ");
		panel.add(robot1, "10, 4");
		
		
		JLabel robot2 = new JLabel("Robot 2 :");
		panel.add(robot2, "14, 4");
		
		
		ConveyorForward = new Panel();
		contentPane.add(ConveyorForward);
		ConveyorForward.setLayout(new GridLayout(1, 0, 0, 0));
		
		WorkersPositions = new Panel();
		contentPane.add(WorkersPositions);
		WorkersPositions.setLayout(new GridLayout(1, 0, 0, 0));
		
		
		ConveyorBackward = new Panel();
		contentPane.add(ConveyorBackward);
		ConveyorBackward.setLayout(new GridLayout(1, 0, 0, 0));
		
		this.setUpFactory();
		// set range for every slider
		this.setSlidersRange();
		
	}	
	
	void setSlidersRange(){
		int min =500; 
		int max = 5000;
		// set min val
		this.beltSliderSpeed.setMinimum(min);
		this.workerSliderSpeed.setMinimum(min);
		this.robotsSliderSpeed.setMinimum(min);
		// set max val
		this.beltSliderSpeed.setMaximum(max);
		this.workerSliderSpeed.setMaximum(max);
		this.robotsSliderSpeed.setMaximum(max);
		
		this.beltSliderSpeed.setValue(2000);
		this.workerSliderSpeed.setValue(2000);
		this.robotsSliderSpeed.setValue(2000);
	}

	void setUpFactory() {

		// note: below you can see how program should work
		// robots :   R1 R2
		//     		   \ /  
		// belt  1  :|  c > _ > _ > _ |
		// places   :   W   W   W   W 
		// belt  2  :|  _ < _ < A < _ |
		//		       / \
		// robots:     R3 R4
		//              1   2   3   4
		
		// create conveyors 
		this.forwardBelt = new ConveyorBelt(this, positions, ConveyorBelt.Mode.R_FORWARD,2000);
		this.backwardBelt = new ConveyorBelt(this, positions, ConveyorBelt.Mode.R_BACKWARD,2000);
		
		// create workers
		this.workers = new Worker[positions];
		for(int i =0; i < positions; i++ ) {
			this.ConveyorForward.add(this.forwardBelt.visualRepresetation[i]);
			this.ConveyorBackward.add(this.backwardBelt.visualRepresetation[i]);
			this.workers[i] = new Worker(this.forwardBelt,this.backwardBelt,i,2000);
			this.WorkersPositions.add( this.workers[i].worker );
		}
		
		// create robots
		this.puttingRobots =new PuttingRobot[2];
		this.puttingRobots[0] = new PuttingRobot(this.forwardBelt,this.backwardBelt,positions,2000);
		this.R1_Item = this.puttingRobots[0].R_Item;
		this.puttingRobots[1] = new PuttingRobot(this.forwardBelt,this.backwardBelt,positions,2000);
		this.R2_Item = this.puttingRobots[1].R_Item;
		panel.add(R1_Item, "12, 4");
		panel.add(R2_Item, "16, 4");
		
		this.takingRobots = new TakingRobot[2];
		this.takingRobots[0] = new TakingRobot(this.forwardBelt,this.backwardBelt,positions,2000);
		this.takingRobots[1] = new TakingRobot(this.forwardBelt,this.backwardBelt, positions,2000);
		
	}
	private void startJob() {
		// run conveyors
		this.forwardBelt.start();
		this.backwardBelt.start();
		
		// start robots
		this.puttingRobots[0].start();
		this.puttingRobots[1].start();
		this.takingRobots[0].start();
		this.takingRobots[1].start();
		
		// strat workers
		for(Worker w : workers)
			w.start();
	}
	
	private void finishJobs() {
		// finish conveyors
		this.forwardBelt.finishJob();
		this.backwardBelt.finishJob();
		
		// finish robots
		this.puttingRobots[0].finishJob();
		this.puttingRobots[1].finishJob();
		this.takingRobots[0].finishJob();
		this.takingRobots[1].finishJob();
		try {
			this.forwardBelt.join();
			System.out.println("F_Belt joined");
			this.backwardBelt.join();
			System.out.println("B_Belt joined");
			this.puttingRobots[0].join();
			this.puttingRobots[1].join();
			this.takingRobots[0].join();
			this.takingRobots[1].join();
			System.out.println("All robots joined");
			// finish workers
			for(Worker w : workers) {
				w.finishJob();
			}
		} catch (InterruptedException e) {}
		
	}
	void beltMoved() {

		// inform robots
		this.puttingRobots[0].unlockEvent();
		this.puttingRobots[1].unlockEvent();
		this.takingRobots[0].unlockEvent();
		this.takingRobots[1].unlockEvent();
		
		// inform workers
		for(Worker w : workers)
			w.unlockEvent();
	}
	 
	void backwardBeltFullEvent() {
		this.puttingRobots[0].unlockEvent();
		this.puttingRobots[1].unlockEvent();
		this.takingRobots[0].unlockEvent();
		this.takingRobots[1].unlockEvent();
	}
	
	void forwardBeltFullEvent() {
		workers[positions-1].unlockEvent();
	}

	class StopButtonPressed implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0) {
			finishJobs();
		}
	}
	
	class StartButtonPressed implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0) {
			startJob();
		}
	}
	class RobotSliderSpeedEvent implements ChangeListener{
	
		@Override
		public void stateChanged(ChangeEvent arg0) {
			puttingRobots[0].setDelay(robotsSliderSpeed.getValue() );
			puttingRobots[1].setDelay(robotsSliderSpeed.getValue() );
			takingRobots[0].setDelay(robotsSliderSpeed.getValue() );
			takingRobots[1].setDelay(robotsSliderSpeed.getValue() );

		}
	}
	
	class BeltSliderSpeedEvent implements ChangeListener{
		@Override
		public void stateChanged(ChangeEvent arg0) {
			forwardBelt.setDelay(beltSliderSpeed.getValue() );
			backwardBelt.setDelay(beltSliderSpeed.getValue() );
		}
	}
	
	class WorkerSliderSpeedEvent implements ChangeListener{
		@Override
		public void stateChanged(ChangeEvent arg0) {
			for(Worker w : workers)
				w.setDealy(workerSliderSpeed.getValue());
		}
	}

}
