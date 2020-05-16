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
        std::vector<std::unordered_map<int, TrieNode*>> lss;
        lss.push_back(std::unordered_map<int, TrieNode*>({ {0, new TrieNode(NULL)} }));
        lss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0)},
            {1, new TrieNode(1)}
        }));
        lss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0)},
            {1, new TrieNode(1)},
            {3, new TrieNode(3)},
        }));
        lss.push_back(std::unordered_map<int, TrieNode*>({
            {1, new TrieNode(1)},
            {3, new TrieNode(3)},
            {7, new TrieNode(7)},
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
        fullLss.push_back(std::unordered_map<int, TrieNode*>({ {0, new TrieNode(NULL)} }));
        fullLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0)},
            {1, new TrieNode(1)},
        }));
        fullLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0)},
            {1, new TrieNode(1)},
            {2, new TrieNode(2)},
            {3, new TrieNode(3)},
        }));
        fullLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0)},
            {1, new TrieNode(1)},
            {2, new TrieNode(2)},
            {3, new TrieNode(3)},
            {4, new TrieNode(4)},
            {5, new TrieNode(5)},
            {6, new TrieNode(6)},
            {7, new TrieNode(7)},
            {8, new TrieNode(8)}
        }));
        fullTrie = new XFastTrie(8);
        fullTrie -> levelSearchStructure = fullLss;
        
        
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
        imbalancedLss.push_back(std::unordered_map<int, TrieNode*>({ {0, new TrieNode(NULL)} }));
        imbalancedLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0)}
        }));
        imbalancedLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0)}
        }));
        imbalancedLss.push_back(std::unordered_map<int, TrieNode*>({
            {0, new TrieNode(0)},
            {1, new TrieNode(1)},
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
    
    EXPECT_EQ(emptyTrie -> successor(1234), nullptr);
}


TEST_F(XFastTest, ClosestAncestorTinyTrie) {
    std::pair<int, TrieNode*> closestAncestorOf0 = tinyTrie -> closestAncestor(0);
    EXPECT_EQ(closestAncestorOf0.first, 2);
    EXPECT_EQ(closestAncestorOf0.second -> key, 0);

    std::pair<int, TrieNode*> closestAncestorOf1 = tinyTrie -> closestAncestor(1);
    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    EXPECT_EQ(closestAncestorOf1.first, tinyTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf1.second -> key, 1);
    
    std::pair<int, TrieNode*> closestAncestorOf2 = tinyTrie -> closestAncestor(2);
    EXPECT_EQ(closestAncestorOf2.first, 2);
    EXPECT_EQ(closestAncestorOf2.second -> key, 1);

    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    std::pair<int, TrieNode*> closestAncestorOf3 = tinyTrie -> closestAncestor(3);
    EXPECT_EQ(closestAncestorOf3.first, tinyTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf3.second -> key, 3);

    std::pair<int, TrieNode*> closestAncestorOf4 = tinyTrie -> closestAncestor(4);
    EXPECT_EQ(closestAncestorOf4.first, 1);
    EXPECT_EQ(closestAncestorOf4.second -> key, 1);

    std::pair<int, TrieNode*> closestAncestorOf5 = tinyTrie -> closestAncestor(5);
    EXPECT_EQ(closestAncestorOf5.first, 1);
    EXPECT_EQ(closestAncestorOf5.second -> key, 1);

    std::pair<int, TrieNode*> closestAncestorOf6 = tinyTrie -> closestAncestor(6);
    EXPECT_EQ(closestAncestorOf6.first, 2);
    EXPECT_EQ(closestAncestorOf6.second -> key, 3);

    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    std::pair<int, TrieNode*> closestAncestorOf7 = tinyTrie -> closestAncestor(7);
    EXPECT_EQ(closestAncestorOf7.first, tinyTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf7.second -> key, 7);
}

TEST_F(XFastTest, ClosestAncestorCompletelyFilledTree) {
    std::pair<int, TrieNode*> closestAncestorOf0 = fullTrie -> closestAncestor(0);
    EXPECT_EQ(closestAncestorOf0.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf0.second -> key, 0);

    std::pair<int, TrieNode*> closestAncestorOf1 = fullTrie -> closestAncestor(1);
    EXPECT_EQ(closestAncestorOf1.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf1.second -> key, 1);
    
    std::pair<int, TrieNode*> closestAncestorOf2 = fullTrie -> closestAncestor(2);
    EXPECT_EQ(closestAncestorOf2.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf2.second -> key, 2);

    std::pair<int, TrieNode*> closestAncestorOf3 = fullTrie -> closestAncestor(3);
    EXPECT_EQ(closestAncestorOf3.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf3.second -> key, 3);

    std::pair<int, TrieNode*> closestAncestorOf4 = fullTrie -> closestAncestor(4);
    EXPECT_EQ(closestAncestorOf4.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf4.second -> key, 4);

    std::pair<int, TrieNode*> closestAncestorOf5 = fullTrie -> closestAncestor(5);
    EXPECT_EQ(closestAncestorOf5.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf5.second -> key, 5);

    std::pair<int, TrieNode*> closestAncestorOf6 = fullTrie -> closestAncestor(6);
    EXPECT_EQ(closestAncestorOf6.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf6.second -> key, 6);

    std::pair<int, TrieNode*> closestAncestorOf7 = fullTrie -> closestAncestor(7);
    EXPECT_EQ(closestAncestorOf7.first, fullTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf7.second -> key, 7);
}

TEST_F(XFastTest, ClosestAncestorImbalancedData) {
    // ~> 0 and 1 should be the only keys with exact matches
    std::pair<int, TrieNode*> closestAncestorOf0 = imbalancedTrie -> closestAncestor(0);
    EXPECT_EQ(closestAncestorOf0.first, imbalancedTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf0.second -> key, 0);

    std::pair<int, TrieNode*> closestAncestorOf1 = imbalancedTrie -> closestAncestor(1);
    EXPECT_EQ(closestAncestorOf1.first, imbalancedTrie -> wordSize - 1);
    EXPECT_EQ(closestAncestorOf1.second -> key, 1);
    
    // ~> The rest should have inexact matches
    std::pair<int, TrieNode*> closestAncestorOf2 = imbalancedTrie -> closestAncestor(2);
    EXPECT_EQ(closestAncestorOf2.first, 1);
    EXPECT_EQ(closestAncestorOf2.second -> key, 0);

    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    std::pair<int, TrieNode*> closestAncestorOf3 = imbalancedTrie -> closestAncestor(3);
    EXPECT_EQ(closestAncestorOf3.first, 1);
    EXPECT_EQ(closestAncestorOf3.second -> key, 0);

    std::pair<int, TrieNode*> closestAncestorOf4 = imbalancedTrie -> closestAncestor(4);
    EXPECT_EQ(closestAncestorOf4.first, 0);
    EXPECT_EQ(closestAncestorOf4.second -> key, 0);

    std::pair<int, TrieNode*> closestAncestorOf5 = imbalancedTrie -> closestAncestor(5);
    EXPECT_EQ(closestAncestorOf5.first, 0);
    EXPECT_EQ(closestAncestorOf5.second -> key, 0);

    std::pair<int, TrieNode*> closestAncestorOf6 = imbalancedTrie -> closestAncestor(6);
    EXPECT_EQ(closestAncestorOf6.first, 0);
    EXPECT_EQ(closestAncestorOf6.second -> key, 0);

    // Closest ancestor should be the node we queried, since this the ancestor of an element is the element itself
    std::pair<int, TrieNode*> closestAncestorOf7 = imbalancedTrie -> closestAncestor(7);
    EXPECT_EQ(closestAncestorOf7.first, 0);
    EXPECT_EQ(closestAncestorOf7.second -> key, 0);
}

TEST(NumberOfBitsInWordTest, SmallWords) {
    EXPECT_EQ(XFastTrie::numberOfBitsInWord(0), 0);
    EXPECT_EQ(XFastTrie::numberOfBitsInWord(1), 1);
    EXPECT_EQ(XFastTrie::numberOfBitsInWord(std::stoi("101", 0, 2)), 3);
}

