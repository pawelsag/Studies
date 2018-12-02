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
	@Override
	public String toString() {
		return this.name;
	}
}
