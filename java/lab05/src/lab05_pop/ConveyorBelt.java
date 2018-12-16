package lab05_pop;


import java.util.concurrent.atomic.AtomicBoolean;

import javax.swing.JLabel;

public class ConveyorBelt extends Thread {
	CustomEvent mutex =new CustomEvent();
	CustomEvent beltMutex =new CustomEvent();
	enum Mode{
		R_BACKWARD,
		R_FORWARD,
		STOP,
	};
	enum State{
		OFF,
		ON
	}
	// belt current mode
	private Mode beltMode, supportMode;
	// belt state
	private State beltState =State.ON;
	// representations of the belt
	// I decided to have two different representations
	// char table is easier to manage requests  
	// JLabel table to visualize the content
	private char[] logicalRepresetation;
	JLabel [] visualRepresetation;
	// size of the belt
	private int length;
	int delay = 1;
	MainWindow parent;
	AtomicBoolean inProgres  =new AtomicBoolean();
	ConveyorBelt(MainWindow p,int n, Mode s, int delay){
		parent = p;
		this.beltMode = this.supportMode =  s;
	    this.beltState =State.ON;
		this.length = n;
		this.logicalRepresetation = new char[n];
		this.visualRepresetation = new JLabel[n];
		this.delay = delay;
		for(int i =0 ; i < n; i++) {
			this.logicalRepresetation[i] = '\0';
			this.visualRepresetation[i] = new JLabel();
			this.visualRepresetation[i].setText("| _ |");
		}
		
	}
	
	void setState(Mode s) {
		this.beltMode = s;
	}
	
	void setBeltSpeed(int d) {
		this.delay = d;
	}

	public void run() {
		
		while( this.beltState != State.OFF ) {
			this.makeMove();
			try {
				sleep(delay);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void makeMove() {
		
		if(this.beltMode == Mode.R_BACKWARD) {
			// if item lies on first position of our conveyer Belt -> do nothing
			if(this.logicalRepresetation[0] !='\0') {
				parent.backwardBeltFullEvent();
				beltMutex.unlock();
				
				return;
			}
			inProgres.set(true);
			// move the belt backward
			for(int i =0 ; i< this.length-1; i++) {
				this.logicalRepresetation[i] =this.logicalRepresetation[i+1];
				this.visualRepresetation[i].setText( this.visualRepresetation[i+1].getText() );
			}
			
			this.logicalRepresetation[this.length-1] = '\0';
			this.visualRepresetation[this.length-1].setText("| _ |");
	
			
		}else if(this.beltMode == Mode.R_FORWARD) {
			// if item lies on last position of our conveyer Belt -> do nothing
			if(this.logicalRepresetation[this.length-1] !='\0') {
				parent.forwardBeltFullEvent();
				beltMutex.unlock();
				return;
			}
			inProgres.set(true);
			// else move the belt forward
			for(int i =this.length-1 ; i > 0 ; i--) {
				this.logicalRepresetation[i] =this.logicalRepresetation[i-1];
				this.visualRepresetation[i].setText( this.visualRepresetation[i-1].getText() );	
			}
			
			this.logicalRepresetation[0] = '\0';
			this.visualRepresetation[0].setText("| _ |");
			
		}else {
			// restore mode 
			this.beltMode  = this.supportMode;
		}
		// inform all listeners that tape has been moved
		parent.beltMoved();
		inProgres.set(false);
		beltMutex.unlock();
		
	}
	
	boolean putItem(int place, char item) {
		if( inProgres.get() ) // if inProgress == true
			beltMutex.lock(); // wait for the moment when conveyor belt finish moving
		// save old state 
		Mode tmp = this.beltMode;
		// hold on the production
		this.beltMode = Mode.STOP;
		// check if item can be put in given position
		if(this.logicalRepresetation[place] !='\0') {
			// restore conveyer belt direction move
			this.beltMode = tmp;
			return false;
		}		
		synchronized(mutex) {
				
			this.logicalRepresetation[place] = item;
			this.visualRepresetation[place].setText("| "+ item + " |");
			// restore conveyer belt direction move
			this.beltMode = tmp;
			
			return true;
		}
		
	}
	
	synchronized char getItem(int place) {
		if( inProgres.get() ) // if inProgress == true
			beltMutex.lock(); // wait for the belt 
		// save old state 
		Mode tmp = this.beltMode;
		// hold on the production
		this.beltMode = Mode.STOP;
		
		// check if item can be put in given position
		if(this.logicalRepresetation[place] =='\0') {
			// restore conveyer belt direction move
			this.beltMode = tmp;
			return '\0';
		}
		
		synchronized(mutex) {
			char item = logicalRepresetation[place];
			logicalRepresetation[place] = '\0';
			visualRepresetation[place].setText("| _ |");
			// restore conveyer belt direction move
			this.beltMode = tmp;
			
			return item;
		}
		
	}
	
	void setDelay(int d) {
		this.delay = d;
	}
	
	void print() {
		for(char item : logicalRepresetation)
			System.out.print(item + "_");
		System.out.println("");
	}
	
	void finishJob() {
		this.beltState = State.OFF;
		
		beltMutex.unlockAll();
	}
}
