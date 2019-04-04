#include "InputProcessor.hh"
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

bool InputProcessor::readInputText(string filename) {

    ifstream fin;
    fin.open(filename);

    char c;
    int i = 0;

	while (fin.get(c)) {
        if(isalpha(c)) {
             if(i < 500) {
                c = tolower(c);
                text.push_back(c);
                ++i;
                wordCount = i;
             } else break;
        }
	}
	fin.close();
  return true; //todo: create a valid return
}

void InputProcessor::readCharMap(string filename) {

    ifstream fin;
    fin.open(filename);

    for(int i=0; i<26; i++) {
            fin >> charCoords[i].c;
            fin >> charCoords[i].x;
            fin >> charCoords[i].y;
            charCoords[i].c = tolower(charCoords[i].c);
    }

    fin.close();
}

void InputProcessor::readTowerSpecs(string filename) {
    float cubeVal = 0;
    float cuboidVals[] = {0,0,0};
    float tetraVals[] = {0,0};
    float tetra90Vals[] = {0,0};
    int blockChooser[4];

    ifstream fin;
    fin.open(filename);
    fin >> blockChooser[0] >> blockChooser[1] >> blockChooser[2] >> blockChooser[3];

    fin >> cubeVal;
    fin >> cuboidVals[0] >> cuboidVals[1] >> cuboidVals[2];
    fin >> tetraVals[0] >> tetraVals[1];
    fin >> tetra90Vals[0] >> tetra90Vals[1];
    fin.close();

    int choosedBlock = 0;
    for (int i=0; i<4; ++i) {
        if (blockChooser[i] == 1) {
            choosedBlock = i;
            break;
        }
    }

    switch (choosedBlock) {
        case 0: specs.blockType = CUBE;
                specs.x = cubeVal;
                specs.y = 0;
                specs.z = 0;
                break;
        case 1: specs.blockType = CUBOID;
                specs.x = cuboidVals[0];
                specs.y = cuboidVals[1];
                specs.z = cuboidVals[2];
                break;
        case 2: specs.blockType = TETRAHEDRON;
                specs.x = tetraVals[0];
                specs.y = tetraVals[1];
                specs.z = 0;
                break;
        case 3: specs.blockType = TETRAHEDRON90;
                specs.x = tetra90Vals[0];
                specs.y = tetra90Vals[1];
                specs.z = 0;
                break;
        default: break;
    }
}
