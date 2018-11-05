package recrutation_system;

public class School {
	int id;
	int avaliablePlaces;
	School(){
		this.id =-1;
		this.avaliablePlaces =-1;
	}
	School(int _id, int _places){
		this.id = _id;
		this.avaliablePlaces = _places;
	}
	 @Override
	public String toString() { 
		return String.format("{ id: " + this.id + ", plaeses: " + this.avaliablePlaces + " }"); 
	} 
}
