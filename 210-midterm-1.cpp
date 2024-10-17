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
        // If there is no head of the list, the list is empty.
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }
        // If the position to delete is the first one, use the pop_front function.
        if (pos == 1)
        {
            pop_front();
            return;
        }
        // Create a new temp pointer to the head.
        Node *temp = head;
        // Loop through each value of the list until reaching the valid position.
        for (int i = 1; i < pos; i++)
        {
            // If the temp pointer reaches the end of the list, the position doesn't exist.
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                // Exit the function.
                return;
            }
            // Otherwise, continue looping through the list.
            else
                temp = temp->next;
        }
        // Once again, check if the temp pointer has reached the end of the list.
        // Then the position doesn't exist. 
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }
        // If there is no next value, the position is at the last value of the list.
        if (!temp->next)
        {
            // Use the pop_back function to remove the value.
            pop_back();
            return;
        }
        // Make a new node to point to the current's previous node.
        Node *tempPrev = temp->prev;
        // Set the previous node's next pointer to the current node's next pointer (skip current node).
        tempPrev->next = temp->next;
        // Set the next node's previous pointer the the previous node (skip current node).
        temp->next->prev = tempPrev;
        // Delete the current node.
        delete temp;
    }
    // Function to add a new node to the end of a linked list.
    void push_back(int v)
    {
        // Create a new node with the new value.
        Node *newNode = new Node(v);
        // If there is no tail, the list is empty.
        if (!tail)
            // Set the head and tail of the list to equal the new node.
            head = tail = newNode;
        else
        {
            // Set the tail's next pointer to the new node.
            tail->next = newNode;
            // Set the new node's previous pointer to the tail.
            newNode->prev = tail;
            // Make the new node to be the tail of the list.
            tail = newNode;
        }
    }
    // Function to add a new node to the beginning of a linked list.
    void push_front(int v)
    {
        // Create a new node with the new value.
        Node *newNode = new Node(v);
        // If there is no head, the list is empty.
        if (!head)
            // Set the head and tail equal to the new node.
            head = tail = newNode;
        else
        {
            // Set the new node's next value to the head.
            newNode->next = head;
            // Set the head's previous value to the new node.
            head->prev = newNode;
            // Make the new node the head of the list.
            head = newNode;
        }
    }
    // Function to remove a node from the beginning of a linked list.
    void pop_front()
    {
        // If there is no head, the list is empty.
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }
        // Set a temporary pointer to the beginning of the list.
        Node *temp = head;
        // If there is a next node,
        if (head->next)
        {
            // Set the new head to the next node.
            head = head->next;
            // Set the new head's previous value to nullptr.
            head->prev = nullptr;
        }
        // Otherwise, there is only one node in the list.
        else
            // Set the head and tail of the list equal to nullptr.
            head = tail = nullptr;
        // Delete the old head of the list.
        delete temp;
    }
    // Function to remove a node from the end of a linked list.
    void pop_back()
    {
        // If there is no tail, the list is empty.
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        // Set a temporary pointer to the end of the list.
        Node *temp = tail;
        // If there is a previous node,
        if (tail->prev)
        {
            // Set the new tail to the previous node.
            tail = tail->prev;
            // Set the new tail's next pointer to nullptr.
            tail->next = nullptr;
        }
        else
            // Otherwise, the node is the only one in the list.
            // Make the head and the tail to  nullptr.
            head = tail = nullptr;
        // Delete the old tail node.
        delete temp;
    }
    // Destructor for the doubly linked list.
    ~DoublyLinkedList()
    {
        // While there is a head of the list, loop through the nodes of the list.
        while (head)
        {
            // Set a temporary pointer at the head.
            Node *temp = head;
            // Set the head to point to the next value of the list.
            head = head->next;
            // Delete the temporary pointer (and previous head value).
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
    // Function to print every other element of the linked list.
    void every_other_element() {
        int count = 0;
        Node *temp = head;
        if (!temp) {
            cout << "List is empty." << endl;
            return;
        }
        while (temp) {
            if (count%2==0){
                cout << temp->data << ", ";
            }
            count++;
            temp = temp->next;
        }
        delete temp;
    }
};
int main()
{
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS << endl;; // dummy statement to avoid compiler warning 
    DoublyLinkedList values;
    values.insert_after(5, 0);
    values.push_back(6);
    values.push_back(7);
    values.push_back(8);
    values.push_back(9);
    values.every_other_element();
    return 0;
}
