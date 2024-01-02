#include "SpaceSectorLLRBT.h"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    

    // Skip the header line
    string header;
    getline(file, header);

    int x, y, z;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);

        char comma;
        if (ss >> x >> comma >> y >> comma >> z) {
            //cerr<<"INSERTING NODE"<<endl;
            insertSectorByCoordinates(x,y,z);
            
            
            //insertSectorByCoordinates(x, y, z);
        } else {
            cerr << "Error reading line: " << line << endl;
        }
    }

    file.close();
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.
    clear(root);  // Call a helper function to recursively delete nodes
}

// Helper function to recursively delete nodes
void SpaceSectorLLRBT::clear(Sector* node) {
    if (node != nullptr) {
        // Recursively delete left and right subtrees
        clear(node->left);
        clear(node->right);

        // Delete the current node
        delete node;
    }
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
    // Start the insertion with the root node
    root = insert(root, x, y, z);
    root->color = BLACK;

    
}

// Placeholder for coordinate comparison logic
int SpaceSectorLLRBT::compareCoordinates(int x1, int y1, int z1, const Sector* node) {
    // Compare the coordinates of the new node (x1, y1, z1) with the coordinates of the given node
    // Return a negative value if the new node should go to the left, positive if it should go to the right,
    // and 0 if the coordinates are equal.

    if (x1 < node->x) {
        return -1;
    } else if (x1 > node->x) {
        return 1;
    } else if (y1 < node->y) {
        return -1;
    } else if (y1 > node->y) {
        return 1;
    } else if (z1 < node->z) {
        return -1;
    } else if (z1 > node->z) {
        return 1;
    } else {
        return 0;  // Coordinates are equal
    }
}

Sector* SpaceSectorLLRBT::leftRotate(Sector *node) {
    // Perform a left rotate in LLRBT
    Sector* child = node->right;
    Sector* childLeft = child->left;

    child->left = node;
    node->right = childLeft;

    if (childLeft != nullptr) {
        childLeft->parent = node;
    }

    child->parent = node->parent;
    node->parent = child;

    return child;
}

Sector* SpaceSectorLLRBT::rightRotate(Sector *node) {
    // Perform a right rotate in LLRBT
    Sector* child = node->left;
    Sector* childRight = child->right;

    child->right = node;
    node->left = childRight;

    if (childRight != nullptr) {
        childRight->parent = node;
    }

    child->parent = node->parent;
    node->parent = child;

    return child;
}

bool isRed(Sector* node) {
    // Check if the node is red
    if (node == nullptr) {
        return false;
    }
    return node->color == RED;
}

void swapColor(Sector* node1, Sector* node2) {
    // Swap the colors of the two nodes
    bool temp = node2->color;
    node2->color = node1->color;
    node1->color = temp;
}

Sector* SpaceSectorLLRBT::insert(Sector* node, int x, int y, int z) {
    // Fix violations in LLRBT after insertion
    if (node == nullptr) {
        Sector* newNode = new Sector(x, y, z);
        
        return newNode;
    }  
    // Compare coordinates for insertion
    if (x < node->x || (x == node->x && y < node->y) || (x == node->x && y == node->y && z < node->z)) {
        node->left = insert(node->left, x, y, z);
        if (node->left != nullptr) {
            node->left->parent = node;
        }
    } else {
        node->right = insert(node->right, x, y, z);
        if (node->right != nullptr) {
            node->right->parent = node;
        }
    }
    
    // Fix violations in LLRBT after insertion
    // case 1: when the right child is red and left child is black or does not exist

    if (isRed(node->right) && !isRed(node->left)) {
        node = leftRotate(node);
        swapColor(node, node->left);
    }

    // case 2: when the left child and the left-left child are red
    if (isRed(node->left) && isRed(node->left->left)) {
        node = rightRotate(node);
        swapColor(node, node->right);
    }

    // case 3: when both children are red
    if (isRed(node->left) && isRed(node->right)) {
        node -> color = !node->color;
        node->left->color = BLACK;
        node->right->color = BLACK;
    }
    return node;
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
    // to STDOUT in the given format.
    std::cout << "Space sectors inorder traversal:" << std::endl;
    inOrderTraversal(root);
}

