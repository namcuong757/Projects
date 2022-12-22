

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class WriteToFileButtonListener implements ActionListener{
	private View view;
	
	/**
	 * Constructor t
	 * @param newView
	 */
	public WriteToFileButtonListener(View newView)
	{
		view = newView;
	}
	/**
	 * Override action perform form ActionListener
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		view.updateGUIToFile();
		
		
	}

}
