package database;

import java.io.IOException;
import java.text.ParseException;
import java.util.Scanner;

class View {
	private Controller controller;
	private ReservationManager reservationManager;
	private OfferManager offersManager;
	private Scanner scanner = new Scanner(System.in);
	View() throws ParseException {
		this.reservationManager = new ReservationManager();
		this.offersManager = new OfferManager();
		controller = new Controller(this, this.offersManager, this.reservationManager);
		this.reservationManager.setController(controller);
		this.offersManager.setController(controller);
		System.out.println("Date : " + Controller.getLocalTime().toString());
	}

	int start() throws ParseException, IOException {

		int errorCode = 0;
		int opcode;


		do {
			System.out.println("Welcome in excursion office software");
			System.out.println("What would you like to do?");
			System.out.println("1. Manage  offers");
			System.out.println("2. Manage  reservation");
			System.out.println("3. Manage  time");
			System.out.println("4. Export/Import data");
			System.out.println("0. Exit");

			switch( opcode = scanner.nextInt() ){
				case 1: // offer manager
					System.out.println("1. Append offer");
					System.out.println("2. Remove offer");
					System.out.println("3. Update offer");
					System.out.println("4. Print offer");
					opcode =scanner.nextInt();
					scanner.nextLine();
					try {
						errorCode = this.controller.manageOffers(opcode);
					}catch(ParseException e){
						System.out.println("Incorrect Date");
						System.out.println("Error code : " + controller.getError_code() );
					}catch(Exception e){
						System.out.println("Error code : " + controller.getError_code() );
					}
						break;
				case 2: // reservation manager
					System.out.println("1. Append reservation");
					System.out.println("2. Remove reservation");
					System.out.println("3. Pay for reservation");
					System.out.println("4. Print reservations");
					System.out.println("5. Generate statistic <option>");
					opcode =scanner.nextInt();
					scanner.nextLine();
					try{
					errorCode = this.controller.manageReservation( opcode );
					}catch(ParseException e){
						System.out.println("Incorrect Date");
						System.out.println("Error code : " + controller.getError_code() );
					}catch(Exception e){
						System.out.println("Error code : " + controller.getError_code() );
					}

					break;
				case 3: // time change option
					System.out.print( controller.timeFormatInfo() );
					System.out.println("Type new date: ");
					scanner.nextLine();
					String format = scanner.nextLine();
					try{
					errorCode =this.controller.setTime(format);
					}catch(ParseException e){
						System.out.println("Incorrect Date");
						System.out.println("Error code : " + controller.getError_code() );
					}catch(Exception e){
						System.out.println("Error code : " + controller.getError_code() );
					}
					break;
				case 4:
					System.out.println("1. Export data");
					System.out.println("2. Import data[ current progress will be deleted ]");
					int option = scanner.nextInt();
					scanner.nextLine();  // Consume newline left-over
					System.out.println( Controller.getDataBasePathInfo() );
					System.out.println("Type file name: [just name]");
					String name = scanner.nextLine();
					try{
					if(option == 1)
						this.controller.exportToDatabase(name);
					else if(option == 2 )
						this.controller.importFromDatabase(name);
					}catch(ParseException e){
						System.out.println("Incorrect Date");
						System.out.println("Error code : " + controller.getError_code() );
					}catch(IOException e){
						System.out.println("Writing/Reading to file error");
						System.out.println("Error code : " + controller.getError_code() );
					} catch(Exception e){
						System.out.println("Error code : " + controller.getError_code() );
					}
					break;
			}
		}while( opcode != 0  && errorCode == 0 );

		return errorCode;
	}
	String getNewFileName(){
		System.out.println("Type new file name: ");
		return scanner.nextLine();
	}

	String confirm(){
		System.out.println("Current progress will be deleted");
		System.out.println("Do you want to save it to file [Y/N]:");
		return scanner.nextLine().toUpperCase();
	}
}
