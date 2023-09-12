# BellintegratorTestTask

Step-by-step instructions to build the TCP server "Bellintegrator Test Task" application using the POCO library:

```markdown
# Building a TCP Server with POCO Library

These instructions will guide you through building a simple test TCP server using the POCO C++ library. The server will accept client connections on port 28888, reverse strings entered by clients, and handle lines exceeding 255 characters.

## Prerequisites

- C++ compiler (e.g., g++)
- POCO C++ libraries installed
  - You can download POCO from [here](https://pocoproject.org/download.html) and follow their installation instructions.

## Building the TCP Server

1. Create a new C++ source file for the server, e.g., `tcp_server.cpp`.

2. Copy and paste the following code into `tcp_server.cpp`:

   ```
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

               clientStream << "Reversed string: " << clientInput << std::endl;
               clientStream.flush();

               clientSocket.close();
           }
       } catch (Poco::Exception& e) {
           std::cerr << "Exception: " << e.displayText() << std::endl;
           return 1;
       }

       return 0;
   }
   ```

3. Compile the code using a C++ compiler that supports POCO and link against the POCO libraries:

   ```bash
   g++ -o tcp_server tcp_server.cpp -lPocoNet -lPocoUtil -lPocoFoundation
   ```

4. Run the compiled executable:

   ```bash
   ./tcp_server
   ```

The TCP server will now be running and listening on port 28888. It will accept client connections, reverse input strings, and handle lines exceeding 255 characters by truncating them.
```
