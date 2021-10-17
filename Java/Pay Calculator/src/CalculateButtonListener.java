
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
