package lab05_pop;

public class CustomEvent {
	
	synchronized void lock() {
		try { wait(); } catch (InterruptedException e) {}
	}
	
	synchronized void unlock() {
		notify();
	}
	synchronized void unlockAll() {
		notifyAll();
	}
}
