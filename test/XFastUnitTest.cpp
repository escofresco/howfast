//
//  XFastUnitTest.cpp
//  why
//
//  Created by Jonasz Karwacki on 5/12/20.
//  Copyright © 2020 Jonasz Karwacki. All rights reserved.
//
#include <cassert>
#include <limits>
#include <iostream>
#include <vector>
#include "XFastUnitTest.hpp"
#include "XFastTrie.hpp"
#include "gtest/gtest.h"

// Define a fixture that allows the reuse of manually-built XFast Trees.
class XFastTest : public ::testing::Test {
protected:
    void SetUp() override {
        
        
        // XFastTrie contains 1, 3, and 7
        //0                       Node(NULL)
        //1        Node(0)                            Node(1)
        //2  Node(00)     Node(01)                        Node(11)
        //3     Node(001)       Node(011)                      Node(111)
        // 000   001    010      011     100     101     110     111
        //  0     1       2       3       4       5       6       7
        //                    │           ┌── 7
        //                    │       ┌── 3
        //                    │       │   └── 0
        //                    │   ┌── 1
        //                    │   │   │   ┌── 0
        //                    │   │   └── 0
        //                    │   │       └── 0
        //                    └── 0
        //                        │       ┌── 3
        //                        │   ┌── 1
        //                        │   │   └── 0
        //                        └── 0
        //                            │   ┌── 1
        //                            └── 0
        //                                └── 0
        // ~> Manually create data structure
        TrieNode* tinyChild1 = new TrieNode(1);
        TrieNode* tinyChild3 = new TrieNode(3, tinyChild1);
        TrieNode* tinyChild7 = new TrieNode(7, tinyChild3);
        tinyChild1 -> right = tinyChild3;
        tinyChild3 -> right = tinyChild7;
        std::vector<std::unordered_map<int, TrieNode*>> lss;
        lss.push_back(std::unordered_map<int, TrieNode*>({ {0, new TrieNode(NULL, tinyChild7, tinyChild3, false)} }));
        lss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0, tinyChild3, tinyChild1, false)},
            {1, new TrieNode(1, tinyChild7, nullptr, false)}
        }));
        lss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0, tinyChild1, nullptr, false)},
            {1, new TrieNode(1, tinyChild3, nullptr, false)},
            {3, new TrieNode(3, tinyChild7, nullptr, false)},
        }));
        lss.push_back(std::unordered_map<int, TrieNode*>({
            {1, tinyChild1},
            {3, tinyChild3},
            {7, tinyChild7},
        }));
        
        tinyTrie = new XFastTrie(8);
        tinyTrie -> levelSearchStructure = lss;
        
        
        // XFastTrie contains 0 and 1
        //                │           ┌── 7
        //                │       ┌── 3
        //                │       │   └── 6
        //                │   ┌── 1
        //                │   │   │   ┌── 5
        //                │   │   └── 2
        //                │   │       └── 4
        //                └── 0
        //                    │       ┌── 3
        //                    │   ┌── 1
        //                    │   │   └── 2
        //                    └── 0
        //                        │   ┌── 1
        //                        └── 0
        //                            └── 0
        // ~> Manually create data structure
        std::vector<std::unordered_map<int, TrieNode*>> fullLss;
        TrieNode* fullChild0 = new TrieNode(0);
        TrieNode* fullChild1 = new TrieNode(1);
        TrieNode* fullChild2 = new TrieNode(2);
        TrieNode* fullChild3 = new TrieNode(3);
        TrieNode* fullChild4 = new TrieNode(4);
        TrieNode* fullChild5 = new TrieNode(5);
        TrieNode* fullChild6 = new TrieNode(6);
        TrieNode* fullChild7 = new TrieNode(7);
        fullLss.push_back(std::unordered_map<int, TrieNode*>({ {0, new TrieNode(NULL, fullChild4, fullChild3, false)} }));
        fullLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0, nullptr, nullptr, false)},
            {1, new TrieNode(1, nullptr, nullptr, false)},
        }));
        fullLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0, nullptr, nullptr, false)},
            {1, new TrieNode(1, nullptr, nullptr, false)},
            {2, new TrieNode(2, nullptr, nullptr, false)},
            {3, new TrieNode(3, nullptr, nullptr, false)},
        }));
        fullLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, fullChild0},
            {1, fullChild1},
            {2, fullChild2},
            {3, fullChild3},
            {4, fullChild4},
            {5, fullChild5},
            {6, fullChild6},
            {7, fullChild7},
        }));
        fullTrie = new XFastTrie(8);
        fullTrie -> levelSearchStructure = fullLss;
        
        // ~> Update descendent pointers of summary nodes
        //fullTrie -> levelSearchStructure[1].find(0) -> second -> ;
        
        
        // XFastTrie contains 0 and 1
        //                │           ┌── 0
        //                │       ┌── 0
        //                │       │   └── 0
        //                │   ┌── 0
        //                │   │   │   ┌── 0
        //                │   │   └── 0
        //                │   │       └── 0
        //                └── 0
        //                    │       ┌── 0
        //                    │   ┌── 0
        //                    │   │   └── 0
        //                    └── 0
        //                        │   ┌── 1
        //                        └── 0
        //                            └── 0
        // ~> Manually create data structure
        std::vector<std::unordered_map<int, TrieNode*>> imbalancedLss;
        TrieNode* imbalancedChild0 = new TrieNode(0);
        TrieNode* imbalancedChild1 = new TrieNode(1, imbalancedChild0);
        imbalancedChild0 -> right = imbalancedChild1;
        
        imbalancedLss.push_back(std::unordered_map<int, TrieNode*>({ {0, new TrieNode(NULL, nullptr, imbalancedChild1, false)} }));
        imbalancedLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0, nullptr, imbalancedChild1, false)}
        }));
        imbalancedLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0, nullptr, imbalancedChild1, false)}
        }));
        imbalancedLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, imbalancedChild0},
            {1, imbalancedChild1},
        }));
        
        imbalancedTrie = new XFastTrie(8);
        imbalancedTrie -> levelSearchStructure = imbalancedLss;
    }

    // void TearDown() override {}
    
    XFastTrie* tinyTrie;
    XFastTrie* fullTrie;
    XFastTrie* imbalancedTrie;
};

