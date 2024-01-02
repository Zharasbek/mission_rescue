#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void clear(Sector* node);
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    Sector* insertNode(Sector* node, int x, int y, int z);
    void inOrderTraversal(Sector* node);
    void preOrderTraversal(Sector* node);
    void postOrderTraversal(Sector* node);
    Sector* deleteNode(Sector* node, const std::string& sector_code);
    Sector* findMin(Sector* node) const;
    Sector* findSectorByCode(Sector* current, const std::string& sector_code) const ;
    void dfsFindPath(Sector* current, Sector* destination, std::vector<Sector*>& path);
};
    

    // ... (rest of the class definition)

#endif // SPACESECTORBST_H
