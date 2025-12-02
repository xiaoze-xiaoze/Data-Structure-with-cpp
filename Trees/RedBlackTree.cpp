#include <iostream>
#include "..\Error.cpp"

template<typename T>
class RedBlackTree {
public:
    enum Color {RED, BLACK};
    struct Node {
        T data;
        Node* parent;
        Node* left;
        Node* right;
        Color color;
    };
     Node* root;

protected:
    void rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* orphan = newRoot->left;
        newRoot->left = node;
        node->right = orphan;
        newRoot->parent = node->parent;
        node->parent = newRoot;
        if (orphan) orphan->parent = node;
        if (newRoot->parent == nullptr) root = newRoot;
        else if (newRoot->parent->left == node) newRoot->parent->left = newRoot;
        else newRoot->parent->right = newRoot;
    }

    void rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* orphan = newRoot->right;
        newRoot->right = node;
        node->left = orphan;
        newRoot->parent = node->parent;
        node->parent = newRoot;
        if (orphan) orphan->parent = node;
        if (newRoot->parent == nullptr) root = newRoot;
        else if (newRoot->parent->left == node) newRoot->parent->left = newRoot;
        else newRoot->parent->right = newRoot;
    }

    void insertFixUp(Node* node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } 
                else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRight(grandparent);
                }
            }
            else {
                Node* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } 
                else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeft(grandparent);
                }
            }
        }
        root->color = BLACK;
    }

    void removeFixUp(Node* node) {

    }

    void erase(Node* node) {
        if (node != nullptr) {
            erase(node->left);
            erase(node->right);
            delete node;
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() { clear(); }

    std::expected <void, DataStructureError> insert(const T& value) {
        Node* newNode = nullptr;
        if (root == nullptr) {
            root = new Node{value, nullptr, nullptr, nullptr, BLACK};
            return {};
        }
        Node* current = root;
        while (current != nullptr) {
            if (value < current->data) {
                if (current->left == nullptr) {
                    newNode = new Node{value, current, nullptr, nullptr, RED};
                    current->left = newNode;
                    break;
                }
                current = current->left;
            }
            else if (value > current->data) {
                if (current->right == nullptr) {
                    newNode = new Node{value, current, nullptr, nullptr, RED};
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }
            else {
                return std::unexpected(DataStructureError::DuplicateValue);
            }
        }
        insertFixUp(newNode);
        return {};
    }

    void clear() {
        erase(root);
        root = nullptr;
    }
};