// UniversalTimeIndicator.java
package UniversalTimeIndicator;

import javax.swing.*;
import java.awt.*;
import java.time.ZoneId;
import java.time.ZonedDateTime;

public class UniversalTimeIndicator extends JFrame {

    private JLabel seoulLabel = new JLabel();
    private JLabel foreignLabel = new JLabel();
    private JComboBox<String> cityComboBox;
    private CityData cityData = new CityData();

    public UniversalTimeIndicator() {
        setTitle("Universal Time Indicator");
        setSize(600, 200);
        setLocation(200, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(3, 1));
        setResizable(false);
        setVisible(true);
        setAlwaysOnTop(true); 

        seoulLabel.setFont(new Font("Arial", Font.BOLD, 24));
        seoulLabel.setHorizontalAlignment(SwingConstants.LEFT);
        seoulLabel.setOpaque(true);
        seoulLabel.setBackground(Color.BLACK);
        add(seoulLabel);

        foreignLabel.setFont(new Font("Arial", Font.BOLD, 24));
        foreignLabel.setHorizontalAlignment(SwingConstants.LEFT);
        foreignLabel.setOpaque(true);
        foreignLabel.setBackground(Color.BLACK);
        add(foreignLabel);

        cityComboBox = new JComboBox<>(cityData.getCities().keySet().toArray(new String[0]));
        cityComboBox.setFont(new Font("Arial", Font.PLAIN, 18));
        add(cityComboBox);

        Timer timer = new Timer(1000, e -> updateTimes());
        timer.start();

        setVisible(true);
    }

    private void updateTimes() {
        ZonedDateTime seoulTime = ZonedDateTime.now(ZoneId.of("Asia/Seoul"));
        seoulLabel.setText("South Korea / Seoul: " + TimeUtils.formatTime(seoulTime));
        seoulLabel.setForeground(TimeUtils.getSmoothGradientColor(seoulTime.getHour()));

        String selectedCity = (String) cityComboBox.getSelectedItem();
        if (selectedCity != null) {
            ZonedDateTime foreignTime = ZonedDateTime.now(ZoneId.of(cityData.getCities().get(selectedCity)));
            foreignLabel.setText(selectedCity + ": " + TimeUtils.formatTime(foreignTime));
            foreignLabel.setForeground(TimeUtils.getSmoothGradientColor(foreignTime.getHour()));
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(UniversalTimeIndicator::new);
    }
}
