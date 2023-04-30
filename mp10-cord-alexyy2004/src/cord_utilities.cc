#include "cord_utilities.hpp"
SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord, const SharedPointer<Cord>& right_cord) {
    if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
        throw std::invalid_argument("aaa");
    }
    Cord* cord = new Cord();
    cord->data_ = nullptr;
    cord->left_ = left_cord;
    cord->right_ = right_cord;
    cord->length_ = left_cord.Get()->length_ + right_cord.Get()->length_;
    SharedPointer<Cord> result = SharedPointer<Cord>{cord};
    return result;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord, unsigned int lower_idx, unsigned int upper_idx) {
    if (lower_idx >= upper_idx || lower_idx < 0 || upper_idx > curr_cord.Get()->Length()) {
        throw std::invalid_argument("aaa");
    }
    if (lower_idx == 0 && upper_idx == curr_cord.Get()->Length()) {
        return curr_cord;
    }
    if (curr_cord.Get()->Left().Get() == nullptr) {
        Cord* cord = new Cord(curr_cord.Get()->Data().substr(lower_idx, upper_idx - lower_idx));
        return SharedPointer<Cord>{cord};
    }
    if (lower_idx >= curr_cord.Get()->Left().Get()->Length() && upper_idx > curr_cord.Get()->Left().Get()->Length()) {
        return SubString(curr_cord.Get()->Right(), lower_idx - curr_cord.Get()->Left().Get()->Length(), upper_idx - curr_cord.Get()->Left().Get()->Length());
    }
    if (lower_idx < curr_cord.Get()->Left().Get()->Length() && upper_idx <= curr_cord.Get()->Left().Get()->Length()) {
        return SubString(curr_cord.Get()->Left(), lower_idx, upper_idx);
    }
    if (lower_idx < curr_cord.Get()->Left().Get()->Length() && upper_idx > curr_cord.Get()->Left().Get()->Length()) {
        SharedPointer<Cord> left = SubString(curr_cord.Get()->Left(), lower_idx, curr_cord.Get()->Left().Get()->Length());
        SharedPointer<Cord> right = SubString(curr_cord.Get()->Right(), 0, upper_idx - curr_cord.Get()->Left().Get()->Length());
        return ConcatCords(left, right);
    }
    return nullptr;
}

