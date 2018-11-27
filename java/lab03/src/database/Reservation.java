package database;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;


public class Reservation
{
	public enum STATUS{
		established,
		paid,      // excursion reserved and all cost paid
		expired,   // excursion date expired
		resignation; // excursion paid, and user discard from trip

		static String restunStatusName(STATUS s){
			if(s == established)
				return "established";
			else if(s  == paid)
				return "paid";
			else if(s == expired)
				return "expired";
			else if(s == resignation)
				return "resignation";
			else
				return "No such status available";
		}
		static STATUS convertToStatus(int statusId){
				if(statusId == 0)
					return STATUS.established;
				else if(statusId == 1)
					return STATUS.paid;
				else if(statusId == 2)
					return  STATUS.expired;
				else if(statusId == 3)
					return STATUS.resignation;
				else
					return null;
		}
		static int convertToId(STATUS statusID){
			if(statusID == established)
				return 0;
			else if(statusID == paid)
				return 1;
			else if(statusID == expired)
				return  2;
			else if(statusID == resignation)
				return 3;
			else
				return -1;
		}

	};
	private static SimpleDateFormat sdf = new SimpleDateFormat(Controller.getPattern());
	private int id;
	static private int idGenerator = 0;
	private Client headPerson;

	private ArrayList<Client> additionalMembers;
	private Date paymentDeadLine;
	private STATUS status;
    private Date lastActivity;
	Reservation(Client _client, ArrayList<Client> _additionalMembers, String _paymentDate, STATUS _status, Date _lastActivity ) throws ParseException {

		this.headPerson = _client;
		this.additionalMembers = new ArrayList<Client>(_additionalMembers);
		this.paymentDeadLine = sdf.parse((_paymentDate));
		this.status = _status;
		this.lastActivity = _lastActivity;
		id = idGenerator;
		idGenerator++;
	}
	Reservation(String name, String surname, ArrayList<Client> _additionalMembers, long _paymentDate, int _status, long _lastActivity ) {

		this.headPerson = new Client(name,surname);
		this.additionalMembers = new ArrayList<Client>(_additionalMembers);
		this.paymentDeadLine = new Date((_paymentDate));
		this.status = STATUS.convertToStatus(_status);
		this.lastActivity = new Date(_lastActivity);
		id = idGenerator;
		idGenerator++;
	}

	public void setPaymentDeadLine(Date paymentDeadLine, Date modificationDate) {
	    this.lastActivity = modificationDate;
		this.paymentDeadLine = paymentDeadLine;
	}

     int getId() {
        return id;
    }

     void setStatus(STATUS status, Date modificationDate) {
        this.lastActivity = modificationDate;
	    this.status = status;
	}

	STATUS getStatus() {
		return status;
	}

	void isReservationExpired(){
		if(this.paymentDeadLine.compareTo( Controller.getLocalTime() ) < 0)
			this.setStatus(STATUS.expired,Controller.getLocalTime() );
	}

	int compareLastModification(Reservation r){
        return this.lastActivity.compareTo( r.getLastActivity() );
    }

     Date getLastActivity() {
        return lastActivity;
    }


	@Override
	public String toString(){

		String displayedString =  "Reservation ID : " + this.id + "\n";
        displayedString +=   "Head Person "  + this.headPerson + '\n';
		displayedString += "Payment deadline: " + this.paymentDeadLine.toString()+ '\n';
		displayedString += "Status " + STATUS.restunStatusName(this.status)+ '\n';
		return displayedString;

	}
	String toDatabaseFormat(){
		String fmt = this.headPerson.toDatabaseString()+ ",";

		fmt +=  String.valueOf(paymentDeadLine.getTime()) + ","
				+ String.valueOf(STATUS.convertToId(this.status)) +","
				+  String.valueOf(lastActivity.getTime()) + ",";

		// add information about additional members count
		fmt += String.valueOf( this.additionalMembers.size() ) + ",";
		for (Client c : this.additionalMembers)
			fmt += c.toDatabaseString() + ",";

		fmt += "\n";
		return fmt;
	}

}
