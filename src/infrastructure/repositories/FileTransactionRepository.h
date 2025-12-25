#ifndef _FILETRANSACTIONREPOSITORY_H_
#define _FILETRANSACTIONREPOSITORY_H_

#include "../../domain/entities/Transaction.h"
#include "../../domain/repositories/ITransactionRepository.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <memory>
using std::shared_ptr, std::make_shared;
namespace filesystem = std::filesystem;

class FileTransactionRepository : public ITransactionRepository {
private:
    string _folder;
    
private:
    string getPath(const string& id) const;
    shared_ptr<Transaction> createTransactionByType(const string& type);
    shared_ptr<Transaction> loadFromFile(const string& path);

public:
    FileTransactionRepository(const string& folder);

public:
    void save(shared_ptr<Transaction> tx) override;
    vector<shared_ptr<Transaction>> findByUserId(const string& userId) override;
};

#endif