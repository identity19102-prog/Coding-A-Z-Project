package LottoPridictProgram;
import java.awt.*;          
import java.awt.event.*;    
import java.util.*;         

public class LottoPridictProgram extends Frame implements ActionListener {

    TextField[][] last7WeeksFields = new TextField[7][7]; 
    TextField[][] lottoFields = new TextField[5][6];      // 5게임 × 6번호
    TextArea hotColdArea;                                 
    Button btnGenerate;
    Random rand = new Random();

    // === 7주차 번호 미리 선언 (IDE에서 수정 가능) ===
    int[][] last7Nums = {
        {3, 4, 12, 19, 22, 27, 9},	//1188회차
        {9, 19, 29, 35, 37, 38, 31},	//1189회차
        {7, 9, 19, 23, 26, 45, 33},	//1190회차
        {1, 4, 11, 12, 20, 41, 2},//1191회차
        {10, 16, 23, 36, 39, 40, 11},	//1192회차
        {6, 9, 16, 19, 24, 28, 17},	//1193회차
        {3, 13, 15, 24, 33, 37, 2} //1194회차
    };

    public LottoPridictProgram() {
        super("로또 번호 생성기 🎰");
        this.setLocation(500, 100);

        setLayout(new BorderLayout());

        // === 상단: 최근 7주차 번호 TextField + 보너스번호 표시 ===
        Panel northPanel = new Panel(new GridLayout(7, 1, 5, 5));
        Font bigFont = new Font("Arial", Font.BOLD, 30);
        Font smallFont = new Font("Arial", Font.BOLD, 25);
        for (int i = 0; i < 7; i++) {
            Panel weekPanel = new Panel(new FlowLayout(FlowLayout.LEFT));
            weekPanel.add(new Label("📅 " + (i + 1188) + "회차 번호: "));
            weekPanel.setFont(smallFont);
            last7WeeksFields[i] = new TextField[7];
            // 6개 연속 번호
            for (int j = 0; j < 6; j++) {
                last7WeeksFields[i][j] = new TextField(2);
                last7WeeksFields[i][j].setFont(bigFont);
                last7WeeksFields[i][j].setText(String.valueOf(last7Nums[i][j]));
                weekPanel.add(last7WeeksFields[i][j]);
            }
            // "+" 라벨
            Label plusLabel = new Label("+");
            plusLabel.setFont(bigFont);
            weekPanel.add(plusLabel);
            // 7번째 번호(보너스)
            last7WeeksFields[i][6] = new TextField(2);
            last7WeeksFields[i][6].setFont(bigFont);
            last7WeeksFields[i][6].setText(String.valueOf(last7Nums[i][6]));
            weekPanel.add(last7WeeksFields[i][6]);

            northPanel.add(weekPanel);
        }
        add(northPanel, BorderLayout.NORTH);

        // === 중앙: 로또 5게임 출력 영역 ===
        Panel centerPanel = new Panel(new GridLayout(5, 7, 5, 5)); // 5줄, 6번호 + 라벨
        for (int i = 0; i < 5; i++) {
            Label lbl = new Label("  "+ (char) (i + 'A')+"  수동  ");
            lbl.setFont(smallFont);
            centerPanel.add(lbl);
            for (int j = 0; j < 6; j++) {
                lottoFields[i][j] = new TextField(3);
                lottoFields[i][j].setFont(smallFont);
                lottoFields[i][j].setEditable(false);
                centerPanel.add(lottoFields[i][j]);
            }
        }
        add(centerPanel, BorderLayout.CENTER);

        // === 하단: 핫/콜드 + 버튼 ===
        Panel southPanel = new Panel(new BorderLayout());
        hotColdArea = new TextArea(2, 30);                 
        hotColdArea.setFont(new Font("Arial", Font.BOLD, 24)); 
        hotColdArea.setEditable(false);
        southPanel.add(hotColdArea, BorderLayout.CENTER);

        btnGenerate = new Button("번호 뽑기!");
        btnGenerate.setFont(bigFont);
        btnGenerate.addActionListener(this);
        southPanel.add(btnGenerate, BorderLayout.SOUTH);

        add(southPanel, BorderLayout.SOUTH);

        // === 프레임 설정 ===
        setSize(800, 900);
        setVisible(true);

        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // 1. TextField에서 번호 읽어오기
        try {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 7; j++) {
                    int num = Integer.parseInt(last7WeeksFields[i][j].getText());
                    if (num < 1 || num > 45) throw new NumberFormatException();
                    last7Nums[i][j] = num; 
                }
            }
        } catch (NumberFormatException ex) {
            showError("1~45 사이 숫자만 입력하세요!");
            return;
        }

        // 2. 등장 횟수 카운트
        Map<Integer,Integer> countMap = new HashMap<>();
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                int num = last7Nums[i][j];
                countMap.put(num, countMap.getOrDefault(num, 0) + 1);
            }
        }

        // 3. 핫/콜드 번호 구하기
        java.util.List<Map.Entry<Integer,Integer>> sortedList = new java.util.ArrayList<>(countMap.entrySet());
        sortedList.sort(new Comparator<Map.Entry<Integer,Integer>>() {
            public int compare(Map.Entry<Integer,Integer> o1, Map.Entry<Integer,Integer> o2) {
                return o2.getValue() - o1.getValue(); // 내림차순
            }
        });
        java.util.List<Integer> hotNumbers = new java.util.ArrayList<>();
        java.util.List<Integer> coldNumbers = new java.util.ArrayList<>();
        for (int i = 0; i < 5 && i < sortedList.size(); i++) hotNumbers.add(sortedList.get(i).getKey());

        sortedList.sort(new Comparator<Map.Entry<Integer,Integer>>() {
            public int compare(Map.Entry<Integer,Integer> o1, Map.Entry<Integer,Integer> o2) {
                return o1.getValue() - o2.getValue(); // 오름차순
            }
        });
        for (int i = 0; i < 5 && i < sortedList.size(); i++) coldNumbers.add(sortedList.get(i).getKey());

        hotColdArea.setText("🔥 핫넘버: " + hotNumbers + "   ❄️ 콜드넘버: " + coldNumbers);

        // 4. 5게임 추천 생성 (핫넘버 우선 반영)
        for (int i = 0; i < 5; i++) {
            Set<Integer> lotto = new TreeSet<>();
            java.util.List<Integer> oddPool = new ArrayList<>();
            java.util.List<Integer> evenPool = new ArrayList<>();

            // hotNumbers 기준으로 홀수/짝수 나누기
            for (int n : hotNumbers) {
                if (n % 2 == 0) evenPool.add(n);
                else oddPool.add(n);
            }

            Random rand = new Random();

            // 부족한 숫자 채우기 (1~45 중에서)
            for (int n = 1; n <= 45; n++) {
                if (!hotNumbers.contains(n)) {
                    if (n % 2 == 0) evenPool.add(n);
                    else oddPool.add(n);
                }
            }

            // 홀수 4개 랜덤 선택
            while (lotto.size() < 4) {
                int num = oddPool.get(rand.nextInt(oddPool.size()));
                lotto.add(num);
            }

            // 짝수 2개 랜덤 선택
            while (lotto.size() < 6) {
                int num = evenPool.get(rand.nextInt(evenPool.size()));
                lotto.add(num);
            }

            // 결과를 TextField에 출력
            int j = 0;
            for (Integer num : lotto) lottoFields[i][j++].setText(String.valueOf(num));
        }
    }

    private void showError(String msg) {
        Dialog dlg = new Dialog(this, "Error", true);
        dlg.setLayout(new FlowLayout());
        dlg.add(new Label(msg));
        Button ok = new Button("OK");
        ok.setFont(new Font("Arial", Font.BOLD, 20));
        ok.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) { dlg.dispose(); }
        });
        dlg.add(ok);
        dlg.setSize(300, 100);
        dlg.setVisible(true);
    }

    public static void main(String[] args) {
        new LottoPridictProgram();
    }
}
