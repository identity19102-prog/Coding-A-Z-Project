package THREADTRACKERGAME;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class THREADTRACKERLOG {

    private static final String FILE = "log.txt";
    private static final DateTimeFormatter F = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    public static synchronized void write(int score, int level, String difficulty, boolean win) {
        try (FileWriter fw = new FileWriter(FILE, true)) {
            String time = LocalDateTime.now().format(F);

            fw.write("[" + time + "] ");
            fw.write("Result=" + (win ? "WIN" : "GAME OVER"));
            fw.write(", Score=" + score);
            fw.write(", Level=" + level);
            fw.write(", Difficulty=" + difficulty);
            fw.write("\n");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
