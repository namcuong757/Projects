
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;

import javax.swing.*;

public class LogInGUI extends JFrame
{		
	/**
	 * variables declaration for LogIn GUI 
	 * 
	 */
	private JFrame passwordframe = new JFrame();

	private JLabel adminLabel = new JLabel("admin");
	private JLabel psswdLabel = new JLabel("password");
	private JLabel wrongPassWordLabel = new JLabel("");	

	private JButton logInbtn = new JButton("Next");
	private JPanel logInPanel = new JPanel();
	
	private JPasswordField passWtxt = new  JPasswordField();
	private JTextField adminTXF = new JTextField (50);
	
	/**
	 * method to generate error message when exception caught
	 * 
	 */
	public void errorMessage()
	{
		JOptionPane.showMessageDialog(this, "ERORR 404",  
                "ERROR", JOptionPane.ERROR_MESSAGE);
	}
	/**
	 * Constructor 
	 * 
	 */
	
	public LogInGUI() 
	{	
		/**
		 * password frame, size, name
		 */
		passwordframe.setTitle("Log In");
		passwordframe.add(logInPanel);
		passwordframe.setSize(350,200);
		
		/**
		 * no layout for LogIn Panel
		 */
		logInPanel.setLayout(null);
		
		
		/**
		 * admin Label - Texfield
		 */
		adminLabel.setBounds(10,20,80,25);
		logInPanel.add(adminLabel);
		logInPanel.add(wrongPassWordLabel);	
		adminTXF.setBounds(100,20,170,25);
		
		/**
		 * psswd Label - Passwordfield
		 */
		logInPanel.add(adminTXF);
		logInPanel.add(psswdLabel);
		psswdLabel.setBounds(10,50,80,25);
		passWtxt.setBounds(100,50,170,25);
		logInPanel.add(passWtxt);
		
		/**
		 *  LogIn button
		 */
		logInbtn.setBounds(150,80,80,25);
		logInPanel.add(logInbtn);	
		logInbtn.addActionListener(new ActionListener()
		
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				if(adminTXF.getText().equals("admin") && Arrays.equals(passWtxt.getPassword(), new char[]{'p','a','s','s'}))
				{
					passwordframe.dispose(); // dipose the window when pass is correct
					try
					{
						new View(); 
					}
					catch(Exception error)
					{
						errorMessage();
					}
				}
				else
				{
					wrongPassWordLabel.setText("sounds good, doesn't work!");
					wrongPassWordLabel.setForeground(Color.RED);
				}
			}
	
		});
		
		//success LogIn
		wrongPassWordLabel.setBounds(10,110,300,25);	
		
		passwordframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);	
		passwordframe.setVisible(true);
		
	}
		
}
