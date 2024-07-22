#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

std::vector<int> clients;
std::mutex clients_mutex;

void broadcast(const std::string& message, int sender_socket) {
    std::lock_guard<std::mutex> guard(clients_mutex);
    for (int client_socket : clients) {
        if (client_socket != sender_socket) {
            if (send(client_socket, message.c_str(), message.size(), 0) == -1) {
                std::cerr << "Failed to send message to client socket " << client_socket << std::endl;
            }
        }
    }
}

void handle_client(int client_socket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            std::cerr << "Client disconnected or error occurred" << std::endl;
            close(client_socket);
            std::lock_guard<std::mutex> guard(clients_mutex);
            clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
            break;
        }
        std::string message(buffer);
        std::lock_guard<std::mutex> guard(clients_mutex);
       
      
        broadcast(message, client_socket); 
    }
}


int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to bind to port 9999" << std::endl;
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    std::cout << "Server started on port 9999" << std::endl;

    while (true) {
        sockaddr_in client_addr;
        socklen_t client_size = sizeof(client_addr);
        int client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_size);
        if (client_socket == -1) {
            std::cerr << "Failed to grab connection" << std::endl;
            continue;
        }

        std::lock_guard<std::mutex> guard(clients_mutex);
        clients.push_back(client_socket);
        std::thread(client_handler, handle_client, client_socket).detach();
    }

    close(server_socket);
    return 0;
}
