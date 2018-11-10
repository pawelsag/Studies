package recrutation_system;


class Priority{
	private int id;
	private boolean isActive;
	static private int id_unique_counter = 0;

	Priority()
	{
		this.id = id_unique_counter;
		this.isActive = false;
		id_unique_counter++;
	}

	Priority(int _id, boolean _isActive)
	{
		this.id = _id;
		this.isActive = _isActive;
		id_unique_counter++;
	}

	public void setId(int id)
	{
		this.id = id;
	}

	public void setActive(boolean active)
	{
		isActive = active;
	}

	public static int getId_unique_counter()
	{
		return id_unique_counter;
	}

	public static void setId_unique_counter(int id_unique_counter)
	{
		Priority.id_unique_counter = id_unique_counter;
	}

	boolean getisActive()
	{
		return this.isActive;
	}
	int getid()
	{
		return this.id;
	}
	
};