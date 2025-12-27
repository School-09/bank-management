#ifndef _FILETRANSACTIONREPOSITORY_H_
#define _FILETRANSACTIONREPOSITORY_H_

#include "../../domain/repositories/ITransactionRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;


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