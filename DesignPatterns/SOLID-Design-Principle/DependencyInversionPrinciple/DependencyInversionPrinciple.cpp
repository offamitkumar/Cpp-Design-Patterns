//
// Created by Amit Kumar on 27/09/23
//

#include "vector"
#include "iostream"
#include "utility"

using namespace std;

class TreeIterator {
public:
    virtual vector<int> get_friends(int node) const = 0;
};

class Tree : public TreeIterator {
    vector<pair<int,int>>edges;
public:

    void add_edge(int u, int v) {
        edges.emplace_back(u,v);
        edges.emplace_back(v,u);
    }

    vector<int> get_friends(int node) const {
        vector<int> result;
        for (auto &[u,v]: edges) {
            if (u == node) {
                result.emplace_back(v);
            }
        }
        return result;
    }
};

class TreeTraversal {
public:

    static void print_friends(const TreeIterator& tree, int node) {
        for (auto &itr: tree.get_friends(node)) {
            cout << node << " is connected with " << itr << endl;
        }
    }

};

int main() {
    Tree tree;
    tree.add_edge(1,2);
    tree.add_edge(1,3);
    tree.add_edge(1,4);

    TreeTraversal::print_friends(tree, 1);
    return 0;
}