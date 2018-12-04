package lab04;

import java.util.ArrayList;

public class TestGroup {
	private int id =0;
	private static int uniqueId = 0;
	private String name;
	private ArrayList<Test> tests;
	
	TestGroup(String _name){
		this.id = TestGroup.uniqueId;
		TestGroup.uniqueId++;
		this.name = _name;
		this.tests = new  ArrayList<>();
	}
	
	TestGroup(String _name, ArrayList<Test> _tests){
		this.id = TestGroup.uniqueId;
		TestGroup.uniqueId++;
		this.name = _name;
		this.tests = _tests;
	}
	TestGroup(int _id, String _name, ArrayList<Test> _tests){
		this.id = _id;
		this.name = _name;
		this.tests = _tests;
	}
	
	void addTest(Test _test) {
		this.tests.add(_test);
	}
	
	void addTest(ArrayList<Test> _test) {		
		_test.forEach(t -> { this.tests.add(t);} );
	}
	
	ArrayList<Test> gettests(){
		return this.tests;
	}
	
	void removeTest(int idx) {
		this.tests.remove(idx);
	}
	
	static int getuniqueId() {
		return TestGroup.uniqueId;
	}
	
	static void setuniqueId(int UID) {
		TestGroup.uniqueId = UID;
	}
	
	String toDatabaseFormat() {
		String fmt = 
				  this.id + ",";
		for(Test T : this.tests ) {
			fmt += T.getId() + ",";
		}
		fmt += this.name;
				 
		return fmt;
	}
	
	@Override
	public String toString() {
		return this.name;
	}

}
