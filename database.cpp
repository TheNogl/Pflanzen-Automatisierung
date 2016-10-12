#include "database.h"

DataBase::DataBase() : d(NULL)
{

}

bool DataBase::open(const string &name)
{
    if(sqlite3_open(name.c_str(), &d) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(d));
        sqlite3_close(d);
        return false;
    }
    return true;
}

void DataBase::close()
{
    sqlite3_close(d);
}

DataBase::~DataBase()
{
    sqlite3_close(d);
}
