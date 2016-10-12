#include "query.h"

Query::Query() : d(NULL)
{

}

Query& Query::operator =(const string &q)
{
    qs = new string(q);
    return *this;
}

void Query::connectDB(sqlite3 *dataBase)
{
    d = dataBase;
}

bool Query::compile()
{
    if(!d)
    {
        cerr<<"Error: No database connected!"<<endl;
        return false;
    }
    stmt = new sqlite3_stmt*;
    if(sqlite3_prepare_v2(d, qs->c_str(), -1, &(*stmt), 0) != SQLITE_OK)
    {
        cerr<<"Failed to compile Statement!"<<endl;
        return false;
    }
    return true;
}

template<>
bool Query::bind<string>(const string &msk, const string &txt)
{
    int i = sqlite3_bind_parameter_index(*stmt, msk.c_str());
    sqlite3_bind_text(*stmt, i, txt.c_str(), -1, NULL);
    return true;
}

template<>
bool Query::bind<int>(const string &msk, const int &x)
{
    int i = sqlite3_bind_parameter_index(*stmt, msk.c_str());
    sqlite3_bind_int(*stmt, i, x);
    return true;
}

int Query::getRow()
{
    int state = SQLITE_OK;
    state = sqlite3_step(*stmt);
    return state;
}

template<>
string Query::fetch<string>(int col)
{
    char *s;
    if((s = (char*)(sqlite3_column_text(*stmt, col))))
        return s;

    return "";
}
template<>
int Query::fetch<int>(int col)
{
    return sqlite3_column_int(*stmt, col);
}

void Query::finalize()
{
    sqlite3_finalize(*stmt);
}

Query::~Query()
{
    delete qs;
}
