#include<iostream>
#include<vector>
using namespace std;

// Here we have developed a class Node. Node is the basic part of a binary search tree. 
// Node stores the data and also it stores pointer variables to the left node and the right node.
class Node
{
    public:
    int data;
    Node* left;
    Node* right;

    Node(int data)
    {
        this->data = data;
        left = right = NULL;
    }
};

// Here we have developed our Binary Search Tree class which has the root node and the helper functions
class BST
{
    public:
    Node* root;
    BST()
    {
        root = NULL;
    }

    void insert(int data)
    {
        root = insertHelper(root , data);
    }

    void inOrderTraversal(Node* root)
    {
        if(root == NULL) return;
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }

    void preOrderTraversal(Node* root)
    {
        if(root == NULL) return;
        cout << root->data << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }

    void postOrderTraversal(Node* root)
    {
        if(root == NULL) return;
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << root->data << " ";
    }

    Node* inOrderSuccessor(Node* root)
    {
        while(root && root->left != NULL)
        {
            root = root->left;
        }
        return root;
    }

    void deleteNode(int key) // This is the delete Node function calling the it's helper function to delete the node.
    {
        root = deleteNodeHelper(root , key);
    }

    int size(Node* root) //This function returns the size i.e, number of nodes in the binary tree.
    {
        if(root == NULL) return 0;
        return 1+size(root->left)+size(root->right);
    }

    bool isLeaf(Node* node)
    {
        return node != NULL && node->left == NULL && node->right == NULL;
    }

    int height(Node * root) //Height is the longest path between the root node and any leaf node.
    {
        if(root == NULL) return -1;
        return 1+max(height(root->left) , height(root->right));  
    }

    void clear(Node* root) // Clear the whole tree recursively 
    {
        if(root == NULL) return;
        clear(root->left);  
        clear(root->right);
        delete root;
    }

    Node* search(Node* root , int key) //This function returns the refernce to the root searched.
    {
        if(root == NULL || root->data == key) return root;
        if(key < root->data) 
        return search(root->left , key);
        else 
        return search(root->right , key);
    }   

    Node* min_node(Node* root)   //Iterative approach to return the minimum value because we know that the left most value in a BST is the smallest value in the tree.
    {
        if(root == NULL) return NULL;
        while(root->left != NULL)  root = root->left;
        return root;
    }

    //Alternative recursive approach :

    // Node* min(Node* root)
    // {
    //     if(root == NULL) return NULL;
    //     if(root->left == NULL) return root;
    //     return min(root->left);
    // }

    Node* max_node(Node* root) //Iterative approach for max function 
    {
        if(root == NULL) return NULL;
        if(root->right == NULL) return root;
        max_node(root->right);
    }


    Node* successor(Node* root , Node* target)
    {
        if(target->right != NULL)
        {
            root = target->right;
            while(root->left != NULL) root = root->left;
            return root;
        }
        Node* succ = NULL;
        while(root != NULL)
        {
            if(target->data < root->data)
            {
                succ = root;
                root = root->left;
            }
            else if(target->data > root->data)
            {
                root = root->right;
            }
            else break;
        }
        return succ;
    }

    Node* predecessor(Node* root , Node* target)
    {
        if(target->left != NULL)
        {
            root = root->left;
            while(root->right != NULL) root = root->right;
            return root;
        }

        Node* pred = NULL;
        while(root != NULL)
        {
            if(target->data > root->data)
           {
              pred = root;
              root = root->right;
           }
           else if(target->data < root->data)
           {
              root = root->left;
           }
           else break;
        }
        return pred;
    }

    private:
    //This is the helper method because if we call it multiple times in the main function without updating the root node it will cause problems and confusions. That's why we have added a simple deleteNod method internally calling the helper method.

    Node* deleteNodeHelper(Node* root , int key) //Deleting a specific node using key of that node 
    {
        if(root == NULL) return root;  //If the current root node for the current recursion is empty simply return the node

        if(key < root->data)
        {
            root->left = deleteNodeHelper(root->left , key);
        }
        else if(key > root->data)
        {
            root->right = deleteNodeHelper(root->right , key);
        }
        else
        {
            //If anyone child node is NULL then simply change the root with the other child and delete the root node.
            if(root->right == NULL)
            {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            else if(root->left == NULL)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else //If the node has 2 children we have to maintain the structure of the binary search tree. For that purpose we first find our inorder successor i.e , the incoming value if we traverse inorderly thorugh the BST and we replace the node with that node and delete the required node.
            {
                Node* temp = inOrderSuccessor(root->right);
                root->data = temp->data;
                root->right = deleteNodeHelper(root->right , temp->data);
            }
        }
        return root;
    }


     //This is the hpler funtion for the insert and has the same reason to have this as mentioned for the above one!
    Node* insertHelper(Node* root , int data)
    {
        if(root == NULL) 
        {
            return new Node(data);
        }

        if(data < root->data)
        {
            root->left = insertHelper(root->left , data);
        }
        else if(data > root->data)
        {
            root->right = insertHelper(root->right , data);
        }
        return root;
    }
};

int main()
{
    BST* myTree = new BST();
    vector<int> myV = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for(int i = 0 ; i < myV.size() ; i++)
    {
        myTree->insert(myV[i]);
    }

    cout<<myTree->height(myTree->root)<<endl;  
    cout<<(myTree->min_node(myTree->root))->data;
}