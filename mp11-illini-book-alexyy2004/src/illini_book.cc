#include "illini_book.hpp"
#include <fstream>
#include "utilities.hpp"
#include <queue>
#include <set>


// Your code here!
IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream ifs{people_fpath};
    std::vector<std::vector<std::string>> vec;
    for (std::string line; std::getline(ifs, line); line = "") {
        std::vector<std::string> temp = utilities::Split(line, ',');
        vec.push_back(temp);
    }
    for (unsigned int i = 0; i < vec.size(); i++) {
        nodes_.push_back(std::stoi(vec.at(i).at(0)));
    }
    std::ifstream ifsr{relations_fpath};
    std::vector<std::vector<std::string>> v;
    for (std::string line; std::getline(ifsr, line); line = "") {
        std::vector<std::string> temp = utilities::Split(line, ',');
        v.push_back(temp);
    }
    for (unsigned int i = 0; i < v.size(); i++) {
        int node_1 = std::stoi(v.at(i).at(0));
        int node_2 = std::stoi(v.at(i).at(1));
        std::string relation = v.at(i).at(2);
        if (graph_.contains(node_1)) {
            graph_[node_1].push_back(node_2);
        } else {
            std::vector<int> temp;
            temp.push_back(node_2);
            graph_[node_1] = temp;
        }
        if (graph_.contains(node_2)) {
            graph_[node_2].push_back(node_1);
        } else {
            std::vector<int> temp;
            temp.push_back(node_1);
            graph_[node_2] = temp;
        }
        std::pair<int, int> pair (node_1, node_2);
        relations_[pair] = relation;
    }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    // for (int i : nodes_) {
    //     std::cout << i << std::endl;
    // }
    // for (int i : nodes_) {
    //     std::cout << "node: " << std::endl;
    //     std::cout << i << std::endl;
    //     if (graph_.contains(i)) {
    //         for (int j : graph_.at(i)) {
    //             std::cout << j << std::endl;
    //         }
    //     }
    // }
    
    std::vector<int> queue;
    std::vector<int> visited;
    queue.push_back(uin_1);
    visited.push_back(uin_1);
    while(!queue.empty()) {
        int cur = queue.at(0);
        queue.erase(queue.begin());
        std::vector<int> neigh;
        if (graph_.contains(cur)) {
            neigh = graph_.at(cur);
        }
        for (int str : neigh) {
            if (std::find(visited.begin(), visited.end(), str) == visited.end()) {
                visited.push_back(str);
                queue.push_back(str);
            }
        }
    }
    for (int i : visited) {
        if (i == uin_2) {
            return true;
        }
    }
    return false;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::vector<int> queue;
    std::vector<int> visited;
    queue.push_back(uin_1);
    visited.push_back(uin_1);
    while(!queue.empty()) {
        int cur = queue.at(0);
        queue.erase(queue.begin());
        std::vector<int> neigh;
        if (graph_.contains(cur)) {
            neigh = graph_.at(cur);
        }
        for (int str : neigh) {
            std::pair<int, int> pair_1 (cur, str);
            std::pair<int, int> pair_2 (str, cur);
            std::string relation;
            if (relations_.contains(pair_1)) {
                relation = relations_.at(pair_1);
            }
            if (relations_.contains(pair_2)) {
                relation = relations_.at(pair_2);
            }
            if (std::find(visited.begin(), visited.end(), str) == visited.end() && relation == relationship) {
                visited.push_back(str);
                queue.push_back(str);
            }
        }
    }
    for (int i : visited) {
        if (i == uin_2) {
            return true;
        }
    }
    return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    if (!AreRelated(uin_1, uin_2)) {
        return -1;
    }
    std::vector<int> queue;
    std::vector<int> visited;
    std::map<int, int> distance;
    distance[uin_1] = 0;
    queue.push_back(uin_1);
    visited.push_back(uin_1);
    while(!queue.empty()) {
        int cur = queue.at(0);
        queue.erase(queue.begin());
        std::vector<int> neigh;
        if (graph_.contains(cur)) {
            neigh = graph_.at(cur);
        }
        for (int str : neigh) {
            if (std::find(visited.begin(), visited.end(), str) == visited.end()) {
                visited.push_back(str);
                queue.push_back(str);
                distance[str] = distance[cur] + 1;
            }
        }
    }
    return distance[uin_2];
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    if (!AreRelated(uin_1, uin_2, relationship)) {
        return -1;
    }
    std::vector<int> queue;
    std::vector<int> visited;
    std::map<int, int> distance;
    distance[uin_1] = 0;
    queue.push_back(uin_1);
    visited.push_back(uin_1);
    while(!queue.empty()) {
        int cur = queue.at(0);
        queue.erase(queue.begin());
        std::vector<int> neigh;
        if (graph_.contains(cur)) {
            neigh = graph_.at(cur);
        }
        for (int str : neigh) {
            std::pair<int, int> pair_1 (cur, str);
            std::pair<int, int> pair_2 (str, cur);
            std::string relation;
            if (relations_.contains(pair_1)) {
                relation = relations_.at(pair_1);
            }
            if (relations_.contains(pair_2)) {
                relation = relations_.at(pair_2);
            }
            if (std::find(visited.begin(), visited.end(), str) == visited.end() && relation == relationship) {
                visited.push_back(str);
                queue.push_back(str);
                distance[str] = distance[cur] + 1;
            }
        }
    }
    return distance[uin_2];
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::vector<int> result;
    std::queue<int> queue;
    std::set<int> visited;
    std::map<int, int> distance;
    distance[uin] = 0;
    queue.push(uin);
    visited.insert(uin);
    while(!queue.empty()) {
        int cur = queue.front();
        queue.pop();
        std::vector<int> neigh;
        if (graph_.contains(cur)) {
            neigh = graph_.at(cur);
        }
        for (int str : neigh) {
            if (visited.count(str) == 0) {
                visited.insert(str);
                queue.push(str);
                distance[str] = distance[cur] + 1;
            }
        }
    }
    for (int i : nodes_) {
        if (distance.contains(i)) {
            if (distance[i] == n) {
                result.push_back(i);
            }
        }
    }
    return result;
}

