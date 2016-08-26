package tianlinz_CS201L_assignment3;

import java.awt.Component;
import java.awt.Container;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;

import javax.swing.JMenu;


public class HelperMethods {

	public static Graphics drawStringCentered(int containerHeight, int containerWidth, Font font, String text, Graphics g){
	    FontMetrics metrics = g.getFontMetrics(font);
	    int x = (containerWidth- metrics.stringWidth(text)) / 2;
	    int y = containerHeight/2 + metrics.getAscent()/2;
	    g.setFont(font);
		g.drawString(text, x, y);
		return g;
	}

	public static String removeNonAlpha(String str){
		String result = "";
		for(char current: str.toCharArray()){
			if( Character.isLetter(current) || Character.isSpaceChar(current))
				result = result + current;
		}
		return result;
	}
	
	public static String normalizeText(String text){
		return text.replaceAll(System.lineSeparator(), " ").toLowerCase();
	}

	public static void customizeFonts(Container c){
		Component[] allComponents = c.getComponents();
		if(c instanceof JMenu){
			 allComponents = ((JMenu)c).getMenuComponents();
		}
		
		for(Component entry: allComponents){
			entry.setFont(Constants.avenir);
			if(entry instanceof Container){
				customizeFonts((Container)entry);
			}
		}
	}
}
