#ifndef COMMIT_H
#define COMMIT_H
#include <QObject>

enum CommitType {
    TYPE_UNKNOWN,
    TYPE_SIGNATURE,
    TYPE_DECISION,
    TYPE_CLAIM
};
const QString CommitTypeNames[] = {"Unknown", "Signature", "Decision", "Claim"};

class Commit : public QObject
{
    Q_OBJECT
public:
    explicit Commit(CommitType type, QString address) {
        _type = type;
        _address = address;
    }
    CommitType type() {return _type;}
    QString typeName() {return CommitTypeNames[_type];}
    virtual QString ID() {return _address;}
    ~Commit() {};
private:
    QString _address;
    CommitType _type;
signals:

};

#endif // COMMIT_H
