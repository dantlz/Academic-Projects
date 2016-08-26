package client;

import java.awt.BorderLayout;
import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowStateListener;
import java.net.Socket;
import java.util.Dictionary;
import java.util.Hashtable;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSlider;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.KeyStroke;
import javax.swing.border.TitledBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;

public class FactoryClientGUI extends JFrame implements KeyListener{
	
	public static final long serialVersionUID = 1;
	
	private FactoryPanel factoryPanel;
	private FactoryManager factoryManager;

	private JTextArea messageTextArea;
	private JTable productTable;
	private DefaultTableModel productTableModel;
	private JScrollPane tableScrollPane;
	private JSlider simulationSpeedController;
	
	private FactoryController factoryController;
	
	private JMenuBar menuBar;
	private JMenuItem controller;
			
	FactoryClientGUI(Socket socket){
		super(Constants.factoryGUITitleString);
		factoryManager = new FactoryManager();
		initializeVariables();
		createGUI();
		new FactoryClientListener(factoryManager, this, socket);
		addActionAdapters();
		setLocationRelativeTo(null);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		createMenu();
		addListener();
		setFocusable(true);
		addKeyListener(this);		
	}
	
	private void initializeVariables() {
		messageTextArea = new JTextArea(10, 50);
		factoryPanel = new FactoryPanel();
		factoryManager.setFactoryRenderer(factoryPanel);
		
		productTableModel = new DefaultTableModel(null, Constants.tableColumnNames);
		productTable = new JTable(productTableModel);
		productTable.setEnabled(false);
		TableRowSorter<TableModel> sorter = new TableRowSorter<TableModel>(productTableModel);
		productTable.setRowSorter(sorter);
		tableScrollPane = new JScrollPane(productTable);
		tableScrollPane.setBounds(Constants.factoryGUIwidth - Constants.tableWidth - 10, 0, Constants.tableWidth, Constants.factoryGUIheight - 100);
		
		simulationSpeedController = new JSlider(JSlider.HORIZONTAL,Constants.simulation_0x, Constants.simulation_3x, Constants.simulation_1x);
		simulationSpeedController.addChangeListener(factoryManager);
		simulationSpeedController.setMajorTickSpacing(1);
		simulationSpeedController.setMinorTickSpacing(1);
		simulationSpeedController.setPaintTicks(true);
		
		factoryController = new FactoryController();
		simulationSpeedController.addChangeListener(factoryController);	
		addWindowStateListener(factoryController);
	}
	
	private void createGUI() {
		setSize(Constants.factoryGUIwidth, Constants.factoryGUIheight);
		setLayout(new BorderLayout());
		JScrollPane messageTextAreaScrollPane = new JScrollPane(messageTextArea);
		
		Box bottomBox = Box.createHorizontalBox();
		bottomBox.add(messageTextAreaScrollPane);
		bottomBox.add(new FactoryProgressPanel(productTable));
		
		add(factoryPanel,BorderLayout.CENTER);
		add(bottomBox, BorderLayout.SOUTH);
		add(tableScrollPane,BorderLayout.EAST);
	}
	
