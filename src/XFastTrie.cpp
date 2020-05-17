//
//  XFastTrie.cpp
//  why
//
//  Created by Jonasz Karwacki on 5/12/20.
//  Copyright © 2020 Jonasz Karwacki. All rights reserved.
//
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "XFastTrie.hpp"
#include "TrieNode.hpp"


XFastTrie::XFastTrie(int universeSize) {
    XFastTrie::universeSize = universeSize;
    XFastTrie::wordSize = numberOfBitsInWord(universeSize);
    levelSearchStructure.assign(wordSize + 1, std::unordered_map<int, TrieNode*>());
    levelSearchStructure[0][0] = new TrieNode(NULL); // Root of tree is always empty.
}


int XFastTrie::numberOfBitsInWord(int word) {
    // Calculate number of bits in word
    int nBits = 0;

    while (word > 0) {
        word >>= 1;
        nBits++;
    }
    return nBits;
}

TrieNode* XFastTrie::find(int key) {
    if (levelSearchStructure.empty() || levelSearchStructure[0].count(key) == 0)
        // key doesn't exist
        return nullptr;
    return levelSearchStructure[0][key];
}

TrieNode* XFastTrie::predecessor(int key) {
    TrieNode* nearestLeafPredecessor = nearestLeaf(key);
    
    if (!nearestLeafPredecessor)
        return nullptr;
    
    if (nearestLeafPredecessor -> key > key)
        return nearestLeafPredecessor -> left;
    return nearestLeafPredecessor;
}

TrieNode* XFastTrie::successor(int key) {
    TrieNode* nearestLeafSuccessor = nearestLeaf(key);
    
    if (!nearestLeafSuccessor)
        return nullptr;
    
    if (nearestLeafSuccessor -> key < key)
        return nearestLeafSuccessor -> right;
    return nearestLeafSuccessor;
}

void XFastTrie::insert(int key) {
}

void XFastTrie::deleteKey(int key) {
}

std::pair<int, TrieNode*> XFastTrie::nearestAncestor(int key) {
    if (levelSearchStructure.empty())
        return std::make_pair(NULL, nullptr);
    TrieNode* ancestorNode = root;
    int ancestorLevel = -1;
    int lo = 0;
    int hi = wordSize;
    
    while (lo <= hi) {
        int level = (lo + hi) >> 1;
        int prefix = key >> (wordSize - level - 1); // Prefix is the first level bits of key
        
        if (levelSearchStructure[level].find(prefix) == levelSearchStructure[level].end()) {
            //~> Prefix wasn't found at current level
            // look farther up the tree
            hi = level - 1;
        } else {
            //~> Prefix exists in current level
            // update ancestorLevel and ancestorNode
            ancestorNode = levelSearchStructure[level].at(prefix);
            ancestorLevel = level;
            
            // look farther down the tree
            lo = level + 1;
        }
    }
    return std::make_pair(ancestorLevel, ancestorNode);
}

TrieNode* XFastTrie::nearestLeaf(int key) {
    std::pair<int, TrieNode*> levelNodePair = nearestAncestor(key);
    int level = levelNodePair.first;
    TrieNode* ancestor = levelNodePair.second;
    
    if (ancestor -> isLeaf)
        // Ancestor of key is leaf because key existing exactly in tree
        return ancestor;
    
    // Direction is left if key was in the right subtree, else direction is right
    int direction = key >> (wordSize - level - 2) & 1;
    
    // Descendent will either be the largest value in the left subtree or smallest
    // value in the right subtree
    TrieNode* descendant = direction == 0 ? ancestor -> left : ancestor -> right;
    
    if (descendant == nullptr) 
        // This happens when there's nothing left or right of ancestor
        return nullptr;
    
    // ~> Check that descendent is the nearest leaf. It should definitely be a leaf, but
    //    we may need to move left or right by one node in the doubly-linked list of leaves
    //    to get the nearest one.
    // Check that there isn't a node to the left or right of descendent that is closer
    // to key
    TrieNode* candidate = direction == 0 ? descendant -> left : descendant -> right;
    
    // Descendant is the nearest leaf if candidate is empty or descendant's value is closer
    // to key than candidate's value
    if (candidate == nullptr || abs(descendant -> key - key) < abs(ancestor -> key - key))
        return descendant;
    return candidate;
}

void XFastTrie::prettyPrint() {
    // ~> Create a new tree of linked TrieNodes so TrieNode::prettyPrint() can be used
    int level; // Current level in XFast Tree being visited
    // Store nodes that are being updated
    TrieNode* newRoot = new TrieNode(NAN);
    std::vector<TrieNode*> lastLevel = {newRoot};
    std::vector<TrieNode*> curLevel;
    
    for (level = 1; level < wordSize; level++) {
        int levelUniverseSize = pow(2, level); // Max number stored in level

        for (int i = 0; i < levelUniverseSize; i++) {
            int nodeVal = levelSearchStructure[level].count(i) > 0 ? levelSearchStructure[level][i] -> key : 0;
            TrieNode* newNode = new TrieNode(nodeVal);
            int parentIndex = i / 2;
            bool isLeft = i % 2 == 0;
            
            if (isLeft)
                lastLevel[parentIndex] -> left = newNode;
            else
                lastLevel[parentIndex] -> right = newNode;
            curLevel.push_back(newNode);
        }
        
        // Update lastLevel with curLevel
        lastLevel = curLevel;
        curLevel.clear();
    }
    newRoot -> prettyPrint();
}

XFastTrie::~XFastTrie(){
}
