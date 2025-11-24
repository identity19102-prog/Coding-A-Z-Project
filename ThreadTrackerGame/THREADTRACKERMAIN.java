package THREADTRACKERGAME;
import javax.swing.*;

public class THREADTRACKERMAIN {
    public static void main(String[] args) {
    	JFrame frame = new JFrame("Thread Tracker Game");
        THREADTRACKERGAMEPANEL gamePanel = new THREADTRACKERGAMEPANEL();
        frame.setLocation(660, 0);
        frame.add(gamePanel);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        
        gamePanel.requestFocus();
    }
}