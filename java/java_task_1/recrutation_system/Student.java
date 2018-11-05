package recrutation_system;

import java.util.ArrayList;

public class Student {
	int id;
	int points;
	ArrayList<Integer> priorites;
	
	Student(){
		this.id =-1;
		this.points = -1;
		this.priorites = new ArrayList<Integer>();
	}
	
	Student(int _id, int _points, ArrayList<Integer> _priorites){
		this.id = _id;
		this.points = _points; 
		this.priorites = new ArrayList<Integer>(_priorites);
	}
	
	int getid() {
		return this.id;
	}
	int getpoints() {
		return this.points;
	}
	ArrayList<Integer> getpriorites(){
		return this.priorites;
	}
	@Override
	public String toString() { 
		return String.format("{ id: " + this.id + ", points: " + this.points + ", prefernces: " + this.priorites.toString() +" }"); 
	}
	
	
}
