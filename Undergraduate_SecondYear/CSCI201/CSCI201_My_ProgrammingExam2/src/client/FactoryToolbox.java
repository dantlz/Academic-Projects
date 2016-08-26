package client;

import java.awt.Rectangle;
import java.util.concurrent.Semaphore;

import libraries.ImageLibrary;

public class FactoryToolbox extends FactoryObject {

	private Semaphore semaphore;
	
	public void acquire(){
		try {
			semaphore.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public void release(){
		semaphore.release();
	}
	
	
	
	protected FactoryToolbox(Rectangle inDimensions, int sNumber) {
		super(inDimensions);
		semaphore = new Semaphore(sNumber);
		mImage =  ImageLibrary.getImage(Constants.resourceFolder + "Toolbox" + Constants.png);
	}

}
