import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ResetButtonListener implements ActionListener {

	private View view;
	
	/**
	 * Constructor for reset button
	 * @param newView
	 */
	public ResetButtonListener(View newView)
	{
		view = newView;
	}
	/**
	 * ActionListener implementation
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		view.resetGUI();
		
	}

}
