// TimeUtils.java
package UniversalTimeIndicator;

import java.awt.*;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;

public class TimeUtils {
    public static final DateTimeFormatter timeFormatter = DateTimeFormatter.ofPattern("YYYY-MM-dd HH:mm:ss");

    public static Color getSmoothGradientColor(int hour) {
        // hour: 0~23
        double t = hour / 24.0; // 0~1
        double sine = Math.sin(2 * Math.PI * (t - 0.25)); // -0.25로 6시에 최대 밝기 맞춤

        int r, g, b;

        if (sine >= 0) { // 낮
            r = 255;
            g = (int) (128 + 127 * sine); // 128~255
            b = 0;
        } else { // 밤
            r = 0;
            g = 128;
            b = (int) (128 + 127 * (-sine)); // 128~255
        }

        return new Color(r, g, b);
    }

    public static String formatTime(ZonedDateTime time) {
        return time.format(timeFormatter);
    }
}
