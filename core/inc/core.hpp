#ifndef CORE_HPP
#define CORE_HPP

#include <b.hpp>
#include <string>

class Server {
public:
    /**
     * @brief Constructs a server to run on a specified port.
     * @param port Port number for the server to listen on.
     */
    Server(int port);

    /**
     * @brief Starts the server.
     * @note This function runs the server in a loop and handles client connections.
     */
    void run();

private:
    b server_;  // Underlying server socket
    int port_;  // Port number

    /**
     * @brief Handles a client connection.
     * @param client The connected client socket.
     */
    void handle_client(b client);
};

#endif // CORE_HPP

