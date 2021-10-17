import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;
@SuppressWarnings("serial")
public class View extends JFrame
{
	/**
	 * create Label
	 */
	
	private JLabel payRollLabel = new JLabel("PAY ROLL");
	private JLabel idLabel = new JLabel("ID");
	private JLabel nameLabel = new JLabel("NAME");
	private JLabel addressLabel = new JLabel("ADDRESS");
	private JLabel emailLabel = new JLabel("EMAIL");
	private JLabel phoneNumberLabel = new JLabel("PHONE NUMBER");
	private JLabel statusLabel = new JLabel("STATUS");
	private JLabel rateLabel = new JLabel("RATE OF PAY");
	private JLabel totalHourLabel = new JLabel("TOTAL HOURS");
	private JLabel PayBeforeTaxLabel = new JLabel("PAY BEFORE TAX");
	private JLabel TaxDeductionLabel = new JLabel("TAX DEDUCTION");
	private JLabel PayAfterTaxLabel = new JLabel("PAY AFTER TAX");
	private JLabel mentorLabel = new JLabel("MENTOR");
	private JLabel convertedStatusLabel = new JLabel("STATUS");
	private JLabel benefitLabel = new JLabel("BENEFIT");
	private JLabel bonusLabel = new JLabel ("BONUS");
	private JLabel totalPayLabel = new JLabel("TOTAL PAY");
	private JLabel creditLabel = new JLabel("Programmed by Cuong Tran");

	/**
	 *  added to BorderLayout
	 */
	private JPanel mainPanel = new JPanel();
	private JPanel centerPanel = new JPanel();
	private JPanel eastPanel = new JPanel();
	private JPanel westPanel = new JPanel();
	private JPanel southPanel = new JPanel();
	private JPanel northPanel = new JPanel();
	
	/**
	 * add TextField
	 */
	private JTextField idField = new JTextField(5);
	private JTextField nameField = new JTextField(5);
	private JTextField addressField = new JTextField(5);
	private JTextField emailField = new JTextField(5);
	private JTextField phoneNumberField = new JTextField(5);
	private JTextField statusField = new JTextField(5);
	private JTextField rateField = new JTextField(5);
	private JTextField totalHourField = new JTextField(5);
	private JTextField PayBeforeTaxField = new JTextField(5);
	private JTextField TaxDeDuctionField = new JTextField(5);
	private JTextField PayAfterTaxField = new JTextField(5);
	private JTextField mentorField = new JTextField(5); 
	private JTextField convertedStatusField = new JTextField(5);
	private JTextField bonusField = new JTextField(5);
	private JTextField totalPayField = new JTextField(5);
	private JTextField benefitField = new JTextField(5);
	
	
	/**
	 * add button
	 */
	private JButton calculateButton = new JButton("CALCULATE");
	private JButton resetButton = new JButton("RESET");
	private JButton writeToFileButton = new JButton("WRITE TO FILE");
	
	private FlowLayout flow =  new FlowLayout();
	
