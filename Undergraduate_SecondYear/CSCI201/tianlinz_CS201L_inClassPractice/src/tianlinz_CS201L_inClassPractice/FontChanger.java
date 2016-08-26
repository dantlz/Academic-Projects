package tianlinz_CS201L_inClassPractice;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class FontChanger extends JFrame {

	private static final long serialVersionUID = 1L;
	
	private JLabel fontNameLabel, fontSizeLabel;
	private JComboBox<String> fontNameCB, fontSizeCB;
	private JTextField textField;
	private JCheckBox boldCB, italicCB, centerCB;
	
	public FontChanger(){
		super("Font Changer");
		instantiateComponents();
		createGUI();
		addActions();
	}
	
	public void instantiateComponents(){
		fontNameLabel = new JLabel("Font Name");
		fontSizeLabel = new JLabel("Font Size");
		textField = new JTextField("CSCI201 M888");
		boldCB = new JCheckBox("Bold");
		italicCB = new JCheckBox("Italic");
		centerCB = new JCheckBox("Center");
		String[] fontNames = new String[]{"Times New Roman", "Courier New", "Arial"};
		fontNameCB = new JComboBox<String>(fontNames);
		String[] fontSizes = new String[]{"8", "12", "24", "36"};
		fontSizeCB = new JComboBox<String>(fontSizes);
	}
	
	public void createGUI(){
		setSize(330, 150);
		setLocation(600, 50);
		JPanel northPanel = new JPanel();
		northPanel.add(fontNameLabel);
		northPanel.add(fontNameCB);
		northPanel.add(fontSizeLabel);
		northPanel.add(fontSizeCB);
		this.add(northPanel, BorderLayout.NORTH);
		this.add(textField, BorderLayout.CENTER);
		JPanel southPanel = new JPanel();
		southPanel.add(boldCB);
		southPanel.add(italicCB);
		southPanel.add(centerCB);
		this.add(southPanel, BorderLayout.SOUTH);
	}
	
	public void addActions(){
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				super.windowClosing(e);
				System.exit(1);
			}
		});
		fontNameCB.addItemListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent e) {
				if(e.getStateChange() == ItemEvent.SELECTED){
					changeText();
				}
			}
		});
		fontSizeCB.addItemListener(new ItemListener() {
			
			@Override
			public void itemStateChanged(ItemEvent e) {
				if(e.getStateChange() == ItemEvent.SELECTED){
					changeText();
				}
			}
		});
	}
	
	public void changeText(){
		String fontName = fontNameCB.getItemAt(fontNameCB.getSelectedIndex());
		int fontSize = Integer.parseInt(fontSizeCB.getItemAt(fontSizeCB.getSelectedIndex()));
		textField.setFont(new Font(fontName, Font.PLAIN,  fontSize));
	}

	public static void main(String[] args) {
		FontChanger fChanger = new FontChanger();
		fChanger.setVisible(true);
	}

}
