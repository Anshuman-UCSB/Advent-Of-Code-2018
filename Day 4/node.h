
template<class T>
class Node{
    public:
    T data;
    Node<T>* next;

    Node(T data){
        this->data = data;
        next = 0;
    }

};
template <class T>
bool operator<(const Node<T>& n1, const Node<T>& n2){
    return(n1.data<n2.data);
}

template <class T>
void insert(Node<T>*& head, T dat){
    insert(head,new Node<T>(dat));
}

template <class T>
void insert(Node<T>*& head, Node<T>* n){
    if(head == 0){
        head = n;
        return;
    }
    if(n->data<=head->data){
        n->next = head;
        head = n;
        return;
    }
    auto p = head->next;
    auto l = head;
    for(;p->next;p=p->next){
        if(n->data<=p->data){
            l->next = n;
            n->next = p;
            return;
        }
        l = l->next;
    }
    p->next = n;
}