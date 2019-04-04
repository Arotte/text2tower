#pragma once

#include "InputProcessor.hh"
#include <string>

using namespace std;

struct Coord {
    float x, y, z;
};
struct Triangle {
  float triangle[3][3] = {0.0};
  float normal[3] = {0.0};
};

class TowerBuilder {
public:
    string sampleSTLFilenames[2] = {"run\\inputs\\sample_STLs\\cubicSTL.txt", "run\\inputs\\sample_STLs\\tetraSTL.txt"};
    vector<Triangle> cubicMatrix; //has 12 elements becase a cubic contsists of 12 triangles
    // Triangle tetraMatrix[][];

    void initSTLMatrix(BlockType);
    string createStringFromTriangle(Triange);
    bool buildTower(InputProcessor input, string outputFilename);
    string drawBuildingBlockAt(Coord drawCoord, BlockSpecs blockSpecs);
    string drawCubeAt(Coord, float);
    string drawCuboidAt(Coord, float, float, float);
    string drawTetraAt(Coord, float, float);
    string drawTetra90At(Coord, float, float);
};
