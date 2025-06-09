#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class AccountException : public exception {
    string message;
    int amount;

public:
    AccountException(const string& msg, int amt) : message(msg), amount(amt) { }

    const char* what() const noexcept override {
        return message.c_str();
    }

    int getAmount() const {
        return amount;
    }
};

class CustomAccount {
    int balance;

public:
    CustomAccount(int b = 0) : balance(b) { }

    int getBalance() { return balance; }

    int deposit(int amount) {
        if (amount <= 0)
            throw AccountException("입금 금액은 0보다 커야 합니다.", amount);
        balance += amount;
        return balance;
    }

    int withdraw(int amount) {
        if (amount > balance)
            throw AccountException("잔액보다 큰 금액은 출금할 수 없습니다.", amount);
        balance -= amount;
        return balance;
    }
};

int main() {
    CustomAccount acc(1000);

    try {
        cout << "현재 잔액: " << acc.getBalance() << endl;
        cout << "500원 입금 후 잔액: " << acc.deposit(500) << endl;
        cout << "2000원 출금 시도..." << endl;
        cout << "출금 후 잔액: " << acc.withdraw(2000) << endl;  // 예외 발생
    }
    catch (const AccountException& e) {
        cerr << "예외 발생: " << e.what() << " (금액: " << e.getAmount() << ")\n";
    }

    try {
        cout << "0원 입금 시도..." << endl;
        cout << "입금 후 잔액: " << acc.deposit(0) << endl;  // 예외 발생
    }
    catch (const AccountException& e) {
        cerr << "예외 발생: " << e.what() << " (금액: " << e.getAmount() << ")\n";
    }

    cout << "최종 잔액: " << acc.getBalance() << endl;

    return 0;
}

