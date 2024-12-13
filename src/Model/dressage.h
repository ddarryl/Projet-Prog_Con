#ifndef DRESSAGE_H
#define DRESSAGE_H

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

class Dressage {
public:
    Dressage(int totalTaches) : totalTaches(totalTaches), tachesCompletees(0) {}

    // Add a task to the process
    void ajouterTache(const std::string& nom, const std::function<void()>& action) {
        taches.push_back({nom, action});
    }

    // Synchronize and execute all tasks
    void executerTaches() {
        std::vector<std::thread> threads;

        for (const auto& tache : taches) {
            threads.emplace_back([this, tache]() {
                executerTache(tache);
            });
        }

        for (auto& th : threads) {
            if (th.joinable()) {
                th.join();
            }
        }

        std::cout << "All tasks completed. The plate is ready!\n";
    }

private:
    struct Tache {
        std::string nom;
        std::function<void()> action;
    };

    int totalTaches;
    int tachesCompletees;
    std::vector<Tache> taches;
    std::mutex mutexTaches;
    std::condition_variable cvTaches;

    void executerTache(const Tache& tache) {
        {
            std::lock_guard<std::mutex> lock(mutexTaches);
            std::cout << "Starting task: " << tache.nom << "\n";
        }

        tache.action(); // Perform the action

        {
            std::lock_guard<std::mutex> lock(mutexTaches);
            tachesCompletees++;
            std::cout << "Completed task: " << tache.nom << "\n";
            cvTaches.notify_all();
        }

        attendreToutesTaches();
    }

    void attendreToutesTaches() {
        std::unique_lock<std::mutex> lock(mutexTaches);
        cvTaches.wait(lock, [this]() { return tachesCompletees >= totalTaches; });
    }
};

#endif // DRESSAGE_H