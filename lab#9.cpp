#include <iostream>
#include <string>
using namespace std;

class KeyValuePair {
private:
    string key;
    string value;

public:
    KeyValuePair(const string &k, const string &v) : key(k), value(v) {}
    KeyValuePair() : key(""), value("") {}

    const string& getKey() const   { return key; }
    const string& getValue() const { return value; }
    void setKey(const string &k)   { key = k; }
    void setValue(const string &v) { value = v; }

    bool operator<(const KeyValuePair &rhs) const {
        return key < rhs.key;
    }
    bool operator>(const KeyValuePair &rhs) const {
        return key > rhs.key;
    }
    bool operator==(const KeyValuePair &rhs) const {
        return key == rhs.key;
    }
};

template <typename T>
class SplayTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T &d) : data(d), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, const T &key) {
        if (!root || root->data == key) {
            return root;
        }

        if (key < root->data) {
            if (!root->left) return root;
            if (key < root->left->data) {
                root->left->left = splay(root->left->left, key);
                root = rotateRight(root);
            }
            else if (key > root->left->data) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right) {
                    root->left = rotateLeft(root->left);
                }
            }
            return (root->left == nullptr) ? root : rotateRight(root);
        }
        else {
            if (!root->right) return root;
            if (key < root->right->data) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left) {
                    root->right = rotateRight(root->right);
                }
            }
            else if (key > root->right->data) {
                root->right->right = splay(root->right->right, key);
                root = rotateLeft(root);
            }
            return (root->right == nullptr) ? root : rotateLeft(root);
        }
    }

    Node* bstInsert(Node* root, const T &val) {
        if (!root) {
            return new Node(val);
        }
        if (val < root->data) {
            root->left = bstInsert(root->left, val);
        } else if (val > root->data) {
            root->right = bstInsert(root->right, val);
        } else {
            root->data = val;
        }
        return root;
    }

    Node* findMax(Node* node) {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

    void clearHelper(Node* root) {
        if (!root) return;
        clearHelper(root->left);
        clearHelper(root->right);
        delete root;
    }

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree() {
        clearHelper(root);
    }

    void insert(const T &val) {
        root = bstInsert(root, val);
        root = splay(root, val);
    }

    bool search(const T &key) {
        root = splay(root, key);
        return (root && root->data == key);
    }

    T find(const T &key, bool &found) {
        root = splay(root, key);
        if (root && root->data == key) {
            found = true;
            return root->data;
        }
        found = false;
        return T();
    }

    T remove(const T &key) {
        if (!root) return T();

        root = splay(root, key);

        if (root && root->data == key) {
            T removedData = root->data;
            if (!root->left) {
                Node* temp = root;
                root = root->right;
                delete temp;
            } else {
                Node* temp = root;
                Node* leftSubtree = root->left;
                Node* rightSubtree = root->right;
                delete temp;

                Node* maxNode = findMax(leftSubtree);
                leftSubtree = splay(leftSubtree, maxNode->data);

                leftSubtree->right = rightSubtree;
                root = leftSubtree;
            }
            return removedData;
        }
        return T();
    }
};

class TreeMap {
private:
    SplayTree<KeyValuePair> tree;

public:
    void insert(const string &key, const string &value) {
        KeyValuePair kv(key, value);
        tree.insert(kv);
    }

    string get(const string &key) {
        bool found = false;
        KeyValuePair kv(key, "");
        KeyValuePair result = tree.find(kv, found);
        if (found) {
            return result.getValue();
        }
        return "";
    }

    string deleteKey(const string &key) {
        KeyValuePair kvToRemove(key, "");
        KeyValuePair removed = tree.remove(kvToRemove);
        if (removed.getKey().empty()) {
            return "";
        }
        return removed.getValue();
    }
};

 
int main() {
  TreeMap map;
 
  // Insert a number of key-value pairs into the tree map
  map.insert("keyOne", "valueOne");
  map.insert("keyTwo", "valueTwo");
  map.insert("keyThree", "valueThree");
 
  // Prints out valueOne
  std::cout << map.get("keyOne");
 
  // Prints out valueThree
  std::cout << map.get("keyThree");
 
  // Prints out an empty string or some default value of your choice
  std::cout << map.get("keyDoesNotExist");
 
  // Deletes the key-value pair from the tree map
  std::cout << map.deleteKey("keyOne");

}
