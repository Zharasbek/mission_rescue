#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void clear(Sector* node);
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    Sector* insert(Sector* node, int x, int y, int z);
    Sector* leftRotate(Sector* node);
    Sector* rightRotate(Sector* node);
    int compareCoordinates(int x1, int y1, int z1, const Sector* node);

    void inOrderTraversal(Sector* node);
    void preOrderTraversal(Sector* node);
    void postOrderTraversal(Sector* node);

    Sector* findSectorByCode(Sector* current, const std::string& sector_code) const;
    void collectStellarPath(Sector* start_sector, Sector* destination_sector, std::vector<Sector*>& path);

};

#endif // SPACESECTORLLRBT_H
