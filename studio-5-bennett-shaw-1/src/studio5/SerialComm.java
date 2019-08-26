package studio5;

import jssc.*;

public class SerialComm {

	SerialPort port;

	private boolean debug;// Indicator of "debugging mode"
	
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
		
	// TODO: Add writeByte() method to write data to serial port
	public void writeByte(byte singleByte) {
		try {
			port.writeByte(singleByte);
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if (debug) {
			System.out.println("0x" + Integer.toHexString(singleByte));
		}
		
	}
	
}
