package BankAccountSystem;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Scanner;
import java.sql.*;
import java.io.*;

public class BankAccountSystemDB {
    private static final String URL = "jdbc:mysql://127.0.0.1:3306/bankdb"; //Your Server
    private static final String USER = "root";
    private static final String PASSWORD = "qwer";
    private static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        try {
        	try {
				Class.forName("com.mysql.cj.jdbc.Driver");
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
            Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
            BankAccountService service = new BankAccountService(new BankAccountDAO(conn));

            while(true) {
                System.out.println("\n1. 계좌 생성  2. 입금  3. 출금  4. 잔액 조회  5. 모든 계좌 조회  6. 종료");
                System.out.print("선택: ");
                int choice = sc.nextInt(); sc.nextLine();

                switch(choice) {
                    case 1 -> {
                        System.out.print("계좌번호: "); String accNum = sc.nextLine();
                        System.out.print("이름: "); String owner = sc.nextLine();
                        System.out.print("초기 입금액: "); double balance = sc.nextDouble(); sc.nextLine();
                        service.createAccount(accNum, owner, balance);
                    }
                    case 2 -> {
                        System.out.print("계좌번호: "); String accNum = sc.nextLine();
                        System.out.print("입금액: "); double amount = sc.nextDouble(); sc.nextLine();
                        service.deposit(accNum, amount);
                    }
                    case 3 -> {
                        System.out.print("계좌번호: "); String accNum = sc.nextLine();
                        System.out.print("출금액: "); double amount = sc.nextDouble(); sc.nextLine();
                        service.withdraw(accNum, amount);
                    }
                    case 4 -> {
                        System.out.print("계좌번호: "); String accNum = sc.nextLine();
                        service.checkBalance(accNum);
                    }
                    case 5 -> service.showAllAccounts();
                    case 6 -> { System.out.println("시스템 종료"); conn.close(); return; }
                    default -> System.out.println("잘못된 선택입니다.");
                }
            }
        } catch(SQLException e) {
            e.printStackTrace();
        }
    }
}