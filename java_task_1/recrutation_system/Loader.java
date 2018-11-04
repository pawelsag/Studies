package recrutation_system;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Loader {
	
	static ArrayList<School> loadSchoolInfo(String fileName){
		ArrayList<School> temp = new ArrayList<School>();
		try {
			String line ;
			
			Scanner scanner = new Scanner(new File(fileName) );
			while( scanner.hasNextLine() ) {
				line = scanner.nextLine();
				String[] args =  line.split(" ");
				temp.add( new School( Integer.parseInt(args[0]),Integer.parseInt(args[1])) );
			}
			scanner.close();
		}catch(FileNotFoundException e) {
				System.out.println("Cant open file: " + fileName);
				return null;
		}
		
		return temp;
		
	}
	
	static ArrayList<Student> loadStudentsInfo(String fileName){
		
		ArrayList<Student> temp = new ArrayList<Student>();
		try {
			String line ;
			
			Scanner scanner = new Scanner(new File(fileName) );
			while( scanner.hasNextLine() ) {
				
				line = scanner.nextLine();
				// get id of student
				String[] args =  line.split(" ");
				// get amount of student points
				String[] priorities = args[2].split(",");
				// get priorities list in array
				ArrayList<Integer> paresedPrioities = new ArrayList<Integer>();  
				for( String priority : priorities) {
					paresedPrioities.add( Integer.parseInt(priority) );
				}
				
				temp.add( new Student( Integer.parseInt(args[0]),Integer.parseInt(args[1]),paresedPrioities )  );
			}
			scanner.close();
		}catch(FileNotFoundException e) {
				System.out.println("Cant open file: " + fileName);
				return null;
		}
		
		return temp;
		
		
	}
}