TEST(XFastInit, NormalData) {

}

TEST(XFastFind, Simple) {
    XFastTrie* emptyTrie = new XFastTrie(128);
    
    EXPECT_EQ(emptyTrie -> find(1234), nullptr);
}

TEST(XFastPredeccessor, Simple) {
    XFastTrie* emptyTrie = new XFastTrie(128);
    
    //EXPECT_EQ(emptyTrie -> predecessor(1234), 0);
}

TEST(XFastSuccessor, Simple) {
    XFastTrie* emptyTrie = new XFastTrie(128);
    
    //EXPECT_EQ(emptyTrie -> successor(1234), nullptr);
}


TEST_F(XFastTest, ClosestAncestorTinyTree) {
    std::pair<int, TrieNode*> nearestAncestorOf0 = tinyTrie -> nearestAncestor(0);
    EXPECT_EQ(nearestAncestorOf0.first, 2);
    EXPECT_EQ(nearestAncestorOf0.second -> key, 0);

    std::pair<int, TrieNode*> nearestAncestorOf1 = tinyTrie -> nearestAncestor(1);
    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    EXPECT_EQ(nearestAncestorOf1.first, tinyTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf1.second -> key, 1);
    
    std::pair<int, TrieNode*> nearestAncestorOf2 = tinyTrie -> nearestAncestor(2);
    EXPECT_EQ(nearestAncestorOf2.first, 2);
    EXPECT_EQ(nearestAncestorOf2.second -> key, 1);

    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    std::pair<int, TrieNode*> nearestAncestorOf3 = tinyTrie -> nearestAncestor(3);
    EXPECT_EQ(nearestAncestorOf3.first, tinyTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf3.second -> key, 3);

    std::pair<int, TrieNode*> nearestAncestorOf4 = tinyTrie -> nearestAncestor(4);
    EXPECT_EQ(nearestAncestorOf4.first, 1);
    EXPECT_EQ(nearestAncestorOf4.second -> key, 1);

    std::pair<int, TrieNode*> nearestAncestorOf5 = tinyTrie -> nearestAncestor(5);
    EXPECT_EQ(nearestAncestorOf5.first, 1);
    EXPECT_EQ(nearestAncestorOf5.second -> key, 1);

    std::pair<int, TrieNode*> nearestAncestorOf6 = tinyTrie -> nearestAncestor(6);
    EXPECT_EQ(nearestAncestorOf6.first, 2);
    EXPECT_EQ(nearestAncestorOf6.second -> key, 3);

    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    std::pair<int, TrieNode*> nearestAncestorOf7 = tinyTrie -> nearestAncestor(7);
    EXPECT_EQ(nearestAncestorOf7.first, tinyTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf7.second -> key, 7);
}

