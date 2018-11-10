package recrutation_system;

public class Main {
	
	public static void main(String[] args)
	{
		// load data from files
		ClassManager managerInstance = new ClassManager(Loader.loadSchoolInfo("school.txt"), Loader.loadStudentsInfo("students.txt") );
		// prepare priorities for algorithm
		// you can disable move priorities
		managerInstance.setPriorities();
		// run algorithm
		boolean result = managerInstance.execute();
		// if no error during algorithm execution
		if(result) {
			managerInstance.printResults();
		}
		
	}
	
}
