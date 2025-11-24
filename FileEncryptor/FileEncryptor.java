package FileEncryptor;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.security.SecureRandom;
import javax.crypto.*;
import javax.crypto.spec.SecretKeySpec;

public class FileEncryptor extends JFrame {

    private JTextField fileField, keyField;
    private JButton browseBtn, encryptBtn, decryptBtn;
    private JFileChooser fileChooser;

    public FileEncryptor() {
        setTitle("File Encryptor v1.00");
        setSize(600, 200);
        setLocation(300, 300); // 창 위치
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new GridLayout(3, 1));

        // 파일 선택 패널
        JPanel filePanel = new JPanel();
        fileField = new JTextField(30);
        browseBtn = new JButton("Browse");
        filePanel.add(new JLabel("File:"));
        filePanel.add(fileField);
        filePanel.add(browseBtn);
        add(filePanel);

        // 키 입력 패널 (복호화용)
        JPanel keyPanel = new JPanel();
        keyField = new JTextField(30);
        keyPanel.add(new JLabel("Decryption Key (optional, will use KEY.TXT if empty):"));
        keyPanel.add(keyField);
        add(keyPanel);

        // 버튼 패널
        JPanel buttonPanel = new JPanel();
        encryptBtn = new JButton("Encrypt");
        decryptBtn = new JButton("Decrypt");
        buttonPanel.add(encryptBtn);
        buttonPanel.add(decryptBtn);
        add(buttonPanel);

        fileChooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter("Encrypted/Decrypted files", "enc", "dec");
        fileChooser.setFileFilter(filter);

        // 이벤트
        browseBtn.addActionListener(e -> {
            int result = fileChooser.showOpenDialog(this);
            if(result == JFileChooser.APPROVE_OPTION) {
                fileField.setText(fileChooser.getSelectedFile().getAbsolutePath());
            }
        });

        encryptBtn.addActionListener(e -> processFile(true));
        decryptBtn.addActionListener(e -> processFile(false));
    }

    private void processFile(boolean encrypt) {
        String filePath = fileField.getText().trim();
        if(filePath.isEmpty()) {
            JOptionPane.showMessageDialog(this, "Please select a file.");
            return;
        }

        try {
            File inputFile = new File(filePath);
            File parentFolder = inputFile.getParentFile();

            if(encrypt) {
                // 랜덤 키 생성
                String keyText = generateRandomKey();
                SecretKeySpec key = new SecretKeySpec(keyText.getBytes(), "AES");
                Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
                cipher.init(Cipher.ENCRYPT_MODE, key);

                File outputFile = new File(filePath + ".enc");
                try (FileInputStream fis = new FileInputStream(inputFile);
                     FileOutputStream fos = new FileOutputStream(outputFile);
                     CipherOutputStream cos = new CipherOutputStream(fos, cipher)) {
                    byte[] buffer = new byte[4096];
                    int read;
                    while((read = fis.read(buffer)) != -1) {
                        cos.write(buffer, 0, read);
                    }
                }

                // 원본 삭제
                if(!inputFile.delete()) {
                    JOptionPane.showMessageDialog(this, "Warning: Could not delete original file.");
                }

                // KEY.TXT 생성
                File keyFile = new File(parentFolder, "KEY.TXT");
                try (BufferedWriter bw = new BufferedWriter(new FileWriter(keyFile))) {
                    bw.write(keyText);
                }

                JOptionPane.showMessageDialog(this, "File encrypted.\nKey saved to KEY.TXT:\n" + keyText);

            } else { // 복호화
                String keyText = keyField.getText().trim();

                // 키 입력 없으면 KEY.TXT 사용
                if(keyText.isEmpty()) {
                    File keyFile = new File(parentFolder, "KEY.TXT");
                    if(!keyFile.exists()) {
                        JOptionPane.showMessageDialog(this, "KEY.TXT not found in the folder and no key entered.");
                        return;
                    }
                    try (BufferedReader br = new BufferedReader(new FileReader(keyFile))) {
                        keyText = br.readLine();
                    }
                }

                // 키 검증
                if(keyText == null || !keyText.matches("[A-Z0-9]{16}")) {
                    JOptionPane.showMessageDialog(this, "Invalid key format.");
                    return;
                }

                SecretKeySpec key = new SecretKeySpec(keyText.getBytes(), "AES");
                Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
                cipher.init(Cipher.DECRYPT_MODE, key);

                File outputFile;
                if(filePath.endsWith(".enc")) {
                    outputFile = new File(filePath.substring(0, filePath.length() - 4));
                } else {
                    outputFile = new File(filePath + ".dec");
                }

                try (FileInputStream fis = new FileInputStream(inputFile);
                     FileOutputStream fos = new FileOutputStream(outputFile);
                     CipherOutputStream cos = new CipherOutputStream(fos, cipher)) {

                    byte[] buffer = new byte[4096];
                    int read;
                    while((read = fis.read(buffer)) != -1) {
                        cos.write(buffer, 0, read);
                    }

                } catch (Exception ex) {
                    if(outputFile.exists()) outputFile.delete();
                    JOptionPane.showMessageDialog(this, "Decryption failed: Incorrect key.");
                    return;
                }

                // 복호화 성공 시 암호화 파일 삭제
                if(!inputFile.delete()) {
                    JOptionPane.showMessageDialog(this, "Warning: Could not delete encrypted file.");
                }

                JOptionPane.showMessageDialog(this, "File decrypted successfully: " + outputFile.getName());
            }

        } catch (Exception ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(this, "Error: " + ex.getMessage());
        }
    }

    // 랜덤 키 생성 (영문 대문자 + 숫자 10자리)
    private String generateRandomKey() {
        String chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        SecureRandom random = new SecureRandom();
        StringBuilder key = new StringBuilder();
        for(int i = 0; i < 16; i++) {
            key.append(chars.charAt(random.nextInt(chars.length())));
        }
        return key.toString();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new FileEncryptor().setVisible(true));
    }
}
