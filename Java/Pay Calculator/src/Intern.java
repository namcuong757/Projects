public class Intern extends Employee implements CalculatePayAndTax
{	
	
    private static boolean benefit = false;
    private boolean mentor;
    private double workingHour = 0;
    private double salary = 0;
    private double payAfterTax = 0;
    private static double taxRate = 0.123;
    private double tax;
    private static double payRate = 13;
    
    public Intern(Information newInfo, double newHour)
    {
        super(newInfo);
        workingHour = newHour;
    }
    public boolean getMentor()
    {
        return mentor;
    } 
    public void setMentor(boolean newMentor)
    {
        mentor = newMentor;
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
		payRate = newPayRate;
		
	}
	@Override
	void setWorkingHours(double newWorkingHour)
	{
		workingHour = newWorkingHour;
		
	}
	@Override
	double getWorkingHours()
	{
		return workingHour;
	}
	@Override
	double getPayRate()
	{
		return payRate;
	}
	@Override
	boolean getBenefit()
	{
		return benefit;
	}    
    
	// Implement CalculatePay and Tax
	@Override
	public void calculatePayBeforeTax()
	{
		salary = workingHour * payRate;
		
	}
    @Override
	public void calculateTaxDeduction()
	{
		// round up
		tax = salary * taxRate;
		tax = Math.round(tax*100);
		tax = tax/100; 
	}
    @Override
    public void calculatePayAfterTax()
	{
    	// Round up
		payAfterTax = salary - tax;
		payAfterTax = Math.round(payAfterTax*100);
		payAfterTax = payAfterTax/100;
	}
    @Override
	public
	double getTaxDeduction() 
    {
		return tax;
	}
	@Override
	public double getPayBeforeTax()
	{
		return salary;
	}
	@Override
	public double getPayAfterTax()
	{
		return payAfterTax;
	}
    
}
