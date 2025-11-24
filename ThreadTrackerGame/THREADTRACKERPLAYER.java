package THREADTRACKERGAME;

public class THREADTRACKERPLAYER {
    private int x, y;

    public THREADTRACKERPLAYER(int x, int y) {
        this.x = x; this.y = y;
    }

    public boolean move(boolean left, boolean right, boolean up, boolean down, THREADTRACKERMAP map) {
        int nextX = x;
        int nextY = y;
        
        if (left) nextX--;
        if (right) nextX++;
        if (up) nextY--;
        if (down) nextY++;

        if (nextX >= 0 && nextX < map.getWidth() &&
                nextY >= 0 && nextY < map.getHeight() &&
                map.getCell(nextX, nextY) != '#') {

                // Only update if position changed
                if (nextX != x || nextY != y) {
                    x = nextX;
                    y = nextY;
                    return true; // actually moved
                }
            }
        return false; // didn't move
    }

    public int getX() { return x; }
    public int getY() { return y; }
}

