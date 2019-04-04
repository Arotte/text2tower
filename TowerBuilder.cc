#include "TowerBuilder.hh"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void TowerBuilder::initSTLMatrix(BlockType bt) {

  if (bt == CUBE || bt == CUBOID) { //building block is cubic

    int vertexCount = 0;
    string buff_str; Triangle buff_tri;
    ifstream ifsCubic(sampleSTLFilenames[0]);

    while (ifsCubic >> buff_str) { //read sample cubic STL to memory

      if (buff_str == "facet") {
        ifsCubic >> buff_str; //facet normal...
        ifsCubic >> buff_tri.normal[0] >> buff_tri.normal[1] >> buff_tri.normal[2];
      } else if (buff_str == "vertex") {
        ++vertexCount;
        ifsCubic >> buff_tri.triangle[vertexCount-1][0]
                 >> buff_tri.triangle[vertexCount-1][1]
                 >> buff_tri.triangle[vertexCount-1][2];
        if (vertexCount == 3) {
          cubicMatrix.push_back(buff_tri);
          vertexCount = 0;
        }
      } else { continue; }
    }
    ifsCubic.close();

  } else if (bt == TETRAHEDRON || bt == TETRAHEDRON90) { //builing block is tetrahedron
    //TODO: read sample STL if building block is Tetra
  }
}

string TowerBuilder::createStringFromTriangle(Triangle tri) {
  string triStr = "facet normal ";
  triStr += to_string(tri.normal[0]) + " " + to_string(tri.normal[1]) + " " + to_string(tri.normal[2]) + "\n"; //normal
  triStr += "outer loop\n";
  //vertex1
  triStr += "vertex" + to_string(tri.triangle[0][0]) + " " + to_string(tri.triangle[0][1]) + " " + to_string(tri.triangle[0][2]) + "\n";
  //vertex2
  triStr += "vertex" + to_string(tri.triangle[1][0]) + " " + to_string(tri.triangle[1][1]) + " " + to_string(tri.triangle[1][2]) + "\n";
  //vertex3
  triStr += "vertex" + to_string(tri.triangle[2][0]) + " " + to_string(tri.triangle[2][1]) + " " + to_string(tri.triangle[2][2]) + "\n";

  triStr += "end loop\nend facet\n";
  return triStr;
}

//main tower builder method;
bool TowerBuilder::buildTower(InputProcessor input, string outputFileName) {
    initSTLMatrix(input.specs.blockType);

    if (input.specs.blockType == CUBE) {
      cout << "TowerBuilder::buildTower : Its going to be a CUBE!" << endl;
    }

    return true; //TODO: create return that makes sense
}

string TowerBuilder::drawBuildingBlockAt(Coord drawCoord, BlockSpecs blockSpecs) {

  if (blockSpecs.blockType == CUBE)
    return drawCubeAt(drawCoord, blockSpecs.x);
  else if (blockSpecs.blockType == CUBOID)
    return drawCuboidAt(drawCoord, blockSpecs.x, blockSpecs.y, , blockSpecs.z);
  else if (blockSpecs.blockType == TETRAHEDRON)
    return drawTetraAt(drawCoord, blockSpecs.x, blockSpecs.y);
  else if (blockSpecs.blockType == TETRAHEDRON90)
    return drawTetra90At(drawCoord, blockSpecs.x, blockSpecs.y);
}

string TowerBuilder::drawCubeAt(Coord drawCoord, float cubeSize) {
  string cubeSTL = "";
  Triangle buff_tri;

  for (auto it = modifiedCube.begin(); it != modifiedCube.end(); ++it) {
    //position:
    for (int i = 0; i < 3; ++i) {
      buff_tri.triangle[i][0] = it->triangle[i][0] + drawCoord.x;
      buff_tri.triangle[i][1] = it->triangle[i][1] + drawCoord.y;
      buff_tri.triangle[i][2] = it->triangle[i][2] + drawCoord.z;
    }
    //size:
    for (int i = 0; i < 2; ++i)
      //if: not changing numbers that are 0
      if (it->triangle[i][0] != 0.0) buff_tri.triangle[i][0] = it->triangle[i][0] + cubeSize;
      if (it->triangle[i][1] != 0.0) buff_tri.triangle[i][1] = it->triangle[i][1] + cubeSize;
      if (it->triangle[i][2] != 0.0) buff_tri.triangle[i][2] = it->triangle[i][2] + cubeSize;
    }

    cubeSTL += createStringFromTriangle(buff_tri);
  }
  return cubeSTL;
}

string TowerBuilder::drawCuboidAt(Coord drawCoord, float cuboidX, float cuboidY, float cuboidZ) {
  string cuboidSTL;
  return cuboidSTL;
}

string TowerBuilder::drawTetraAt(Coord drawCoord, float tetraW, float tetraH) {
  string tetraSTL;
  return tetraSTL;
}

string TowerBuilder::drawTetra90At(Coord drawCoord, float tetra90W, float tetra90H) {
  string tetra90STL;
  return tetra90STL;
}
