package lab04;

import java.util.ArrayList;

public class Result {
	
	String nickName;
	ArrayList<Integer>points = new ArrayList<>();
	int testId;
	int id;
	static int uniqueId = 0;
	
	Result( String _nickName, int points, int _testId ){
		this.nickName = _nickName;	
		this.testId = _testId;
		this.points.add(points);
		id = uniqueId;
		uniqueId++;
	}
	
	void AddPoints(int _points) {
		points.add(_points);
		System.out.println(points.size());
	}
	
	int getId() {
		return this.id;
	}
	
	String getnickName() {
		return this.nickName;
	}
	
}
