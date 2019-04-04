#include "TowerBuilder.hh"
#include "InputProcessor.hh"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

    string inputTextFilename = "run\\inputs\\intext.txt";
    string inputCharMapFilename = "run\\inputs\\charmap.txt";
    string inputTowerSpecsFilename = "run\\inputs\\towerspecs.txt";

    string outputFilePath = "run\\outputs\\";
    string outputFilename = "tower_";

    // Constructing output file name
    time_t now = time(0);
    tm *now_time = localtime(&now);
    string buff = to_string(now_time->tm_year+1900) + "_" +
                  to_string(now_time->tm_mon+1) + "_" +
                  to_string(now_time->tm_mday) + "_" +
                  to_string(now_time->tm_hour+1) + "_" +
                  to_string(now_time->tm_min+1) + ".stl";
    outputFilename.append(buff);

    // Reading inputs
    InputProcessor input;
    input.readInputText(inputTextFilename);
    input.readCharMap(inputCharMapFilename);
    input.readTowerSpecs(inputTowerSpecsFilename);


    //Building the tower
    TowerBuilder towerBuilder;
    if (towerBuilder.buildTower(input, outputFilePath+outputFilename)) {
        cout << "Building tower succesful." << endl
             << "Saving output file to: "
             << outputFilePath+outputFilename << "." << endl;
    } else {
        cout << "Error while building tower." << endl;
    }

    // Outputting the output file name to a file
    string outFileFileName = "run\\latestOutFileName.txt";
    ofstream ofs;
    ofs.open(outFileFileName);
    ofs << outputFilename;
    ofs.close();

    return 0;
}
