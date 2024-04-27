#include <iostream>
#include "chat.h"

int main() {
    setlocale(LC_ALL, "RU");
    Chat chat;

    chat.addUser("Alice");
    chat.addUser("Bob");
    chat.addUser("Charlie");

    chat.sendMessage("Alice", "Bob", "������, ��� ����?");
    chat.sendMessage("Bob", "Alice", "������! � ���� �� �������, �������!");
    chat.sendMessage("Bob", "Charlie", "������, �����!");
    chat.sendMessage("Charlie", "Alice", "������, �����!");

    std::cout << "������� ��������� ��� ������������ Bob:" << std::endl;
    chat.displayMessageHistory("Bob");

    std::cout << "������� ������� ��������� ��� ������������ Bob..." << std::endl;
    chat.clearMessageHistory("Bob");

    std::cout << "������� ��������� ��� ������������ Bob ����� �������:" << std::endl;
    chat.displayMessageHistory("Bob");

    return 0;
}
