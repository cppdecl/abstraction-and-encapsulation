#include <iostream>

class BankAccount {
protected:
    double balance;

public:
    BankAccount(double initialBalance = 0.0) : balance(initialBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        } else {
            std::cout << "Insufficient balance." << std::endl;
            return false;
        }
    }

    virtual double getBalance() const {
        return balance;
    }

    virtual void displayBalance() const {
        std::cout << "Current Balance: " << balance << std::endl;
    }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
private:
    static const double MIN_BALANCE;

public:
    SavingsAccount(double initialBalance = 1000.0) : BankAccount(initialBalance) {}

    bool withdraw(double amount) override {
        if ((balance - amount) >= MIN_BALANCE) {
            return BankAccount::withdraw(amount);
        } else {
            std::cout << "Cannot withdraw. Minimum balance of " << MIN_BALANCE << " required." << std::endl;
            return false;
        }
    }
};

const double SavingsAccount::MIN_BALANCE = 1000.0;

class CurrentAccount : public BankAccount {
public:
    CurrentAccount(double initialBalance = 0.0) : BankAccount(initialBalance) {}

    bool withdraw(double amount) override {
        return BankAccount::withdraw(amount);
    }
};

void displayMainMenu() {
    std::cout << "Main Menu\n";
    std::cout << "1 - Savings Account\n";
    std::cout << "2 - Current Account\n";
    std::cout << "3 - Exit\n";
}

void displaySubMenu() {
    std::cout << "Sub Menu\n";
    std::cout << "1 - Deposit\n";
    std::cout << "2 - Withdraw\n";
    std::cout << "3 - Check Balance\n";
    std::cout << "4 - Back\n";
}

int main() {
    SavingsAccount* savingsAccount = nullptr;
    CurrentAccount* currentAccount = nullptr;

    BankAccount* account = nullptr;
    int mainChoice, subChoice;
    double amount;

    do {
        displayMainMenu();
        std::cin >> mainChoice;

        system("cls");

        switch (mainChoice) {
            case 1:
                if (!savingsAccount) {
                    savingsAccount = new SavingsAccount();
                }

                account = savingsAccount;
                break;
            case 2:
                if (!currentAccount) {
                    currentAccount = new CurrentAccount();
                }

                account = currentAccount;
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice.\n";
                continue;
        }

        do {
            displaySubMenu();
            std::cin >> subChoice;

            system("cls");

            switch (subChoice) {
                case 1:
                    std::cout << "Enter amount to deposit: ";
                    std::cin >> amount;
                    account->deposit(amount);
                    break;
                case 2:
                    std::cout << "Enter amount to withdraw: ";
                    std::cin >> amount;
                    account->withdraw(amount);
                    break;
                case 3:
                    account->displayBalance();
                    break;
                case 4:
                    std::cout << "Returning to main menu...\n";
                    break;
                default:
                    std::cout << "Invalid choice.\n";
            }
        } while (subChoice != 4);

    } while (mainChoice != 3);

    delete savingsAccount;
    delete currentAccount;

    account = nullptr;
    savingsAccount = nullptr;
    currentAccount = nullptr;

    return 0;
}
