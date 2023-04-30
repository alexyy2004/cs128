#include "db_table.hpp"

// const unsigned int kRowGrowthRate = 2;
void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
    if (col_descs_.size() == row_col_capacity_) {
        for (int id = 0; id < (int)next_unique_id_; id++) {
            void**& row = rows_.at(id);
            void** new_row = new void*[row_col_capacity_ + row_col_capacity_];
            for (int col = 0; col < (int)row_col_capacity_; col++) {
                void* row_col = row[col];
                std::string type;
                void* new_row_col = nullptr;
                switch (col_descs_.at(col).second){case DataType::kDouble:{double* temp = static_cast<double*>(row_col);if (temp != nullptr) {new_row_col = new double(*temp);delete temp;}break;}
                case DataType::kInt:{int* temp = static_cast<int*>(row_col);if (temp != nullptr) {new_row_col = new int(*temp);delete temp;}break;}
                case DataType::kString:{std::string* temp = static_cast<std::string*>(row_col);if (temp != nullptr) {new_row_col = new std::string(*temp);delete temp;}break;}
                default:
                    break;
                }
                new_row[col] = new_row_col;
            }
            delete[] row;
            rows_.at(id) = new_row;
        }
        row_col_capacity_ *= 2;
    }
    col_descs_.push_back(col_desc);
    for (int id = 0; id < (int)next_unique_id_; id++) {
        void**& row = rows_.at(id);
        switch (col_desc.second){
        case DataType::kDouble:{double* value = new double(0.0);row[col_descs_.size() - 1] = value;break;}
        case DataType::kInt:{int* value = new int(0);row[col_descs_.size() - 1] = value;break;}
        case DataType::kString:{
            std::string* value = new std::string("");
            row[col_descs_.size() - 1] = value;
            break;
        }default:   break;}
    }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
    if (col_idx >= col_descs_.size()) {throw std::out_of_range("Column index out of range.");}
    if (col_descs_.size() == 1 && !rows_.empty()) {throw std::runtime_error("Cannot delete the only column in the table.");}
    for (int id = 0; id < (int)next_unique_id_; id++) {if (rows_.contains(id)) {void** row = rows_.at(id);
            switch (col_descs_.at(col_idx).second) {
                case DataType::kDouble:delete static_cast<double*>(row[col_idx]);break;
                case DataType::kInt:delete static_cast<int*>(row[col_idx]);break;
                case DataType::kString:delete static_cast<std::string*>(row[col_idx]);break;default:break;
            }
        }
    }
    for (int id = 0; id < (int)next_unique_id_; id++) {
        if (rows_.contains(id)) {
            void** row = rows_.at(id);
            for (int col = col_idx + 1; col < (int)col_descs_.size(); col++) {
                switch (col_descs_.at(col).second) {
                    case DataType::kDouble: {double* temp = static_cast<double*>(row[col]);double* new_row_col = temp != nullptr ? new double(*temp) : new double(0.0);
                        delete temp;
                        row[col - 1] = new_row_col;break;
                    }
                    case DataType::kInt: {int* temp = static_cast<int*>(row[col]);int* new_row_col = temp != nullptr ? new int(*temp) : new int(0);
                        delete temp;
                        row[col - 1] = new_row_col;break;
                    }
                    case DataType::kString: {std::string* temp = static_cast<std::string*>(row[col]);std::string* new_row_col = temp != nullptr ? new std::string(*temp) : new std::string("");
                        delete temp;
                        row[col - 1] = new_row_col;break;
                    }
                    default:break;
                }
            }
        }
    }auto it = col_descs_.begin() + col_idx;col_descs_.erase(it);
}


void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
    if (col_data.size() != col_descs_.size()) {
        throw std::invalid_argument("Number of elements in initializer list does not match number of columns.");
    }
    void** new_row_data = new void*[row_col_capacity_];
    size_t col_idx = 0;
    for (std::string data : col_data) {
        auto data_type = col_descs_[col_idx].second;
        if (data_type == DataType::kString) {
            std::string* new_col_data = new std::string(data);
            new_row_data[col_idx] = new_col_data;
        } else if (data_type == DataType::kInt) {
            int* new_col_data = new int(std::stoi(data));
            new_row_data[col_idx] = new_col_data;
        } else if (data_type == DataType::kDouble) {
            double* new_col_data = new double(std::stod(data));
            new_row_data[col_idx] = new_col_data;
        }
        col_idx++;
    }
    rows_.insert({next_unique_id_, new_row_data});
    //rows_[next_unique_id_] = new_row_data;
    next_unique_id_++;
}




