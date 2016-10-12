#ifndef QUERY_H
#define QUERY_H

#include <sqlite3.h>
#include <iostream>

using namespace std;

class Query
{
public:
    Query();
    ~Query();
    Query& operator=(const string &q);

    void connectDB(sqlite3 *dataBase);
    bool compile();
    template<typename t> bool bind(const string &msk, const t &txt);
    int getRow();
    template<typename t> t fetch(int col);
    void finalize();

private:
    sqlite3 *d;
    string *qs;
    sqlite3_stmt **stmt;
};

#endif // QUERY_H
