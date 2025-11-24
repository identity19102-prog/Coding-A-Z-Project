package THREADTRACKERGAME;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Random;

public class THREADTRACKERGAMEPANEL extends JPanel implements KeyListener {
    // --- Constants ---
	public static final int gridWidth = 32;
	public static final int gridHeight = 32;
    private final int cellSize = 30;
    private final int maxLevel = 9;

    // --- Game State ---
    private int currentLevel = 0;
    private int levelTime = 15;
    private int elapsedTime = 0;
    private int score = 0;

    private enum GameState { READY, PLAYING, GAMEOVER, WIN }
    private GameState state = GameState.READY;

    public enum Difficulty { EASY, NORMAL, HARD }
    public Difficulty difficulty = Difficulty.NORMAL;

    // --- Objects ---
    private THREADTRACKERPLAYER player;
    private ArrayList<THREADTRACKERCHASER> chasers = new ArrayList<>();
    private THREADTRACKERMAP map;

    private Timer timer;
    private boolean moveLeft, moveRight, moveUp, moveDown;
    private Font gameFont = new Font("PxPlus Rainbow100 re.66", Font.PLAIN, 32);

    private Random rand = new Random();

    public THREADTRACKERGAMEPANEL() {
        setPreferredSize(new Dimension(gridWidth * cellSize, gridHeight * cellSize + 40));
        setBackground(Color.BLACK);
        setFocusable(true);
        addKeyListener(this);

        setupLevel(currentLevel, true);

        // Player movement updater
        new Thread(() -> {
            while (true) {
                if (state == GameState.PLAYING) {
                    boolean moved = player.move(moveLeft, moveRight, moveUp, moveDown, map);
                    if (moved) score++;
                    checkCollision();
                    repaint();
                }
                try { Thread.sleep(100); } catch (InterruptedException e) {}
            }
        }).start();
    }

    private void setupLevel(int level, boolean resetScore) {
        elapsedTime = 0;
        levelTime = 5 + level * 1;
        if (resetScore) score = 0;

        map = new THREADTRACKERMAP(gridWidth, gridHeight, 0.05);

        player = new THREADTRACKERPLAYER(gridWidth / 2, gridHeight / 2);

        chasers.clear();
        int chaserCount = 4 + level;
        for (int i = 0; i < chaserCount; i++) {
            int cx, cy;
            int corner = i % 4;
            switch (corner) {
                case 0: cx = 0; cy = 0; break;
                case 1: cx = gridWidth - 1; cy = 0; break;
                case 2: cx = 0; cy = gridHeight - 1; break;
                default: cx = gridWidth - 1; cy = gridHeight - 1; break;
            }
            chasers.add(new THREADTRACKERCHASER(cx, cy, player, map, difficulty));
        }

        // Timer
        if (timer != null) timer.stop();
        timer = new Timer(1000, e -> {
            elapsedTime++;
            if (elapsedTime > levelTime) nextLevel();
            repaint();
        });
    }

    private void nextLevel() {
        timer.stop();
        if (currentLevel < maxLevel) {
            currentLevel++;
            setupLevel(currentLevel, false); //scoring
            state = GameState.PLAYING;
            for (THREADTRACKERCHASER c : chasers) new Thread(c).start();
            timer.start();
        } else {
            state = GameState.WIN;
        }
        repaint();
    }

