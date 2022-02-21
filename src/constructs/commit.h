#ifndef COMMIT_H
#define COMMIT_H
#include <QObject>

enum CommitType {
    TYPE_UNKNOWN,
    TYPE_SIGNATURE,
    TYPE_CLAIM
};
const QString CommitTypeNames[] = {"Unknown", "Signature", "Claim"};

class Commit : public QObject
{
    Q_OBJECT
public:
    explicit Commit(CommitType type, QString address) {
        _type = type;
        _address = address;
    }
    bool operator==(const Commit& c) {
        if(c._address != _address) {
            return false;
        }
        if(c._type != _type) {
            return false;
        }
        return true;
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
