#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Define structures for Item and Node
struct Item {
    int id;
    string name;
    double startingPrice;
    double currentBid;
    string highestBidder;
};

struct Node {
    Item data;
    Node* left;
    Node* right;
};

// BST operations
Node* createNode(Item item) {
    Node* newNode = new Node;
    newNode->data = item;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void insertNode(Node*& root, Node* newNode) {
    if (root == nullptr) {
        root = newNode;
    } else if (newNode->data.id < root->data.id) {
        insertNode(root->left, newNode);
    } else if (newNode->data.id > root->data.id) {
        insertNode(root->right, newNode);
    } else {
        cout << "Duplicate ID not allowed." << endl;
    }
}

Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int id) {
    if (root == nullptr) return root;
    if (id < root->data.id) {
        root->left = deleteNode(root->left, id);
    } else if (id > root->data.id) {
        root->right = deleteNode(root->right, id);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.id);
    }
    return root;
}

void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << "ID: " << root->data.id << ", Name: " << root->data.name << ", Starting Price: $" << root->data.startingPrice << ", Current Bid: $" << root->data.currentBid << ", Highest Bidder: " << root->data.highestBidder << endl;
        inOrderTraversal(root->right);
    }
}

// Add Item
void addItem(Node*& root, Item item) {
    Node* newNode = createNode(item);
    insertNode(root, newNode);
    cout << "Item added successfully." << endl;
}

// Search Item by ID
Item* searchItemByID(Node* root, int id) {
    if (root == nullptr) return nullptr;
    if (root->data.id == id) return &root->data;
    if (id < root->data.id) return searchItemByID(root->left, id);
    return searchItemByID(root->right, id);
}

// Search Item by Name
Item* searchItemByName(Node* root, string name) {
    if (root == nullptr) return nullptr;
    if (root->data.name == name) return &root->data;
    Item* foundItem = searchItemByName(root->left, name);
    if (foundItem == nullptr) foundItem = searchItemByName(root->right, name);
    return foundItem;
}

// Place Bid
void placeBid(Node* root, int id, double bidAmount, string bidderName) {
    Item* item = searchItemByID(root, id);
    if (item != nullptr) {
        if (bidAmount > item->currentBid) {
            item->currentBid = bidAmount;
            item->highestBidder = bidderName;
            cout << "Bid placed successfully." << endl;
        } else {
            cout << "Bid amount is lower than the current highest bid." << endl;
        }
    } else {
        cout << "Item not found." << endl;
    }
}

// Generate Report
void generateReport(Node* root) {
    if (root == nullptr) {
        cout << "No items available for auction." << endl;
    } else {
        cout << "=== Auction Report ===" << endl;
        inOrderTraversal(root);
    }
}

// Function to get integer input with validation
int getIntInput(const string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            break;
        }
    }
    return input;
}

// Function to get double input with validation
double getDoubleInput(const string& prompt) {
    double input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid number." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            break;
        }
    }
    return input;
}

// Function to get string input
string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer before taking string input
    getline(cin, input);
    return input;
}

int main() {
    Node* root = nullptr;

    int choice;
    do {
        cout << "\nOnline Auction System" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Search Item" << endl;
        cout << "3. Place Bid" << endl;
        cout << "4. Generate Report" << endl;
        cout << "0. Exit" << endl;
        choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1: {
                Item newItem;
                newItem.id = getIntInput("Enter Item ID: ");
                newItem.name = getStringInput("Enter Item Name: ");
                newItem.startingPrice = getDoubleInput("Enter Starting Price: ");
                newItem.currentBid = newItem.startingPrice;
                newItem.highestBidder = "None";
                addItem(root, newItem);
            } break;
            case 2: {
                // Search Item
                int searchChoice;
                cout << "=== Search Item ===" << endl;
                cout << "1. By ID" << endl;
                cout << "2. By Name" << endl;
                searchChoice = getIntInput("Enter choice: ");

                switch (searchChoice) {
                    case 1: {
                        // Search by ID
                        int searchID = getIntInput("Enter Item ID to search: ");
                        Item* foundItem = searchItemByID(root, searchID);
                        if (foundItem != nullptr) {
                            cout << "Item Found: ID: " << foundItem->id << ", Name: " << foundItem->name << ", Starting Price: $" << foundItem->startingPrice << ", Current Bid: $" << foundItem->currentBid << ", Highest Bidder: " << foundItem->highestBidder << endl;
                        } else {
                            cout << "Item not found." << endl;
                        }
                    } break;
                    case 2: {
                        // Search by Name
                        string searchName = getStringInput("Enter Item Name to search: ");
                        Item* foundItem = searchItemByName(root, searchName);
                        if (foundItem != nullptr) {
                            cout << "Item Found: ID: " << foundItem->id << ", Name: " << foundItem->name << ", Starting Price: $" << foundItem->startingPrice << ", Current Bid: $" << foundItem->currentBid << ", Highest Bidder: " << foundItem->highestBidder << endl;
                        } else {
                            cout << "Item not found." << endl;
                        }
                    } break;
                    default:
                        cout << "Invalid choice! Please try again." << endl;
                }
            } break;
            case 3: {
                int itemID = getIntInput("Enter Item ID to place bid on: ");
                double bidAmount = getDoubleInput("Enter Bid Amount: ");
                string bidderName = getStringInput("Enter Bidder Name: ");
                placeBid(root, itemID, bidAmount, bidderName);
            } break;
            case 4:
                generateReport(root);
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}

