#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <memory>
#include <vector>
#include "Account.h"

class Customer {
    private:
    std::string name;
    std::string id;
    std::vector<std::shared_ptr<Account>> accounts;
    public:
    void addAccount(std::shared_ptr<Account> account) {
        accounts.push_back(account);
    }
    Account* getAccount(const std::string& accountNumber) {
        for(const auto& a : accounts) {
            if(a->getAccountNumber() == accountNumber) {
                return a.get();
            }
        }
        return nullptr;
    }
    int getTotalBalance() {
        int sum = 0;
        for(const auto& a : accounts) {
            sum += a->getBalance();
        }
        return sum;
    }
    void listAccount() const {
        for(const auto& a : accounts) {
            std::cout << a->getInfo() << std::endl;
        }
    }
};

#endif