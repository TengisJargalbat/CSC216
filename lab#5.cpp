#include <iostream>

using namespace std;

template <typename T>
class CircularLinkedList{

    class Node{
    public:
        T element;
        Node* next;
        Node(const T elt): element{elt}, next{nullptr}{}
    };
    Node* tail{};
    Node* current{};

public:

    void append(const T& data){
        Node* newNode = new Node(data);
        if (!tail) {
            tail = newNode;
            current = newNode;
            newNode->next = newNode;
        } 
        else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
    }
    T currentNode(){
        return current->element;
    }
    void step(){
        current = current->next;
    }
};

int main(){
    CircularLinkedList monopolyBoard = CircularLinkedList<string>();
    
    monopolyBoard.append("Go");
    monopolyBoard.append("Mediteranean Avenue");
    monopolyBoard.append("Community Chest");
    monopolyBoard.append("Baltic Avenue");
    monopolyBoard.append("Income Tax");
    // And so on for all of the spaces on the board...
    
    cout << monopolyBoard.currentNode() << '\n'; // This should print "Go" to the console
    
    monopolyBoard.step();
    
    cout << monopolyBoard.currentNode() << '\n'; // This should print "Mediteranean Avenue" to the console
    
    monopolyBoard.step();
    monopolyBoard.step();
    monopolyBoard.step();
    
    cout << monopolyBoard.currentNode() << '\n'; // This should print "Income Tax" to the console
    
    for(int i = 0; i < 37; i++) {
    monopolyBoard.step();
    }
    
    cout << monopolyBoard.currentNode() << '\n'; // This should print "Mediteranean Avenue" to the console since we have looped back around

    int x;
    std::cin >> x;

    return 0;
}
