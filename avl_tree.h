#include <iostream>
#include "doubly_linked_list.h"
using namespace std;

//--------------------------------------------------------------------------------------------
/**----------------
  AVL Tree
 ---------------**/

template <typename Object>

class avl_tree
{

private:
    struct Node
    {
        Object data;
        Node *left;
        Node *right;
        int height;

        Node(const Object d = Object(), Node *l = NULL, Node *r = NULL, int h = 0) : data(d), left(l), right(r), height(h) {}
    };

    Node *root;

    int height(const Node &n) const
    {
        return n == NULL ? -1 : n->height;
    }

    // AVL rotations
    void rotate_left(Node *&root)
    {
        Node *left_child = root->left;
        root->left = left_child->right;
        left_child->right = root;
        root->height = max(height(root->left), height(root->right)) + 1;
        left_child->height = max(height(left_child->left), height(left_child->right)) + 1;
        root = left_child;
    }

    void rotate_right(Node *&root)
    {
        Node *right_child = root->right;
        root->right = right_child->left;
        right_child->left = root;
        root->height = max(height(root->right), height(root->left)) + 1;
        right_child->height = max(height(right_child->right), height(right_child->left)) + 1;
        root = right_child;
    }

    void double_rotate_left(Node *&root)
    {
        rotate_right(root->left);
        rotate_left(root);
    }
 
    void double_rotate_right(Node *&root)
    {
        rotate_left(root->right);
        rotate_right(root);
    }

    void insert(const Object &x, Node *&t) const
    {
        if (t == NULL)
            t = new Node(x);

        else if (t->data > x)
        {
            insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (x < t->left->data)
                    rotate_left(t);
                else
                    double_rotate_left(t);
            }
        }
        else if (t->data < x)
        {
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->data)
                    rotate_right(t);
                else
                    double_rotate_right(t);
            }
        }

        else
            ; // duplicate elements
        t->height = max(height(t->left), height(t->right)) + 1;
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
    avl_tree()
    {
        root = new Node();
    }

    // copy constructor
    avl_tree(const avl_tree &rhs);

    // destructor
    ~avl_tree()
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
    const avl_tree &operator=(const avl_tree &rhs)
    {
        if (this != rhs)
        {
            make_empty();
            root = clone(rhs);
        }

        return *this;
    }
};

//---------------------------------------------------------------------
