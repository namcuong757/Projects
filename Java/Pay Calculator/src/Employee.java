public abstract class Employee
{	
	private static int id = 1;
	private int employeeId;
	private Information info;
	
	public int createEmployeeId()
	{
		int idInstance = id;	
		id++;
		return idInstance;
	}
	
	public Employee(Information newInfo)
	{
		info = newInfo;
		this.employeeId = createEmployeeId();
	}
	
	abstract void setTax(double newTax);
	abstract void setBenefit(boolean newBenefit);
	abstract void setPayRate(double newPayRate);
	abstract void setWorkingHours(double newWorkingHour);
	abstract boolean getBenefit();
	abstract double getWorkingHours();
	abstract double getPayRate();
	
	public int getEmployeeId()
	{
		return employeeId;
	}
	public String toString()
	{
		return info.toString() + employeeId;
	}
}
