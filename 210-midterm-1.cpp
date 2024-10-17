#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList
{
// Private section for a doubly linked list.
private:
    // Create a new struct to define a node within the class.
    struct Node
    {
        int data; // Stores a value.
        Node *prev; // Points to previous node in list.
        Node *next; // Points to next node in list.
        // Parameter constructor for a node.
        Node(int val, Node *p = nullptr, Node *n = nullptr)
        {
            // Initiate the values for the data, the previous node, and the next node.
            data = val;
            prev = p;
            next = n;
        }
    };
    // Node variable for the head of the list.
    Node *head;
    // Node variable for the tail of the list.
    Node *tail;

// Public member functions of the doubly linked list class.
public:
    // Default constructor.
    DoublyLinkedList()
    {
        // Set both the head pointer and tail pointer of the list to nullptr.
        head = nullptr;
        tail = nullptr;
    }
    // Function to insert a value after a certain position in the linked list.
    void insert_after(int value, int position)
    {
        // Check for invalid, negative position values.
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }
        // Create a newNode that holds the value.
        Node *newNode = new Node(value);
        // If the list doesn't have a head, then it is empty.
        // Turn the newNode into the head and tail of the linked list.
        if (!head)
        {
            head = tail = newNode;
            return;
        }
        // Otherwise, create a new temporary pointer that points to the head of the list.
        Node *temp = head;
        // Loop through the linked list until the correct position is reached,
        // or until the end of the list is reached.
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        // If temp, reaches the end of the list, it's an invalid position and output an error.
        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            // Delete the new node.
            delete newNode;
            return;
        }
        // If temp reaches the correct position, insert the newNode between the previous and next nodes in the list.
        // Set the next pointer of newNode to the next pointer of temp (next node in list).
        newNode->next = temp->next;
        // Set the previous pointer of newNode to point at temp (current node of list)
        newNode->prev = temp;
        // If there is still a value after temp, make the next node's, previous pointer point to newNode.
        if (temp->next)
            temp->next->prev = newNode;
        // If there isn't a value after temp, newNode is the tail of the list.
        else
            tail = newNode;
        // Make the current node's next pointer point to the newNode.
        temp->next = newNode;
    }
    // Function to delete a value from the list.
    void delete_val(int value)
    {
        // Exit the function if the list is empty.
        if (!head)
            return;
        // Set a temporary node pointing to head.
        Node *temp = head;
        // Loop through the linked list, until it reaches the correct value to delete.
        while (temp && temp->data != value)
            temp = temp->next;
        // If the value wasn't found, exit the list.
        if (!temp)
            return;
        // If there is a previous node,
        // set the previous node's next value to the current node's next value (skip the current node).
        if (temp->prev)
            temp->prev->next = temp->next;
        // If there isn't a previous value, then the current value to delete is at the head of the list.
        // S0, et the head equal to the next value.
        else
            head = temp->next;
        // If there is a next node,
        // Set the next nodes's previous pointer to the current node's previous pointer (skip current node).
        if (temp->next)
            temp->next->prev = temp->prev;
        // If there isn't a next node, then the current pointer is at the tail.
        // Set the tail equal to the previous node.
        else
            tail = temp->prev;
        // Delete the temporary pointer.
        delete temp;
    }
    // Function to delete a Node at a certain position.
    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }
        if (pos == 1)
        {
            pop_front();
            return;
        }
        Node *temp = head;
        for (int i = 1; i < pos; i++)
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }
        if (!temp->next)
        {
            pop_back();
            return;
        }
        Node *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }
    void push_back(int v)
    {
        Node *newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void push_front(int v)
    {
        Node *newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void pop_front()
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = head;
        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }
    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;
        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }
    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    // Function to print the list.
    void print()
    {
        // Set a pointer to the head of the list.
        Node *current = head;
        // If the head doesn't exist, the list is empty.
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        // Loop through the list from the head to the tail.
        while (current)
        {
            // Print the value of the node.
            cout << current->data << " ";
            // Set current to the next node in the list.
            current = current->next;
        }
        cout << endl;
    }
    // Function to print the list reversed.
    void print_reverse()
    {
        // Set a pointer to the tail of the list.
        Node *current = tail;
        // If it doesn't exist, then the list is empty.
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        // Loop through each value of the list, from the tail to the head.
        while (current)
        {
            // Print the value of the node.
            cout << current->data << " ";
            // Set current to the previous node.
            current = current->prev;
        }
        cout << endl;
    }
};
int main()
{
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning 
    return 0;
}
