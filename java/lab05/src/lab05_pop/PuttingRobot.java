package lab05_pop;

import java.util.Random;


public class PuttingRobot extends Robot{
	static CustomEvent mutex =new CustomEvent();
	PuttingRobot(ConveyorBelt forwardbelt, ConveyorBelt backwardbelt, int n, int delay){
		super(forwardbelt,backwardbelt,Robot.Function.Putting,n,delay);
	}
	
	@Override
	synchronized public void run() {
		Random rand = new Random();
		boolean result;
		char item;
		this.status = Status.On;
		while(this.status != Status.Off) {
				// get new  item 
				item =(char)(rand.nextInt(25) + 65); // take random number between <65 ... 90> < A ... Z>
				R_Item.setText("| " + item + " |");
				// try to put item on belt
				result = beltWithRawItems.putItem(0, item );
				
				while(result != true){
					// wait for tape movement
					mutex.lock();
					// retry to put item
					result = beltWithRawItems.putItem(0, item );
					if(this.status == Status.Off) break;
				}
				
				R_Item.setText("| _ |");
			}
			// wait some time before taking new item;
			try { sleep(delay); } catch (InterruptedException e) {}
	}
	
	void unlockEvent() {
		mutex.unlock();
	}
	
	void finishJob() {
		this.status = Status.Off;
		mutex.unlockAll();
	}
	
}
