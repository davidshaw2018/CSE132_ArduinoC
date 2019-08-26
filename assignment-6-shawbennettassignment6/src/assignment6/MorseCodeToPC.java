package assignment6;

import java.io.IOException;


import jssc.SerialPortException;

public class MorseCodeToPC {
	public static void main(String[] args) throws SerialPortException, IOException {		
		// TODO:  Complete program to show "training messages" and decoded Morse code
		SerialComm port = new SerialComm("/dev/cu.usbserial-DN02B5Z2");
		port.setDebug(true);
		
		while (true) {
			while (port.available()) {
				char printout = (char)(port.readByte());
				if (printout != '#') {
					System.out.print(printout);
				}
				
			}
		}
		
	}

}
