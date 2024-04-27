
#ifndef CHAT_H
#define CHAT_H

#include <vector>
#include <map>
#include "user.h"

class Chat {
private:
    std::map<std::string, User> users;

public:
    void addUser(const std::string& name) {
        users.insert({ name, User(name) });
    }

    void sendMessage(const std::string& sender, const std::string& receiver, const std::string& message) {
        if (users.count(receiver) == 0) {
            std::cout << "Ошибка: Получатель не существует." << std::endl;
            return;
        }

        users[receiver].addMessage(sender + ": " + message);
    }

    void displayMessageHistory(const std::string& name) const {
        if (users.count(name) > 0) {
            users.at(name).displayMessageHistory();
        }
        else {
            std::cout << "Пользователь не найден." << std::endl;
        }
    }

    void clearMessageHistory(const std::string& name) {
        if (users.count(name) > 0) {
            users.at(name).clearMessageHistory();
        }
    }

   
};

#endif // CHAT_H
