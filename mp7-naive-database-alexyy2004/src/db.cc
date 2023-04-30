#include "db.hpp"

void Database::CreateTable(const std::string& table_name) {
    //DbTable* table = new DbTable();
    //tables_.insert({table_name, table});
    tables_[table_name] = new DbTable();
}
void Database::DropTable(const std::string& table_name) {
    if (!tables_.contains(table_name)) {
        throw std::invalid_argument("aaa");
    }
    DbTable* table = tables_.at(table_name);
    delete table;
    tables_.erase(table_name);
}
DbTable& Database::GetTable(const std::string& table_name) {
    DbTable& temp = *tables_[table_name];
    return temp;
}

Database::Database(const Database& rhs) {
    /*
    std::map<std::string, DbTable*>::iterator it;
    std::map<std::string, DbTable*> new_tables = rhs.tables_;
    for (it = new_tables.begin(); it != new_tables.end(); it++) {
        DbTable temp;
        temp = *(new_tables.at(it->first));
        tables_.insert({it->first, &temp});
    }
    */
    for (auto table : rhs.tables_) {
        DbTable* temp = new DbTable(*table.second);
        tables_.insert({table.first, temp});
    }
}
Database& Database::operator=(const Database& rhs) {
    if (this == &rhs) {
        return *this;
    }
    /*
    std::map<std::string, DbTable*>::iterator it;
    for (it = tables_.begin(); it != tables_.end(); it++) {
        DropTable(it->first);
    }
    std::map<std::string, DbTable*> new_tables = rhs.tables_;
    for (it = new_tables.begin(); it != new_tables.end(); it++) {
        DbTable temp;
        temp = *(rhs.tables_.at(it->first));
        tables_.insert({it->first, &temp});
    }
    */
    for (auto table : tables_) {
        delete table.second;
    }
    tables_.clear();
    for (auto table : rhs.tables_) {
        DbTable* temp = new DbTable(*table.second);
        tables_.insert({table.first, temp});
        //delete temp;
    }
    return *this;
}
Database::~Database() {
    /*
    std::map<std::string, DbTable*>::iterator it;
    for (it = tables_.begin(); it != tables_.end(); it++) {
        DropTable(it->first);
    }
    */
    for (auto temp : tables_) {
        delete temp.second;
    }
    tables_.clear();
}
std::ostream& operator<<(std::ostream& os, const Database& db) {
    std::cout << db.tables_.size() << std::endl;
    return os;
}