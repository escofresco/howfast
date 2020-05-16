//
//  TrieNodeUnitTest.cpp
//  why
//
//  Created by Jonasz Karwacki on 5/12/20.
//  Copyright © 2020 Jonasz Karwacki. All rights reserved.
//

#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#include "TrieNodeUnitTest.hpp"
#include "TrieNode.hpp"

void testTrieNodeInit() {
    //    │       ┌── 7
    //    │   ┌── 3
    //    │   │   └── 6
    //    └── 1
    //        │   ┌── 5
    //        └── 2
    //            └── 4
    TrieNode* leftleft = new TrieNode(4, nullptr, nullptr);
    TrieNode* leftright = new TrieNode(5, nullptr, nullptr);
    TrieNode* rightleft = new TrieNode(6, nullptr, nullptr);
    TrieNode* rightright = new TrieNode(7, nullptr, nullptr);
    TrieNode* left = new TrieNode(2, leftleft, leftright);
    TrieNode* right = new TrieNode(3, rightleft, rightright);
    TrieNode* root = new TrieNode(1, left, right);
    
    assert(leftleft -> key == 4);
    assert(leftleft -> left == nullptr);
    assert(leftleft -> right == nullptr);

    assert(leftright -> key == 5);
    assert(leftright -> left == nullptr);
    assert(leftright -> right == nullptr);
    
    assert(rightleft -> key == 6);
    assert(rightleft -> left == nullptr);
    assert(rightleft -> right == nullptr);
    
    assert(rightright -> key == 7);
    assert(rightright -> left == nullptr);
    assert(rightright -> right == nullptr);

    assert(left -> key == 2);
    assert(left -> left -> key == 4);
    assert(left -> right -> key == 5);

    assert(right -> key == 3);
    assert(right -> left -> key == 6);
    assert(right -> right -> key == 7);
    
    assert(root -> key == 1);
    assert(root -> left -> key == 2);
    assert(root -> right -> key == 3);
}

void runNodeTests() {
    testTrieNodeInit();
}
