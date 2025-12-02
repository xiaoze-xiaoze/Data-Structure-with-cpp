#include "BinarySearchTree.cpp"

template<typename T>
class AVLTree : public BinarySearchTree<T> {
public:
    using Node = typename BinaryTree<T>::Node;
    using BinaryTree<T>::root;

protected:
    int getBalanceFactor (Node* node) const {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

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

    void rebalance(Node* node) {
        while (node != nullptr) {
            int balance = getBalanceFactor(node);
            if (balance > 1 && getBalanceFactor(node->left) >= 0) rotateRight(node);
            else if (balance > 1 && getBalanceFactor(node->left) < 0) {
                rotateLeft(node->left);
                rotateRight(node);
            }
            else if (balance < -1 && getBalanceFactor(node->right) <= 0) rotateLeft(node);
            else if (balance < -1 && getBalanceFactor(node->right) > 0) {
                rotateRight(node->right);
                rotateLeft(node);
            }
            node = node->parent;
        }
    }

public:
    AVLTree() : BinarySearchTree<T>() {}
    
    std::expected<void, DataStructureError> insert(const T& value) {
        if (root == nullptr) {
            root = new Node(value, nullptr, nullptr, nullptr);
            return {};
        }
        Node* current = root;
        while (current != nullptr) {
            if (value < current->data) {
                if (current->left == nullptr) {
                    current->left = new Node(value, nullptr, nullptr, current);
                    break;
                }
                current = current->left;
            } 
            else if (value > current->data) {
                if (current->right == nullptr) {
                    current->right = new Node(value, nullptr, nullptr, current);
                    break;
                }
                current = current->right;
            } 
            else return std::unexpected(DataStructureError::DuplicateValue);
        }
        rebalance(current->parent);
        return {};
    }

    std::expected<void, DataStructureError> remove(const T& value) {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        TRY(target, this->find(value));
        Node* rebalanceStart = nullptr;
        if (target->left == nullptr && target->right == nullptr) {
            rebalanceStart = target->parent;
            if (target == root) root = nullptr;
            else if (target == target->parent->left) target->parent->left = nullptr;
            else target->parent->right = nullptr;
            delete target;
        }
        else if (target->left == nullptr || target->right == nullptr) {
            Node* child = target->left ? target->left : target->right;
            rebalanceStart = target->parent;
            if (target == root) {
                root = child;
                root->parent = nullptr;
            }
            else if (target->parent->left == target) {
                target->parent->left = child;
                child->parent = target->parent;
            }
            else {
                target->parent->right = child;
                child->parent = target->parent;
            }
            delete target;
        }
        else {
            Node* successor = target->right;
            while (successor->left != nullptr) successor = successor->left;
            target->data = successor->data;
            rebalanceStart = successor->parent;
            if (successor->parent->left == successor) successor->parent->left = successor->right;
            else successor->parent->right = successor->right;
            if (successor->right != nullptr) successor->right->parent = successor->parent;
            delete successor;
        }
        rebalance(rebalanceStart);
        return {};
    }
};