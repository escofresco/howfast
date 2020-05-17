//
//  TrieNode.hpp
//  why
//
//  Created by Jonasz Karwacki on 5/12/20.
//  Copyright © 2020 Jonasz Karwacki. All rights reserved.
//

#ifndef TrieNode_hpp
#define TrieNode_hpp

#include <stdio.h>
class TrieNode {
public:
    int key;
    
    // Property indicated by if node is at bottom of tree (it may still have a left and right)
    bool isLeaf;
    
    // If isLeaf is true, then this stores the node's predecessor. Else the node is a summary
    // (internal) node, which means if it would be missing a left child, then it stores
    // the smallest leaf in its right subtree.
    TrieNode* left;
    
    // If isLeaf is true, then this stores the node's successor. Else the node is a summary
    // (internal) node, which means if it would be missing a right child, then it stores
    // the largest leaf in its left subtree.
    TrieNode* right;
    
    //TrieNode(int key);
    /**
     * Constructs a TrieNode.
     *
     * @param key The value of the current node.
     * @param left Left child.
     * @param right Right child.
     */
    TrieNode(int key, TrieNode* left = nullptr, TrieNode* right = nullptr, bool isLeaf = true);
    
    
    /**
     * Method to deep copy the object.
     *
     * @return Deep copy of node.
     */
    TrieNode* deepCopy();
    
    /**
     * Method for printing TrieNode and its children to console.
     */
    void prettyPrint();
};
#endif /* TrieNode_hpp */
