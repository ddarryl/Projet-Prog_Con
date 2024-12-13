#include "ipc_utils.h"
#include <iostream>
#include <sys/shm.h>
#include <cstring>
#include <unistd.h>

// File de messages
int createMessageQueue(key_t key) {
    int msgQueueId = msgget(key, IPC_CREAT | 0666);
    if (msgQueueId == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    return msgQueueId;
}

void sendMessage(int msgQueueId, const std::string& content, long type) {
    Message msg{};
    msg.type = type;
    strncpy(msg.data, content.c_str(), sizeof(msg.data) - 1);
    if (msgsnd(msgQueueId, &msg, sizeof(msg.data), 0) == -1) {
        perror("msgsnd");
    }
}

std::string receiveMessage(int msgQueueId, long type) {
    Message msg{};
    if (msgrcv(msgQueueId, &msg, sizeof(msg.data), type, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    return std::string(msg.data);
}

void deleteMessageQueue(int msgQueueId) {
    if (msgctl(msgQueueId, IPC_RMID, nullptr) == -1) {
        perror("msgctl (remove)");
    }
}

// Mémoire partagée
int createSharedMemory(key_t key, size_t size) {
    int shmId = shmget(key, size, IPC_CREAT | 0666);
    if (shmId == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    return shmId;
}

void* attachSharedMemory(int shmId) {
    void* addr = shmat(shmId, nullptr, 0);
    if (addr == (void*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    return addr;
}

// Sémaphores
int createSemaphore(key_t key) {
    int semId = semget(key, 1, IPC_CREAT | 0666);
    if (semId == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    semctl(semId, 0, SETVAL, 1); // Initialize semaphore to 1
    return semId;
}

void semaphoreWait(int semId) {
    struct sembuf sb = {0, -1, 0};
    if (semop(semId, &sb, 1) == -1) {
        perror("semop (wait)");
        exit(EXIT_FAILURE);
    }
}

void semaphoreSignal(int semId) {
    struct sembuf sb = {0, 1, 0};
    if (semop(semId, &sb, 1) == -1) {
        perror("semop (signal)");
        exit(EXIT_FAILURE);
    }
}

void deleteSemaphore(int semId) {
    if (semctl(semId, 0, IPC_RMID) == -1) {
        perror("semctl (remove)");
    }
}
