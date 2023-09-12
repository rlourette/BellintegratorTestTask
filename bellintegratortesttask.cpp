#include <iostream>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Exception.h>

using namespace Poco::Net;
using namespace Poco;

int main() {
    try {
        ServerSocket serverSocket(28888);
        std::cout << "Server started on port 28888." << std::endl;

        while (true) {
            StreamSocket clientSocket = serverSocket.acceptConnection();
            SocketStream clientStream(clientSocket);

            clientStream << "\"Welcome to POCO TCP server. Enter you(sic) string:\"" << std::endl;
            clientStream.flush();

            std::string clientInput;
            std::getline(clientStream, clientInput);

            if (clientInput.length() > 255) {
                clientInput = clientInput.substr(0, 255);
            }

            // Reverse the string
            std::reverse(clientInput.begin(), clientInput.end());

            clientStream << "\nReversed string: " << clientInput << std::endl;
            clientStream.flush();

            clientSocket.close();
        }
    } catch (Poco::Exception& e) {
        std::cerr << "Exception: " << e.displayText() << std::endl;
        return 1;
    }

    return 0;
}