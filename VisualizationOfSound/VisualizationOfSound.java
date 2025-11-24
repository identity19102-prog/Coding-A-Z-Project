package VisualizationOfSound;

import javax.sound.sampled.*;
import javax.swing.*;
import java.awt.*;

public class VisualizationOfSound extends JFrame {

    private AudioPanel audioPanel;

    public VisualizationOfSound() {
        setTitle("PC Sound dB Meter v0.00");
        setLocation(660, 100);
        setSize(600, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        audioPanel = new AudioPanel();
        add(audioPanel, BorderLayout.CENTER);

        setVisible(true);

        new Thread(this::captureAudio).start();
    }

    private void captureAudio() {
        try {
            AudioFormat format = new AudioFormat(44100.0f, 16, 2, true, false);
            DataLine.Info info = new DataLine.Info(TargetDataLine.class, format);
            TargetDataLine line = null;

            Mixer.Info[] mixers = AudioSystem.getMixerInfo();
            for (Mixer.Info mixerInfo : mixers) {
                Mixer mixer = AudioSystem.getMixer(mixerInfo);
                if (mixer.isLineSupported(info)) {
                    line = (TargetDataLine) mixer.getLine(info);
                    //System.out.println("Using mixer: " + mixerInfo.getName());
                    break;
                }
            }

            if (line == null) {
                System.err.println("No suitable line found. Make sure Stereo Mix is enabled.");
                return;
            }

            line.open(format);
            line.start();

            byte[] buffer = new byte[4096];

            while (true) {
                int bytesRead = line.read(buffer, 0, buffer.length);
                double sum = 0.0;
                for (int i = 0; i < bytesRead; i += 2) {
                    int sample = (buffer[i + 1] << 8) | (buffer[i] & 0xFF);
                    sum += sample * sample;
                }
                double rms = Math.sqrt(sum / (bytesRead / 2));
                double dbValue = 20 * Math.log10(rms / 32768.0);
                if (dbValue < -60) dbValue = -60;

                final double finalDb = dbValue;
                SwingUtilities.invokeLater(() -> audioPanel.setDb(finalDb));

                Thread.sleep(16); // 60fps
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    class AudioPanel extends JPanel {
        private double db = -60;
        private double displayedDb = -60; // 잔상용 표시 값
        private final Color[] spectrum = {
                new Color(128, 0, 128), // 보라
                Color.BLUE,             // 파랑
                Color.CYAN,
                Color.GREEN,            // 녹색
                Color.YELLOW,           // 주황
                Color.RED               // 빨강
        };

        public void setDb(double db) {
            this.db = db;
            // 부드러운 증가
            if (db > displayedDb) {
                displayedDb = db;
            } 
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            int width = getWidth();
            int height = getHeight();

            g.setColor(Color.BLACK);
            g.fillRect(0, 0, width, height);

            // 부드러운 감소
            if (displayedDb > db) {
                displayedDb -= 1; // 감소 속도 조절
                if (displayedDb < db) displayedDb = db;
                repaint(); // 잔상 애니메이션
            }

            double normalized = (displayedDb + 60) / 60.0;
            int totalPixels = 50;
            int activePixels = (int) (normalized * totalPixels);
            int pixelWidth = width / totalPixels - 2;
            int pixelHeight = height - 40;

            for (int i = 0; i < totalPixels; i++) {
                double ratio = (i + 1.0) / totalPixels * (spectrum.length - 1);
                int idx = (int) ratio;
                double t = ratio - idx;
                Color c1 = spectrum[idx];
                Color c2 = spectrum[Math.min(idx + 1, spectrum.length - 1)];
                int r = (int) (c1.getRed() + t * (c2.getRed() - c1.getRed()));
                int gr = (int) (c1.getGreen() + t * (c2.getGreen() - c1.getGreen()));
                int b = (int) (c1.getBlue() + t * (c2.getBlue() - c1.getBlue()));
                Color pixelColor = new Color(r, gr, b);

                if (i < activePixels) {
                    g.setColor(pixelColor);
                } else {
                    g.setColor(Color.DARK_GRAY);
                }

                g.fillRect(i * (pixelWidth + 2) + 10, 20, pixelWidth, pixelHeight);
            }

            g.setColor(Color.WHITE);
            g.setFont(new Font("PxPlus Rainbow100 re.66", Font.BOLD, 18));
            g.drawString(String.format("%.1f dB", displayedDb), 10, height - 10);
        }
    }

    public static void main(String[] args) {
        new VisualizationOfSound();
    }
}
