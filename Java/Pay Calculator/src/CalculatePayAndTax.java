// Interface used in fulltime and intern
public interface CalculatePayAndTax
{	
    void calculateTaxDeduction();
	void calculatePayBeforeTax();
	void calculatePayAfterTax();
    double getPayBeforeTax();
    double getPayAfterTax();
    double getTaxDeduction();
}