size_t IlliniBook::CountGroups() const {
    unsigned int count = 0;
    std::vector<int> to_visit = nodes_;
    std::vector<int> visited;
    for (unsigned int i = 0; i < to_visit.size(); i++) {
        int cur = to_visit.at(i);
        if (std::find(visited.begin(), visited.end(), cur) == visited.end()) {
        //BFS start
        std::vector<int> queue;
        queue.push_back(cur);
        visited.push_back(cur);
        while(!queue.empty()) {
            int cur = queue.at(0);
            queue.erase(queue.begin());
            std::vector<int> neigh;
            if (graph_.contains(cur)) {
                neigh = graph_.at(cur);
            }
            for (int str : neigh) {
                if (std::find(visited.begin(), visited.end(), str) == visited.end()) {
                    visited.push_back(str);
                    queue.push_back(str);
                }
            }
        }
        //BFS end
        visited.push_back(cur);
        count += 1;
        }
    }
    return count;
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::map<int, std::vector<int>> graph_temp = graph_;
    std::map<std::pair<int, int>, std::string> relations_temp = relations_;
    for (auto const& temp : relations_) {
        if (temp.second != relationship) {
            std::pair<int, int> key = temp.first;
            relations_temp.erase(key);
        }
    }
    // for (auto const& temp : relations_temp) {
    //     std::cout << temp.first.first << "," << temp.first.second << ":" << temp.second << std::endl;
    // }
    for (auto const& temp : graph_temp) {
        int cur = temp.first;
        for (unsigned int i = 0; i < temp.second.size(); i++) {
            int str = temp.second.at(i);
            std::pair<int, int> pair_1 (cur, str);
            std::pair<int, int> pair_2 (str, cur);
            if (!relations_temp.contains(pair_1) && !relations_temp.contains(pair_2)) {
                graph_temp.at(cur).erase(graph_temp.at(cur).begin() + i);
                i--;
            }
        }
    }
    // for (auto const& temp : graph_temp) {
    //     std::cout << temp.first << ":" << std::endl;
    //     for (unsigned int i = 0; i < temp.second.size(); i++) {
    //         std::cout << temp.second.at(i) << " " ;
    //     }
    //     std::cout << "\n";
    // }
    unsigned int count = 0;
    std::vector<int> to_visit = nodes_;
    std::vector<int> visited;
    for (unsigned int i = 0; i < to_visit.size(); i++) {
        int cur = to_visit.at(i);
        if (std::find(visited.begin(), visited.end(), cur) == visited.end()) {
            //BFS start
            std::vector<int> queue;
            queue.push_back(cur);
            visited.push_back(cur);
            while(!queue.empty()) {
                int cur = queue.at(0);
                queue.erase(queue.begin());
                std::vector<int> neigh;
                if (graph_temp.contains(cur)) {
                    neigh = graph_temp.at(cur);
                }
                for (int str : neigh) {
                    if (std::find(visited.begin(), visited.end(), str) == visited.end()) {
                        visited.push_back(str);
                        queue.push_back(str);
                    }
                }
            }
            //BFS end
            visited.push_back(cur);
            count += 1;
        }
    }
    return count;
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::map<int, std::vector<int>> graph_temp = graph_;
    std::map<std::pair<int, int>, std::string> relations_temp = relations_;
    for (auto const& temp : relations_) {
        if (std::find(relationships.begin(), relationships.end(), temp.second) == relationships.end()) {
            std::pair<int, int> key = temp.first;
            relations_temp.erase(key);
        }
    }
    // for (auto const& temp : relations_temp) {
    //     std::cout << temp.first.first << "," << temp.first.second << ":" << temp.second << std::endl;
    // }
    for (auto const& temp : graph_temp) {
        int cur = temp.first;
        for (unsigned int i = 0; i < temp.second.size(); i++) {
            int str = temp.second.at(i);
            std::pair<int, int> pair_1 (cur, str);
            std::pair<int, int> pair_2 (str, cur);
            if (!relations_temp.contains(pair_1) && !relations_temp.contains(pair_2)) {
                graph_temp.at(cur).erase(graph_temp.at(cur).begin() + i);
                i--;
            }
        }
    }
    // for (auto const& temp : graph_temp) {
    //     std::cout << temp.first << ":" << std::endl;
    //     for (unsigned int i = 0; i < temp.second.size(); i++) {
    //         std::cout << temp.second.at(i) << " " ;
    //     }
    //     std::cout << "\n";
    // }
    unsigned int count = 0;
    std::vector<int> to_visit = nodes_;
    std::vector<int> visited;
    for (unsigned int i = 0; i < to_visit.size(); i++) {
        int cur = to_visit.at(i);
        if (std::find(visited.begin(), visited.end(), cur) == visited.end()) {
            //BFS start
            std::vector<int> queue;
            queue.push_back(cur);
            visited.push_back(cur);
            while(!queue.empty()) {
                int cur = queue.at(0);
                queue.erase(queue.begin());
                std::vector<int> neigh;
                if (graph_temp.contains(cur)) {
                    neigh = graph_temp.at(cur);
                }
                for (int str : neigh) {
                    if (std::find(visited.begin(), visited.end(), str) == visited.end()) {
                        visited.push_back(str);
                        queue.push_back(str);
                    }
                }
            }
            //BFS end
            visited.push_back(cur);
            count += 1;
        }
    }
    return count;
}