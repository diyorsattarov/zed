#include <iostream>
#include <b.hpp>
#include <n.hpp>
#include <thread> // For std::thread
#include <sstream> // For std::ostringstream and std::istringstream

// Helper function to serialize an `n` object
template <typename T>
std::string serialize(const n<T>& node) {
    std::ostringstream oss;
    oss << node.get(); // Serialize the value
    return oss.str();  // Return as string
}

// Helper function to deserialize a string into an `n` object
template <typename T>
n<T> deserialize(const std::string& data) {
    std::istringstream iss(data);
    T value;
    iss >> value; // Extract the value
    return n<T>(value); // Create and return an `n` object
}

void server_function() {
    try {
        b server(true);
        server.c(8080);
        server.b_();
        server.l();
        std::cout << "[Server] Listening on port 8080..." << std::endl;

        b client = server.a();
        std::cout << "[Server] Client connected!" << std::endl;

        // Create an `n` object and serialize it
        n<int> node(42); // Example `n` object with value 42
        std::string serialized_data = serialize(node);
        client.s(serialized_data);
        std::cout << "[Server] Sent n object with value: " << node.get() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Server] Error: " << e.what() << std::endl;
    }
}

void client_function() {
    try {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Ensure server starts first

        b client_socket(false);
        client_socket.c(8080, "127.0.0.1");
        client_socket.x();
        std::cout << "[Client] Connected to server!" << std::endl;

        // Receive serialized data and deserialize it
        std::string received_data = client_socket.r();
        n<int> received_node = deserialize<int>(received_data);
        std::cout << "[Client] Received n object with value: " << received_node.get() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[Client] Error: " << e.what() << std::endl;
    }
}

int main() {
    // Run server and client in separate threads
    std::thread server_thread(server_function);
    std::thread client_thread(client_function);

    // Wait for both threads to complete
    server_thread.join();
    client_thread.join();

    return 0;
}

