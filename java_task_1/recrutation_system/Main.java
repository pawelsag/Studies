package recrutation_system;


public class Main {
	
	public static void main(String[] args) {
		
		// load data from files
		ClassManager managerInstnace = new ClassManager(Loader.loadSchoolInfo("school.txt"), Loader.loadStudentsInfo("students.txt") );
		// preferences order for algorithm
		int[] preferncesOrder = {1,2,3};
		// choose right order for algorithm sort
		
		
	}
	
}
