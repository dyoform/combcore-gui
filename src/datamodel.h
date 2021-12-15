#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <vector>
#include <QString>
#include <memory>
#include "construct.h"
#include "commit.h"

class DataModel
{
public:
    std::vector<std::unique_ptr<Construct>> constructs;
    std::vector<std::unique_ptr<Commit>> pending_commits;
    DataModel();
    void addConstruct(Construct* construct) {
        constructs.emplace_back(std::unique_ptr<Construct>(construct));
    }
    void addCommit(Commit* commit) {
        pending_commits.emplace_back(std::unique_ptr<Commit>(commit));
    }
};

#endif // DATAMODEL_H
