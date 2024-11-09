/****************************************************************************
 * File: b.hpp
 * Author: Diyor Sattarov
 * Email: diyorsattarov@outlook.com
 *
 * Created: 2024-11-09
 *
 * Description: This header file defines a class `b` for managing Berkeley
 * sockets. The class provides functionalities to create, bind, listen,
 * and accept connections, as well as send and receive data over a TCP
 * connection, with all methods named using single letters.
 * Copyright (c) 2024 diyorsattarov. All rights reserved.
 ****************************************************************************/

#ifndef b_hpp
#define b_hpp

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h>  // For inet_pton
#include <unistd.h>     // For close
#include <cstring>      // For memset
#include <string>       // For std::string

class b {
    int s_;               // Socket file descriptor
    sockaddr_in addr_;    // Socket address structure
    bool is_server_;      // Indicates if the socket is in server mode

public:
    b(bool is_server = true) : s_(-1), is_server_(is_server) {
        s_ = socket(AF_INET, SOCK_STREAM, 0);
        if (s_ < 0) {
            throw std::runtime_error("Socket creation failed");
        }
        memset(&addr_, 0, sizeof(addr_));
    }

    void c(int port, const std::string& ip = "0.0.0.0") {
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        if (is_server_) {
            addr_.sin_addr.s_addr = INADDR_ANY; // For server, bind to any address
        } else {
            if (inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr) <= 0) {
                throw std::runtime_error("Invalid IP address");
            }
        }
    }

    void b_() {
        if (bind(s_, (sockaddr*)&addr_, sizeof(addr_)) < 0) {
            throw std::runtime_error("Bind failed");
        }
    }

    void l(int backlog = 5) {
        if (listen(s_, backlog) < 0) {
            throw std::runtime_error("Listen failed");
        }
    }

    b a() {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(s_, (sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            throw std::runtime_error("Accept failed");
        }
        b client(false);
        client.s_ = client_socket;
        client.addr_ = client_addr;
        return client;
    }

    void x() {
        if (connect(s_, (sockaddr*)&addr_, sizeof(addr_)) < 0) {
            throw std::runtime_error("Connect failed");
        }
    }

    void s(const std::string& data) {
        if (send(s_, data.c_str(), data.size(), 0) < 0) {
            throw std::runtime_error("Send failed");
        }
    }

    std::string r(size_t buffer_size = 1024) {
        char buffer[buffer_size];
        memset(buffer, 0, buffer_size);
        ssize_t bytes_received = recv(s_, buffer, buffer_size - 1, 0);
        if (bytes_received < 0) {
            throw std::runtime_error("Receive failed");
        }
        return std::string(buffer, bytes_received);
    }

    void q() {
        if (s_ >= 0) {
            close(s_);
            s_ = -1;
        }
    }

    ~b() {
        q();
    }
};

#endif // b_hpp

