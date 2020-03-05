
template<class T>
class Node{
    public:
    T data;
    Node<T>* next;

    Node(T data){
        this->data = data;
        next = 0;
    }

    ~Node(){
        delete next;
        delete this;
    }

    void insertEnd(T dat){
        this->next = new Node<T>(dat);
    }
    
};