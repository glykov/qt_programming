#ifndef PARSESYMBOL_H
#define PARSESYMBOL_H
#include <QString>
#include <QMap>

class ParseSymbol
{
public:
    ParseSymbol();
    QString parse(QString inStr);
private:
    QMap<QString, QString> symbolsMap;
};

#endif // PARSESYMBOL_H
