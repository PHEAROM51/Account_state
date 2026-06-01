#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "Bank.h"

int main() {
    // Read input 1: Customer details (format: name,customerId)
    std::string customerInput;
    std::getline(std::cin, customerInput);

    char comma = customerInput.find(',');
    std::string customerName = customerInput.substr(0, comma);
    customerInput.erase(0, comma + 1);
    std::string customerId = customerInput;

    
    // Read input 2: Savings account details (format: accountNumber,minBalance)
    std::string accountInput;
    std::getline(std::cin, accountInput);
    comma = accountInput.find(',');
    std::string accountNumber = accountInput.substr(0, comma);
    accountInput.erase(0, comma + 1);
    std::string minBalance = accountInput;
    
    // Read input 3: Operation 1 (format: action,accountNumber,amount)
    std::string op1Input;
    std::getline(std::cin, op1Input);
    comma = op1Input.find(',');
    std::string action1 = op1Input.substr(0, comma);
    op1Input.erase(0, comma + 1);
    comma = op1Input.find(',');
    std::string accountNumber1 = op1Input.substr(0, comma);
    op1Input.erase(0, comma + 1);
    std::string amount1 = op1Input;
    
    // Read input 4: Operation 2 (format: action,accountNumber,amount or freeze,accountNumber)
    std::string op2Input;
    std::getline(std::cin, op2Input);
    std::string action2, accountNumber2, amount2;
    if(op2Input.find("freeze") != std::string::npos) {
        comma = op2Input.find(',');
        action2 = op2Input.substr(0, comma);
        op2Input.erase(0, comma + 1);
        accountNumber2 = op2Input;
    } else {
        comma = op2Input.find(',');
        action2 = op2Input.substr(0, comma);
        op2Input.erase(0, comma + 1);
        comma = op2Input.find(',');
        accountNumber2 = op2Input.substr(0, comma);
        op2Input.erase(0, comma + 1);
        amount2 = op2Input;
    }

    Bank bank;
    auto customer = std::make_shared<Customer>();
    
    customer->addAccount(std::make_shared<SavingsAccount>(accountNumber, customerName, 0.0, std::make_unique<ActiveState>(), std::stoi(minBalance)));

    bank.addCustomer(customer);

    // Operation 1
    if(action1 == "deposit") {
        bank.processDeposit(accountNumber1, std::stoi(amount1));
    } else {
        bank.processWithdrawal(accountNumber1, std::stoi(amount1));
    }

    // Operation 2
    if(action2 == "freeze") {
        bank.findAccount(accountNumber2)->freeze();
        bank.processWithdrawal(accountNumber2, 10.0);
    } 
    else if (action2 == "deposit") {
        bank.processDeposit(accountNumber2, std::stoi(amount2));
    } else {
        bank.processWithdrawal(accountNumber2, std::stoi(amount2));
    }
    
    std::cout << bank.findAccount(accountNumber)->getInfo() << std::endl;

    std::cout << "Transactions: " << bank.getTransactionCount() << std::endl;

    return 0;
}
