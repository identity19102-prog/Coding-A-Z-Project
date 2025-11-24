package BankAccountSystem;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class BankAccountDAO {
    private Connection conn;

    public BankAccountDAO(Connection conn) {
        this.conn = conn;
    }

    public boolean createAccount(BankAccount account) throws SQLException {
        String sql = "INSERT INTO accounts (accountNumber, owner, balance) VALUES (?, ?, ?)";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, account.getAccountNumber());
        pstmt.setString(2, account.getOwner());
        pstmt.setDouble(3, account.getBalance());
        return pstmt.executeUpdate() > 0;
    }

    public BankAccount findAccount(String accNum) throws SQLException {
        String sql = "SELECT * FROM accounts WHERE accountNumber = ?";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, accNum);
        ResultSet rs = pstmt.executeQuery();
        if(rs.next()) {
            return new BankAccount(rs.getString("accountNumber"),
                                   rs.getString("owner"),
                                   rs.getDouble("balance"));
        }
        return null;
    }

    public boolean updateBalance(String accNum, double newBalance) throws SQLException {
        String sql = "UPDATE accounts SET balance = ? WHERE accountNumber = ?";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setDouble(1, newBalance);
        pstmt.setString(2, accNum);
        return pstmt.executeUpdate() > 0;
    }

    public List<BankAccount> getAllAccounts() throws SQLException {
        List<BankAccount> list = new ArrayList<>();
        String sql = "SELECT * FROM accounts";
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery(sql);
        while(rs.next()) {
            list.add(new BankAccount(rs.getString("accountNumber"),
                                     rs.getString("owner"),
                                     rs.getDouble("balance")));
        }
        return list;
    }
}