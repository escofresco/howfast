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
    if (levelSearchStructure.empty() || levelSearchStructure[wordSize].find(key) == levelSearchStructure[wordSize].end())
        // key doesn't exist
        return nullptr;
    return levelSearchStructure[wordSize][key];
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
    
    if (find(key))
        // Exit early if key already exists
        return;
    
    // ~> Find the predecessor and successor of key and then put key in between them.
    TrieNode* left = predecessor(key);
    TrieNode* right = successor(key);
    
    // Create the node to insert
    TrieNode* leaf = new TrieNode(key, left, right);
    
    // ~> Put leaf in between left and right
    if (left)
        left -> right = leaf;
    
    if (right)
        right -> left = leaf;
    
    // ~> Update global min and max
    if (globalMin == NAN)
        globalMin = key;
    globalMin = std::min(globalMin, key);
    
    if (globalMax == NAN)
        globalMax = key;
    globalMax = std::max(globalMax, key);
    
    // ~> Walk down tree from leaf to root and create summary nodes if they don't exist
    for (int level = 1; level < wordSize; level++) {
        int prefix = key >> (wordSize - level);
        
        if (levelSearchStructure[level].find(prefix) == levelSearchStructure[level].end()) {
            // ~> Prefix doesn't exist in level, so create node for it
            // Create the node to insert
            TrieNode* summaryNode = new TrieNode(key);
            int parentPrefix = prefix >> 1;
            
            // Add summary node to search structure
            levelSearchStructure[level][prefix] = summaryNode;
            
            if (prefix & 1)
                // Prefix is the right leg if its parent, assign summary node to parent's right
                levelSearchStructure[level - 1][parentPrefix] -> right = summaryNode;
            else
                levelSearchStructure[level - 1][parentPrefix] -> left = summaryNode;
        }
    }
    
    // Place leaf into tree
    levelSearchStructure[wordSize][key] = leaf;
    int parentPrefix = key >> 1;
    
    // Assign leaf (the node to ultimately be inserted) as a child of its expected parent
    if (key & 1)
        // Key is on the right leg of its parent
        levelSearchStructure[wordSize - 1][parentPrefix] -> right = leaf;
    else
        // Key is on the left leg of its parent
        levelSearchStructure[wordSize - 1][parentPrefix] -> left = leaf;
    
    // ~> Walk up the tree from leaf and update descendant pointers
    int prefix = key;
    
    for (int level = wordSize - 1; level > 0; level--) {
        prefix >>= 1;
        
        if (levelSearchStructure[level][prefix] -> left == nullptr)
            // Left pointer of prefix isn't set
            // Set the leftmost leaf of the right subtree to prefix node's left
            levelSearchStructure[level][prefix] -> left = leftmostLeaf(levelSearchStructure[level][prefix] -> right, level + 1);
        else if (levelSearchStructure[level][prefix] -> right == nullptr)
            // Right pointer of prefix isn't set
            // Set the rightmost leaf of the left subtree to prefix node's right
            levelSearchStructure[level][prefix] -> right = rightmostLeaf(levelSearchStructure[level][prefix] -> left, level + 1);
    }
    
    // ~> Set left and right pointers of root
    if (levelSearchStructure[0][0] -> left)
        levelSearchStructure[0][0] -> left = leftmostLeaf(levelSearchStructure[0][0] -> left, 1);
    
    if (levelSearchStructure[0][0] -> right)
        levelSearchStructure[0][0] -> right = rightmostLeaf(levelSearchStructure[0][0] -> right, 1);
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

TrieNode* XFastTrie::leftmostLeaf(TrieNode* node, int level) {
    
    while (level < wordSize) {
        // Search through node's subtree until we get to the bottom
        
        if (node -> left)
            node = node -> left;
        else
            node = node -> right;
        level++;
    }
    return node;
}

TrieNode* XFastTrie::rightmostLeaf(TrieNode* node, int level) {
    while (level < wordSize) {
        // Search through node's subtree until we get to the bottom

        if (node -> right)
            node = node -> right;
        else
            node = node -> left;
        level++;
    }
    return node;
}

XFastTrie::~XFastTrie(){
    // Teardown
}
