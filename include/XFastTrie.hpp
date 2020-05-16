//
//  XFastTrie.hpp
//  why
//
//  Created by Jonasz Karwacki on 5/12/20.
//  Copyright © 2020 Jonasz Karwacki. All rights reserved.
//

#ifndef XFastTrie_hpp
#define XFastTrie_hpp

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include "TrieNode.hpp"

/**
 * A bitwise trie for storing integers in a bounded domain. Offers near-optimal performance for common
 * operations in a universe.
 *
 * Space  Complexity:  O(n lg u)
 * Find O(1)
 * Seach O(log log u)
 * Insert O(log u) amortized average
 * Delete O(log u) amortized average
 */
class XFastTrie {
public:
    
    // The largest value that can be stored in tree (universe)
    int universeSize;
    
    // The maximum number of bits that can be stored
    int wordSize;
    
    // Root node maintains structure of tree but doesn't contain data
    TrieNode* root;
    
    // At each level there is a hash table that holds all the nodes for
    // that level.
    // TODO: Use dynamic-perfect hashing or cuckoo hashing.
    std::vector<std::unordered_map<int, TrieNode*>> levelSearchStructure;
    
    static int numberOfBitsInWord(int word);
    
    /**
     * Constructs trie to handle integers with an upper bound of U.
     *
     * @param U Universe size.
     */
    XFastTrie(int U);

    /**
     * Find the value associated with the given key by looking it up in the level search structure.
     * Time Complexity: O(1)
     *
     * @param key The number associated with a node.
     * @return The node associated with the given key.
     */
    TrieNode* find(int key);
    
    /**
     * Find the smallest key/value pair that is larger than the given key.
     *
     * @param key The number to find the successor to.
     * @return The key/value that immediately follows the given key.
     */
    TrieNode* successor(int key);
    
    /**
     * Find the largest key/value pair that is smaller than the given key.
     *
     * @param key The number to find the predecessor to.
     * @return The key/value that immediate precede the given key.
     */
    TrieNode* predecessor(int key);
    
    /**
     * Insert the given key into the tree.
     *
     * @param key The number to insert.
     */
    void insert(int key);
    
    /**
     * Remove the given key from the tree.
     *
     * @param key The number to delete.
     */
    void deleteKey(int key);
    
    /**
     * Helper method to find the lowest ancestor for key by binary searching through the level search structure. Start at the
     * middle level (height / 2) If a key is found with a prefix of the given key, then lowest ancestor must be on bottom half
     * else it's at the top half.
     *
     * @param key The key to find the closest ancestor to.
     * @return A pair containing the level of the closest ancestor and the node corresponding to that ancestor.
     */
    std::pair<int, TrieNode*> closestAncestor(int key);
    
    /**
     * Finds the leaf with a key nearest in value to the given key.
     *
     * @param key The key to find the nearest leaf of.
     * @return The leaf node closest in value to the given key.
     */
    TrieNode* nearestLeaf(int key);
    
    /**
     Get the level search structure.
     
     @return The reference to the level search structure.
     */
    
    /**
     * Getter for level search structure.
     *
     * @return level search structure.
     */
    const std::vector<std::unordered_map<int, TrieNode*>>& getLevelSearchStructure() const;
    
    /**
     * Visualize the tree to the console.
     */
    void show();
    
    ~XFastTrie();
};
#endif /* XFastTrie_hpp */
