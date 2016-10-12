#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>

using namespace std;

class DataBase
{
public:
    DataBase();
    ~DataBase();

    operator sqlite3*() {return d;}

    bool open(const string &name);
    void close();

private:
    sqlite3 *d;

};

#endif // DATABASE_H