void SpaceSectorLLRBT::inOrderTraversal(Sector* node) {
    if (node != nullptr) {
        // Recursively traverse the left subtree
        inOrderTraversal(node->left);
        std::cout << (node->color ? "RED" : "BLACK") << " sector: " << node->sector_code << std::endl;
        // Recursively traverse the right subtree
        inOrderTraversal(node->right);
    }
}



void SpaceSectorLLRBT::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
    std::cout << "Space sectors preorder traversal:" << std::endl;
    preOrderTraversal(root);
}

void SpaceSectorLLRBT::preOrderTraversal(Sector* node) {
    if (node != nullptr) {
        // Print the current sector before traversing subtrees
        std::cout << (node->color ? "RED" : "BLACK") << " sector: " << node->sector_code << std::endl;

        // Recursively traverse the left subtree
        preOrderTraversal(node->left);

        // Recursively traverse the right subtree
        preOrderTraversal(node->right);
    }
}


void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    std::cout << "Space sectors postorder traversal:" << std::endl;
    postOrderTraversal(root);
}

void SpaceSectorLLRBT::postOrderTraversal(Sector* node) {
    if (node != nullptr) {
        // Recursively traverse the left subtree
        postOrderTraversal(node->left);

        // Recursively traverse the right subtree
        postOrderTraversal(node->right);
        
        // Print the current sector after traversing subtrees
        std::cout << (node->color ? "RED" : "BLACK") << " sector: " << node->sector_code << std::endl;
    }
}


std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    

    // Find the starting sector with sector code "0SSS"
    Sector* start_sector = findSectorByCode(root, "0SSS");

    // Find the destination sector
    Sector* destination_sector = findSectorByCode(root, sector_code);

    // Collect the stellar path from the start sector to the destination sector
    collectStellarPath(start_sector, destination_sector, path);

    return path;
}

void SpaceSectorLLRBT::collectStellarPath(Sector* start_sector, Sector* destination_sector, std::vector<Sector*>& path) {
    // Helper function to collect the stellar path from the start sector to the destination sector
    if (start_sector == nullptr || destination_sector == nullptr) {
        return;
    }

    // Use a temporary vector to store the path from start_sector to the root
    std::vector<Sector*> temp_path;
    while (start_sector != nullptr) {
        temp_path.push_back(start_sector);
        start_sector = start_sector->parent;
    }

    // Reverse the temporary path to get the path from root to start_sector
    size_t start = 0;
    size_t end = temp_path.size() - 1;
    while (start < end) {
        std::swap(temp_path[start], temp_path[end]);
        ++start;
        --end;
    }
    Sector* des;
    des = destination_sector;

    // Append the path from destination_sector to the root
    while (des != nullptr) {
        path.push_back(des);
        des = des->parent;
    }

    // Iterate through each sector in path
    for (size_t path_index = 0; path_index < path.size(); ++path_index) {
        // Iterate through each sector in temp_path
        for (size_t temp_path_index = 0; temp_path_index < temp_path.size(); ++temp_path_index) {
            // Check if the sector codes match
            if (path[path_index]->sector_code == temp_path[temp_path_index]->sector_code) {
                // Matching sector code found, erase remaining sectors in path
                path.erase(path.begin() + path_index + 1, path.end());
                
                // Insert sectors from temp_path after the match
                for (size_t i = temp_path_index + 1; i < temp_path.size(); ++i) {
                    path.push_back(temp_path[i]);
                }

                // Break out of the inner loop once a match is found
                break;
            }
        }
    }
    size_t start1 = 0;
    size_t end1 = path.size() - 1;
    while (start1 < end1) {
        std::swap(path[start1], path[end1]);
        ++start1;
        --end1;
    }
    
}

Sector* SpaceSectorLLRBT::findSectorByCode(Sector* current, const std::string& sector_code) const {
    if (current == nullptr) {
        return nullptr;
    }

    // Check the current node
    if (current->sector_code == sector_code) {
        return current;
    }

    // Traverse the left subtree
    Sector* foundLeft = findSectorByCode(current->left, sector_code);
    if (foundLeft != nullptr) {
        return foundLeft;
    }

    // Traverse the right subtree
    Sector* foundRight = findSectorByCode(current->right, sector_code);
    return foundRight;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
    if (path.size()>0){
        std::cout << "The stellar path to Dr. Elara: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i]->sector_code;
        if (i < path.size() - 1) {
            std::cout << "->";
        }

    }
    } else{
        std::cout<<"A path to Dr. Elara could not be found.";
    }
    
}
