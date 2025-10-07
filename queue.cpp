#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;  // Front of queue
    Node* tail;  // Back of queue
    int count;
    
public:
    // Constructor
    Queue() : head(nullptr), tail(nullptr), count(0) {}
    
    // Destructor
    ~Queue() {
        clear();
    }
    
    // Copy constructor
    Queue(const Queue& other) : head(nullptr), tail(nullptr), count(0) {
        Node* curr = other.head;
        while (curr) {
            enqueue(curr->data);
            curr = curr->next;
        }
    }
    
    // Copy assignment operator
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            Node* curr = other.head;
            while (curr) {
                enqueue(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }
    
    // Add element to back of queue
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }
    
    // Remove and return front element
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = head;
        T value = head->data;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        count--;
        return value;
    }
    
    // Get front element without removing
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }
    
    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }
    
    // Check if queue is empty
    bool isEmpty() const {
        return head == nullptr;
    }
    
    // Get size of queue
    int size() const {
        return count;
    }
    
    // Clear all elements
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    // Display queue contents
    void display() const {
        Node* curr = head;
        std::cout << "Queue: ";
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
};

// Example usage
int main() {
    Queue<int> q;
    
    // Enqueue elements
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    
    std::cout << "After enqueuing 10, 20, 30, 40:" << std::endl;
    q.display();
    std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Front: " << q.front() << std::endl;
    
    // Dequeue elements
    std::cout << "\nDequeued: " << q.dequeue() << std::endl;
    std::cout << "Dequeued: " << q.dequeue() << std::endl;
    
    q.display();
    std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Front: " << q.front() << std::endl;
    
    // Test copy constructor
    Queue<int> q2 = q;
    std::cout << "\nCopied queue:" << std::endl;
    q2.display();
    
    return 0;
}