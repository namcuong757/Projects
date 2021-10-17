public class FullTime extends Employee implements CalculatePayAndTax
{
	private static boolean benefit = true;
	private double workingHour = 0;
    	private double salary = 0;
    	private double salaryAfterTax = 0; 
    	private static double taxRate = 0.123;
    	private double tax;
    	private static double fullTimeRate = 35;
   	 private double bonus = 0;
    	private double payAfterTax = 0;
    
 
	public FullTime(Information newInfo, double newHour)
	{
		super(newInfo);
		workingHour = newHour;
	}
	
	public void calculateBonus()
	{
		bonus = salaryAfterTax * 0.05;
		bonus = Math.round(bonus*100);
		bonus = bonus/100;
	}
	
	public double getBonus()
	{
		return bonus;
	}
	
	// Inherited from Employee
	@Override
	void setTax(double newTax)
	{
		taxRate = newTax;
	}
	@Override	
	void setBenefit(boolean newBenefit)
	{
		benefit = newBenefit;
	}
	@Override
	void setPayRate(double newPayRate)
	{
		
		fullTimeRate = newPayRate;
	}
	@Override
	void setWorkingHours(double newWorkingHour)
	{
		workingHour = newWorkingHour;		
	}
	@Override
	boolean getBenefit()
	{
		return benefit;
	}
		@Override
	double getWorkingHours() {
		return workingHour;
	}
	@Override
	double getPayRate() {
		return fullTimeRate;
	}
	
	// Implement CalculatePayAndTax interface
	@Override
	public void calculateTaxDeduction()
	{
		tax = salary * taxRate;
	}
	@Override
	public void calculatePayBeforeTax()
	{
		salary = workingHour * fullTimeRate;
	}
	@Override
	public void calculatePayAfterTax()
	{
		payAfterTax = salary - tax;
		
	}
		@Override
	public double getTaxDeduction()
	{
		return tax;
	}
	@Override
	public double getPayBeforeTax()
	{
		return salary;
	}
	@Override
	public double getPayAfterTax() {
		return payAfterTax;
	}
	
}