TEST_F(XFastTest, ClosestAncestorCompletelyFilledTree) {
    std::pair<int, TrieNode*> nearestAncestorOf0 = fullTrie -> nearestAncestor(0);
    EXPECT_EQ(nearestAncestorOf0.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf0.second -> key, 0);

    std::pair<int, TrieNode*> nearestAncestorOf1 = fullTrie -> nearestAncestor(1);
    EXPECT_EQ(nearestAncestorOf1.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf1.second -> key, 1);
    
    std::pair<int, TrieNode*> nearestAncestorOf2 = fullTrie -> nearestAncestor(2);
    EXPECT_EQ(nearestAncestorOf2.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf2.second -> key, 2);

    std::pair<int, TrieNode*> nearestAncestorOf3 = fullTrie -> nearestAncestor(3);
    EXPECT_EQ(nearestAncestorOf3.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf3.second -> key, 3);

    std::pair<int, TrieNode*> nearestAncestorOf4 = fullTrie -> nearestAncestor(4);
    EXPECT_EQ(nearestAncestorOf4.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf4.second -> key, 4);

    std::pair<int, TrieNode*> nearestAncestorOf5 = fullTrie -> nearestAncestor(5);
    EXPECT_EQ(nearestAncestorOf5.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf5.second -> key, 5);

    std::pair<int, TrieNode*> nearestAncestorOf6 = fullTrie -> nearestAncestor(6);
    EXPECT_EQ(nearestAncestorOf6.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf6.second -> key, 6);

    std::pair<int, TrieNode*> nearestAncestorOf7 = fullTrie -> nearestAncestor(7);
    EXPECT_EQ(nearestAncestorOf7.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf7.second -> key, 7);
}

TEST_F(XFastTest, ClosestAncestorImbalancedData) {
    // ~> 0 and 1 should be the only keys with exact matches
    std::pair<int, TrieNode*> nearestAncestorOf0 = imbalancedTrie -> nearestAncestor(0);
    EXPECT_EQ(nearestAncestorOf0.first, imbalancedTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf0.second -> key, 0);

    std::pair<int, TrieNode*> nearestAncestorOf1 = imbalancedTrie -> nearestAncestor(1);
    EXPECT_EQ(nearestAncestorOf1.first, imbalancedTrie -> wordSize - 1);
    EXPECT_EQ(nearestAncestorOf1.second -> key, 1);
    
    // ~> The rest should have inexact matches
    std::pair<int, TrieNode*> nearestAncestorOf2 = imbalancedTrie -> nearestAncestor(2);
    EXPECT_EQ(nearestAncestorOf2.first, 1);
    EXPECT_EQ(nearestAncestorOf2.second -> key, 0);

    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    std::pair<int, TrieNode*> nearestAncestorOf3 = imbalancedTrie -> nearestAncestor(3);
    EXPECT_EQ(nearestAncestorOf3.first, 1);
    EXPECT_EQ(nearestAncestorOf3.second -> key, 0);

    std::pair<int, TrieNode*> nearestAncestorOf4 = imbalancedTrie -> nearestAncestor(4);
    EXPECT_EQ(nearestAncestorOf4.first, 0);
    EXPECT_EQ(nearestAncestorOf4.second -> key, 0);

    std::pair<int, TrieNode*> nearestAncestorOf5 = imbalancedTrie -> nearestAncestor(5);
    EXPECT_EQ(nearestAncestorOf5.first, 0);
    EXPECT_EQ(nearestAncestorOf5.second -> key, 0);

    std::pair<int, TrieNode*> nearestAncestorOf6 = imbalancedTrie -> nearestAncestor(6);
    EXPECT_EQ(nearestAncestorOf6.first, 0);
    EXPECT_EQ(nearestAncestorOf6.second -> key, 0);

    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    std::pair<int, TrieNode*> nearestAncestorOf7 = imbalancedTrie -> nearestAncestor(7);
    EXPECT_EQ(nearestAncestorOf7.first, 0);
    EXPECT_EQ(nearestAncestorOf7.second -> key, 0);
}

