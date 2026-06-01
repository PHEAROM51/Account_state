#ifndef ACCOUNTSTATE_H
#define ACCOUNTSTATE_H

#include <string>

class AccountState {
    public:
    virtual bool deposit(int amount) const = 0;
    virtual bool withdraw(int amount) const = 0;
    virtual std::string getStateName() const = 0;
    virtual ~AccountState() = default;
};

class ActiveState : public AccountState {
    public:
    bool deposit(int amount) const {
        return true;
    }
    bool withdraw(int amount) const {
        return true;
    }
    std::string getStateName() const {
        return "Active";
    }
};

class FrozenState : public AccountState {
    public:
    bool deposit(int amount) const {
        return true;
    }
    bool withdraw(int amount) const {
        return false;
    }
    std::string getStateName() const {
        return "Frozen";
    }
};

class ClosedState : public AccountState {
    public:
    bool deposit(int amount) const {
        return false;
    }
    bool withdraw(int amount) const {
        return false;
    }
    std::string getStateName() const {
        return "Closed";
    }
};

#endif