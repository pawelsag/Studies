package lab05_pop;



public class TakingRobot extends Robot{
	static CustomEvent mutex =new CustomEvent();
	
	TakingRobot(ConveyorBelt forwardbelt, ConveyorBelt backwardbelt, int n, int delay){
		super(forwardbelt,backwardbelt,Robot.Function.Taking,n,delay);
	}
	
	@Override
	synchronized public void run() {
		char item;
		this.status = Status.On;
		while(this.status != Status.Off) {
				// try to get item
				item = beltWithProcessedItems.getItem(0);
				
				while( item == '\0' ){
					// wait for tape movement
					mutex.lock();
					item = beltWithProcessedItems.getItem(0);
					// retry to put item
					if(this.status == Status.Off) break;
				}
				
				System.out.println("Item ="+ item);
				// wait some time before taking new item;
				try { sleep(delay); } catch (InterruptedException e) {}
		}		
	}
	
	void unlockEvent() {
		mutex.unlock();

	}
	
	void finishJob() {
		this.status = Status.Off;
		TakingRobot.mutex.unlockAll();
	}
	
}
