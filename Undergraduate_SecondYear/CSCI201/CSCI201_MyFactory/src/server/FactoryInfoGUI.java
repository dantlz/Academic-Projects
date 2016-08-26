package server;

import java.awt.BorderLayout;
import java.awt.Color;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneConstants;
import javax.swing.plaf.metal.MetalScrollBarUI;

import resource.Factory;

public class FactoryInfoGUI extends JDialog {

	private static final long serialVersionUID = 1L;

	private Factory factory;
	private JMenuBar menuBar;
	private JMenuItem aboutMenuItem;
	private JPanel topPanel;
	private JLabel dimensionsLabel;
	private JLabel taskBoardLocLabel;
	private JPanel bottomPanel;
	private JScrollPane resourcesScroll;
	private JPanel resourcesPanel;
	private JScrollPane productsScroll;
	private JPanel productsPanel;
	private Vector<String> resourceTitles;
	private Vector<JPanel> resourcePanels;
	
	public FactoryInfoGUI(){
		initializeVariables();
		createGUI();
	}
	
	private void initializeVariables(){
		menuBar = new JMenuBar();
		aboutMenuItem = new JMenuItem("About");
		
		topPanel = new JPanel();
		dimensionsLabel = new JLabel();
		taskBoardLocLabel = new JLabel();
		
		bottomPanel = new JPanel();
		resourcesScroll = new JScrollPane();
		resourcesPanel = new JPanel();
		productsScroll = new JScrollPane();
		productsPanel = new JPanel();
		
		resourceTitles = new Vector<String>();
		resourceTitles.add("Motherboard");
		resourceTitles.add("Processor");
		resourceTitles.add("Hard Drive");
		resourceTitles.add("Memory");
		resourceTitles.add("Box");
		
		resourcePanels = new Vector<JPanel>();
		for(int i = 0; i < resourceTitles.size(); i++){
			resourcePanels.add(new JPanel());
		}
	}
	
	private void createGUI(){
		setDefaultCloseOperation(HIDE_ON_CLOSE);
		setSize(Constants.factoryGUIwidth, Constants.factoryGUIheight);
		setLayout(new BorderLayout());
		setVisible(false);
		setJMenuBar(menuBar);
		menuBar.add(aboutMenuItem);
		
		add(topPanel, BorderLayout.NORTH);
		topPanel.setBorder(BorderFactory.createLineBorder(Color.black, 2));
		topPanel.add(dimensionsLabel);
		topPanel.add(taskBoardLocLabel);
		
		add(bottomPanel, BorderLayout.CENTER);
		bottomPanel.setLayout(new BoxLayout(bottomPanel, BoxLayout.X_AXIS));
		bottomPanel.add(resourcesScroll);
		resourcesScroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		resourcesScroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		resourcesScroll.getVerticalScrollBar().setUI(new MetalScrollBarUI());
		resourcesScroll.add(resourcesPanel);
		resourcesPanel.setLayout(new BoxLayout(resourcesPanel, BoxLayout.Y_AXIS));
		
		bottomPanel.add(productsScroll);
		productsScroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		productsScroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		productsScroll.add(productsPanel);
		productsPanel.setLayout(new BoxLayout(productsPanel, BoxLayout.Y_AXIS));
		
		for(int i = 0; i < resourcePanels.size(); i ++){
			JPanel current = resourcePanels.get(i);
			current.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black), resourceTitles.get(i)));
			current.setBackground(Color.blue);
			current.setPreferredSize(current.getMaximumSize());
			resourcesPanel.add(current);
		}
	}
	
	public void receiveFactory(Factory factory){
		this.factory = factory;
		populateWithData();
	}
	
	private void populateWithData(){
		dimensionsLabel.setText("Width: " 
				+ factory.getWidth() 
				+ " Height: " 
				+ factory.getHeight()
				+"          ");
		taskBoardLocLabel.setText("          "
				+"TaskBoard Location: ("
				+factory.getTaskBoardLocation().x
				+","+factory.getTaskBoardLocation().y
				+")");
	}
	
	
}
