#pragma once
// Reading and storing input text and attributes in memory

#include<vector>
#include<string>

using namespace std;

enum BlockType {
    CUBE,
    CUBOID,
    TETRAHEDRON,
    TETRAHEDRON90
};

struct BlockSpecs {
    BlockType blockType;
    float x, y, z;
};

class InputProcessor {
    struct ccoords {
        char c;
        int x, y;
    };

public:
    unsigned int wordCount = 0;
    vector<char> text;
    ccoords charCoords[26];
    BlockSpecs specs;

    bool readInputText(string filename);
    void readCharMap(string filename);
    void readTowerSpecs(string filename);
};
