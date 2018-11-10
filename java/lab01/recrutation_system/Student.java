package recrutation_system;

import java.util.ArrayList;

public class Student {
	private int id;
	private int points;
	private ArrayList<Integer> preference;
	
	Student()
	{
		this.id =-1;
		this.points = -1;
		this.preference = new ArrayList<>();
	}

	Student(int _id, int _points, ArrayList<Integer> _priorities)
	{
		this.id = _id;
		this.points = _points; 
		this.preference = new ArrayList<>(_priorities);
	}
	
	int getid()
	{
		return this.id;
	}

	int getpoints()
	{
		return this.points;
	}

	ArrayList<Integer> getpreference()
	{
		return this.preference;
	}
	@Override
	public String toString()
	{
		return "{ id: " + this.id + ", points: " + this.points + ", preferences: " + this.preference.toString() +" }";
	}

	int compare(Student student1)
	{
		return Integer.compare(student1.points, this.points);
	}


	int comparePrioritySize(Student student)
	{
		if(this.preference.size() < student.preference.size() )
			return -1;
		else if (this.preference.size() == student.preference.size() )
			return 0;
		else
			return 1;
	}

}
