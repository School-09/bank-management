#ifndef _FILE_RESET_PASSWORD_REPOSITORY_H_
#define _FILE_RESET_PASSWORD_REPOSITORY_H_

#include "../../domain/repositories/IResetPasswordRepository.h"

class FileResetPasswordRepository : public IResetPasswordRepository {
private:
    string _folder;

private:
    string getPath(const string& id) const;

public:
    FileResetPasswordRepository(const string& folderPath);

public:
    void save(const ResetPasswordToken& token) override;
    bool remove(const string& tokenId) override;
    bool exists(const string& tokenId) override;

    ResetPasswordToken findByTokenId(const string& tokenId) override;
    vector<ResetPasswordToken> findByUserId(const string& userId) override;
    
};

#endif