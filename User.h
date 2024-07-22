#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>

class User {
private:
    std::string name;
    std::vector<std::string> messageHistory;

public:
    User() {}

    User(const std::string& _name) : name(_name) {}

    std::string getName() const {
        return name;
    }

    void addMessage(const std::string& message) {
        messageHistory.push_back(message);
    }

    void displayMessageHistory() const {
        for (const std::string& message : messageHistory) {
            std::cout << message << std::endl;
        }
    }

    void clearMessageHistory() {
        messageHistory.clear();
    }

    void removeMessage(int index) {
        if (index < 0 || index >= static_cast<int>(messageHistory.size())) {
            std::cout << "Ошибка: недопустимый индекс сообщения." << std::endl;
            return;
        }

        messageHistory.erase(messageHistory.begin() + index);
    }

    void displayLastNMessages(int n) const {
        int start = std::max(static_cast<int>(messageHistory.size()) - n, 0);
        for (int i = start; i < static_cast<int>(messageHistory.size()); ++i) {
            std::cout << messageHistory[i] << std::endl;
        }
    }
};

#endif // USER_H

