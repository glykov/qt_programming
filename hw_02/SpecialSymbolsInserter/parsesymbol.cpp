#include "parsesymbol.h"

ParseSymbol::ParseSymbol()
{
    symbolsMap.insert(QString("COPY"), QString("©"));
    symbolsMap.insert("PROM", "‰");
    symbolsMap.insert("RIGHT", "®");
    symbolsMap["EURO"] = "€";
    symbolsMap["RUB"] = "₽";
}

QString ParseSymbol::parse(QString inStr)
{
    QString outStr = "";

    int start = inStr.indexOf("#@");
    int stop = 0;
    int pos = 0;

    while (start != -1) {
        stop = inStr.indexOf("@", start + 2);

        if (stop != -1) {
            outStr.append(inStr.mid(pos, start - pos));
            pos = stop + 1;
            QString s = inStr.mid(start + 2, stop - start - 2);
            if (symbolsMap.contains(s)) {
                outStr.append(symbolsMap.value(s));
            }
        }

        start = inStr.indexOf("#@", stop + 1);
    }

    outStr.append(inStr.mid(pos));

    return outStr;
}
