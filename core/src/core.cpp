#include <core.hpp>
#include <iostream>
#include <string>

// Helper function to build the HTML linked list
n<std::string>* build_html() {
    auto* html = new n<std::string>("<!DOCTYPE html>");
    auto* head = new n<std::string>("<html>");
    auto* title = new n<std::string>("<head><title>Server</title></head>");
    auto* body_start = new n<std::string>("<body>");
    auto* h1 = new n<std::string>("<h1>Welcome to the Server!</h1>");
    auto* p = new n<std::string>("<p>This is a simple HTTP server encapsulated in a class.</p>");
    auto* body_end = new n<std::string>("</body>");
    auto* html_end = new n<std::string>("</html>");

    // Link the nodes
    html->l(head);
    head->l(title);
    title->l(body_start);
    body_start->l(h1);
    h1->l(p);
    p->l(body_end);
    body_end->l(html_end);

    return html;
}

// Helper function to traverse and build the HTML response string
std::string generate_html_response(n<std::string>* html) {
    std::string response = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html; charset=UTF-8\r\n\r\n";

    auto* current = html;
    while (current) {
        response += current->get();
        current = current->next();
    }

    return response;
}

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

        // Build the HTML linked list
        n<std::string>* html = build_html();

        // Generate the HTML response
        std::string response = generate_html_response(html);

        // Respond with the dynamically generated HTML content
        client.s(response);
        std::cout << "HTML response sent to client." << std::endl;

        // Free the linked list
        while (html) {
            auto* next = html->next();
            delete html;
            html = next;
        }

        // Close the client connection
        client.q();
    } catch (const std::exception& e) {
        std::cerr << "Error handling client: " << e.what() << std::endl;
    }
}

