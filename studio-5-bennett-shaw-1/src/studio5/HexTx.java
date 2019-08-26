package studio5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

//import com.sun.java_cup.internal.runtime.Scanner;

import jssc.SerialPortException;



public class HexTx {
	static char firstLetter;
	public static void main(String[] args) {		
		// TODO:  Fix this: 
		//           a) Uncomment to create a SerialComm object
		//           b) Update the "the port" to refer to the serial port you're using
		//              (The port listed in the Arduino IDE Tools>Port menu.		
		//           c) Deal with the unresolved issue
		try {
			SerialComm port = new SerialComm("COM4");
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		BufferedReader sys = new BufferedReader(new InputStreamReader(System.in));
		try {
			System.out.print((sys).read());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		try {	
			int a;

			a = sys.read();

			if (a > 47 && a < 58) {
				a = a-48;
			}
			else if (a > 96 && a < 103)
				a = a-87;


		} 
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}




	//		InputStream s = System.in;
	//		firstLetter = String.valueOf((System.in.charAt(0));

	// TODO: Complete section 6 of the Studio (gather sanitized user input
	//       and send it to the Arduino)
}