TEST_F(XFastTest, NearestLeafTinyTree) {
    
    // ~> Test nearest leaves of leaves
    TrieNode* nearestLeafOf1 = tinyTrie -> nearestLeaf(1);
    TrieNode* nearestLeafOf3 = tinyTrie -> nearestLeaf(3);
    TrieNode* nearestLeafOf7 = tinyTrie -> nearestLeaf(7);
    
    EXPECT_EQ(nearestLeafOf1 -> key, 1);
    EXPECT_TRUE(nearestLeafOf1 -> isLeaf);
    EXPECT_EQ(nearestLeafOf1 -> left, nullptr);
    EXPECT_EQ(nearestLeafOf1 -> right, nearestLeafOf3);
    
    EXPECT_EQ(nearestLeafOf3 -> key, 3);
    EXPECT_TRUE(nearestLeafOf3 -> isLeaf);
    EXPECT_EQ(nearestLeafOf3 -> left, nearestLeafOf1);
    EXPECT_EQ(nearestLeafOf3 -> right, nearestLeafOf7);
    
    EXPECT_EQ(nearestLeafOf7 -> key, 7);
    EXPECT_TRUE(nearestLeafOf7 -> isLeaf);
    EXPECT_EQ(nearestLeafOf7 -> left, nearestLeafOf3);
    EXPECT_EQ(nearestLeafOf7 -> right, nullptr);
    
    // ~> Test nearest leaves of inexact queries
    TrieNode* nearestLeafOf0 = tinyTrie -> nearestLeaf(0);
    TrieNode* nearestLeafOf2 = tinyTrie -> nearestLeaf(2);
    TrieNode* nearestLeafOf4 = tinyTrie -> nearestLeaf(4);
    TrieNode* nearestLeafOf5 = tinyTrie -> nearestLeaf(5);
    TrieNode* nearestLeafOf6 = tinyTrie -> nearestLeaf(6);
    
    EXPECT_EQ(nearestLeafOf0 -> key, 1);
    EXPECT_TRUE(nearestLeafOf0 -> isLeaf);
    EXPECT_EQ(nearestLeafOf0, nearestLeafOf1);
    
    EXPECT_EQ(nearestLeafOf2 -> key, 1);
    EXPECT_TRUE(nearestLeafOf2 -> isLeaf);
    EXPECT_EQ(nearestLeafOf2, nearestLeafOf1);
    
    EXPECT_EQ(nearestLeafOf4 -> key, 3);
    EXPECT_TRUE(nearestLeafOf4 -> isLeaf);
    EXPECT_EQ(nearestLeafOf4, nearestLeafOf3);
    
    EXPECT_EQ(nearestLeafOf5 -> key, 7);
    EXPECT_TRUE(nearestLeafOf5 -> isLeaf);
    EXPECT_EQ(nearestLeafOf5, nearestLeafOf7);
    
    EXPECT_EQ(nearestLeafOf6 -> key, 7);
    EXPECT_TRUE(nearestLeafOf6 -> isLeaf);
    EXPECT_EQ(nearestLeafOf6, nearestLeafOf7);
}

