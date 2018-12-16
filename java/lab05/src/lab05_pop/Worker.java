package lab05_pop;

import java.awt.Color;

import javax.swing.JLabel;


public class Worker extends Thread {
	static CustomEvent mutex =new CustomEvent();
	enum Status{
		Working, // worker took item and he is processing it now
		Idle, // worker has finished processing item, is able to get next
		Free, // worker finished job, is about to go home
	}
	
	JLabel worker;
	Status workerStatus;
	int delay;
	int position;
	
	ConveyorBelt beltWithRawItems;
	ConveyorBelt beltWithProcessedItems;
	
	Worker(ConveyorBelt forwardbelt,ConveyorBelt backwardbelt, int pos, int delay){
		
		this.position = pos;
		this.worker = new JLabel();
		this.delay = delay;
		this.workerStatus = Status.Idle;
		this.worker.setText("| * |");
		this.worker.setForeground(ready);
		beltWithRawItems = forwardbelt;
		beltWithProcessedItems = backwardbelt;
		
	}
	Color ready = new Color(34,177,76);
	Color busy = new Color(255,128,34);
	
	public void run() {
		char item;
		boolean result;
		while(this.workerStatus != Status.Free ) {
			// get item to process
			item = this.beltWithRawItems.getItem(this.position);
			// if no item available
			if(item == '\0' ) {
				// wait for tape movement
				Worker.mutex.lock();
				// retry to take item again
				continue;
			}
			//else process item
			this.workerStatus = Status.Working;
			this.worker.setText("|"+ item +" |");
			this.worker.setForeground(busy);
			try { sleep(delay); } catch (InterruptedException e) {}
			
			do{
				// try to put processed item on conveyor
				result = beltWithProcessedItems.putItem(this.position, item);
				// if item has been put, change worker status
				if(result == true)
					this.workerStatus = Status.Idle;
				else
					// wait for tape movement
					Worker.mutex.lock();
				//if worker still have item, retry to put its 
			}while(this.workerStatus == Status.Working);
			this.worker.setText("| * |");
			this.worker.setForeground(ready);
		}
		
	}
	
	void finishJob() {
		this.workerStatus = Status.Free;
		Worker.mutex.unlockAll();
	}
	
	void unlockEvent() {
		Worker.mutex.unlock();
	}
	void setDealy(int d) {
		this.delay = d;
	}
}
