/****************************************************************************
 * File: core.hpp
 * Author: Diyor Sattarov
 * Email: diyorsattarov@outlook.com
 *
 * Created: 2024-10-09
 * Last Modified: 2024-10-05
 *
 * Description:
 * This header file defines the `Server` class, which encapsulates the 
 * functionality of a simple HTTP server. The `Server` class uses the `b` class 
 * from the `utility` component for networking and integrates with `n` 
 * structures from the `common` component to manage data.
 *
 * Copyright (c) 2024 diyorsattarov. All rights reserved.
 ****************************************************************************/

#ifndef CORE_HPP
#define CORE_HPP

#include <n.hpp>
#include <b.hpp>

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

