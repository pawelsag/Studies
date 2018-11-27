package database;

import java.io.IOException;
import java.text.ParseException;

public class Main {

	public static void main(String[] args) throws ParseException, IOException {
		// create view, which implements user interface
		View window = new View();

//		 this method should return on error or on exit request
		int result = window.start();

		if(result == 0) {
			System.out.println("Exit correctly");
		}else {
			// @Todo error handling should be implemented at the end
			// go here only on critical situations
			System.out.println("Error no:  " + String.valueOf(result));
		}
		
	}

}
