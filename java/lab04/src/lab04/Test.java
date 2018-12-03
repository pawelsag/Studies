package lab04;
import java.util.*;

public class Test {
	int id;
	static int uiniqueId = 0;
	ArrayList<Question> questions = new ArrayList<>();
	String name;
	Test(String _name,ArrayList<Question> _questions ){
		this.name = _name;
		this.questions = _questions;
		this.id = Test.uiniqueId;
		Test.uiniqueId++;
	}
	
	Test(int _id, String _name,ArrayList<Question> _questions ){
		this.name = _name;
		this.questions = _questions;
		this.id = _id;
		
	}
	@Override
	public String toString() {
		return this.name;
	}
	
	static public int  getUniqueId() {
		return Test.uiniqueId;
	}
	
	static void setUniqueId(int UID) {
		Test.uiniqueId = UID;
	}
	int getId() {
		return this.id;
	}
	String getName() {
		return this.name;
	}
	ArrayList<Question> getquestions(){
		return questions;
	}
	
	public String toDatabaseFormat() {
		String fmt = 
				  this.id + ",";
		for(Question Q : this.questions ) {
			fmt += Q.getId() + ",";
		}
		fmt += this.name;
				 
		return fmt;
	}
}
