package client;

import decode.Decoder;

public class DecoderThread extends Thread{

	private String mString;
	private FactoryWorkerCommunicator fwc;
	
	public DecoderThread(String message, FactoryWorkerCommunicator f) {
		mString = message;
		fwc = f;
	}
	
	public void run(){
		String decoded = Decoder.resolve(mString);
		fwc.receiveDecodedMessag(decoded);
	}
}