void DbTable::DeleteRowById(unsigned int id) {
    if (!rows_.contains(id)) {
        throw std::invalid_argument("aaa");
    }
    void** row = rows_.at(id);
    for (int i = 0; i < (int)col_descs_.size(); i++) {
        //void* row_col = row[i];
        switch (col_descs_.at(i).second)
        {
        case DataType::kDouble:
            delete static_cast<double*>(row[i]);
            break;
        case DataType::kInt:
            delete static_cast<int*>(row[i]);
            break;
        case DataType::kString:
            delete static_cast<std::string*>(row[i]);
            break;
        default:
            break;
        }
    }
    delete[] row;
    rows_.erase(rows_.find(id));
}

DbTable::DbTable(const DbTable& rhs) {
    next_unique_id_ = rhs.next_unique_id_;
    row_col_capacity_ = rhs.row_col_capacity_;
    col_descs_ = rhs.col_descs_;
    for (auto i : rhs.rows_) {
        rows_[i.first] = new void*[row_col_capacity_];
        for (size_t col = 0; col < col_descs_.size(); col++) {
            switch (col_descs_.at(col).second) {
            case DataType::kDouble: {
                rows_[i.first][col] = static_cast<void*>(new double(*(static_cast<double*>(i.second[col]))));
                break;
            }
            case DataType::kInt: {
                rows_[i.first][col] = static_cast<void*>(new int(*(static_cast<int*>(i.second[col]))));
                break;
            }
            case DataType::kString:{
                rows_[i.first][col] = static_cast<void*>(new std::string(*(static_cast<std::string*>(i.second[col]))));
                break;
            }
            default:
                break;
            }
        }
    }
}
DbTable& DbTable::operator=(const DbTable& rhs) {
    if (this == &rhs) {
        return *this;
    }
    for (int i = 0; i < (int)next_unique_id_; i++) {
        if (rows_.contains(i)) {
            DeleteRowById(i);
        }
    }
    next_unique_id_ = rhs.next_unique_id_;
    row_col_capacity_ = rhs.row_col_capacity_;
    col_descs_ = rhs.col_descs_;
    for (int i = 0; i < (int)rhs.next_unique_id_; i++) {
        if (rhs.rows_.contains(i)) {
            void** new_row = new void*[row_col_capacity_];
            void** rhs_row = rhs.rows_.at(i);
            for (int col = 0; col < (int)rhs.col_descs_.size(); col++) {
                switch (rhs.col_descs_.at(col).second){
                case DataType::kDouble:{if (rhs_row[col] == nullptr) {new_row[col] = nullptr;} else {double temp = *static_cast<double*>(rhs_row[col]);new_row[col] = new double(temp);}break;}
                case DataType::kInt:{if (rhs_row[col] == nullptr) {new_row[col] = nullptr;} else {int temp = *static_cast<int*>(rhs_row[col]);new_row[col] = new int(temp);}break;}
                case DataType::kString:{
                    if (rhs_row[col] == nullptr) {
                        new_row[col] = nullptr;
                    } else {
                        std::string temp = *static_cast<std::string*>(rhs_row[col]);
                        new_row[col] = new std::string(temp);
                    }
                    break;
                }
                default:
                    break;
                }
            }
            rows_.insert({i, new_row});
            //next_unique_id_++;
        }
    }
    return *this;
}

DbTable::~DbTable() {
    for (auto temp : rows_) {
        for (int i = 0; i < (int)col_descs_.size(); i++) {
            DataType type = col_descs_.at(i).second;
            if (type == DataType::kDouble) {
                delete static_cast<double*>(temp.second[i]);
            } else if (type == DataType::kInt) {
                delete static_cast<int*>(temp.second[i]);
            } else {
                delete static_cast<std::string*>(temp.second[i]);
            }
        }
        delete[] temp.second;
        temp.second = nullptr;
    }
    rows_.clear();
    //col_descs_.clear();
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
    for (unsigned i = 0; i < table.col_descs_.size(); i++) {
        os << table.col_descs_.at(i).first;
        switch (table.col_descs_.at(i).second)
        {
        case DataType::kDouble:
            os << "(double)";
            break;
        case DataType::kInt:
            os << "(int)";
            break;
        case DataType::kString:
            os << "(std::string)";
            break;
        default:
            break;
        }
        if(i != table.col_descs_.size() - 1) {
            os << ", ";
        }
    }
    os << "\n";
    for (unsigned i = 0; i < table.rows_.size(); i++) {
        void** row = table.rows_.at(i);
        for (unsigned col = 0; col < table.col_descs_.size(); col++) {
            switch (table.col_descs_.at(col).second) {
                case DataType::kDouble: os << *(static_cast<double*>(row[col]));break;
                case DataType::kInt:os << *(static_cast<int*>(row[col]));break;
                case DataType::kString:os << *(static_cast<std::string*>(row[col]));break;
                default:
                    break;
            }
            if (col != table.col_descs_.size() - 1) {os << ", ";}
        }
        if (i != table.rows_.size() - 1) {os << "\n";}
    }
    return os;
}