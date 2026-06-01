#include "splay_tree_api.h"
#include <iostream>
#include <string>

int main() {
    SplayTree<int, std::string> tree;
    
    tree.insert(10, "Успешно");
    tree.insert(1, "1");
    
    auto* val = tree.search(10);
    if (val) {
        std::cout << *val << std::endl;
    }
    
    std::cout << "Size: " << tree.size() << std::endl;
    
    return 0;
}
