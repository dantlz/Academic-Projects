package tianlinz_CS201L_inClassPractice;

public class TestThreads {

	public static void main(String[] args) {
		for(int i = 1 ; i <= 100; i ++){
			MyThread mThread = new MyThread(i);
			mThread.start();
		}
	}

}


//When debugging multi threaded code, use 
//System.out.println("Thread "+ num + ": ##"); 
//to see what executes

class MyThread extends Thread {
	private int num;
	
	public MyThread(int num){
		this.num = num;
	}
	public void run(){
		System.out.println("Thread "+ num + " started");
		System.out.println("Thread "+ num + " ended");

	}
}