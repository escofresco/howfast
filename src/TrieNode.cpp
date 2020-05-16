//
//  TrieNode.cpp
//  why
//
//  Created by Jonasz Karwacki on 5/12/20.
//  Copyright © 2020 Jonasz Karwacki. All rights reserved.
//
#include <vector>
#include <iostream>
#include "TrieNode.hpp"


TrieNode::TrieNode(int key, TrieNode* left, TrieNode* right, bool isLeaf) {
    TrieNode::key = key;
    TrieNode::isLeaf = isLeaf;
    TrieNode::left = left;
    TrieNode::right = right;
}

void trimLeftTrailingSpaces(std::string &input) {
    // ~> Taken from Leetcode's Binary Tree playground <~ //
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(std::string &input) {
    // ~> Taken from Leetcode's Binary Tree playground <~ //
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

void TrieNode::prettyPrint() {
    // ~> Adapted from Leetcode's Binary Tree playground snippet <~ //
    std::vector<std::tuple<TrieNode*, std::string, bool>> stack;
    stack.push_back(std::make_tuple(this, "", true));
    
    while (!stack.empty()) {
        std::tuple<TrieNode*, std::string, bool> curTuple = stack.back();
        stack.pop_back();
        TrieNode* node = std::get<0>(curTuple);
        std::string prefix = std::get<1>(curTuple);
        bool isLeft = std::get<2>(curTuple);
    
        if (node) {
            if (node -> left)
                stack.push_back(std::make_tuple(node -> left, prefix + (isLeft ? "    " : "│   "), true));
            
            stack.push_back(make_tuple(nullptr, prefix + (isLeft ? "└── " : "┌── ") + std::to_string(node -> key) + "\n", false));
            
            if (node -> right)
                stack.push_back(std::make_tuple(node -> right, prefix + (isLeft ? "│   " : "    "), false));
        } else
            std::cout << prefix;
    }
}
