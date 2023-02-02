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

public:
    Node* root = nullptr;
    void leftRotation(Node*);
    void rightRotation(Node*);
    void fixcolors(Node*);
    void insert(int, Node*);

};

void Red_Black_tree::leftRotation(Node* r){
    Node *p = r->rightchild;
    if (r->parent != nullptr) p->parent = r->parent;
    if (r->parent == nullptr){
        root = p;
        p->parent = nullptr;
    }
    else
    {
        if(r==r->parent->leftchild)
            r->parent->leftchild=p;
        else
            r->parent->rightchild=p;
    }
    if (p->leftchild != nullptr) p->leftchild->parent = r;
    r->rightchild = p->leftchild;
    r->parent = p;
    p->leftchild = r;
    return;
}

void Red_Black_tree::rightRotation(Node* r){
    Node *p = r->leftchild;
    if (r->parent != nullptr) p->parent = r->parent;
    if (r->parent == nullptr){
        root = p;
        p->parent = nullptr;
    }
    else
    {
        if(r==r->parent->leftchild)
            r->parent->leftchild = p;
        else
            r->parent->rightchild = p;
    }
    if (p->rightchild != nullptr) p->rightchild->parent = r;
    r->leftchild = p->rightchild;
    p->rightchild = r;
    r->parent = p;
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
                        leftRotation(temp->parent);
                    }
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
                    if(temp->parent->leftchild != nullptr and temp->parent->leftchild == temp){
                        rightRotation(temp->parent);
                    }
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

void Red_Black_tree::insert(int number, Node* par){
    Node *p,*q;
    Node *t=new Node(nullptr,number,'R');
    p=root;
    q= nullptr;
    if(root== nullptr)
    {
        root=t;
        root->color = 'B';
        return;
    }
    else
    {
        while(p!= nullptr)
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
    fixcolors(t);

    return;
}

int main(){
    Red_Black_tree tree;
    char commant;
    int number = 0;
    std::cin >> commant;
    while (commant != 's'){
        if (commant == 'a'){
            std::cin >> number;
            tree.insert(number, nullptr);
        }
        std::cin >> commant;
    }

    return 0;
}
