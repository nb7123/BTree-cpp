//
// Created by michael on 18-9-11.
//

#include <cassert>
#include "BSTree.h"

BSTree::BSTree() {
    root = nullptr;
    depth = 0;
}

void BSTree::insert(Node *parent, const int &value) {
    if (parent->value > value) {
        if (parent->left) insert(parent->left, value);
        else {
            auto node = new Node(Node::NODE_TYPE_LEFT, value);
            node->parent = parent;
            parent->left = node;

            depth = calDepth(root);
        }
    } else {
        if (parent->right) insert(parent->right, value);
        else {
            auto node = new Node(Node::NODE_TYPE_RIGHT, value);
            node->parent = parent;
            parent->right = node;

            depth = calDepth(root);
        }
    }
}

int BSTree::calDepth(Node *root) {
    int depth = 0;
    if (root) {
        depth = 1;
        int l = calDepth(root->left);
        int r = calDepth(root->right);
        depth += l > r ? l : r;
    } else {
        depth = 0;
    }

    return depth;
}

Node *BSTree::find(Node *parent, const int &value) {
    Node *found = nullptr;

    if (parent) {
        if (parent->value == value) {
            found = parent;
        } else if (parent->value > value) {
            found = find(parent->left, value);
        } else {
            found = find(parent->right, value);
        }
    }

    return found;
}

Node *BSTree::findMinNode(Node *root) {
    Node *node = nullptr;
    if (root->isLeaf() || !(root->left)) {
        node = root;
    } else {
        node = findMinNode(root ->left);
    }

    return node;
}

Node *BSTree::findMaxNode(Node *root) {
    Node *node = nullptr;
    if (root->isLeaf() || !(root->right)) {
        node = root;
    } else {
        node = findMinNode(root ->right);
    }

    return node;
}

bool BSTree::delNode(Node *parent, const int &value) {
    bool deleted = false;

    if (parent) {
        if (parent->value > value) {
            deleted = delNode(parent->left, value);
        } else if (parent->value < value) {
            deleted = delNode(parent->right, value);
        } else if (parent->value == value) {
            // leaf node
            if (!(parent->left) && !(parent->right)) {
                if (parent->nodeType == Node::NODE_TYPE_LEFT) {
                    parent->parent->left = nullptr;
                } else {
                    parent->parent->right = nullptr;
                }
            } else if (parent->left && !(parent->right)) {
                // only has left child
                if (parent->nodeType == Node::NODE_TYPE_LEFT) {
                    parent->parent->left = parent->left;
                } else {
                    parent->parent->right = parent->left;
                }
            } else if (!(parent->left) && parent->right) {
                // only has right child
                if (parent->nodeType == Node::NODE_TYPE_LEFT) {
                    parent->parent->left = parent->right;
                } else {
                    parent->parent->right = parent->right;
                }
            } else {
                // has left and right child
                auto leftMax = findMaxNode(parent->left);
                auto replaceNode = new Node(parent->nodeType, leftMax->value);
                deleted = delNode(parent, leftMax->value);
                assert(deleted);

                replaceNode->left = parent->left;
                replaceNode->right = parent->right;

                if (parent->nodeType == Node::NODE_TYPE_LEFT) {
                    parent->parent->left = replaceNode;
                } else {
                    parent->parent->right = replaceNode;
                }
            }

            delete parent;
            deleted = true;
        }
    }

    return deleted;
}

bool BSTree::insert(const int &value) {
    if (!root) {
        root = new Node(Node::NODE_TYPE_ROOT, value);
        depth += 1;
    }

    Node *exist = find(value);
    bool inserted = false;
    if (!exist) {
        inserted = true;
        insert(root, value);
    }

    return inserted;
}

Node *BSTree::find(const int &value) {
    return find(root, value);
}

bool BSTree::delNode(const int &value) {
    return delNode(root, value);
}

void BSTree::printL2R() {
    printL2R(root);
}

void BSTree::printMinddle() {
    printMinddle(root);
}

void BSTree::printR2L() {
    printR2L(root);
}

void BSTree::printL2R(Node *root) {
    if (root->left) {
        printL2R(root->left);
    }
    root->print();
    if (root->right) {
        printL2R(root->right);
    }
}

void BSTree::printMinddle(Node *root) {
    root->print();
    if (root->left) {
        printMinddle(root->left);
    }
    if (root->right) {
        printMinddle(root->right);
    }
}

void BSTree::printR2L(Node *root) {
    if (root->right) {
        printR2L(root->right);
    }
    root->print();
    if (root->left) {
        printR2L(root->left);
    }
}

int BSTree::getDepth() {
    return this->depth;
}

BSTree::~BSTree() {
    if (root) delete root;
}
