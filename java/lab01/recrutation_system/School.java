package recrutation_system;

import java.util.ArrayList;

public class School {
	private int id;
	private int availablePlaces;
    private ArrayList<Student> students = new ArrayList<>();

	School()
    {
		this.id =-1;
		this.availablePlaces =-1;
	}

	School(int _id, int _places)
    {
		this.id = _id;
		this.availablePlaces = _places;
	}
	 @Override
	 public String toString()
     {
		return "{ id: " + this.id + ", places: " + this.availablePlaces + " }";
	 }

	int getId()
    {
        return id;
    }

    void setId(int id)
    {
        this.id = id;
    }
    void sortByPoints()
    {
	    this.students.sort(Student::compare);
    }
    int getAvailablePlaces()
    {
        return availablePlaces;
    }

     boolean limitReached()
     {
        return this.availablePlaces <= students.size();
    }

    void setAvailablePlaces(int availablePlaces)
    {
        this.availablePlaces = availablePlaces;
    }

    ArrayList<Student> getStudents()
    {
        return students;
    }

    void setStudents(ArrayList<Student> students)
    {
        this.students = students;
    }
}
