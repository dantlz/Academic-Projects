package client;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.Random;
import java.util.Stack;
import java.util.Vector;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import resource.Product;
import resource.Resource;
import libraries.ImageLibrary;

public class FactoryWorker extends FactoryObject implements Runnable{

	private static final long serialVersionUID = 1L;

	private int mNumber;
	
	private FactorySimulation mFactorySimulation;
	private Product mProductToMake;
	
	private Lock mLock;
	private Condition atLocation;
	
	//Nodes each worker keeps track of for path finding
	private FactoryNode mCurrentNode;
	private FactoryNode mNextNode;
	private FactoryNode mDestinationNode;
	private Stack<FactoryNode> mShortestPath;
	
	private Vector<String> completedProducts;
	private Vector<Integer> completedNumbers;
	
	private WorkerInfoGUI infoGUI;
	
	//instance constructor
	{
		Random random = new Random();
		int n = random.nextInt()%6;
		switch (n) {
		case 1:
			mImage = ImageLibrary.getImage(Constants.resourceFolder + "worker_black" + Constants.png);
			break;
		case 2:
			mImage = ImageLibrary.getImage(Constants.resourceFolder + "worker_blue" + Constants.png);
			break;		
		case 3:
			mImage = ImageLibrary.getImage(Constants.resourceFolder + "worker_green" + Constants.png);
			break;		
		case 4:
			mImage = ImageLibrary.getImage(Constants.resourceFolder + "worker_purple" + Constants.png);
			break;		
		case 5:
			mImage = ImageLibrary.getImage(Constants.resourceFolder + "worker_red" + Constants.png);
			break;
		default://0
			mImage = ImageLibrary.getImage(Constants.resourceFolder + "worker_yellow" + Constants.png);
			break;
		}
		mLock = new ReentrantLock();
		atLocation = mLock.newCondition();
	
	}
	
	FactoryWorker(int inNumber, FactoryNode startNode, FactorySimulation inFactorySimulation) {
		super(new Rectangle(startNode.getX(), startNode.getY(), 1, 1));
		mNumber = inNumber;
		mCurrentNode = startNode;
		mFactorySimulation = inFactorySimulation;
		mLabel = Constants.workerString + String.valueOf(mNumber);
		
		//TODO
		completedProducts = new Vector<String>();
		completedNumbers = new Vector<Integer>();
		infoGUI = new WorkerInfoGUI(this);
		infoGUI.setVisible(false);
		
		new Thread(this).start();
	}
	
	@Override
	public void draw(Graphics g, Point mouseLocation) {
		super.draw(g, mouseLocation);
		drawMouseover(g,mouseLocation);
	}
	
	private void drawMouseover(Graphics g, Point mouseLocation) {
		if(renderBounds.contains(mouseLocation)) {
			if(!infoGUI.isVisible())
				infoGUI.setVisible(true);
		}
	}
	
	@Override
	public void update(double deltaTime) {
		if(!mLock.tryLock()) return;
		//if we have somewhere to go, go there
		if(mDestinationNode != null) {
			if(moveTowards(mNextNode,deltaTime * Constants.workerSpeed)) {
				//if we arrived, save our current node
				mCurrentNode = mNextNode;
				if(!mShortestPath.isEmpty()) {
					//if we have somewhere else to go, save that location
					mNextNode = mShortestPath.pop();
				}//if we arrived at the location, signal the worker thread so they can do more actions
				if(mCurrentNode == mDestinationNode) atLocation.signal();
			}
		}
		mLock.unlock();
	}
	
	//Use a separate thread for expensive operations
	//Path finding
	//Making objects
	//Waiting
	@Override
	public void run() {
		mLock.lock();
		try {
			//Thread.sleep(1000*mNumber); //used to space out the factory workers
			while(true) {
				if(mProductToMake == null) {
					//get an assignment from the table
					mDestinationNode = mFactorySimulation.getNode("Task Board");
					mShortestPath = mCurrentNode.findShortestPath(mDestinationNode);
					mNextNode = mShortestPath.pop();
					atLocation.await();
					

					
					while(!mDestinationNode.aquireNode())Thread.sleep(1);
					mProductToMake = mFactorySimulation.getTaskBoard().getTask();
					Thread.sleep(1000);
					mDestinationNode.releaseNode();
					
					if(mProductToMake == null) {
						break; //No more tasks, end here
					}
				}
				//build the product
				for(Resource resource : mProductToMake.getResourcesNeeded()) {
					mDestinationNode = mFactorySimulation.getNode(resource.getName());
					mShortestPath = mCurrentNode.findShortestPath(mDestinationNode);
					mNextNode = mShortestPath.pop();
					atLocation.await();
					FactoryResource toTake = (FactoryResource)mDestinationNode.getObject();
					toTake.takeResource(resource.getQuantity());
				}
				//update table
				{
					mDestinationNode = mFactorySimulation.getNode("Task Board");
					
					
					//TODO
					boolean ok = false;
					for(int i = 0; i < completedProducts.size(); i++){
						if(completedProducts.get(i).equals(mProductToMake.getName())){
							completedNumbers.set(i, completedNumbers.get(i)+mProductToMake.getQuantity());
							ok = true;
						}
					}
					if(!ok){
						completedProducts.add(mProductToMake.getName());
						completedNumbers.add(mProductToMake.getQuantity());
					}
						
						
					mShortestPath = mCurrentNode.findShortestPath(mDestinationNode);
					mNextNode = mShortestPath.pop();
					atLocation.await();
					mFactorySimulation.getTaskBoard().endTask(mProductToMake);
					mProductToMake = null;
				}
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		mLock.unlock();
	}

	public int getWorkerName(){
		return mNumber;
	}
	
	public FactoryNode getCurrentPosition(){
		return mCurrentNode;
	}
	
	public Product getCurrentTask(){
		return mProductToMake;
	}
	
	public FactoryNode getDestination(){
		return mDestinationNode;
	}
	
	public Vector<String> finishedProducts(){
		return completedProducts;
	}
	
	public Vector<Integer> finishedNumbers(){
		return completedNumbers;
	}
}
