package database;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

class ExcursionOffer
{
	private Date termBegin, termFinish;
	private String description;
	private String destination;
	private Integer placeQuantity;
	private static  SimpleDateFormat sdf = new SimpleDateFormat(Controller.getPattern());
	private static int  uniqueID=0 ; // next id to assign
	private int id; // id
	ExcursionOffer(String _termBegin, String _termFinish, String _description, String _destination, Integer _placeQuantity )throws ParseException
	{
		this.termBegin = sdf.parse(_termBegin);
		this.termFinish = sdf.parse(_termFinish);
		this.description = _description;
		this.destination = _destination;
		this.placeQuantity = _placeQuantity;
		this.id = uniqueID;
		uniqueID++;
	}
	ExcursionOffer(long _termBegin, long _termFinish, String _description, String _destination, Integer _placeQuantity )throws ParseException
	{

		this.termBegin = new Date(_termBegin);
		this.termFinish = new Date(_termFinish);
		this.description = _description;
		this.destination = _destination;
		this.placeQuantity = _placeQuantity;
		this.id = uniqueID;
		uniqueID++;
	}

	 ExcursionOffer(ExcursionOffer offer) {
		if(offer == null)
			return;
		 this.termBegin =  offer.termBegin;
		 this.termFinish = offer.termFinish;
		 this.description = offer.description;
		 this.destination = offer.destination;
		 this.placeQuantity = offer.placeQuantity;
		 this.id = uniqueID;
		 uniqueID++;
	}

	int getId() {
		return id;
	}

	void setId(int id) {
		this.id = id;
	}

	void setTermBegin(String termBegin) throws ParseException {

		this.termBegin = sdf.parse(termBegin);
	}


	void setTermFinish(String termFinish) throws ParseException {
		this.termFinish = sdf.parse(termFinish);
	}


	void setDescription(String description)
	{
		this.description = description;
	}


	void setDestination(String destination)
	{
		this.destination = destination;
	}

	void setPlaceQuantity(Integer placeQuantity)
	{
		this.placeQuantity = placeQuantity;
	}

	 String getDestination() {
		return destination;
	}

	 Integer getPlaceQuantity() {
		return placeQuantity;
	}

	 Date getTermBegin() {
		return termBegin;
	}

	static int getUniqueID() {
		return uniqueID;
	}

	static void setUniqueID(int uniqueID) {
		ExcursionOffer.uniqueID = uniqueID;
	}

	int compareDateASC(ExcursionOffer offer_2){
		return this.termBegin.compareTo(offer_2.getTermBegin());
	}

	int compareDateDSC(ExcursionOffer offer_2){
		return offer_2.getTermBegin().compareTo(this.termBegin);
	}

	int compareDirectionASC(ExcursionOffer offer_2){
		return this.destination.compareTo(offer_2.getDestination());
	}

	int compareDirectionDSC(ExcursionOffer offer_2){
		return offer_2.getDestination().compareTo(this.destination);
	}

	int comparePlaceASC(ExcursionOffer offer_2){
		return this.placeQuantity.compareTo(offer_2.getPlaceQuantity());
	}
	int comparePlaceDSC(ExcursionOffer offer_2){
		return offer_2.getPlaceQuantity().compareTo(this.placeQuantity);
	}

	@Override
	public String toString()
	{
		String formattedOffer = "";
		formattedOffer += "ID: " + String.valueOf(this.id) + "\n";
		formattedOffer += "Offer destination: " + this.destination + "\n";
		formattedOffer += "Trip begins: " + this.termBegin.toString() + "\n";
		formattedOffer += "Trip ends: " + this.termFinish.toString() + "\n";
		formattedOffer += "Offer description: " + this.description + "\n";
		formattedOffer += "Max participants number: " + String.valueOf(this.placeQuantity) + "\n";

		return formattedOffer;
	}
	String toDatabaseFormat(){
		// format same as initialization in constructor

		return   String.valueOf(this.termBegin.getTime())+ ","
				   + String.valueOf(this.termFinish.getTime())+ ","
				   + this.description + ","
				   + this.destination + ","
				   + String.valueOf(this.placeQuantity)+","
				   + String.valueOf(this.id)
				   + "\n";
	}
}
