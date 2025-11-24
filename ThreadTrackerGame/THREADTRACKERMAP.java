package THREADTRACKERGAME;
import java.util.Random;

public class THREADTRACKERMAP {
    private int width, height;
    private char[][] cells;

    public THREADTRACKERMAP(int width, int height, double obstacleRate) {
        this.width = width;
        this.height = height;
        cells = new char[height][width];

        Random rand = new Random();

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cells[y][x] = ' ';
            }
        }

        int total = (int)(width * height * obstacleRate);
        for (int i = 0; i < total; i++) {
            int ox, oy;
            do {
                ox = rand.nextInt(width);
                oy = rand.nextInt(height);
            } while (cells[oy][ox] != ' ');
            cells[oy][ox] = '#';
        }
    }

    public char getCell(int x, int y) { return cells[y][x]; }
    public int getWidth() { return width; }
    public int getHeight() { return height; }
}

