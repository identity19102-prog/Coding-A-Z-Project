package JunkSerialGenerate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Random;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;

public class JunkSerialGenerate {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while(true) {
			try {
				LocalDateTime now = LocalDateTime.now();
				DateTimeFormatter format = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
				
				System.out.println("================================");
				System.out.println("====== J.S.G System v1.00 ======");
				System.out.println("================================");
				//J.S.G : Junk Serial Generate
				System.out.println("Current Time: " + now.format(format));
				System.out.print("Input Sirial Numbers: ");
				int number = sc.nextInt();
				System.out.print("Input Padding Size: ");
				int padding = sc.nextInt();
				System.out.print("Input Serial Count: ");
				int serialCount = sc.nextInt();		
				System.out.print("Input Random Outout Seed: ");
				int seed = sc.nextInt();					
				System.out.print("Output BPM: ");
				int BPM = sc.nextInt();
				
				SerialExecutor se = new SerialExecutor();
                se.ExecuteGenerator(number, padding, serialCount, seed, BPM, sc);
				
			} catch (Exception e) {
				System.out.println("Invalid Input. Try again.");
                sc.nextLine();
			}
		}
	}
}

class SerialExecutor{
	void ExecuteGenerator(int number, int padding, int serialCount, int seed, int BPM, Scanner sc) {
		String chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        Random random = new Random(seed);
        long Delay = (long) ((60.0 / BPM) * 1000);
        
        String fileName = "serial_log_" + 
        LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss"))+".txt";
        
        try(FileWriter writer = new FileWriter(fileName)) {
        	System.out.println("\nGenerating " + serialCount + " Garbage Serials...\n");
        	writer.write("=== Junk Serial Generate Log ===\n");
        	writer.write("Seed: " + seed + ", BPM: " + BPM + "\n\n");
        	
        	for (int s = 1; s <= serialCount; s++) {
        		StringBuilder serial = new StringBuilder();
        		
        		for(int i = 0; i < number; i++) {
        			char c = chars.charAt(random.nextInt(chars.length()));
        			
        			if (Character.isUpperCase(c)) {
        			    c = (char)(((c - 'A' + 3) % 26) + 'A');
        			}
        			else if (Character.isDigit(c)) {
        			    c = (char)(((c - '0' + 3) % 10) + '0');
        			}
        			
        			serial.append(c);
        			
        			if((i + 1) % padding == 0 && (i + 1) != number) {
        				serial.append("-");
        			}
        		}
        		
        		String line = "Serial #" + s + ": " + serial;
        		System.out.println(line);
        		writer.write(line + "\n");
        		
        		Thread.sleep(Delay);
        	}
        	
        	 System.out.println("\nAll garbage serials generated successfully.");
             writer.write("\nAll garbage serials generated successfully.\n");
             
             double Elapsed_time = (double) (serialCount * Delay) / 1000;
             System.out.printf("\nElapsed time: %.3f Secs.", Elapsed_time);
             System.out.printf(" (%.0f ms)\n", (Elapsed_time * 1000));
             writer.write(String.format("\nElapsed time: %.3f Secs. (%.0f ms)\n", Elapsed_time, (Elapsed_time * 1000)));
        	
             writer.flush();
             System.out.println("Serials have been saved to file: " + fileName);
             
             System.out.print("Terminate This Program? (exit): ");
             String answer = sc.next();
             
             if (answer.equalsIgnoreCase("exit")) {
                 System.out.println("Program is Terminated.");
                 sc.close();
                 System.exit(0);
             }
        } catch (InterruptedException e) {
            System.out.println("Generation Interrupted!");
        } catch (IOException e) {
            System.out.println("File write error: " + e.getMessage());
        }
	}
}



