#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <memory>
#include <iostream>
#include "AccountState.h"

class Account {
    protected:
    std::string accNum;
    std::string ownerName;
    int balance;
    std::unique_ptr<AccountState> state;
    public:
    Account(std::string num, std::string name, int b, std::unique_ptr<AccountState> s) : accNum(num), ownerName(name), balance(b), state(std::move(s)) {}
    std::string getAccountNumber() const {
        return accNum;
    }
    int getBalance() const {
        return balance;
    }
    bool depositStatus(int amount) {
        return state->deposit(amount);
    }
    void deposit(int amount) {
        if(state->deposit(amount)) {
            balance += amount;
            std::cout << "Deposited " << amount << " to " << accNum << std::endl;
        } else {
            std::cout << "Deposit rejectd: account is " << state->getStateName() << std::endl;
        }
    }
    bool withdrawStatus(int amount) {
        return state->withdraw(amount);
    }
    virtual void withdraw(int amount) {
        if(state->withdraw(amount)) {
            if(amount > balance) {
                std::cout << "Insufficient funds" << std::endl;
            } else {
                balance -= amount;
                std::cout << "Withdrew " << amount << " from " << accNum << std::endl;
            }
        } else {
            std::cout << "Withdrawal rejected: account is " << state->getStateName() << std::endl; 
        }
    }
    void freeze() {
        state = std::make_unique<FrozenState>();
    }
    void activate() {
        state = std::make_unique<ActiveState>();
    }
    void close() {
        state = std::make_unique<ClosedState>();
    }
    std::string getInfo() const {
        return accNum + " (" + ownerName + "): $" + std::to_string(balance) + " - " + state->getStateName();
    }
    virtual std::string getAccountType() const {
        return "Basic";
    }
};

class SavingsAccount : public Account {
    private:
    int minBalance;
    public:
    SavingsAccount(std::string accNum, std::string ownerName, int balance, std::unique_ptr<AccountState> state, int min) : Account(accNum, ownerName, balance, std::move(state)), minBalance(min) {}
    void withdraw(int amount) override {
        if(state->withdraw(amount)) {
            if(amount > balance) {
                std::cout << "Insufficient funds" << std::endl;
            } 
            else if(balance - amount < minBalance) {
                std::cout << "Cannot go below minimum balance of " << minBalance << std::endl;
            }
            else {
                balance -= amount;
                std::cout << "Withdrew " << amount << " from " << accNum << std::endl;
            }
        } else {
            std::cout << "Withdrawal rejected: account is " << state->getStateName() << std::endl; 
        }
    }
    std::string getAccountType() const {
        return "Savings";
    }
};

class CheckingAccount : public Account {
    private:
    int overdraftLimit;
    public:
    CheckingAccount(std::string accNum, std::string ownerName, int balance, std::unique_ptr<AccountState> state, int limit) : Account(accNum, ownerName, balance, std::move(state)), overdraftLimit(limit) {}
    void withdraw(int amount) override {
        if(state->withdraw(amount)) {
            if(amount > balance + overdraftLimit) {
                std::cout << "Insufficient funds" << std::endl;
            } 
            else {
                balance -= amount;
                std::cout << "Withdrew " << amount << " from " << accNum << std::endl;
            }
        } else {
            std::cout << "Withdrawal rejected: rejected: account is " << state->getStateName() << std::endl; 
        }
    }
    std::string getAccountType() const {
        return "Checking";
    }
};

#endif