#ifndef _FILERESETPASSWORDREPOSITORY_H_
#define _FILERESETPASSWORDREPOSITORY_H_

#include "../../domain/repositories/IResetPasswordRepository.h"


class FileResetPasswordRepository : public IResetPasswordRepository {
private:
    string _folder;
    string getPath(const string& id) const;

public:
    FileResetPasswordRepository(const string& folderPath);

public:
    void save(const ResetPasswordToken& token) override;

    ResetPasswordToken findById(const string& tokenId) override;
    vector<ResetPasswordToken> findByUserId(const string& userId) override;

    bool remove(const string& tokenId) override;
    
    bool exists(const string& tokenId) override;
};

#endif