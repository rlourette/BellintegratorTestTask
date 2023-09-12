#include "Poco/Net/ServerSocket.h"
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

// #include <iostream>
// #include <string>
// #include <Poco/Net/ServerSocket.h>
// #include <Poco/Net/StreamSocket.h>
// #include <Poco/Net/SocketStream.h>
// #include <Poco/Exception.h>

// using namespace Poco::Net;
// using namespace Poco;

// int main() {
//     try {
//         ServerSocket server(28888);
//         std::cout << "Server listening on port 28888..." << std::endl;
//         StreamSocket client = server.acceptConnection();
//         SocketStream ss(client);
        
//         // Send a welcome message to the client
//         ss << "\"Welcome to POCO TCP server. Enter you(sic) string:\"" << std::endl;
//         ss.flush();

//         while (true) {
//             // Receive and process client input
//             std::string clientInput;
//             std::getline(ss, clientInput);

//             // Ensure the input does not exceed 255 characters
//             if (clientInput.length() > 255) {
//                 clientInput = clientInput.substr(0, 255);
//             }

//             // Reverse the string
//             std::reverse(clientInput.begin(), clientInput.end());

//             // Send the reversed string back to the client
//             ss << clientInput << std::endl;
//             ss.flush();

//             // Keep the connection open for further requests
//         }
//     } catch (Exception& e) {
//         std::cerr << "Exception: " << e.displayText() << std::endl;
//         return 1;
//     }

//     return 0;
// }
