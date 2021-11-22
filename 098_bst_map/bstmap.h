#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  struct Node {
    Node * left;
    Node * right;
    K key;
    V value;

    Node() : left(NULL), right(NULL), key(K()), value(V()) {}
    Node(K key, V value) : left(NULL), right(NULL), key(key), value(value) {}
  };

  Node * root;

 public:
  virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    *current = new Node(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("invalid key");
  }

  Node * getSimilarNode(Node * curr) {
    while (curr != NULL && curr->left != NULL) {
      curr = curr->left;
    }
    return curr;
  }
  Node * removeHelper(Node * curr, const K & key) {
    if (curr == NULL) {
      return NULL;
    }
    else if (key < curr->key) {
      curr->left = removeHelper(curr->left, key);
    }
    else if (key > curr->key) {
      curr->right = removeHelper(curr->right, key);
    }
    else {
      // leaf node
      if (curr->left == NULL && curr->right == NULL) {
        delete curr;
        curr = NULL;
      }
      else if (curr->left == NULL) {
        Node * temp = curr->right;
        delete curr;
        curr = temp;
      }
      else if (curr->right == NULL) {
        Node * temp = curr->left;
        delete curr;
        curr = temp;
      }
      else {
        Node * temp = getSimilarNode(curr->right);
        curr->key = temp->key;
        curr->value = temp->value;
        curr->right = removeHelper(curr->right, curr->key);
      }
    }

    return curr;
  }

  virtual void remove(const K & key) { removeHelper(root, key); }
  void destroy(Node * root) {
    if (root == NULL) {
      return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
  }
  virtual ~BstMap<K, V>() { destry(root); }
};
