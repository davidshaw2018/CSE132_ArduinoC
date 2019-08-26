package studio8;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


// TODO: Develop an algorithm to count steps in accelerometer data
//    Major steeps:
//       1. Create a class and main method.
//       2. Using a Scanner and File object, read data from your .csv file.
//       3. Develop and test algorithms to count the "peaks" in the data.

public class CountSteps {
	
	
	
	public static void main(String[] args) throws FileNotFoundException {
		Scanner sc = new Scanner(new File("stud8stepsdata.csv"));
		double[][] vectorParts = new double[284][3];
		int xPeak  = 0;
		int yPeak = 0;
		int zPeak = 0;
		for (int i = 1; i < 283; ++i) {
			String vector = sc.nextLine();
			String[] toCast = vector.split(",");
			for (int j = 0; j < 3; ++j) {
				vectorParts[i][j] = Double.parseDouble(toCast[j]);
				if (vectorParts[i][j] > vectorParts[i-1][j] &&
						vectorParts[i][j] > vectorParts[i+1][j]) {
					if (j == 0) {
						xPeak += 1;
					}
					if (j == 1) {
						yPeak += 1;
					}
					if (j == 2) {
						zPeak += 1;
					}
				}
			}
			
		}
		sc.close();
		System.out.println("X Steps: " + xPeak);
		System.out.println("Y Steps: " + yPeak);
		System.out.println("Z Steps: " + zPeak);
	}
	
}