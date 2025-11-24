package BankAccountSystem;

import java.sql.SQLException;
import java.util.List;

public class BankAccountService {
    private BankAccountDAO dao;

    public BankAccountService(BankAccountDAO dao) {
        this.dao = dao;
    }

    public void createAccount(String accNum, String owner, double balance) throws SQLException {
        BankAccount account = new BankAccount(accNum, owner, balance);
        if(dao.createAccount(account)) System.out.println("계좌 생성 완료!");
        else System.out.println("계좌 생성 실패");
    }

    public void deposit(String accNum, double amount) throws SQLException {
        BankAccount acc = dao.findAccount(accNum);
        if(acc != null) {
            acc.setBalance(acc.getBalance() + amount);
            dao.updateBalance(accNum, acc.getBalance());
            System.out.println(amount + "원이 입금되었습니다.");
        } else System.out.println("계좌를 찾을 수 없습니다.");
    }

    public void withdraw(String accNum, double amount) throws SQLException {
        BankAccount acc = dao.findAccount(accNum);
        if(acc != null) {
            if(amount <= acc.getBalance()) {
                acc.setBalance(acc.getBalance() - amount);
                dao.updateBalance(accNum, acc.getBalance());
                System.out.println(amount + "원이 출금되었습니다.");
            } else System.out.println("잔액이 부족합니다.");
        } else System.out.println("계좌를 찾을 수 없습니다.");
    }

    public void checkBalance(String accNum) throws SQLException {
        BankAccount acc = dao.findAccount(accNum);
        if(acc != null) System.out.println(acc.getOwner() + "님의 잔액: " + acc.getBalance() + "원");
        else System.out.println("계좌를 찾을 수 없습니다.");
    }

    public void showAllAccounts() throws SQLException {
        List<BankAccount> list = dao.getAllAccounts();
        System.out.println("\n--- 모든 계좌 ---");
        for(BankAccount acc : list) System.out.println(acc);
    }
}