	public void addListener(){
		controller.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C, InputEvent.CTRL_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK));
	}
	
	public JTable getTable() {
		return productTable;
	}
	
	private void addActionAdapters() {
		addWindowListener(new WindowAdapter() {
			  public void windowClosing(WindowEvent we) {
				  System.exit(0);
			  }
		});
	}
	
	public void addMessage(String msg) {
		if (messageTextArea.getText().length() != 0) {
			messageTextArea.append("\n");
		}
		messageTextArea.append(msg);
	}
	
	private void createMenu(){
		menuBar = new JMenuBar();
		controller = new JMenuItem("Controller");
		controller.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				factoryController.setVisible(true);
			}
		});
		menuBar.add(controller);
		setJMenuBar(menuBar);
	}

	@Override
	public void keyPressed(KeyEvent e) {
		switch (e.getKeyChar()) {
		case 'p':
			factoryController.pause();
			return;
		case 'c':
			factoryController.cont();
			return;
		case 'r':
			factoryController.reset();
			return;
		}
		
		switch (e.getKeyCode()) {
		case KeyEvent.VK_RIGHT:
			switch (simulationSpeedController.getValue()) {
			case Constants.simulation_0x:
				simulationSpeedController.setValue(Constants.simulation_1x);
				break;
			case Constants.simulation_1x:
				simulationSpeedController.setValue(Constants.simulation_2x);
				break;
			case Constants.simulation_2x:
				simulationSpeedController.setValue(Constants.simulation_3x);
				break;
			case Constants.simulation_3x:
				break;
			}
			break;
		case KeyEvent.VK_LEFT:
			switch (simulationSpeedController.getValue()) {
			case Constants.simulation_0x:
				break;
			case Constants.simulation_1x:
				simulationSpeedController.setValue(Constants.simulation_0x);
				break;
			case Constants.simulation_2x:
				simulationSpeedController.setValue(Constants.simulation_1x);
				break;
			case Constants.simulation_3x:
				simulationSpeedController.setValue(Constants.simulation_2x);
				break;
			}
			break;
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		
	}
	@Override
	public void keyTyped(KeyEvent e) {
	}

	class FactoryController extends JFrame implements ChangeListener, WindowStateListener{
		private static final long serialVersionUID = 1L;
		private int speed = Constants.simulation_1x;
		private int windowSaveSpeed;
		private JTabbedPane tabbedPane;
		private JPanel timePanel;
		private JPanel buttonBox;
		private JButton pauseButton;
		private JButton continueButton;
		private JButton resetButton;
		
		public FactoryController(){
			super("Factory Controller");
			setSize(320, 240);
			tabbedPane = new JTabbedPane();
			
			createTimePanel();
			createOtherPanel();
			addListeners();
			
			add(tabbedPane);
			
			setVisible(false);
			setLocationRelativeTo(null);
		}

		private void createTimePanel(){
			timePanel = new JPanel();
			timePanel.setLayout(new BorderLayout());
			
			buttonBox = new JPanel();
			buttonBox.setLayout(new GridBagLayout());
			GridBagConstraints gbc = new GridBagConstraints();
			gbc.fill = GridBagConstraints.HORIZONTAL;
			gbc.weighty = 1;
			pauseButton = new JButton("Pause");
			gbc.gridy = 1;
			buttonBox.add(pauseButton, gbc);
			continueButton = new JButton("Continue");
			continueButton.setEnabled(false);
			gbc.gridy = 2;
			buttonBox.add(continueButton, gbc);			
			resetButton = new JButton("Reset");
			gbc.gridy = 3;
			buttonBox.add(resetButton, gbc);
			
			
			Dictionary<Integer, JLabel> labelTable = new Hashtable<>();
			labelTable.put(Constants.simulation_0x, new JLabel("Paused"));
			labelTable.put(Constants.simulation_1x, new JLabel("Normal"));
			labelTable.put(Constants.simulation_2x, new JLabel("Double"));
			labelTable.put(Constants.simulation_3x, new JLabel("Triple"));
			simulationSpeedController.setLabelTable(labelTable);
			simulationSpeedController.setPaintLabels(true);
			simulationSpeedController.setBorder(new TitledBorder("Speed Controller"));
			
	
			timePanel.add(buttonBox);
			timePanel.add(simulationSpeedController, BorderLayout.SOUTH);
			tabbedPane.add("Time", timePanel);
		}
		
		private void createOtherPanel(){
			JPanel otherPanel = new JPanel();
			tabbedPane.add("Other", otherPanel);
		}
		
		public void addListeners(){
			pauseButton.addActionListener(new ActionListener() {		
				@Override
				public void actionPerformed(ActionEvent e) {
					pause();
				}
			});
			
			continueButton.addActionListener(new ActionListener() {		
				@Override
				public void actionPerformed(ActionEvent e) {
					cont();
				}
			});
			
			resetButton.addActionListener(new ActionListener() {		
				@Override
				public void actionPerformed(ActionEvent e) {
					reset();
				}
			});
		}

		@Override
		public void stateChanged(ChangeEvent e) {
			int state = ((JSlider)e.getSource()).getValue();
			if(state == Constants.simulation_0x){
				continueButton.setEnabled(true);
				pauseButton.setEnabled(false);
			}
			else{
				continueButton.setEnabled(false);
				pauseButton.setEnabled(true);
			}
		}

		@Override
		public void windowStateChanged(WindowEvent e) {
			int state = e.getNewState();
			if((state & Frame.ICONIFIED) == Frame.ICONIFIED){
				setVisible(false);
				windowSaveSpeed = simulationSpeedController.getValue();
				simulationSpeedController.setValue(Constants.simulation_0x);
			}
			else{
				simulationSpeedController.setValue(windowSaveSpeed);
			}
		}
		
		public void reset(){
			continueButton.setEnabled(false);
			pauseButton.setEnabled(true);
			speed = Constants.simulation_1x;
			simulationSpeedController.setValue(speed);
			factoryManager.reset();
		}
		
		public void pause(){
			continueButton.setEnabled(true);
			pauseButton.setEnabled(false);
			speed = simulationSpeedController.getValue();
			simulationSpeedController.setValue(Constants.simulation_0x);
		}
		
		public void cont() { 
			continueButton.setEnabled(false);
			pauseButton.setEnabled(true);
			simulationSpeedController.setValue(speed);
		}
	}
	
}
