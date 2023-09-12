#include <iostream>
#include <string>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Exception.h>

using namespace Poco::Net;
using namespace Poco;

int main() {
    try {
        ServerSocket server(28888);
        std::cout << "Server listening on port 28888..." << std::endl;

        while (true) {
            StreamSocket client = server.acceptConnection();
            SocketStream ss(client);

            // Send a welcome message to the client
            ss << "\"Welcome to POCO TCP server. Enter you(sic) string:\"" << std::endl;
            ss.flush();

            // Receive and process client input
            std::string clientInput;
            std::getline(ss, clientInput);

            // Ensure the input does not exceed 255 characters
            if (clientInput.length() > 255) {
                clientInput = clientInput.substr(0, 255);
            }

            // Reverse the string
            std::reverse(clientInput.begin(), clientInput.end());

            // Send the reversed string back to the client
            ss << "Reversed string: \"" << clientInput << "\"" << std::endl;
            ss.flush();

            // Keep the connection open for further requests
        }
    } catch (Exception& e) {
        std::cerr << "Exception: " << e.displayText() << std::endl;
        return 1;
    }

    return 0;
}
