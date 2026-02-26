//======= Copyright (c) 2025, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2025-02-19
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Tomáš Šuda
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"
#include "iostream"
//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.

TEST(EmptyTree,InsertNode){
    BinaryTree tree;
    auto[statement,ptr] = tree.InsertNode(2);
    // expectace pro InsertNode: statement == true, ptr != nullptr
    EXPECT_TRUE(statement);
    EXPECT_NE(ptr, nullptr);
    // tree is empty before InsertNode, so ptr should be root
    auto root_ptr = tree.GetRoot();
    EXPECT_EQ(root_ptr, ptr);
}

TEST(EmptyTree,DeleteNode){
    BinaryTree tree;
    // delete non-existing node should return false
    EXPECT_FALSE(tree.DeleteNode(2));
}

TEST(EmptyTree,FindNode){
    BinaryTree tree;
    // find non-existing node should return nullptr
    EXPECT_EQ(tree.FindNode(2), nullptr);
}

TEST(NonEmptyTree,InsertNode){
    BinaryTree tree;
    auto[statement,ptr]=tree.InsertNode(2);
    EXPECT_TRUE(statement);
    EXPECT_NE(ptr, nullptr);
    // insert same node again should return false and same pointer
    auto[statement2,ptr2]=tree.InsertNode(2);
    EXPECT_FALSE(statement2);
    EXPECT_EQ(ptr, ptr2);

    // insert 10 nodes and check if they are inserted correctly
    for(int i=0; i<10; i++){
        auto[statement,ptr]=tree.InsertNode(i);
        if(i==2){
            EXPECT_FALSE(statement);
            EXPECT_EQ(ptr, ptr2);
        } else {
            EXPECT_TRUE(statement);
            EXPECT_NE(ptr, nullptr);
        }
    }
}


TEST(NonEmptyTree,DeleteNode){
    BinaryTree tree;
    tree.InsertNode(2);
    EXPECT_TRUE(tree.DeleteNode(2));
    // delete same node again should return false
    EXPECT_FALSE(tree.DeleteNode(2));
}

TEST(NonEmptyTree,FindNode){
    BinaryTree tree;
    tree.InsertNode(2);
    EXPECT_NE(tree.FindNode(2), nullptr);

    // find non-existing node should return nullptr
    EXPECT_EQ(tree.FindNode(464646), nullptr);
}
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

TEST(TreeAxioms,Axiom1){
    BinaryTree tree;
    std::vector<int> values;
    for(int i=0; i<100; i++){
        values.push_back(i);
    }
    std::vector<std::pair<bool, Node_t *> > ret_values ={};
    std::vector<Node_t *> outLeafNodes ={};
    tree.InsertNodes(values,ret_values);
    tree.GetLeafNodes(outLeafNodes);
    EXPECT_FALSE(outLeafNodes.empty());
    EXPECT_NE(tree.GetRoot(), nullptr);
    for (auto node : outLeafNodes){
        EXPECT_EQ(node->color, BinaryTree::BLACK);
    }
}

TEST(TreeAxioms,Axiom2){
    BinaryTree tree;
    std::vector<int> values;
    for(int i=0; i<100; i++){
        values.push_back(i);
    }
    std::vector<std::pair<bool, Node_t *> > ret_values ={};
    std::vector<Node_t *> allNodes ={};
    tree.InsertNodes(values,ret_values);
    tree.GetAllNodes(allNodes);
    EXPECT_FALSE(allNodes.empty());
    EXPECT_NE(tree.GetRoot(), nullptr);
    for (auto node : allNodes){
        if(node->color == BinaryTree::RED){
            if(node->pLeft)
                 EXPECT_EQ(node->pLeft->color,BinaryTree::BLACK);// left node is black
            if(node->pRight)
            EXPECT_EQ(node->pRight->color,BinaryTree::BLACK);// right node is black
        }
    }
}
// helper function for Axiom3 test
// recursively counts the number of black nodes on the path from a given node to the root
void roadToRoot(Node_t * node,unsigned int  *length,Node_t *root){
    if(node == root){
        (*length)++;
         return ;
    }

    if (node->color == BinaryTree::BLACK){
        (*length)++;
         roadToRoot(node->pParent,length,root);
    }
    else
        roadToRoot(node->pParent,length,root);
}

TEST(TreeAxioms,Axiom3){
    BinaryTree tree;
    std::vector<int> values;
    for(int i=0; i<100; i++){
        values.push_back(i);
    }
    std::vector<std::pair<bool, Node_t *> > ret_values ={};
    std::vector<Node_t *> outLeafNodes ={};
    tree.InsertNodes(values,ret_values);
    tree.GetLeafNodes(outLeafNodes);
    Node_t *root = tree.GetRoot();
    unsigned int road = 0 ;

    EXPECT_NE(root, nullptr);
    EXPECT_FALSE(outLeafNodes.empty());
    //for each leaf node  checks if the number of black nodes on the path from the leaf to the root is the same for all leaf nodes
    for (auto node : outLeafNodes){
       if(  0 == road ){ // first pass calculates path length for first leaf node and stores it as reference value
            roadToRoot(node,&road,root);
       }
       else{//for other leaf nodes  compares path length to reference value
            unsigned int tmp_length = 0;
            roadToRoot(node,&tmp_length,root);
            EXPECT_EQ(tmp_length,road);
       }
    }
}

/*** Konec souboru black_box_tests.cpp ***/
