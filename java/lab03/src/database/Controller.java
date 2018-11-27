package database;

import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.Date;


public class Controller{

	private OfferManager offerManager;
	private ReservationManager reservationManager;
	private View view;
	private SimpleDateFormat simpleDateFormat = new SimpleDateFormat(pattern);
	// code == 0 -> no error
	// code == 1 -> incorrect data
	// code == 2 -> writing error
	// code == 3 -> reading error
	// code == 4 -> opening file error
	// code == 5 -> out of scope
	private int error_code = 0;
	private static Date localTime;
	private static String pattern = "yyyy-MM-dd";
	private static String dataBasePath = "./DataBase/";

	Controller(View _view,OfferManager _offerManager,ReservationManager _reservationManager ) throws ParseException {
		LocalDate tmpDate = LocalDate.now();
		int day = tmpDate.getDayOfMonth();
		int month = tmpDate.getMonthValue();
		int year = tmpDate.getYear();
		String fmt = String.valueOf(year) + "-" + String.valueOf(month) + "-" + String.valueOf(day);
		localTime = simpleDateFormat.parse(fmt);
		this.offerManager = _offerManager;
		this.reservationManager = _reservationManager;
		this.view = _view ;

		File f = new File(dataBasePath);
		f.mkdir();
	}

	int manageOffers(int criteria) throws ParseException {

		switch ( criteria ){
			case 1:
				error_code = this.offerManager.createOffer();
				break;
			case 2:
				error_code = this.offerManager.removeOffer();
				break;
			case 3:
				error_code = this.offerManager.updateOffer();
				break;
			case 4:
				error_code = this.offerManager.printOffers();
				break;
		}

		return 0;
	}

	int manageReservation(int criteria) throws ParseException {

		switch ( criteria ){
			case 1:
				error_code = this.reservationManager.createReservation();
				break;
			case 2:
				error_code = this.reservationManager.discardReservation();
				break;
			case 3:
				error_code = this.reservationManager.payForReservation();
				break;
			case 4:
				this.reservationManager.printReservations();
				break;
			case 5:
				error_code = this.reservationManager.generateStatistic();
				break;
		}
		return 0;
	}
	void exportToDatabase(String fileName) throws IOException {
		System.out.println(fileName);
		String [] validFileName = fileName.split("\\." );
		String reservationFileName = validFileName[0] + "_reservation.txt";
		String offersFileName = validFileName[0] + "_offers.txt";
		this.offerManager.exportToDatabase(dataBasePath+ offersFileName);
		this.reservationManager.exportToDatabase(dataBasePath + reservationFileName);

	}


	void importFromDatabase(String fileName) throws IOException, ParseException {
		String [] validFileName = fileName.split("\\.");

		String reservationFileName = validFileName[0] + "_reservation.txt";
		String offersFileName = validFileName[0] + "_offers.txt";

		if(this.offerManager.getOffers().size() > 0 || this.reservationManager.getReservations().size() > 0){
			// confirm decision, cause all data will be removed
			if ( view.confirm().equals("Y") ) {
				String fileNameOutput = this.view.getNewFileName();
				this.exportToDatabase(fileNameOutput);
			}
		}

		this.offerManager.importFromDatabase(dataBasePath +offersFileName);
		this.reservationManager.importFromDatabase(dataBasePath +reservationFileName);
	}

	ExcursionOffer searchForOffer(int idx){
		return this.offerManager.searchForIndex(idx);
	}

	int setTime(String timeFormat) throws ParseException {

		localTime = simpleDateFormat.parse(timeFormat);
		this.validateReservation();
		return 0;
	}
	static boolean validateDate(String data){
		String [] tmp = data.split("-");
		// it's really poor validation of date and it doesn't consider edge cases
		if( Integer.valueOf(tmp[1]) > 12 || Integer.valueOf(tmp[2]) > 32   )
			return false;
		return true;
	}
	private void validateReservation() {
		this.reservationManager.validateReservations();
	}

	public void setError_code(int error_code) {
		this.error_code = error_code;
	}

	static Date getLocalTime() {
		return localTime;
	}
	String timeFormatInfo(){
		return "Current time format is: " + pattern;
	}
	static String getDataBasePathInfo(){
		return "Path: " + dataBasePath ;
	}
	static String getPattern() {
		return pattern;
	}

	public int getError_code() {
		return error_code;
	}


}
