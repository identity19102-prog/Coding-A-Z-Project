package THREADTRACKERGAME;
import java.awt.*;
import java.util.Random;

public class THREADTRACKERCHASER implements Runnable {

    // ====== 모든 추적자가 공유하는 "좌표 점유 테이블" ======
    private static boolean[][] occupied = new boolean[THREADTRACKERGAMEPANEL.gridWidth][THREADTRACKERGAMEPANEL.gridHeight];  

    private int x, y;
    private THREADTRACKERPLAYER player;
    private THREADTRACKERMAP map;
    private Random rand = new Random();
    private Color color = Color.RED;
    private THREADTRACKERGAMEPANEL.Difficulty difficulty;

    public THREADTRACKERCHASER(int x, int y, THREADTRACKERPLAYER player, THREADTRACKERMAP map,
                               THREADTRACKERGAMEPANEL.Difficulty difficulty) {
        this.x = x;
        this.y = y;
        this.player = player;
        this.map = map;
        this.difficulty = difficulty;

        occupied[x][y] = true;
    }

    @Override
    public void run() {

        int delay;
        switch (difficulty) {
            case EASY:   delay = 280; break;
            case NORMAL: delay = 160; break;
            case HARD:   delay = 90;  break;
            default:     delay = 180; break;
        }

        while (true) {
            moveTowardPlayerOneStep();
            randomColor();

            try { Thread.sleep(delay); } catch (InterruptedException e) {}
        }
    }


    // ====== 한 칸 이동 + 충돌 방지 ======
    private void moveTowardPlayerOneStep() {
        int px = player.getX();
        int py = player.getY();

        int dx = Integer.compare(px, x); // -1, 0, 1
        int dy = Integer.compare(py, y); // -1, 0, 1

        // --- X 방향 이동 체크
        attemptMove(dx, 0);

        // --- Y 방향 이동 체크
        attemptMove(0, dy);
    }


    // ====== 이동 시도 (벽, 충돌 검사 모두 처리) ======
    private void attemptMove(int dx, int dy) {
        if (dx == 0 && dy == 0) return;

        int nx = x + dx;
        int ny = y + dy;

        // 1) 벽(#)이면 이동 불가
        if (map.getCell(nx, ny) == '#') return;

        // 2) 다른 추적자가 점유 중이면 이동 불가
        synchronized (occupied) {
            if (occupied[nx][ny]) return;

            // 이동 가능 → 점유 이동 처리
            occupied[x][y] = false;
            occupied[nx][ny] = true;
        }

        // 실제 좌표 이동
        x = nx;
        y = ny;
    }


    private void randomColor() {
        color = new Color(rand.nextInt(256), rand.nextInt(256), rand.nextInt(256));
    }

    public Color getColor() { return color; }
    public int getX() { return x; }
    public int getY() { return y; }
}
