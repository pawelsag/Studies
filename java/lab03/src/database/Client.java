package database;

public class Client 
{
	private String name, surname;
	
	Client(String _name,String _surname)
	{
		this.name = _name;
		this.surname = _surname;
	}
	
	@Override
	public String toString()
	{
		return "{ Name: " + this.name + ", Surname: " + this.surname + " }" ;
	}
	String toDatabaseString()
	{
		return this.name + "," + this.surname ;
	}
	
	String getname()
	{
		return this.name;
	}
	
	String getsurname()
	{
		return this.surname;
	}
	void setname(String _name)
	{
		this.name = _name;
	}
	void setsurname(String _surname) 
	{
		this.surname = _surname;
	}
	
}
