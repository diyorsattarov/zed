#include <core.hpp>
#include <iostream>
#include <string>

const std::string HTML_RESPONSE = R"(HTTP/1.1 200 OK
Content-Type: text/html; charset=UTF-8

<!DOCTYPE html>
<html>
<head>
    <title>Server</title>
</head>
<body>
    <h1>Welcome to the Server!</h1>
    <p>This is a simple HTTP server encapsulated in a class.</p>
</body>
</html>
)";

Server::Server(int port) : server_(true), port_(port) {
    server_.c(port_); // Configure the server to listen on the specified port
    server_.b_();     // Bind the server
    server_.l();      // Start listening
}

void Server::run() {
    std::cout << "Server running on http://localhost:" << port_ << " ..." << std::endl;

    while (true) {
        try {
            // Accept an incoming connection
            b client = server_.a();
            std::cout << "Client connected!" << std::endl;

            // Handle the client connection
            handle_client(client);
        } catch (const std::exception& e) {
            std::cerr << "Server error: " << e.what() << std::endl;
        }
    }
}

void Server::handle_client(b client) {
    try {
        // Read the incoming request (not actually parsing it here)
        std::string request = client.r(1024);
        std::cout << "Received request:\n" << request << std::endl;

        // Respond with the HTML content
        client.s(HTML_RESPONSE);
        std::cout << "HTML response sent to client." << std::endl;

        // Close the client connection
        client.q();
    } catch (const std::exception& e) {
        std::cerr << "Error handling client: " << e.what() << std::endl;
    }
}