	/**
	 * Constructor
	 */
	public View()
	{
		
		setTitle("PAY CALCULATOR");
		setSize(500,500);
		
		/**
		 * set up layout
		 */
		mainPanel.setLayout(new BorderLayout());
		westPanel.setLayout(new BoxLayout(westPanel, BoxLayout.Y_AXIS));
		eastPanel.setLayout(new BoxLayout(eastPanel, BoxLayout.Y_AXIS));
		centerPanel.setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridwidth = GridBagConstraints.REMAINDER;
		gbc.fill = GridBagConstraints.HORIZONTAL;
		
		southPanel.setLayout(flow);
		northPanel.setLayout(flow);
		
		/**
		 * implementing ActiomListeners
		 */
		ActionListener calculateListener = new CalculateButtonListener(this);
		ActionListener resetListener = new ResetButtonListener(this);
		ActionListener writeToFileListener = new WriteToFileButtonListener(this);
		calculateButton.addActionListener(calculateListener);
		resetButton.addActionListener(resetListener);
		writeToFileButton.addActionListener(writeToFileListener);
		
		/**
		 * add buttons to Center panel
		 */
		centerPanel.add(calculateButton, gbc);
		centerPanel.add(resetButton, gbc);
		centerPanel.add(writeToFileButton, gbc);
		/**
		 * add labels to SOuth and North Panel
		 */
		southPanel.add(creditLabel);
		northPanel.add(payRollLabel);
		
		///////////////INPUT////////////////////////////
		
		westPanel.add(nameLabel);
		westPanel.add(nameField);
		
		westPanel.add(addressLabel);
		westPanel.add(addressField);
		
		westPanel.add(emailLabel);
		westPanel.add(emailField);
		
		westPanel.add(phoneNumberLabel);
		westPanel.add(phoneNumberField);
		
		westPanel.add(statusLabel);
		westPanel.add(statusField);
		
		
		westPanel.add(totalHourLabel);
		westPanel.add(totalHourField);
		
		///////////////////OUTPUT////////////////////////
		
		eastPanel.add(idLabel);
		eastPanel.add(idField);
		
		eastPanel.add(convertedStatusLabel);
		eastPanel.add(convertedStatusField);
		
		eastPanel.add(mentorLabel);
		eastPanel.add(mentorField);
		
		eastPanel.add(benefitLabel);
		eastPanel.add(benefitField);
		
		eastPanel.add(rateLabel);
		eastPanel.add(rateField);
		
		eastPanel.add(PayBeforeTaxLabel);
		eastPanel.add(PayBeforeTaxField);
		
		eastPanel.add(TaxDeductionLabel);
		eastPanel.add(TaxDeDuctionField);
		
		eastPanel.add(PayAfterTaxLabel);
		eastPanel.add(PayAfterTaxField);
		
		eastPanel.add(bonusLabel);
		eastPanel.add(bonusField);
		
		eastPanel.add(totalPayLabel);
		eastPanel.add(totalPayField);
		
		/**
		 * Outputs fields are not editable
		 * 
		 */
		idField.setEditable(false);
		convertedStatusField.setEditable(false);
		mentorField.setEditable(false);
		benefitField.setEditable(false);
		rateField.setEditable(false);
		PayBeforeTaxField.setEditable(false);
		TaxDeDuctionField.setEditable(false);
		PayAfterTaxField.setEditable(false);

		
		/**
		 * add everything to mainPanel
		 */
		mainPanel.add(centerPanel, BorderLayout.CENTER);
		mainPanel.add(creditLabel, BorderLayout.SOUTH);
		mainPanel.add(northPanel, BorderLayout.NORTH);
		mainPanel.add(westPanel, BorderLayout.WEST);
		mainPanel.add(eastPanel, BorderLayout.EAST);
		
		/**
		 * set Jframe visible
		 */
		this.add(mainPanel);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
		setVisible(true);
	}
	
	// declare variable needed for below classes
	private Employee person;		
	private Information personalInfo;
	private double totalHours = 0;
	private double rop = 0;
	private double pbt = 0;
	private double td = 0;
	private double pat = 0;
	private double pay = 0;
	private int idNumber = 0;
	private double bonus = 0;
	