TEST_F(XFastTest, NearestLeafFullTree) {
    // ~> Test nearest leaves of exact queries
    TrieNode* nearestLeafOf0 = fullTrie -> nearestLeaf(0);
    TrieNode* nearestLeafOf1 = fullTrie -> nearestLeaf(1);
    TrieNode* nearestLeafOf2 = fullTrie -> nearestLeaf(2);
    TrieNode* nearestLeafOf3 = fullTrie -> nearestLeaf(3);
    TrieNode* nearestLeafOf4 = fullTrie -> nearestLeaf(4);
    TrieNode* nearestLeafOf5 = fullTrie -> nearestLeaf(5);
    TrieNode* nearestLeafOf6 = fullTrie -> nearestLeaf(6);
    TrieNode* nearestLeafOf7 = fullTrie -> nearestLeaf(7);
    
    EXPECT_EQ(nearestLeafOf0 -> key, 0);
    EXPECT_TRUE(nearestLeafOf0 -> isLeaf);
    EXPECT_EQ(nearestLeafOf0, nearestLeafOf0);
    
    EXPECT_EQ(nearestLeafOf1 -> key, 1);
    EXPECT_TRUE(nearestLeafOf1 -> isLeaf);
    EXPECT_EQ(nearestLeafOf1, nearestLeafOf1);
    
    EXPECT_EQ(nearestLeafOf2 -> key, 2);
    EXPECT_TRUE(nearestLeafOf2 -> isLeaf);
    EXPECT_EQ(nearestLeafOf2, nearestLeafOf2);
    
    EXPECT_EQ(nearestLeafOf3 -> key, 3);
    EXPECT_TRUE(nearestLeafOf3 -> isLeaf);
    EXPECT_EQ(nearestLeafOf3, nearestLeafOf3);
    
    EXPECT_EQ(nearestLeafOf4 -> key, 4);
    EXPECT_TRUE(nearestLeafOf4 -> isLeaf);
    EXPECT_EQ(nearestLeafOf4, nearestLeafOf4);
    
    EXPECT_EQ(nearestLeafOf5 -> key, 5);
    EXPECT_TRUE(nearestLeafOf5 -> isLeaf);
    EXPECT_EQ(nearestLeafOf5, nearestLeafOf5);
    
    EXPECT_EQ(nearestLeafOf6 -> key, 6);
    EXPECT_TRUE(nearestLeafOf6 -> isLeaf);
    EXPECT_EQ(nearestLeafOf6, nearestLeafOf6);
    
    EXPECT_EQ(nearestLeafOf7 -> key, 7);
    EXPECT_TRUE(nearestLeafOf7 -> isLeaf);
    EXPECT_EQ(nearestLeafOf7, nearestLeafOf7);
}

TEST_F(XFastTest, NearestLeafImbalancedTrie) {
    // ~> Test nearest leaves of exact queries
    TrieNode* nearestLeafOf0 = imbalancedTrie -> nearestLeaf(0);
    TrieNode* nearestLeafOf1 = imbalancedTrie -> nearestLeaf(1);
//    
//    EXPECT_EQ(nearestLeafOf0 -> key, 0);
//    EXPECT_TRUE(nearestLeafOf0 -> isLeaf);
//    EXPECT_EQ(nearestLeafOf0, nearestLeafOf0);
//    
//    EXPECT_EQ(nearestLeafOf1 -> key, 1);
//    EXPECT_TRUE(nearestLeafOf1 -> isLeaf);
//    EXPECT_EQ(nearestLeafOf1, nearestLeafOf1);
    
    // ~> Test nearest leaves of inexact queries
    TrieNode* nearestLeafOf2 = imbalancedTrie -> nearestLeaf(2);
    TrieNode* nearestLeafOf3 = imbalancedTrie -> nearestLeaf(3);
    TrieNode* nearestLeafOf4 = imbalancedTrie -> nearestLeaf(4);
    TrieNode* nearestLeafOf5 = imbalancedTrie -> nearestLeaf(5);
    TrieNode* nearestLeafOf6 = imbalancedTrie -> nearestLeaf(6);
    TrieNode* nearestLeafOf7 = imbalancedTrie -> nearestLeaf(7);
    
    EXPECT_EQ(nearestLeafOf2 -> key, 1);
    EXPECT_TRUE(nearestLeafOf2 -> isLeaf);
    EXPECT_EQ(nearestLeafOf2, nearestLeafOf1);
    
    EXPECT_EQ(nearestLeafOf3 -> key, 1);
    EXPECT_TRUE(nearestLeafOf3 -> isLeaf);
    EXPECT_EQ(nearestLeafOf3, nearestLeafOf1);
        
    EXPECT_EQ(nearestLeafOf4 -> key, 1);
    EXPECT_TRUE(nearestLeafOf4 -> isLeaf);
    EXPECT_EQ(nearestLeafOf4, nearestLeafOf1);
    
    EXPECT_EQ(nearestLeafOf5 -> key, 1);
    EXPECT_TRUE(nearestLeafOf5 -> isLeaf);
    EXPECT_EQ(nearestLeafOf5, nearestLeafOf1);
    
    EXPECT_EQ(nearestLeafOf6 -> key, 1);
    EXPECT_TRUE(nearestLeafOf6 -> isLeaf);
    EXPECT_EQ(nearestLeafOf6, nearestLeafOf1);
    
    EXPECT_EQ(nearestLeafOf7 -> key, 1);
    EXPECT_TRUE(nearestLeafOf7 -> isLeaf);
    EXPECT_EQ(nearestLeafOf7, nearestLeafOf1);
}

