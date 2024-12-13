#ifndef COMPTOIR_SOCKET_H
#define COMPTOIR_SOCKET_H

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class ComptoirSocket {
public:
    explicit ComptoirSocket(int port);
    ~ComptoirSocket();

    void start();                              // Start the socket server
    void stop();                               // Stop the socket server
    void processRequests();                    // Handle incoming client requests
    void addItem(const std::string& item);     // Add an item to the queue
    std::string getItem();                     // Retrieve an item from the counter
    std::vector<std::string> getAllItems();    // Retrieve all items from the counter

private:
    int serverSocket;                          // Server socket descriptor
    int port;                                  // Port number
    std::queue<std::string> platsPrets;        // Queue for ready dishes
    std::mutex mutexComptoir;                  // Mutex for thread-safe queue access
    bool running;                              // Server running status
};

#endif // COMPTOIR_SOCKET_H