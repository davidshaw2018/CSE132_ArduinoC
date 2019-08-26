import jssc.SerialPortException;

public class PCPlayer {

	public static void main(String[] args) throws SerialPortException {
		//
		SerialComm comm = new SerialComm("/dev/cu.usbserial-DN02B5Z2");
		comm.setDebug(true);
		int press_time = 600;
		long last_time = 0;

		while(true) {
			// store time in variable
			long time = System.currentTimeMillis();
			// booleans describing which key is pressed
			boolean left = StdDraw.isKeyPressed(37);
			boolean up = StdDraw.isKeyPressed(38);
			boolean right = StdDraw.isKeyPressed(39);
			boolean down = StdDraw.isKeyPressed(40);
			//delta timing if statement
			if (time > last_time + press_time) {
				
				if (left) {
					comm.writeByte((byte)1);
				}
				if (up) {
					comm.writeByte((byte)2);
				}
				if (right) {
					comm.writeByte((byte)3);
				}
				if (down) {
					comm.writeByte((byte)4);
				}
				last_time = time;
				
			}
		}
		
		



	}

}

