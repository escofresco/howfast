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
    levelSearchStructure.assign(wordSize + 1, std::unordered_map<int, TrieNode*>());
    levelSearchStructure[0][0] = new TrieNode(NULL);
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

TrieNode* XFastTrie::successor(int key) {
    return nullptr;
}

TrieNode* XFastTrie::predecessor(int key) {
    return nullptr;
}

void XFastTrie::insert(int key) {
}

void XFastTrie::deleteKey(int key) {
}

std::pair<int, TrieNode*> XFastTrie::closestAncestor(int key) {
    if (levelSearchStructure.empty())
        return std::make_pair(NULL, nullptr);
    TrieNode* ancestorNode = root;
    int ancestorLevel = -1;
    int level;
    int prefix;
    int lo = 0;
    int hi = wordSize;
    
    while (lo <= hi) {
        level = (lo + hi) >> 1;
        prefix = key >> (wordSize - level);
        std::cout << "level: "<< level << '\n';
        if (getLevelSearchStructure()[level].count(prefix) > 0) {
            //~> Prefix exists in current level
            // update ancestorLevel and ancestorNode
            ancestorNode = getLevelSearchStructure()[level].at(prefix);
            ancestorLevel = level;
            
            // look farther down the tree
            lo = level + 1;
        } else
            //~> Prefix wasn't found at current level
            // look farther up the tree
            hi = level - 1;
        
    }
    return std::make_pair(ancestorLevel, ancestorNode);
}

TrieNode* XFastTrie::nearestLeaf(int key) {
    return nullptr;
}

const std::vector<std::unordered_map<int, TrieNode*>>& XFastTrie::getLevelSearchStructure() const {
    return levelSearchStructure;
}

void XFastTrie::show() {

}

XFastTrie::~XFastTrie(){
}
