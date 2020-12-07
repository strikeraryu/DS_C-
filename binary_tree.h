#include <iostream>
#include "doubly_linked_list.h"
using namespace std;

//--------------------------------------------------------------------------------------------
/**----------------
  Binary Tree
 ---------------**/

template <typename Object>

class binary_tree
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
    int thesize;

public:
    // constructors
    // Default constructors
    binary_tree()
    {
        root = NULL;
        thesize = 0;
    }

    // Copy Constructor
    binary_tree(const binary_tree &rhs) { operator=(rhs); }

    // Destructor
    ~binary_tree()
    {
        List<Node *> q;
        q.push_back(root);

        while (q.empty())
        {
            Node *curr = q.front();
            q.pop_front();

            if (curr->left)
            {
                q.push_back(curr->left);
            }

            if (curr->right)
            {
                q.push_back(curr->right);
            }

            delete curr;
        }
    }

    // operator overloading
    const binary_tree &operator=(const binary_tree &rhs)
    {
        if (rhs.root)
        {

            root = new Node(rhs.root->data);
            List<Node *> q1;
            List<Node *> q2;
            q1.push_back(rhs.root);
            q2.push_back(root);

            while (!q1.empty())
            {
                Node *src = q1.front();
                q1.pop_front();
                Node *dst = q2.front();
                q2.pop_front();

                if (src->left)
                {
                    dst->left = new Node(src->left->data);
                    q1.push_back(src->left);
                    q2.push_back(dst->left);
                }

                if (src->right)
                {
                    dst->right = new Node(src->right->data);
                    q1.push_back(src->right);
                    q2.push_back(dst->right);
                }
            }

            thesize = rhs.thesize;
        }
    }

    // main functions
    bool empty() { return thesize == 0; }
    int size() { return thesize; }
    Node *&get_root() { return root; }

    // clear the tree
    void clear()
    {
        ~binary_tree();
        root = NULL;
    }

    // insert data at last location
    void insert(Object d)
    {
        if (root == NULL)
        {
            root = new Node(d);
            thesize++;
            return;
        }
        List<Node *> q;
        q.push_back(root);
        Node *last;
        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop_front();

            if (curr->left == NULL && curr->right == NULL)
            {
                curr->left = new Node(d);
                thesize++;
                return;
            }
            else if (curr->right == NULL)
            {
                curr->right = new Node(d);
                thesize++;
                return;
            }
            q.push_back(curr->left);
            q.push_back(curr->right);
        }
    }

    // delete last node
    void delete_last()
    {
        if (root == NULL)
            return;

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            thesize--;
            return;
        }

        List<Node *> q1;
        List<Node *> q2;
        q1.push_back(root);
        q2.push_back(root);

        Node *last = NULL;

        while (!q1.empty())
        {
            Node *curr = q1.front();
            q1.pop_front();
            last = q2.front();
            q2.pop_front();

            if (curr->left)
            {
                q1.push_back(curr->left);
                q2.push_back(curr);
            }
            if (curr->right)
            {
                q1.push_back(curr->right);
                q2.push_back(curr);
            }
        }

        if (last != NULL)
        {
            if (last->right != NULL)
            {
                delete last->right;
                last->right = NULL;
                thesize--;
            }
            else if (last->left != NULL)
            {
                delete last->left;
                last->left = NULL;
                thesize--;
            }
        }
    }

    // delete last node with specific data
    void delete_node(Object d)
    {

        if (root != NULL)
        {
            if (root->left == NULL && root->right == NULL)
            {
                if (root->data == d)
                {
                    delete root;
                    root = NULL;
                    thesize--;
                }
                return;
            }
        }
        else
        {
            return;
        }

        List<Node *> q;
        q.push_back(root);
        Node *tmp = NULL;
        Object last;
        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop_front();

            if (curr->data == d)
            {
                tmp = curr;
            }

            if (curr->left)
            {
                q.push_back(curr->left);
            }

            if (curr->right)
            {
                q.push_back(curr->right);
            }

            last = curr->data;
        }
        if (tmp)
        {
            tmp->data = last;
            delete_last();
        }
    }

    // find if specific data is in tree
    bool find(const Object &d)
    {
        if (root == NULL)
        {
            return false;
        }

        List<Node *> q;
        q.push_back(root);
        Node *last;
        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop_front();

            if (curr->data == d)
            {
                return true;
            }

            if (curr->left)
            {
                q.push_back(curr->left);
            }

            if (curr->right)
            {
                q.push_back(curr->right);
            }
        }

        return false;
    }

    // print tree in inorder
    void print_inorder(Node *node)
    {
        if (node == NULL)
        {
            return;
        }

        print_inorder(node->left);
        cout << node->data << " ";
        print_inorder(node->right);
    }

    // print tree in postorder
    void print_postorder(Node *node)
    {
        if (node == NULL)
        {
            return;
        }

        print_postorder(node->left);
        print_postorder(node->right);
        cout << node->data << " ";
    }


    // print tree in preorder
    void print_preorder(Node *node)
    {
        if (node == NULL)
        {
            return;
        }

        cout << node->data << " ";
        print_preorder(node->left);
        print_preorder(node->right);
    }
};
//---------------------------------------------------------------------