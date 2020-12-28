#include <iostream>
#include "doubly_linked_list.h"
using namespace std;

//--------------------------------------------------------------------------------------------
/**----------------
  Binary Search Tree
 ---------------**/

template <typename Object>

class binary_search_tree
{

private:
    struct Node
    {
        Object data;
        Node *left;
        Node *right;

        Node(const Object d = Object(), Node *l = NULL, Node *r = NULL) : data(d), left(l), right(r) {}
    };

    Node *root;

    void insert(const Object &x, Node *&t) const
    {
        if (t == NULL)
            t = new Node(x);

        else if (t->data > x)
            insert(x, t->left);
        else if (t->data < x)
            insert(x, t->right);

        else
            return; // duplicate elements
    }

    void remove(const Object &x, Node *&t) const
    {
        if (t == NULL)
            return;

        else if (t->data > x)
            remove(x, t->left);
        else if (t->data < x)
            remove(x, t->right);

        else if (t->left != NULL && t->right != NULL)
        {
            t->data = find_min(t->right)->data;
            remove(t->element, t->right);
        }

        else
        {
            Node *old_node = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete old_node;
        }
    }

    Node *find_min(Node *t) const
    {
        if (t == NULL)
            return NULL;

        if (t->left == NULL)
            return t;

        find_min(t->left);
    }

    Node *find_max(Node *t) const
    {
        if (t == NULL)
            return NULL;

        if (t->right == NULL)
            return t;

        find_max(t->right);
    }

    bool contains(const Object &x, Node *t) const
    {
        if (t == NULL)
            return false;

        else if (t->data > x)
            return contains(x, root->left);
        else if (t->data < x)
            return contains(x, t->right);

        else
            return true;
    }

    void make_empty(Node *&t)
    {
        if (t != NULL)
        {
            make_empty(t->left);
            make_empty(t->right);
            delete t;
        }

        t = NULL;
    }

    void print_tree(Node *t) const
    {
        if (t == NULL)
            return;

        print_tree(t->left);
        print_tree(t->right);

        cout << t->data << " ";
    }

    Node *clone(Node *t) const
    {
        if (t == NULL)
            return NULL;

        return new Node(t->data, clone(t->left), clone(t->right));
    }

public:
    // constructors
    // default constructor
    binary_search_tree()
    {
        root = new Node();
    }

    // copy constructor
    binary_search_tree(const binary_search_tree &rhs);

    // destructor
    ~binary_search_tree()
    {
        make_empty();
    }

    const Object &find_min() const
    {
        return find_min(root);
    }

    const Object &find_max() const
    {
        return find_max(root);
    }

    bool contains(const Object &x) const
    {
        return contains(x, root);
    }

    bool is_empty() const
    {
        if (root == NULL)
            return true;

        return false;
    }

    void print_tree() const
    {
        print_tree(root);
    }

    // modifier function
    void make_empty()
    {
        make_empty(root);
    }

    void insert(const Object &x)
    {
        return insert(x, root);
    }

    void remove(const Object &x)
    {
        return remove(x, root);
    }

    // '=' operator overloading
    const binary_search_tree &operator=(const binary_search_tree &rhs)
    {
        if (this != rhs)
        {
            make_empty();
            root = colne(rhs);
        }

        return *this;
    }
};

//---------------------------------------------------------------------