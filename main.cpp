#include <iostream>
#include "chat.h"

int main() {
    setlocale(LC_ALL, "RU");
    Chat chat;

    chat.addUser("Alice");
    chat.addUser("Bob");
    chat.addUser("Charlie");

    chat.sendMessage("Alice", "Bob", "Привет, как дела?");
    chat.sendMessage("Bob", "Alice", "Привет! У меня всё отлично, спасибо!");
    chat.sendMessage("Bob", "Charlie", "Привет, Чарли!");
    chat.sendMessage("Charlie", "Alice", "Привет, Алиса!");

    std::cout << "История сообщений для пользователя Bob:" << std::endl;
    chat.displayMessageHistory("Bob");

    std::cout << "Очистка истории сообщений для пользователя Bob..." << std::endl;
    chat.clearMessageHistory("Bob");

    std::cout << "История сообщений для пользователя Bob после очистки:" << std::endl;
    chat.displayMessageHistory("Bob");

    return 0;
}
