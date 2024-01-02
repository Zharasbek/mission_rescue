#include "Sector.h"

// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
    // TODO: Calculate the distance to the Earth, and generate the sector code
    distance_from_earth = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    // Generate the sector code
    generateSectorCode();
}

void Sector::generateSectorCode() {
    // Distance Component
    int distance_component = static_cast<int>(distance_from_earth);

    // Coordinate Components
    std::string x_component = (x == 0) ? "S" : (x > 0) ? "R" : "L";
    std::string y_component = (y == 0) ? "S" : (y > 0) ? "U" : "D";
    std::string z_component = (z == 0) ? "S" : (z > 0) ? "F" : "B";

    // Form the sector code
    sector_code = std::to_string(distance_component) + x_component + y_component + z_component;
}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}

Sector& Sector::operator=(const Sector& other) {
    // TODO: Overload the assignment operator
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        distance_from_earth = other.distance_from_earth;
        sector_code = other.sector_code;
        left = other.left;
        right = other.right;
        parent = other.parent;
        color = other.color;
    }
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}
