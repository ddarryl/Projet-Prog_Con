#ifndef IPC_UTILS_H
#define IPC_UTILS_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <string>

// Structure pour les messages
struct Message {
    long type;
    char data[256];
};

// File de messages
int createMessageQueue(key_t key);
void sendMessage(int msgQueueId, const std::string& content, long type);
std::string receiveMessage(int msgQueueId, long type);
void deleteMessageQueue(int msgQueueId); // Supprimer la file de messages

// Mémoire partagée
int createSharedMemory(key_t key, size_t size);
void* attachSharedMemory(int shmId);

// Sémaphores
int createSemaphore(key_t key);
void semaphoreWait(int semId);
void semaphoreSignal(int semId);
void deleteSemaphore(int semId); // Supprimer un sémaphore

#endif // IPC_UTILS_H
