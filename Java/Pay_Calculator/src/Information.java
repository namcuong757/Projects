public class Information
{
	private String name;
	private String address;
	private String phoneNumber;
	private String emailAddress;
	
	public Information() {}
	public Information(String newName, String newAddress, String newPhoneNumber, String newEmailAddress)
	{
		name = newName;
		address = newAddress;
		phoneNumber = newPhoneNumber;
		emailAddress = newEmailAddress;
	}
	public void setName(String newName)
	{
		name = newName;
	}
	public void setAddress(String newAddress)
	{
		address = newAddress;
	}
	public void setPhoneNumber(String newPhoneNumber)
	{
		phoneNumber = newPhoneNumber;
	}
	public void setEmailAddress(String newEmailAddress)
	{
		emailAddress = newEmailAddress;
	}
	public String getName()
	{
		return name;
	}
	public String getAddress()
	{
		return address;
	}
	public String getPhoneNumber()
	{
		return phoneNumber;
	}
	public String getEmailAddress()
	{
		return emailAddress;
	}
	public String toString()
	{
		return "\nName: " + name + "\nAddress: " + address + "\nPhone Number: " + phoneNumber;
	}
}