	public void updateGUI()
	{
		totalHours = Double.parseDouble(totalHourField.getText());
		personalInfo = new Information(nameField.getText(),addressField.getText(),phoneNumberField.getText(), emailField.getText());
		try {
			/**
			 * those TextField are not Editable, after clicking the button
			 */
			nameField.setEditable(false);
			addressField.setEditable(false);
			emailField.setEditable(false);
			phoneNumberField.setEditable(false);
			statusField.setEditable(false);
			totalHourField.setEditable(false);
			idField.setEditable(false);
			convertedStatusField.setEditable(false);
			mentorField.setEditable(false);
			benefitField.setEditable(false);
			rateField.setEditable(false);
			PayBeforeTaxField.setEditable(false);
			TaxDeDuctionField.setEditable(false);
			PayAfterTaxField.setEditable(false);
			bonusField.setEditable(false);
			
			/**
			 * Condition to separate Intern and fulltime. (true-false)
			 * and their respected outputs would be changed as well
			 * 
			 */
			if(statusField.getText().toLowerCase().equals("fulltime"))
			{
				/**
				 * If status = true, condition set to full-time.
				 */
				person = new FullTime(personalInfo,totalHours);
				
				/**
				 * invoke method from Employee to calculate Salary,Tax,....
				 */
				((FullTime)person).calculatePayBeforeTax();
				((FullTime)person).calculateTaxDeduction();
				((FullTime)person).calculateBonus();
				((FullTime)person).calculatePayAfterTax();
				
				idNumber++;
				/**
				 * casting to person type, get respected information calculated above.
				 */
				rop = ((FullTime)person).getPayRate(); 
				pbt = ((FullTime)person).getPayBeforeTax();
				td  = ((FullTime)person).getTaxDeduction();
				pat = ((FullTime)person).getPayAfterTax();
				bonus = ((FullTime)person).getBonus();
				
				/**
				 * information is unique for Full-time, invoked by condition set to true
				 * 
				 */
				idField.setText(Integer.toString(idNumber));
				convertedStatusField.setText("Full Time");
				mentorField.setText("Off");
				benefitField.setText("TRUE");
				rateField.setText(Double.toString(rop));
				
				/**
				 * convert to String
				 */
				PayBeforeTaxField.setText(Double.toString(pbt));
				TaxDeDuctionField.setText(Double.toString(td));
				PayAfterTaxField.setText(Double.toString(pat));
				bonusField.setText(Double.toString(bonus));
				totalPayField.setText(Double.toString(pat));			
			}
			else if(statusField.getText().toLowerCase().equals("intern"))
			{	
				/**
				 * If status = true, condition set to intern.
				 */
				if (totalHours <= 20)
				{
					person = new Intern(personalInfo, totalHours);

					/**
					 * invoke method from Employee to calculate Salary,Tax,....
					 */
					((Intern) person).calculatePayBeforeTax();
					((Intern) person).calculateTaxDeduction();
					((Intern) person).calculatePayAfterTax();
					
					/**
					 * casting to person type, get respected information calculated above.
					 */
					idNumber++;
					rop = ((Intern) person).getPayRate();
					pbt = ((Intern) person).getPayBeforeTax();
					td = ((Intern) person).getTaxDeduction();
					pat = ((Intern) person).getPayAfterTax();
					
					/**
					 * information is unique for Intern, invoke by condition false
					 * 
					 */
					idField.setText(Integer.toString(idNumber));
					convertedStatusField.setText("Intern");
					mentorField.setText("On");
					benefitField.setText("FALSE");
					rateField.setText(Double.toString(rop));
					
					
					/**
					 * convert to String
					 */
					
					PayBeforeTaxField.setText(Double.toString(pbt));
					TaxDeDuctionField.setText(Double.toString(td));
					PayAfterTaxField.setText(Double.toString(pat));
					bonusField.setText(Double.toString(bonus));
					totalPayField.setText(Double.toString(pat));
				}
				/**
				 * Generate Error if Intern working hour exceed 20 hours
				 * 
				 */
				else
				{
					JOptionPane.showMessageDialog(this, "Intern cannot exceed 20 working hours",  
		                    "ERROR", JOptionPane.ERROR_MESSAGE);
				}
			}
			/**
			 * exception caught if input is invalid
			 * 
			 */
		} catch (Exception e) {
			JOptionPane.showMessageDialog(this, "Invalid Input",  
                    "ERROR", JOptionPane.ERROR_MESSAGE); 
		}
	}
	/**
	 * Method to read from TextField  write to a txt file
	 * receive the input, then write all the respected outputs to a file(txt)
	 * depends on intern or fulltime.
	 * Generate exceptions in input are invalid
	 */
	void updateGUIToFile()
	{
		FileHandler file = new FileHandler();
		updateGUI();
		String output = "-INFORMATION OF THE EMPLOYEE-\n" + "Status: " + statusField.getText() + "\nBenefit: " + benefitField.getText() + "\nMentor: " + mentorField.getText() + personalInfo.toString() +
		"\nEmployee ID: " + idNumber + "\n" +"\n--PAY ROLL--" + "\nTotal Hour: " + totalHours + "\nRate Of Pay: $" +
		String.format("%.2f", rop) + "\nTax Rate: $" + "12.3%" + "\nPay Before Tax: $" + String.format("%.2f", pbt)
		+ "\nTax Deduction: $" + String.format("%.2f", td) + "\nPay After Tax: $" + String.format("%.2f", pat) + "\nBonus: $" + 
		String.format("%.2f", bonus) + "\n*Total Pay: $" + String.format("%.2f", pay);
			/*
			 *  we will write this out put to a file, name Output!
			 */
			file.writeToFile("/Users/TranCuong/eclipse-workspace/Project 2/src/Output.txt", output);
	
	}
	/**
	 * Reset
	 * 
	 */
	void resetGUI()
	{	
		/**
		 * set all inputs and outputs field back to blank ""
		 * 
		 */
		idField.setText("");
		nameField.setText("");
		addressField.setText("");
		emailField.setText("");
		phoneNumberField.setText("");
		statusField.setText("");
		totalHourField.setText("");
		convertedStatusField.setText("");
		mentorField.setText("");
		benefitField.setText("");
		rateField.setText("");
		PayBeforeTaxField.setText("");
		TaxDeDuctionField.setText("");
		PayAfterTaxField.setText("");
		bonusField.setText("");
		totalPayField.setText("");
		
		/**
		 * set inputs fields to be editable again
		 */
		nameField.setEditable(true);
		addressField.setEditable(true);
		emailField.setEditable(true);
		phoneNumberField.setEditable(true);
		statusField.setEditable(true);
		totalHourField.setEditable(true);
	}
	
	public static void main(String[] args)
	{	
		new LogInGUI();
	}
	
}
