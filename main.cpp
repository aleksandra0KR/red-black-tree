#include <iostream>
struct Node{
    int data;
    unsigned char color;
    Node *leftchild,*rightchild;
    Node *parent;
    Node( Node *par, int val, unsigned char c){
        leftchild = nullptr;
        rightchild = nullptr;
        parent = par;
        data = val;
        color = c;
    }
};
class Red_Black_tree{
private:
    Node* root;
public:
    void insert();
    void leftRotation(Node*);
    void rightRotation(Node*);
    void fixcolors(Node*);



};

void Red_Black_tree::leftRotation(Node* root){
    Node *p = root->rightchild;
     p->parent = root->parent;
    if (p->leftchild != nullptr) p->leftchild->parent = root;
    root->rightchild = p->leftchild;
    root->parent = p;
    p->leftchild = root;
    p->parent = nullptr;
    return;
}

void Red_Black_tree::rightRotation(Node* root){
    Node *p = root->leftchild;
    p->parent = root->parent;
    if (p->rightchild != nullptr) p->rightchild->parent = root;
    root->leftchild = p->rightchild;
    root->parent = p;
    p->rightchild = root;
    return;
}



void Red_Black_tree::fixcolors(Node* temp){ // takes inserted node
    if (temp->parent == nullptr){
        temp->color = 'B';
        return;
    }
        while(temp->parent!= nullptr and temp->parent->color == 'R'){

            if (temp->parent!= nullptr and temp->parent->parent->leftchild != nullptr and temp->parent->parent->leftchild == temp->parent){

                if (temp->parent->parent->rightchild != nullptr and temp->parent->parent->rightchild->color == 'R'){
                    // colorflip
                    temp->parent->parent->rightchild->color = 'B';
                    temp->parent->color = 'B';
                    temp->parent->parent->color = 'R';
                    temp = temp->parent->parent;
                }

                else{ // rotation
                    temp->color = 'R';
                    temp->parent->color = 'B';
                    temp->parent->parent->color = 'R';
                    if(temp->parent->rightchild != nullptr and temp->parent->rightchild == temp){
                        temp->parent->parent->leftchild = leftRotation(temp->parent);
                    }
                    if (temp->parent->parent->parent != nullptr) {
                        (temp->parent->parent->parent->leftchild) = rightRotation(temp->parent->parent);}
                    rightRotation(temp->parent->parent);
                    //rightRotation(temp->parent->parent);

                }
            }

            else{

                if (temp->parent->parent->leftchild != nullptr and temp->parent->parent->leftchild->color == 'R'){
                    // colorflip
                    temp->parent->parent->leftchild->color = 'B';
                    temp->parent->color = 'B';
                    temp->parent->parent->color = 'R';
                    temp = temp->parent->parent;
                }

                else{ // rotation
                    temp->color = 'R';
                    temp->parent->color = 'B';
                    temp->parent->parent->color = 'R';
                    if(temp->parent->rightchild != nullptr and temp->parent->rightchild == temp){
                        rightRotation(temp->parent);
                    }
                    if (temp->parent->parent->parent != nullptr) leftRotation(temp->parent->parent);
                    leftRotation(temp->parent->parent);

                }

            }
        }
    root->color = 'B';
    return;

    }


/*Node* insert(Node *root, int number, Node* par){
    if (root == nullptr){
        root = new Node(par, number, 'R');
        fixcolors(root);
        return root;
    }
    if( number<root->data ){
        root->leftchild = insert(root->leftchild, number, root);
        fixcolors(root->leftchild);}
    else{
        root->rightchild = insert(root->rightchild, number, root);
        fixcolors(root->rightchild);}
    root->color = 'B';
    return root;
}*/

Node* insert(Node *root, int number, Node* par){
    Node *p,*q;
    Node *t=new Node(nullptr,number,'R');
    p=root;
    q=NULL;
    if(root==NULL)
    {
        root=t;
        root->color = 'B';
        return root;
    }
    else
    {
        while(p!=NULL)
        {
            q=p;
            if(p->data < t->data)
                p=p->rightchild;
            else
                p=p->leftchild;
        }
        t->parent=q;
        if(q->data < t->data)
            q->rightchild=t;
        else
            q->leftchild=t;
    }
    root = fixcolors(t, root);

    return root;
}

int main(){
    Node* tree = nullptr;
    char commant;
    int number = 0;
    std::cin >> commant;
    while (commant != 's'){
        if (commant == 'a'){
            std::cin >> number;
            tree = insert(tree, number, nullptr);
        }
        std::cin >> commant;
    }

    return 0;
}
