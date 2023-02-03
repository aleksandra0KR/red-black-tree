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
    Node* root = nullptr;

public:
    void leftRotation(Node*);
    void rightRotation(Node*);
    void fixcolors(Node*);
    void insert(int, Node*);
    void deleteByVal(int);
    Node* exist(int);
    void del(Node*);
    Node* node_for_replacement(Node*);
    void replace_nodes(Node*, Node*);
    void fixdelblack(Node*);

};

Node* Red_Black_tree::exist(int number){
    Node* temp = root;
    while (temp != nullptr){
        if (temp->data == number) return temp;
        if (temp->data < number){
            temp = temp->rightchild;
        }
        else temp = temp->leftchild;
    }
    return nullptr;
}

Node* Red_Black_tree::node_for_replacement(Node* r){
    Node* temp = nullptr;
    if(r->leftchild != nullptr){
        temp = r->leftchild;
        while(temp->leftchild != nullptr){
            temp = temp->leftchild;
        }
    }
    else{
        temp = r->rightchild;
        while (temp->leftchild != nullptr){
            temp = temp->leftchild;
        }
    }
    return temp;

}

void Red_Black_tree::replace_nodes(Node* deletednode, Node* replacement){
    int temp = deletednode->data;
    deletednode->data = replacement->data;
    replacement->data = temp;
}

void Red_Black_tree::fixdelblack(Node* r){

    char siblingpos;
    Node* sibling = nullptr;
    if (r->parent->leftchild != nullptr and r->parent->leftchild == r) {
        sibling = r->parent->rightchild;
        siblingpos = 'R';
    }
    else {
        sibling = r->parent->leftchild;
        siblingpos = 'L';
    }

    if (sibling == nullptr) {

        // No sibiling, double black pushed up
        fixdelblack(r->parent);

    }
    else {

        if (sibling->color == 'R') {
            // Sibling red
            r->parent->color = 'R';
            sibling->color = 'B';

            if (siblingpos == 'L') {
                // left case
                rightRotation(r->parent);
            }
            else {
                // right case
                leftRotation(r->parent);
            }

            fixdelblack(r);
        }
        else {
            // Sibling black
            if ((sibling->leftchild != nullptr and sibling->leftchild->color == 'R') or (sibling->rightchild != nullptr and sibling->rightchild->color == 'R')) {
                // at least 1 red children
                if (sibling->leftchild!= nullptr and sibling->leftchild->color == 'R') {
                    if (siblingpos == 'L') {

                        // left left
                        sibling->leftchild->color = sibling->color;
                        sibling->color = r->parent->color;
                        rightRotation(r->parent);

                    }
                    else {
                        // right left
                        sibling->leftchild->color = r->parent->color;
                        rightRotation(sibling);
                        leftRotation(r->parent);
                    }
                }
                else {
                    if (siblingpos == 'L') {
                        // left right
                        sibling->rightchild->color = r->parent->color;
                        leftRotation(sibling);
                        rightRotation(r->parent);
                    }
                    else {

                        // right right
                        sibling->rightchild->color = sibling->color;
                        sibling->color = r->parent->color;
                        leftRotation(r->parent);
                    }
                }
                r->parent->color = 'B';
            } else {
                // 2 black children
                sibling->color = 'R';
                if (r->parent->color == 'B')
                    fixdelblack(r->parent);
                else
                    r->parent->color = 'B';
            }
        }
    }
}

void Red_Black_tree::del(Node* deletednode){

    if (deletednode == nullptr) return; // if isn't in the tree

    char deletedcolot = deletednode->color;

    // if it's a single root
    if (root == deletednode and root->leftchild == nullptr and root->rightchild == nullptr){
        delete root;
        root = nullptr;
    }

    // if it's red leaf node
    else if (deletednode->color == 'R' and deletednode->rightchild == nullptr and deletednode->leftchild == nullptr){
        // find which child it is
        if (deletednode->parent->leftchild != nullptr and deletednode->parent->leftchild == deletednode) {
            Node* par = deletednode->parent;
            delete par->leftchild;
            par->leftchild = nullptr;
            return;
        }
        else {
            //delete deletednode->parent->rightchild;
            deletednode->parent->rightchild = NULL;
            return;
        }
    }
    else if (deletednode->rightchild == nullptr and deletednode->leftchild == nullptr){
        if (deletednode->parent->leftchild != nullptr and deletednode->parent->leftchild == deletednode){
            if (deletednode->parent->rightchild != nullptr) deletednode->parent->rightchild->color == 'R';
            deletednode->parent->leftchild == nullptr;
        }
        else{
            if (deletednode->parent->leftchild != nullptr) deletednode->parent->leftchild->color == 'R';
            deletednode->parent->rightchild == nullptr;
        }
        //delete deletednode;
    }

    // if it has only one child
    else if(deletednode->rightchild == nullptr or deletednode->leftchild == nullptr) {
        // if it is a root
        if (deletednode == root){
            if (deletednode->rightchild != nullptr){ // if it has a right child
                root = deletednode->rightchild;
                root->parent = nullptr;
                root->color = 'B';
                delete deletednode;
            }
            else{
                root = deletednode->leftchild;
                root->parent = nullptr;
                root->color = 'B';
                delete deletednode;
            }
        }
        // if it's not a root
        else{
            Node* replacement = Red_Black_tree::node_for_replacement(deletednode);;
            if(deletednode->parent->leftchild != nullptr and deletednode->parent->leftchild == deletednode){
                deletednode->parent->leftchild = replacement;
                replacement->parent = deletednode->parent;
            }

            else {
                deletednode->parent->rightchild = replacement;
                replacement->parent = deletednode->parent;
            }

            delete deletednode;

            if (deletedcolot == replacement->color){
                fixdelblack(replacement);
            }
            else{
                replacement->color = 'B';
            }

        }
    }

    else{ // 2 children
        Node* replacement = Red_Black_tree::node_for_replacement(deletednode);
        Red_Black_tree::replace_nodes(deletednode, replacement);
        Red_Black_tree::del(replacement);
    }
    return;
}


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
void Red_Black_tree::deleteByVal(int number) {

    Node *v = exist(number);
    del(v);

}

int main(){
    Red_Black_tree tree;
    char commant;
    int number = 0;
    Node* delnode = nullptr;
    std::cin >> commant;
    while (commant != 's'){
        if (commant == 'a'){
            std::cin >> number;
            tree.insert(number, nullptr);
        }
        else if (commant == 'd'){
            std::cin >> number;
            tree.deleteByVal(number);
        }
        std::cin >> commant;
    }

    return 0;
}
