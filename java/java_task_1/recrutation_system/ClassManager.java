package recrutation_system;

import java.util.ArrayList;

public class ClassManager {
	ArrayList<School> avaliableSchools;
	ArrayList<Student> avaliableStudents;
	boolean dataReady = false;
	// Priorities in which algorithm will sort students through different schools
	// id 1 = most amount of satisfied students
	// id 2 = most amount of unsatisfied students
	// id 3 = priority consequent from students points
	int[] Priorites;
	
	ClassManager(){
		this.avaliableSchools = new ArrayList<School>();
		this.avaliableStudents = new ArrayList<Student>();
	}
	
	ClassManager(ArrayList<School> avSchools, ArrayList<Student> avStudents){
		//  check if data was read
		if (avSchools == null || avStudents == null) {
			System.out.println("Can't init manager. Data corrupted");
			return;
		}
		// check data correctness
		// school can't have 0 available places for students
		// students must have proper school ids in preferences
		
		dataReady = true;
		this.avaliableSchools = avSchools;
		this.avaliableStudents = avStudents;
		this.printData();
	}
	
	void printData() {
		// print all obtained schools
		System.out.println("Schools");
		for(School s : this.avaliableSchools ) {
			System.out.println(s.toString());
		}
		// print all obtained students
		System.out.println("Students: ");
		for(Student s : this.avaliableStudents ) {
			System.out.println(s.toString());
		}
	}
	void setPriorites(int[]priorites) {
		this.Priorites = priorites;
	}
}
