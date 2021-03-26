#include<iostream>
#include<algorithm>



using namespace std;

class TreeNode{
    public:
    int *keys;
    int t;
    TreeNode **C;
    int n;
    bool leaf;
    TreeNode(int t,bool leaf){
        keys = new int[2*t-1];
        this->t = t;
        this->leaf = leaf;
        C = new TreeNode*[2*t];
        n=0;
    }
    void splitNode(int);
    void insertinNotFull(int);
    void traverse();
    void search(int);
};

class Tree{
    public:
    TreeNode *root;
    int t;
    Tree(int t){
        //Initializes the Empty Tree
        this->t = t;
        root = NULL;
    }
    void insert(int);
    void remove(int);
    void traverse() 
	{ 
		if (root != NULL) root->traverse(); 
	} 
    // function to search a key in this tree 
	void search(int k) 
	{ 
		if(root == NULL)  cout<<"key is not present in the Tree"<<endl;
        else{
            root->search(k);
        }
	} 
};

void Tree :: insert(int data){
    if(root == NULL){
        TreeNode *newNode = new TreeNode(t,true);
        newNode->keys[0] = data;
        newNode->n++;
        root = newNode;
        if(newNode->leaf == true){
            //
        }
    }
    else{
        if(root->n == 2*t-1){
            TreeNode *newNode = new TreeNode(t,false);
            newNode->C[0] = root;
            newNode->splitNode(0);
            //newNode will have two children now. Decide which children will have the new key
            int i=0;
            if(newNode->keys[i]<data){
                i++;
            }
            newNode->C[i]->insertinNotFull(data);

            root = newNode;

        }
        else
            root->insertinNotFull(data);
    }

}

void TreeNode :: insertinNotFull(int data){
    int i = n-1;
    if(leaf == true){ //if the node is the leaf node
        while(i>=0 && keys[i]>data){
            keys[i+1]=keys[i];
            i--;
        }
        keys[i+1] = data;
        n++;
    }
    else{
        //if the node is not leaf node
        //find the child of that node which will have the data
        while(i>=0 && keys[i] > data)
            i--;
        if(C[i+1]->n == 2*t-1){//if the found child which will have the data is full
            //split the child node
            splitNode(i+1);
            if (keys[i+1] < data) 
				i++; 
        }
        C[i+1]->insertinNotFull(data);
    }

}
void TreeNode :: splitNode(int i){

    TreeNode *newNode = new TreeNode(t,C[i]->leaf);
    newNode->n = t;
    int x = 0;
    //copy the last t keys of C[i+1] to new Node
    while(x<t){
        newNode->keys[x] = C[i]->keys[x+t-1];
        x++;
    }
    //Copy the last t Childs of C[i+1] to new Node
    if(C[i]->leaf == false){
        x=0;
     while(x<t){
            newNode->C[x] = C[i]->C[x+t-1];
            x++;
        }
    }
    else{ //part for B+tree
        newNode->C[2*t]=C[i]->C[2*t];
        C[i]->C[2*t] = newNode;
    }
    C[i]->n = t-1;
    
    //This node is going to have a new child so create a space for this newNode child
    x = n;
    while(x >= i+1){
        C[x+1] = C[x];
        x--;
    }
    //link the new Child to this node;
    C[i+1] = newNode;
    //A key from C[i+1] will move to this node
    // Find the location of the key and move all greater keys one space ahead
    x = n-1;
    while(x >= i){
        keys[x+1]=keys[x];
        x--;
    }
    keys[i] = C[i+1]->keys[0];
    //Increment the total keys count in this node
    n = n+1;

}
// Function to traverse all nodes in a subtree rooted with this node 
void TreeNode::traverse() 
{ 
	TreeNode *tmp = this;
    while(1){
        if(tmp->leaf) break;
        else{
            tmp = tmp->C[0];
        }
    }
    while(tmp){
        int len = tmp->n;
        for(int i=0; i<len; i++){
            cout<<tmp->keys[i] <<" ";
        }
        tmp = tmp->C[2*t];
        cout<<"\n";
    }
    //cout<<"key is not present in the Tree"<<endl;
} 
// Function to search key k in subtree rooted with this node 
void TreeNode::search(int k) 
{ 
    TreeNode *tmp = this;
    while(1){
        if(tmp->leaf) break;
        else{
            tmp = tmp->C[0];
        }
    }
    while(tmp){
        int len = tmp->n;
        for(int i=0; i<len; i++){
            if(tmp->keys[i] == k){
                cout<<"key is present in the Tree."<<endl;
                return;
            }
        }
        tmp = tmp->C[2*t];
    }
    cout<<"key is not present in the Tree"<<endl;

} 
int main(){
    
    int choice,element,t;
    cout<<"Enter a value of degree : \n";
    cin>>t;
    Tree bt(t);
    while(true){
        cout<<"Enter 1 to insert an Element\n";
        cout<<"Enter 2 to Delete and Element\n";
        cout<<"Enter 3 to search for an Element\n";
        cout<<"Enter 4 to traverse for the BTree\n";
        cout<<"Enter 5 to create B+ Tree again\n";
        cin>>choice;
        switch(choice){
            case 1:
                cin>>element;
                bt.insert(element);

                break;
            case 2:
                break;
            case 3:
                cin>>element;
                bt.search(element);
                break;
            case 4:
                bt.traverse();
                break;
            case 5:
                break;
            default:
                break;
        }
        if(choice == 5)break;
    }
    return 0;

}