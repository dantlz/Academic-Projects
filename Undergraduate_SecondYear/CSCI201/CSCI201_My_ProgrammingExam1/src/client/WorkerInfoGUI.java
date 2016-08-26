package client;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;

public class WorkerInfoGUI extends javax.swing.JFrame {
	
	private static final long serialVersionUID = 1L;
	private FactoryWorker currentWorker;
	
	private JPanel leftPanel;
	private JLabel picture;
	private JLabel position;
	private JLabel fixed_currentTask;
	private JLabel currentTask;
	private JLabel fixed_destination;
	private JLabel destination;
	
	private JPanel rightPanel;
	private JLabel name;
	private JScrollPane scrollPane;
	private JTable productsTable;
	private JButton refreshButton;

	public WorkerInfoGUI(FactoryWorker worker) {
		super();
		currentWorker = worker;
		initializeVariables();
		createGUI();
		addListeners();
		addData();
		setLocationRelativeTo(null);
		setVisible(true);
		setDefaultCloseOperation(HIDE_ON_CLOSE);	
		setSize(400,400);
	}
	
	public void initializeVariables(){
		this.setTitle("Worker Info");
		
		leftPanel = new JPanel();
		picture = new JLabel();
		position = new JLabel("N/A");
		fixed_currentTask = new JLabel("Current Task:");
		currentTask = new JLabel("N/A");
		fixed_destination = new JLabel("Current Destination: ");
		destination = new JLabel("N/A");
		
		rightPanel = new JPanel();		
		name = new JLabel();
		scrollPane = new JScrollPane();
		scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		String [] columnNames = {"Products", "# Complete"};
		Vector<String> completedProducts = currentWorker.finishedProducts();
		Vector<Integer> completedNumbers = currentWorker.finishedNumbers();
		Object [][] data = new Object[completedProducts.size()][2];
		for(int i = 0; i < completedProducts.size(); i ++){
			data[i][0] = completedProducts.get(i);
			data[i][1] = completedNumbers.get(i);
		}
		productsTable= new JTable(data, columnNames);
		refreshButton = new JButton("Refresh");
	}
	
	public void createGUI(){
		this.setLayout(new BoxLayout(getContentPane(), BoxLayout.X_AXIS));
		this.add(leftPanel);
		leftPanel.setLayout(new BoxLayout(leftPanel, BoxLayout.Y_AXIS));
		leftPanel.add(picture);
		leftPanel.add(position);
		leftPanel.add(fixed_currentTask);
		leftPanel.add(currentTask);
		leftPanel.add(fixed_destination);
		leftPanel.add(destination);
		this.add(rightPanel);
		rightPanel.setLayout(new BoxLayout(rightPanel, BoxLayout.Y_AXIS));
		rightPanel.add(name);
		rightPanel.add(scrollPane);
		scrollPane.add(productsTable);
		rightPanel.add(refreshButton);
	}
	
	public void addData(){

		picture.setIcon(new ImageIcon(currentWorker.getPicture()));
		position.setText("Positon: ("+currentWorker.getCurrentPosition().getX()+","+currentWorker.getCurrentPosition().getY()+")");
		if(currentWorker.getCurrentTask()!=null)
			currentTask.setText(currentWorker.getCurrentTask().getName());
		else
			currentTask.setText("N/A");
		if(currentWorker.getDestination()!=null)
			destination.setText(currentWorker.getDestination().mLabel);
		else
			destination.setText("N/A");
		
		name.setText("Worker "+currentWorker.getWorkerName());
		String [] columnNames = {"Products", "# Complete"};
		Vector<String> completedProducts = currentWorker.finishedProducts();
		Vector<Integer> completedNumbers = currentWorker.finishedNumbers();
		Object [][] data = new Object[completedProducts.size()][2];
		for(int i = 0; i < completedProducts.size(); i ++){
			data[i][0] = completedProducts.get(i);
			data[i][1] = completedNumbers.get(i);
		}
		productsTable= new JTable(data, columnNames);
	}
	
	public void addListeners(){
		refreshButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				refreshData();
			}
		});
	}
	
	public void refreshData(){
		
	}
	
}
