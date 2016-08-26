package client;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.table.TableModel;;

public class FactoryProgressPanel extends JPanel implements Runnable{
	private static final long serialVersionUID = 1L;
	
	private JTable mTable;
	private TableModel mModel;
	private final String title = "Factory Progress";
	private final int border = 20;
	
	public FactoryProgressPanel(JTable inTable) {
		mTable = inTable;
		mModel = mTable.getModel();
		new Thread(this).start();
	}
	
	@Override
	protected void paintComponent(Graphics g){
		super.paintComponent(g);
		int w = this.getWidth();
		int h = this.getHeight();
		Font font = new Font("Times New Roman", Font.BOLD | Font.ITALIC, w/24);
		g.setFont(font);
		int strWidth = g.getFontMetrics(font).stringWidth(title);
		g.drawString(title, (w-strWidth)/2, g.getFontMetrics(font).getHeight());
	
		double total = 0;
		double started = 0;
		double completed = 0;
		for(int i = 0; i < mModel.getRowCount(); ++i){
			total += (int) mModel.getValueAt(i, Constants.totalNameIndex);
			started += (int) mModel.getValueAt(i, Constants.startedIndex);
			completed += (int) mModel.getValueAt(i, Constants.completedIndex);
		}
		
		int frameX = border;
		int frameY = border + g.getFontMetrics(font).getHeight();
		int frameW = w-border-border;
		int frameH = h-border-border - g.getFontMetrics(font).getHeight();
		g.drawRect(frameX-1, frameY-1, frameW+1, frameH+1);
		
		int startedWidth = (int) ((started/total)*frameW);
		int completedWidth = (int) ((completed/total)*frameW);
		int nostatusWidth = frameW - (startedWidth + completedWidth);

		g.setColor(Color.GREEN);
		g.fillRect(frameX, frameY, completedWidth, frameH);
		if(completed > 0){
			g.setColor(Color.BLACK);
			g.drawString((int)((double)completed/(double)total*100) + "%", 
				completedWidth/2, 
				frameH);
			g.drawString("Completed", 
					completedWidth/2, 
					this.getHeight()-50);
			
		}
		g.setColor(Color.YELLOW);
		g.fillRect(frameX+completedWidth, frameY, startedWidth, frameH);	
		if(startedWidth > 0){
			g.setColor(Color.BLACK);
			g.drawString((int)((double)started/(double)total*100) + "%", 
				startedWidth/2 + completedWidth, 
				frameH);
			g.drawString("Started", 
					startedWidth/2 + completedWidth, 
					this.getHeight()-50);
		}
		g.setColor(Color.RED);
		g.fillRect(frameX + startedWidth + completedWidth, frameY, nostatusWidth, frameH);
		if(nostatusWidth > 0){
			g.setColor(Color.BLACK);
			g.drawString((int)((double)(total-completed-started)/(double)total*100) + "%"+"\n", 
				startedWidth/2 + completedWidth + startedWidth, 
				frameH);
			g.drawString("Not Started", 
					startedWidth/2 + completedWidth + startedWidth, 
					this.getHeight()-50);
		}
	}

	@Override
	public void run() {
		while(true){
			try{
				Thread.sleep(33);
				repaint();
			}
			catch (InterruptedException e){
				e.printStackTrace();
			}
		}
	}
}
