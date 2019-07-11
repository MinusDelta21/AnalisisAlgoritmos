// BinarySearchTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <ctime>
struct Node {
  //Value this node contains.
  int key;
  //Amount of times this value repeats.
  int count;
  //Child Nodes
  Node * leftChild;
  Node * rightChild;

  Node *  Init(int _key) {
    this->key = _key;
    this->count = 1;
    leftChild = nullptr;
    rightChild = nullptr;

    return this;
  }
};

struct BinaryTree {

private:
  void Inorder(Node * node) {
    if (root == nullptr) {
      std::cout << "Root is NULL" << std::endl;
    }
    if (node != nullptr) {
      Inorder(node->leftChild);
      for (int i = 0; i < node->count; i++) {
        std::cout << node->key << std::endl;
      }
      Inorder(node->rightChild);
    }

  }
  Node * AddNode(int key) {
    Node * temp = new Node();
    temp->Init(key);
    if (root == nullptr) {
      root = temp;
    }
    return temp;
  }
  Node * Search(Node* node, int key) {
    if (node == nullptr) {
      std::cout << "Key with value " << key << " was not found" << std::endl;
      return node;
    }
    if (key == node->key) {
      std::cout << "The key with value " << key << " was found " << node->count << " times in tree." << std::endl;
      return node;
    }
    if (node->key < key) {
      return Search(node->leftChild, key);
    }
    else {
      return Search(node->rightChild, key);
    }
  }
  Node * Insert(Node* node, int key) {
    if (node == nullptr) {
      return AddNode(key);
    }
    //If key is lower.
    if (key < node->key) {
      node->leftChild = Insert(node->leftChild, key);
    }
    //If key is higher.
    else if (key > node->key) {
      node->rightChild = Insert(node->rightChild, key);
    }
    //If key is the same.
    else {
      node->count++;
    }
    return node;
  }
  Node * Delete(struct Node* node, int key)
  {
    if (node == NULL) {
      return node;
    } 

    if (key < node->key) {
      node->leftChild = Delete(node->leftChild, key);
    }

    else if (key > node->key) {
      root->rightChild = Delete(node->rightChild, key);
    }

    else
    {
      if (root->count > 1)
      {
        node->count--;
        return node;
      }

      if (node->leftChild == NULL)
      {
        Node * temp = node->rightChild;
        free(node);
        return temp;
      }
      else if (node->rightChild == NULL)
      {
        Node * temp = node->leftChild;
        free(node);
        return temp;
      }

      Node * current = node->rightChild;
      while (current->leftChild != NULL) {
        current = current->leftChild;
      }
      Node * temp = current;
      node->key = temp->key;
      node->rightChild = Delete(node->rightChild, temp->key);
      
    }
    return node;
  }
  
public:
  void Inorder() {
    Inorder(root);
  }
  Node * Search(int key) {
    return Search(root, key);
  }
  Node * Insert(int key) {
    return Insert(root, key);
  }
  Node * Delete(int key) {
    return Delete(root, key);
  }

  Node * root = nullptr;
};

int main()
{
  //Create BinaryTree.
  BinaryTree binaryTree;
  //Insert a bunch of numbers in the tree.
  binaryTree.Insert(10);
  binaryTree.Insert(15);
  binaryTree.Insert(5);
  binaryTree.Insert(0);
  binaryTree.Insert(10);

  //Print elements in Tree.
  binaryTree.Inorder();

  //Search for existing value.
  binaryTree.Search(10);
  //Search for unexisting value.
  binaryTree.Search(20);
  std::cout << std::endl;

  binaryTree.Delete(10);
  binaryTree.Inorder();
  std::cout << std::endl;
  binaryTree.Delete(10);
  binaryTree.Inorder();

}
