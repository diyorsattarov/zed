#include <core.hpp>
#include <iostream>

int main() {
    try {
        Server server(8080); // Create a server on port 8080
        server.run();        // Run the server
    } catch (const std::exception& e) {
        std::cerr << "Failed to start server: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

