/**
 * Lead Author(s):
 * @author Cuong Tran
 * @author Nhat Le
 * 
 * Other contributors: none
 * 
 * Responsibilities of class: implementing ActionListener for CalculateButton from view Class
 * 
 * 
 */

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CalculateButtonListener implements ActionListener{
	private View view ;
	
	public CalculateButtonListener(View newView)
	{
		view = newView;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		view.updateGUI();
	}

}
