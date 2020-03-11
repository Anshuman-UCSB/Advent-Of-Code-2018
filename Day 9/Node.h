
struct Node{
    int number;
    Node* next;
    Node(int dat){
        number = dat;
    }
};

void insert(Node* before, Node* ins){
    ins->next = before->next;
    before->next = ins;
}

int remove(Node* before){
    Node* rem = before->next;
    before = rem->next;
    int ret = rem->number;
    delete rem;
    return ret;
}