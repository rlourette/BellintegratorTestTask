# BellintegratorTestTask

Step-by-step instructions to build the TCP server "Bellintegrator Test Task" application using the POCO library:

# Building a TCP Server with POCO Library

These instructions will guide you through building a simple test TCP server using the POCO C++ library. The server will accept client connections on port 28888, reverse strings entered by clients, and handle lines exceeding 255 characters.

## Prerequisites

- C++ compiler (e.g., g++)
- POCO C++ libraries installed
  - You can download POCO from [here](https://pocoproject.org/download.html) and follow their installation instructions.

## Building the TCP Server

1. Create a new C++ source file for the server, e.g., `bellintegratortesttask.cpp`.

2. Copy and paste the following code into `bellintegratortesttask.cpp`:

   ```cpp
    include "Poco/Net/ServerSocket.h"
    #include "Poco/Net/StreamSocket.h"
    #include "Poco/Net/SocketStream.h"
    #include "Poco/Thread.h"
    #include "Poco/Runnable.h"
    #include "Poco/Exception.h"
    #include <iostream>
    #include <string>
    #include <sstream>
    #include <algorithm>
    using namespace Poco::Net;
    using namespace Poco;

    class TCPServer : public Runnable {
    public:
        TCPServer(ServerSocket& socket) : _socket(socket) {}
        void run() {
            while (true) {
                try {
                    StreamSocket clientSocket = _socket.acceptConnection();
                    SocketStream stream(clientSocket);
                    std::string welcomeMessage = "Welcome to POCO TCP server. Enter you(SIC) string:";
                    stream << "\"" << welcomeMessage << "\"" << std::endl;
                    while (true) {
                        std::string inputLine;
                        std::getline(stream, inputLine);
                        if (inputLine.empty()) {
                            // Client closed the connection
                            break;
                        }
                        // Truncate input if it exceeds 255 characters
                        if (inputLine.length() > 255) {
                            inputLine = inputLine.substr(0, 255);
                        }
                        // Reverse the string
                        std::reverse(inputLine.begin(), inputLine.end());
                        stream << inputLine << std::endl;
                    }
                } catch (Exception& ex) {
                    std::cerr << "Exception: " << ex.displayText() << std::endl;
                }
            }
        }
    private:
        ServerSocket _socket;
    };

    int main() {
        try {
            ServerSocket server(28888);
            TCPServer tcpServer(server);
            Thread thread;
            thread.start(tcpServer);
            thread.join();
        } catch (Exception& ex) {
            std::cerr << "Exception: " << ex.displayText() << std::endl;
        }
        return 0;
    }

   ```

3. Compile the code using a C++ compiler that supports POCO and link against the POCO libraries:

   ```bash
   g++ -o bellintegratortesttask bellintegratortesttask.cpp -lPocoNet -lPocoUtil -lPocoFoundation
   ```

4. Run the compiled executable:

   ```bash
   ./bellintegratortesttask
   ```

5. Connecto to the server:

    ```bash
    telnet localhost 28888
    ```

6. Example session:

    ```bash
    $ telnet localhost 28888
    Trying 127.0.0.1...
    Connected to localhost.
    Escape character is '^]'.
    "Welcome to POCO TCP server. Enter you(sic) string:"
    1234567890
    0987654321
```
The TCP server will now be running and listening on port 28888. It will accept client connections, reverse input strings, and handle lines exceeding 255 characters by truncating them.
```
