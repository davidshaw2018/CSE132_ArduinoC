package studio6;

import jssc.*;

public class SerialComm {

	SerialPort port;

	private boolean debug;  // Indicator of "debugging mode"
	
	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}	
	

	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);		
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
			SerialPort.DATABITS_8,
			SerialPort.STOPBITS_1,
			SerialPort.PARITY_NONE);
		
		debug = false; // Default is to NOT be in debug mode
	}
		
	// TODO: Add writeByte() method from Studio 5
	public void writeByte(byte singleByte) {
		try {
			port.writeByte(singleByte);
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if (debug) {
			System.out.println(singleByte);
		}
		
	}
	
	// TODO: Add available() method
	public boolean available() {
		int bytes = 0;
		try {
			bytes = port.getInputBufferBytesCount();
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if (bytes > 0) {
			return true;
		} else {
			return false;
		}
	}
		
	
	
	// TODO: Add readByte() method	
	public byte readByte() {
		byte[] byteArray = null;
		try {
			byteArray = port.readBytes();
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if (debug) {
			System.out.println(String.format("%02x", byteArray[0]));
		}
		return byteArray[0];
	}
	
	// TODO: Add a main() method
	public static void main(String[] args) {
		try {
			SerialComm newByte = new SerialComm("COM3");
			newByte.setDebug(true);
			while (true) {
				if (newByte.available()) {
					byte Result = newByte.readByte();
					System.out.println(Result);
				}
			}
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
