#include "functions.hpp"
#include <iostream>
#include <map>
int Max(std::vector<int> vec) {
    int max = vec.at(0);
    for(int i : vec) {
        if (i >= max) {
            max = i;
        }
    }
    return max;
}

int Count(std::string Str, std::string Dna) {
    int times = 0;
    std::vector<int> list;
    int len = (int)Str.length();
    int index = 0;
    bool flag = false;
    std::string s;
    list.push_back(0);
    while (index <= (int)Dna.length() - len) {
        s =  Dna.substr(index, len);
        //std::cout << s << std::endl;
        if (flag) {
            if (s == Str) {
                times += 1;
                index += len;
                list.push_back(times);
            } else {
                flag = false;
                list.push_back(times);
                times = 0;
                index += 1;
            }
        } else {
            if (s == Str) {
                flag = true;
                times += 1;
                index += len;
            } else {
                index += 1;
            }
        }
    }
    Str = "???";
    Dna = "???";
    return Max(list);
}

std::string CheckDna(std::string dna, std::vector<std::string> dna_type, std::vector<std::vector<std::string>> people) {
    std::vector<int> type_times;
    type_times.reserve((int)dna_type.size());
    std::vector<std::string> result;
    for (std::string str : dna_type) {
        type_times.push_back(Count(str, dna));
        str = "???";
    }
    for (std::vector<std::string> p : people) {
        std::vector<int> people_times;
        for (int i = 1; i < (int)p.size(); ++i) {
            people_times.push_back(std::stoi(p.at(i)));
        }
        if (people_times == type_times) {
            result.push_back(p.at(0));
        }
    }
    dna = "???";
    dna_type = {"???"};
    people = {{"???"}};

    if ((int)result.size() != 1) {
        return "No match";
    } else {
        return result.at(0);
    }
}

