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


void testXFastInit() {

}

void testXFastFind() {
    XFastTrie* emptyTrie = new XFastTrie(128);
    
    assert(emptyTrie -> find(1234) == nullptr);
}

void testXFastPredecessor() {
    XFastTrie* emptyTrie = new XFastTrie(128);
    
    assert(emptyTrie -> predecessor(1234) == 0);
}

void testXFastSuccessor() {
    XFastTrie* emptyTrie = new XFastTrie(128);
    
    assert(emptyTrie -> successor(1234) == nullptr);
}

void testXFastClosestAncestor() {
    // XFastTrie contains 1, 3, and 7
    //0                       Node(NULL)
    //1        Node(0)                            Node(1)
    //2  Node(00)     Node(01)                        Node(11)
    //3     Node(001)       Node(011)                      Node(111)
    // 000   001    010      011     100     101     110     111
    //  0     1       2       3       4       5       6       7
//    std::vector<std::unordered_map<int, TrieNode*>> lss;
//    lss.push_back(std::unordered_map<int, TrieNode*>({ {0, new TrieNode(NULL)} }));
//    lss.push_back(std::unordered_map<int, TrieNode*>({
//        {0, new TrieNode(0)},
//        {1, new TrieNode(1)}
//    }));
//    lss.push_back(std::unordered_map<int, TrieNode*>({
//        {0, new TrieNode(0)},
//        {1, new TrieNode(1)},
//        {3, new TrieNode(3)},
//    }));
//    lss.push_back(std::unordered_map<int, TrieNode*>({
//        {1, new TrieNode(1)},
//        {3, new TrieNode(3)},
//        {7, new TrieNode(7)},
//    }));
//    
//    XFastTrie* tinyTrie = new XFastTrie(8);
//    tinyTrie -> setLevelSearchStructure(lss);
//    tinyTrie -> show();
//    
//    std::pair<int, TrieNode*> closestAncestorOf1 = tinyTrie -> closestAncestor(1);
//    std::cout << "\n--->" << closestAncestorOf1.first;
//    assert(closestAncestorOf1.first == 3);
//    assert(closestAncestorOf1.second -> getKey() == 1);
    
//    //~> Result should be at top
//    // Closest ancestor of root (key = 0) should be at the topmost summary structure
//    std::pair<int, TrieNode*> closestAncestorOf0 = tinyTrie -> closestAncestor(0);
//    assert(closestAncestorOf0.first == 7);
//    assert(closestAncestorOf0.second -> getKey() == 0);
//
//    //~> 1 result should be one from top
//    // Closest ancestor of root (key = 0) should be one below the topmost summary structure
//    std::pair<int, TrieNode*> closestAncestorOf1 = tinyTrie -> closestAncestor(1);
//    assert(closestAncestorOf1.first == 6);
//    assert(closestAncestorOf1.second -> getKey() == 0);
//
//    //~> 2 results should be two from top
//    std::pair<int, TrieNode*> closestAncestorOf2 = tinyTrie -> closestAncestor(2);
//    assert(closestAncestorOf2.first == 5);
//    assert(closestAncestorOf2.second -> getKey() == 0);
//
//    std::pair<int, TrieNode*> closestAncestorOf3 = tinyTrie -> closestAncestor(3);
//    assert(closestAncestorOf3.first == 5);
//    assert(closestAncestorOf3.second -> getKey() == 0);
//
//    //~> 4 restuls should be three from top
//    std::pair<int, TrieNode*> closestAncestorOf4 = tinyTrie -> closestAncestor(4);
//    assert(closestAncestorOf4.first == 4);
//    assert(closestAncestorOf4.second -> getKey() == 0);
//
//    std::pair<int, TrieNode*> closestAncestorOf5 = tinyTrie -> closestAncestor(5);
//    assert(closestAncestorOf5.first == 4);
//    assert(closestAncestorOf5.second -> getKey() == 0);
//
//    std::pair<int, TrieNode*> closestAncestorOf6 = tinyTrie -> closestAncestor(6);
//    assert(closestAncestorOf6.first == 4);
//    assert(closestAncestorOf6.second -> getKey() == 0);
//
//    std::pair<int, TrieNode*> closestAncestorOf7 = tinyTrie -> closestAncestor(7);
//    assert(closestAncestorOf7.first == 4);
//    assert(closestAncestorOf7.second -> getKey() == 0);
//
//    //~ 8 results should be 3 from the top
//    std::pair<int, TrieNode*> closestAncestorOf8 = tinyTrie -> closestAncestor(8);
//    assert(closestAncestorOf8.first == 3);
//    assert(closestAncestorOf8.second -> getKey() == 1);
}

void testNumberOfBitsInWord() {
    assert(XFastTrie::numberOfBitsInWord(0) == 0);
    assert(XFastTrie::numberOfBitsInWord(1) == 1);
    assert(XFastTrie::numberOfBitsInWord(std::stoi("101", 0, 2)) == 3);
}


void runXFastTests() {
    testXFastInit();
    testNumberOfBitsInWord();
    testXFastFind();
    testXFastPredecessor();
    testXFastSuccessor();
    testXFastClosestAncestor();
}
