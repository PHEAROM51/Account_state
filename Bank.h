#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include <memory>
#include "Customer.h"
#include "Transaction.h"

class Bank {
    private:
    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<Transaction>> transactions;
    public:
    void addCustomer(std::shared_ptr<Customer> customer) {
        customers.push_back(customer);
    }
    Account* findAccount(const std::string& accountNumber) {
        for(const auto& c : customers) {
            return c->getAccount(accountNumber);
        }
        return nullptr;
    }
    void processDeposit(const std::string& accountNumber, int amount) {
        findAccount(accountNumber)->deposit(amount);
        transactions.push_back(std::make_shared<Transaction>("Deposit", amount, accountNumber, findAccount(accountNumber)->depositStatus(amount)));
    }
    void processWithdrawal(const std::string& accountNumber, int amount) {
        findAccount(accountNumber)->withdraw(amount);
        transactions.push_back(std::make_shared<Transaction>("Withdrawal", amount, accountNumber, findAccount(accountNumber)->withdrawStatus(amount)));
    }
    int getTransactionCount() const {
        return transactions.size();
    }
};

#endif