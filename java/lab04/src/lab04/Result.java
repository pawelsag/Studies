package lab04;

import java.util.ArrayList;

public class Result {
	
	class ResultDescriptor{
		private int testId;
		private ArrayList<Integer>points = new ArrayList<>();
		
		ResultDescriptor(int _testId, int _points){
			testId = _testId;
			points.add(_points);
		}
		
		void addPoints(int _point) {
			points.add(_point);
		}
		int gettestId() {
			return this.testId;
		}
		ArrayList<Integer> getpoints(){
			return this.points;
		}
		double getAvg() {
			int avg = 0 ;
			for(int p : points) {
				avg += p;
			}
			int amount = points.size();
			//  if there is no elements
			if(amount == 0) 
				return 0;
			
			return avg/(amount*1.0);
		}
		int getSum() {
			int sum = 0;
			for(int p : points) {
				sum += p;
			}
			return sum;
		}
	}
	
	String nickName;
	ArrayList<ResultDescriptor>userResults = new ArrayList<>();
	int testId;
	int id;
	static int uniqueId = 0;
	Result(){}
	
	Result( String _nickName, int points, int _testId ){
		this.nickName = _nickName;	
		this.userResults.add(new ResultDescriptor(_testId, points) );
		id = uniqueId;
		uniqueId++;
	}
	ArrayList<ResultDescriptor> getuserResults(){
		return this.userResults;
	}
	ResultDescriptor getTestDescriptorByID(int id) {
		for(ResultDescriptor r : userResults) {
			if(r.gettestId() == id)
				return r;
		}
		return null;
	}
	
	void AddPoints(int testId, int _points) {
		
		ResultDescriptor userTestDescriptor = getTestDescriptorByID(testId);
		
		if(userTestDescriptor == null)
			userResults.add( new ResultDescriptor( testId, _points ) );
		else
			userTestDescriptor.addPoints( _points );
	}
	
	int getId() {
		return this.id;
	}
	
	static int getuniqueId() {
		return Result.uniqueId;
	}
	
	static void setuniqueId(int UID) {
		Result.uniqueId = UID;
	}
	
	String getnickName() {
		return this.nickName;
	}
	
	@Override
	public String toString() {
		return this.nickName;
	}
	
	String toDataBaseFormat() {
		String fmt ="";
		fmt += this.id +","
			+  this.nickName + ",";
		
		// get size of all test which user completed
		fmt += this.userResults.size()+",";
		// for each test save his result
		for(ResultDescriptor r : userResults ) {
			// write testId
			fmt += r.gettestId() + "," 
					// write sizeof points array 
			    + r.getpoints().size() + ",";
			
			for(Integer i: r.getpoints() ) {
				// save points
				fmt += i.toString() + ",";
			}
		}
		// remove last ',' and return
		return fmt.substring(0, fmt.length()- 3);
	}
	
	void fromDatabaseFmt(String fmt) {
		String[] args = fmt.split(",");
		// get id of current user
		this.id = Integer.valueOf(args[0]);
		// get nickname of current user
		this.nickName = args[1];
		int nextArg = 2;
		// get value of test amount
		int testAmount = Integer.valueOf( args[nextArg] );
		nextArg++;
		for( int i =0 ; i < testAmount ;i++ ) {
			int testID = Integer.valueOf( args[nextArg] );
			nextArg++;
			// get sizeof test points
			int pointsArraySize = Integer.valueOf( args[nextArg] );
			nextArg++;
			// assign points to user
			for(int j =0 ; j < pointsArraySize; j++) {
				this.AddPoints(testID,Integer.valueOf( args[nextArg] ) );
				nextArg++;
			}
			nextArg = 3;
		}
		
	}
}
