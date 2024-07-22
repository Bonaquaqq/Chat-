#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

void receive_messages(int client_socket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            std::cerr << "Disconnected from server or error occurred" << std::endl;
            close(client_socket);
            break;
        }
        std::cout << buffer << std::endl;
    }
}

int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(client_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    std::thread(receive_messages, client_socket).detach();

    std::string message;
    std::string recipient;
    while (true) {
        std::cout << "Enter recipient and message (format: recipient message): ";
        std::getline(std::cin, message);
        if (message == "exit") {
            break;
        }
        // Assume message format is "recipient message"
        size_t pos = message.find(' ');
        if (pos != std::string::npos) {
            recipient = message.substr(0, pos);
            std::string msg = message.substr(pos + 1);
            std::string full_message = recipient + ": " + msg;
            send(client_socket, full_message.c_str(), full_message.size(), 0);
        }
    }

    close(client_socket);
    return 0;
}
