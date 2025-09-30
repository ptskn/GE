//
// Created by ptskn on 29/09/2025.
//

#ifndef SAASCORE_TRANSACTIONMANAGER_H
#define SAASCORE_TRANSACTIONMANAGER_H
#include <string>
#include <stdexcept>
#include <functional>
class TransactionManager {
public:
    void executeInTransaction(std::function<void()> action) {
        std::string tempFile = "data.tmp";
        std::string finalFile = "data.json";

        try {
            // 1. Écrire dans un fichier temporaire
            action();  // Exécute la logique de stockage (ex: sauvegarde JSON)

            // 2. Remplacer le fichier final (atomique sur POSIX)
            if (std::rename(tempFile.c_str(), finalFile.c_str()) != 0) {
                throw std::runtime_error("Échec du commit transactionnel");
            }
        } catch (...) {
            // Rollback: supprimer le fichier temporaire
            std::remove(tempFile.c_str());
            throw;
        }
    }
};



#endif //SAASCORE_TRANSACTIONMANAGER_H