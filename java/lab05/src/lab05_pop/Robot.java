package lab05_pop;

import java.awt.Color;
import java.util.Random;

import javax.swing.JLabel;

public class Robot extends Thread{
	
	
	enum Function{
		Putting,
		Taking,
	}
	enum Status{
		Off,
		On,
	}
	protected Function robotFunction;
	protected Status status;
	protected int delay;
	protected int length;
	public JLabel R_Item = new JLabel("| _ |");
	// reference to forward moving belt
	protected ConveyorBelt beltWithRawItems;
	// reference to backward moving belt
	protected ConveyorBelt beltWithProcessedItems;
	Color ready = new Color(34,177,76);
	Color busy = new Color(255,128,34);
	
	Robot( ConveyorBelt forwardbelt, ConveyorBelt backwardbelt, Function f, int n, int delay){
		
		this.beltWithRawItems = forwardbelt;
		this.beltWithProcessedItems = backwardbelt;
		this.robotFunction = f;
		this.status = Status.On;
		this.length = n;
		this.delay = delay;
		
	}
	synchronized public void run() {
		Random rand = new Random();
		boolean result;
		char item;
		this.status = Status.On;
		while(this.status != Status.Off) {
			// check for robot function
			if(this.robotFunction == Function.Putting) {
				// get new  item 
				item =(char)(rand.nextInt(25) + 65); // take random number between <65 ... 90> < A ... Z>
				R_Item.setText("| " + item + " |");
				// try to put item on belt
				result = beltWithRawItems.putItem(0, item );
				
				while(result != true){
					// wait for tape movement
					try{ wait(); }catch(InterruptedException e) {}
					// retry to put item
					result = beltWithRawItems.putItem(0, item );
				}
				
				R_Item.setText("| _ |");
			}else { // in the other case robot takes items from belt 
				// try to get item
				item = beltWithProcessedItems.getItem(0);
				
				while( item == '\0' ){
					// wait for tape movement
					try{ wait(); }catch(InterruptedException e) {}
					// retry to put item
					item = beltWithProcessedItems.getItem(0);
				}
			}	
			// wait some time before taking new item;
			try { sleep(delay); } catch (InterruptedException e) {}
		}	
	}
	
	void finishJob() {
		this.status = Status.Off;
		notifyAll();
	}
	
	void unlockEvent() {
		notifyAll();
	}
	void setDelay(int d) {
		this.delay = d;
	}
	
}