    private void checkCollision() {
        for (THREADTRACKERCHASER c : chasers) {
            if (player.getX() == c.getX() && player.getY() == c.getY()) {
                state = GameState.GAMEOVER;
                timer.stop();
            }
        }
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setFont(gameFont);

        // Top HUD
        g.setColor(Color.WHITE);
        g.drawString("" + score, 40, 20);
        g.setColor(Color.CYAN);
        g.drawString("" + currentLevel, getWidth()/2, 20);
        g.setColor(Color.WHITE);
        g.drawString("" + (levelTime - elapsedTime), getWidth() - 120, 20);

        switch (state) {
            case READY:
                drawCenteredString(g, "SELECT DIFFICULTY", getWidth(), getHeight(), Color.WHITE);
                drawCenteredString(g, "E : EASY", getWidth(), getHeight() + 120, Color.GREEN);
                drawCenteredString(g, "N : NORMAL", getWidth(), getHeight() + 200, Color.YELLOW);
                drawCenteredString(g, "H : HARD", getWidth(), getHeight() + 280, Color.RED);
                break;
            case GAMEOVER:
            	THREADTRACKERLOG.write(score, currentLevel, difficulty.name(), false);
                drawCenteredString(g, "GAME OVER!", getWidth(), getHeight() - 20, Color.RED);
                drawCenteredString(g, "FINAL SCORE: " + score, getWidth(), getHeight() + 40, Color.YELLOW);
                drawCenteredString(g, "PRESS ANY KEY TO RETRY", getWidth(), getHeight() + 120, Color.CYAN);
                break;
            case WIN:
            	THREADTRACKERLOG.write(score, currentLevel, difficulty.name(), true);
                drawCenteredString(g, "YOU WIN! MAX LEVEL REACHED", getWidth(), getHeight() - 20, Color.GREEN);
                drawCenteredString(g, "FINAL SCORE: " + score, getWidth(), getHeight() + 40, Color.YELLOW);
                drawCenteredString(g, "PRESS ANY KEY TO RESTART", getWidth(), getHeight() + 120, Color.CYAN);
                break;
            case PLAYING:
                // Map
                for (int y = 0; y < gridHeight; y++) {
                    for (int x = 0; x < gridWidth; x++) {
                        char c = map.getCell(x, y);
                        g.setColor(c == '#' ? Color.GRAY : Color.WHITE);
                        g.drawString(String.valueOf(c), x * cellSize, (y + 1) * cellSize);
                    }
                }

                // Chasers
                for (THREADTRACKERCHASER c : chasers) {
                    g.setColor(c.getColor());
                    g.drawString("☻", c.getX() * cellSize, (c.getY() + 1) * cellSize);
                }

                // Player
                g.setColor(Color.RED);
                g.drawString("♥", player.getX() * cellSize, (player.getY() + 1) * cellSize); //☺

                // Coordinates
                g.setColor(Color.YELLOW);
                g.drawString("" + player.getX() + "," + player.getY() + "", 10, gridHeight * cellSize + 25);
                
                if(difficulty == Difficulty.EASY) {g.setColor(Color.GREEN);g.drawString(""+difficulty,600, gridHeight * cellSize + 25);}
                if(difficulty == Difficulty.NORMAL) {g.setColor(Color.YELLOW);g.drawString(""+difficulty,600, gridHeight * cellSize + 25);}
                if(difficulty == Difficulty.HARD) {g.setColor(Color.RED);g.drawString(""+difficulty,600, gridHeight * cellSize + 25);}
                break;
        }
    }

    private void drawCenteredString(Graphics g, String text, int width, int height) {
        drawCenteredString(g, text, width, height, Color.CYAN);
    }

    private void drawCenteredString(Graphics g, String text, int width, int height, Color color) {
        FontMetrics fm = g.getFontMetrics();
        int x = (width - fm.stringWidth(text)) / 2;
        int y = height / 2;
        g.setColor(color);
        g.drawString(text, x, y);
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();

        if (state == GameState.READY) {
            if (key == KeyEvent.VK_E) difficulty = Difficulty.EASY; //VK: KEY VALUE
            if (key == KeyEvent.VK_N) difficulty = Difficulty.NORMAL;
            if (key == KeyEvent.VK_H) difficulty = Difficulty.HARD;

            state = GameState.PLAYING;
            timer.start();
            for (THREADTRACKERCHASER c : chasers) new Thread(c).start();
            return;
        }

        if (state == GameState.GAMEOVER || state == GameState.WIN) {
            currentLevel = 0;
            setupLevel(currentLevel, true);
            state = GameState.READY;
            repaint();
            return;
        }

        if (key == KeyEvent.VK_LEFT) moveLeft = true;
        if (key == KeyEvent.VK_RIGHT) moveRight = true;
        if (key == KeyEvent.VK_UP) moveUp = true;
        if (key == KeyEvent.VK_DOWN) moveDown = true;
    }

    @Override
    public void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT) moveLeft = false;
        if (key == KeyEvent.VK_RIGHT) moveRight = false;
        if (key == KeyEvent.VK_UP) moveUp = false;
        if (key == KeyEvent.VK_DOWN) moveDown = false;
    }

    @Override public void keyTyped(KeyEvent e) {}
}