TEST_F(XFastTest, PredecessorTinyTrie) {
    TrieNode* predecessor0 = tinyTrie -> predecessor(0);
    EXPECT_EQ(predecessor0, nullptr);
    
    TrieNode* predecessor1 = tinyTrie -> predecessor(1);
    EXPECT_EQ(predecessor1 -> key, 1);
    
    TrieNode* predecessor2 = tinyTrie -> predecessor(2);
    EXPECT_EQ(predecessor2 -> key, 1);
    
    TrieNode* predecessor3 = tinyTrie -> predecessor(3);
    EXPECT_EQ(predecessor3 -> key, 3);
    
    TrieNode* predecessor4 = tinyTrie -> predecessor(4);
    EXPECT_EQ(predecessor4 -> key, 3);
    
    TrieNode* predecessor5 = tinyTrie -> predecessor(5);
    EXPECT_EQ(predecessor5 -> key, 3);
    
    TrieNode* predecessor6 = tinyTrie -> predecessor(6);
    EXPECT_EQ(predecessor6 -> key, 3);
    
    TrieNode* predecessor7 = tinyTrie -> predecessor(7);
    EXPECT_EQ(predecessor7 -> key, 7);
}

TEST_F(XFastTest, SuccessorTinyTrie) {
    TrieNode* successor0 = tinyTrie -> successor(0);
    EXPECT_EQ(successor0 -> key, 1);
    
    TrieNode* successor1 = tinyTrie -> successor(1);
    EXPECT_EQ(successor1 -> key, 1);
    
    TrieNode* successor2 = tinyTrie -> successor(2);
    EXPECT_EQ(successor2 -> key, 3);
    
    TrieNode* successor3 = tinyTrie -> successor(3);
    EXPECT_EQ(successor3 -> key, 3);
    
    TrieNode* successor4 = tinyTrie -> successor(4);
    EXPECT_EQ(successor4 -> key, 7);
    
    TrieNode* successor5 = tinyTrie -> successor(5);
    EXPECT_EQ(successor5 -> key, 7);
    
    TrieNode* successor6 = tinyTrie -> successor(6);
    EXPECT_EQ(successor6 -> key,7);
    
    TrieNode* successor7 = tinyTrie -> successor(7);
    EXPECT_EQ(successor7 -> key, 7);
}

TEST(NumberOfBitsInWordTest, SmallWords) {
    EXPECT_EQ(XFastTrie::numberOfBitsInWord(0), 0);
    EXPECT_EQ(XFastTrie::numberOfBitsInWord(1), 1);
    EXPECT_EQ(XFastTrie::numberOfBitsInWord(std::stoi("101", 0, 2)), 3);
}

