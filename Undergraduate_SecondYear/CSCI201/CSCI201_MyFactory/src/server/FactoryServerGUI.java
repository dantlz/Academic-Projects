package server;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import utilities.Util;

public class FactoryServerGUI extends JFrame {

	public static final long serialVersionUID = 1;
	private static JTextArea textArea;
	private JScrollPane textAreaScrollPane;
	private JButton selectFactoryButton;
	private JComboBox<String> selectFactoryComboBox;

	private JButton factoryInfoButton;
	private FactoryInfoGUI factoryInfoGUI;
	
	public FactoryServerGUI() {
		super(Constants.factoryGUITitleString);
		initializeVariables();
		createGUI();
		addActionAdapters();
		setVisible(true);
	}
	
	private void initializeVariables() {
		textArea = new JTextArea();
		textArea.setEditable(false);
		textAreaScrollPane = new JScrollPane(textArea);

		Vector<String> filenamesVector = new Vector<String>();
		File directory = new File(Constants.defaultResourcesDirectory);
		File[] filesInDirectory = directory.listFiles();
		for (File file : filesInDirectory) {
		    if (file.isFile()) {
		    	filenamesVector.add(file.getName());
		    }
		}
		selectFactoryButton = new JButton(Constants.selectFactoryButtonString);
		selectFactoryComboBox = new JComboBox<String>(filenamesVector);
		
		factoryInfoButton = new JButton("Factory Info");
		factoryInfoGUI = new FactoryInfoGUI();
	}
	
	private void createGUI() {
		setSize(Constants.factoryGUIwidth, Constants.factoryGUIheight);
		JPanel northPanel = new JPanel();
		northPanel.add(selectFactoryComboBox);
		northPanel.add(selectFactoryButton);
		northPanel.add(factoryInfoButton);
		add(northPanel, BorderLayout.NORTH);
		add(textAreaScrollPane, BorderLayout.CENTER);
	}
	
	private void addActionAdapters() {
		addWindowListener(new WindowAdapter() {
			  public void windowClosing(WindowEvent we) {
				  System.exit(0);
			  }
		});
		
		selectFactoryButton.addActionListener(new ConfigureFactoryListener(selectFactoryComboBox));
		
		factoryInfoButton.addActionListener(new ConfigureFactoryListener(selectFactoryComboBox){
			@Override
			public void actionPerformed(ActionEvent ae) {

				BufferedReader br = null;
				try {
					String factoryFileName = (String)selectFactoryComboBox.getSelectedItem();
					br = new BufferedReader(new FileReader(Constants.defaultResourcesDirectory + factoryFileName));
					factory = readFile(br);
					factoryInfoGUI.receiveFactory(factory);
					factoryInfoGUI.setModal(true);
					factoryInfoGUI.setVisible(true);
				} catch (FileNotFoundException fnfe) {
					Util.printExceptionToCommand(fnfe);
				} catch (IOException ioe) {
					Util.printExceptionToCommand(ioe);
				} finally {
					if (br != null) {
						try {
							br.close();
						} catch (IOException ioe1) {
							Util.printExceptionToCommand(ioe1);
						}
					}
				}
				
			}
		});		
	}
	
	public static void addMessage(String msg) {
		if (textArea.getText() != null && textArea.getText().trim().length() > 0) {
			textArea.append("\n" + msg);
		}
		else {
			textArea.setText(msg);
		}
	}
}
