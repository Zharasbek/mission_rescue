#include "SpaceSectorBST.h"

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    // Free any dynamically allocated memory in this class.
    clear(root);  // Call a helper function to recursively delete nodes
}

// Helper function to recursively delete nodes
void SpaceSectorBST::clear(Sector* node) {
    if (node != nullptr) {
        // Recursively delete left and right subtrees
        clear(node->left);
        clear(node->right);

        // Delete the current node
        delete node;
    }
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison criteria based on the sector coordinates.
    ifstream file(filename);
    

    // Skip the header line
    string header;
    getline(file, header);

    int x, y, z;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);

        char comma;
        if (ss >> x >> comma >> y >> comma >> z) {
            insertSectorByCoordinates(x, y, z);
        } else {
            cerr << "Error reading line: " << line << endl;
        }
    }
    file.close();
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    // Instantiate and insert a new sector into the space sector BST map according to the 
    // coordinates-based comparison criteria.
    root = insertNode(root, x, y, z);
}

Sector* SpaceSectorBST::insertNode(Sector* node, int x, int y, int z) {
    if (node == nullptr) {
        // Create and return a new node
        return new Sector(x, y, z);
    }

    // Compare coordinates for insertion
    if (x < node->x || (x == node->x && y < node->y) || (x == node->x && y == node->y && z < node->z)) {
        node->left = insertNode(node->left, x, y, z);
        node->left->parent = node;
    } else {
        node->right = insertNode(node->right, x, y, z);
        node->right->parent = node;
    }

    // Return the updated node
    return node;
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
    root = deleteNode(root, sector_code);
}

Sector* SpaceSectorBST::deleteNode(Sector* root, const std::string& sector_code) {
    
    if (root == nullptr) {
        return root;
    }
    Sector* required = findSectorByCode(root, sector_code);
    if (required == nullptr) {
        std::cout << "Sector " << sector_code << " not found." << std::endl;
        return root;
    }
    // Compare sector codes for deletion
    if ((required->x < root->x) || (required->x == root->x && required->y < root->y) || (required->x == root->x && required->y == root->y && required->z < root->z)) {
        // Search in the left subtree
        root->left = deleteNode(root->left, sector_code);
    } else if ((required->x > root->x) || (required->x == root->x && required->y > root->y) || (required->x == root->x && required->y == root->y && required->z > root->z)){
        // Search in the right subtree
        root->right = deleteNode(root->right, sector_code);
    } else {
        // Node with matching sector_code found, perform deletion
        
        // Case 1: Node with no children (leaf node)
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        // Case 2: Node with one child
        else if (root->left == nullptr) {
            Sector* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            Sector* temp = root;
            root = root->left;
            delete temp;
        }
        // Case 3: Node with two children
        else {
            // Find the in-order successor (smallest node in the right subtree)
            Sector* temp = findMin(root->right);
            root->sector_code = temp->sector_code;
            root->x = temp->x;
            root->y = temp->y;
            root->z = temp->z;
            root->distance_from_earth = temp->distance_from_earth;
            root->right = deleteNode(root->right, temp->sector_code);
        }
    }
    return root;
    

}


Sector* SpaceSectorBST::findMin(Sector* node) const {
    // Find the leftmost node to get the in-order successor
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void SpaceSectorBST::displaySectorsInOrder() {
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
    std::cout << "Space sectors inorder traversal:" << std::endl;
    inOrderTraversal(root);
}

void SpaceSectorBST::inOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->left);
    std::cout << node->sector_code << std::endl;
    inOrderTraversal(node->right);
}

void SpaceSectorBST::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
    std::cout << "Space sectors preorder traversal:" << std::endl;
    preOrderTraversal(root);
}

void SpaceSectorBST::preOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << node->sector_code << std::endl;
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

void SpaceSectorBST::displaySectorsPostOrder() {
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    std::cout << "Space sectors postorder traversal:" << std::endl;
    postOrderTraversal(root);
    
}

void SpaceSectorBST::postOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    std::cout << node->sector_code << std::endl;
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    Sector* destination = findSectorByCode(root, sector_code);

    // Perform DFS to find the path from Earth to the destination
    dfsFindPath(root, destination, path);
    return path;
}

void SpaceSectorBST::dfsFindPath(Sector* current, Sector* destination, std::vector<Sector*>& path) {
    if (current == nullptr || destination == nullptr) {
        return;
    }

    // Add the current sector to the path
    path.push_back(current);

    // Check if the current sector is the destination
    if (current == destination) {
        return;
    }

    // Recursively search in the left subtree
    dfsFindPath(current->left, destination, path);

    // Recursively search in the right subtree
    dfsFindPath(current->right, destination, path);

    // If the destination is found in either subtree, remove unnecessary nodes from the path
    if (path.back() != destination) {
        path.pop_back();
    }
}


Sector* SpaceSectorBST::findSectorByCode(Sector* current, const std::string& sector_code) const {
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


void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
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
        std::cout << "A path to Dr. Elara could not be found.";
    }
    
}
