package tianlinz_CS201L_assignment4;

import javax.swing.UIManager;

//This should be the only main() method. Use this to run the project
public class Launcher {
	public static void main(String[] args) {
		try{
			UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
		}
		catch(Exception e){
			System.out.println("Warning! Cross-platform L&F not used!");
		}
		
		MyClient loginWindow = new MyClient();
		loginWindow.setVisible(true);
		MyServerGUI test = new MyServerGUI();
		test.setVisible(true);	
	}
}