// https://github.com/RedGuff/ColoredTextureGenerator/edit/master/main.cpp enhanced:
#include <iostream>
#include <cstdlib> // https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Standard_C_Library/Functions/system
#include <fstream>
#include <math.h>
#include <time.h> // enough
#include <vector>
using namespace std;

int maxHz = 768; // pixels of the image. Few seconds for (2⁸ - 1) * (2⁸ - 1).
int maxVt = 768; // pixels of the image. Few seconds for (2⁸ - 1) * (2⁸ - 1).
const int nbComposantRGB = 3;
const int minRGB = 0; // Each. // 0 min, 65535 max.
const int maxRGB = 255; // Each. // 0 min, 65535 max.
// const int maxRGB = 65535; // Each. // 0 min, 65535 max..
int rgb = 1; // R = 1, G = 2, B = 3.
vector<vector<vector<int> > > imageTableauRGB_int(maxHz, vector<vector<int> >(maxVt, vector<int>(nbComposantRGB, 0)));

int pixelModif(int x, int y, int rgb, int intensity, float couleur) { // Not used?  // Rewrite with size()!
    x = x % maxHz; // Color over the limit: go to the other side!
    y = y % maxVt; // Color over the limit: go to the other side!
    int result = imageTableauRGB_int[x][y][rgb] +  intensity * couleur; // ints tous inclus. Quel tableau ?
    result = max(result, minRGB);    // Saturation if needed.
    result = min(result, maxRGB);    // Saturation if needed.
    // imageTableauRGB_int[x][y][rgb] = result;
    return  result;
}

int pixelInit(int h = 0, int v = 0, int rgb = 1) { // ?
    return minRGB + rand() % maxRGB;
}


int vector2ppm(vector<vector<vector<int>>>& imageTableauRGB_int, string name_noext = "file") { // colors // Rewrite with size()!
    string name_ext = name_noext + ".ppm";
    ofstream replaceFile(name_ext.c_str()); // remplace!
    if(!replaceFile) {
        cerr << "Impossible to open the file " << name_ext << " in order to write in it!" << endl;
    } else {
        string whiteS = "              "; // Log et répét ?
        replaceFile << "P3" << endl; // PPM format...
        replaceFile << maxHz << " " << maxVt << endl;
        replaceFile << maxRGB << endl << endl;
        for(int h = 0; h < maxVt; h++) {
            for(int v = 0; v < maxHz; v++) {
                for(int rgb = 1; rgb <= nbComposantRGB; rgb++) {
                    replaceFile << imageTableauRGB_int[h][v][rgb] << " " ;
                }
                replaceFile  << endl;
            }
            cout << whiteS + "\r" << h << "/" << maxVt;
            replaceFile << endl; // For a new line.
        }
    }
    replaceFile.close();
    return 0;
}

int vector2pgm() { // gray // TODO?
    cerr << "vector2pgm TODO!" << endl;
    return -1;
}

void order(auto& a, auto& b) {
    if (a>b) {
        swap(a,b);
    }
}

void initRGB0(int& minRGB0,int& maxRGB0) {
    minRGB0  = minRGB + rand() % maxRGB;
    maxRGB0  = minRGB + rand() % maxRGB;
    order(minRGB0, maxRGB0);
}

void lisseVt( vector<vector<vector<int>>>& Matrix, float seuil = 0.15) {  // Rewrite with size()!
// cout << "liss Start:" << endl;
    int minRGB0 = minRGB;
    int maxRGB0 = maxRGB;
    for(int rgb = 1; rgb <= nbComposantRGB; rgb++) {
        for(int hz = 0; hz < maxHz; hz++) {
            int start = 0+rand()%maxVt;
            initRGB0(minRGB0,maxRGB0);
            for(int vt = 0; vt < maxVt; vt++) {
                // Matrix2[vt][hz][rgb] =   Matrix1[vt][hz][rgb];
                if (vt+start>maxVt-1) {
                    start = -vt;
                }
                /*
                                cout << "hz:" << hz << endl;
                                cout << "vt:" << vt << endl;
                                cout << "rgb:" << rgb << endl;
                                cout << "start:" << start << endl;
                                cout << "vt + start:" << vt + start << endl;
                */
                Matrix[vt+start][hz][rgb] =  minRGB0 + rand() % maxRGB0;
                if (seuil*100>rand()%100) {
                    initRGB0(minRGB0,maxRGB0);
                }
            }
        }
    }
// cout << "liss End." << endl;
}

void lisseB45( vector<vector<vector<int>>>& Matrix, float seuil = 0.05) {  // Rewrite with size()!
// cout << "" << endl;
    // cout << "Liss45 Start:" << endl;
    int minRGB0 = minRGB;
    int maxRGB0 = maxRGB;
    for(int rgb = 1; rgb <= nbComposantRGB; rgb++) {
        for(int hz = 0; hz < maxHz; hz++) {
            int startH = 0+rand()%maxHz;
            int startV = 0+rand()%maxVt;
            initRGB0(minRGB0,maxRGB0);
            for(int vt = 0; vt < maxVt; vt++) {
                // Matrix2[vt][hz][rgb] =   Matrix1[vt][hz][rgb];
                if (vt+startV>maxVt-1) {
                    startV = -vt;
                }
                if (vt+startH>maxHz-1) {
                    startH = -vt;
                }
                /*
                                cout << "hz:" << hz << endl;
                                cout << "vt:" << vt << endl;
                                cout << "rgb:" << rgb << endl;
                                cout << "startV:" << startV << endl;
                                cout << "startH:" << startH << endl;
                                cout << "vt + startV:" << vt + startV << endl;
                                cout << "vt + startH:" << vt + startH << endl;
                */
                Matrix[vt+startV][vt+startH][rgb] =  minRGB0 + rand() % maxRGB0;
                if (seuil*100>rand()%100) {
                    initRGB0(minRGB0,maxRGB0);
                }
            }
        }
    }
// cout << "Liss45 End." << endl;
}




/*

void lisseHzOLD( vector<vector<vector<int>>>& Matrix1, vector<vector<vector<int>>>& Matrix2, float seuil = 0.01, int longueur = 42, int coef = 1) {
    int valeur = 0;
    int valeurStepInit = 0+rand()%maxHz;
     for(int rgb = 1; rgb <= nbComposantRGB; rgb++) {
        for(int hz = 0; hz < maxHz; hz++) {
    for(int vt = 0; vt < maxVt; vt++) {
                    valeur =  Matrix1[vt][hz][rgb];
                for (int stepInit2 = 0;stepInit2<longueur; stepInit2++){ // longueur not included.
int step = stepInit2 + valeurStepInit;
if (step>maxVt){
stepInit2 = 0;
}

                  //  Matrix2[vt][step][rgb] = (coef * Matrix1[vt][step][rgb] + valeur)/(coef+1); // moyenne avec coef qui décroit ?
                    Matrix2[vt][step][rgb] = (coef * Matrix1[vt][hz][rgb] + valeur)/(coef+1); // moyenne avec coef qui décroit ?
                }
            }
        }
    }
}


*/

void initMatrixRandom(vector<vector<vector<int>>>& imageTableauRGB_int) { // Rewrite with size()!
    for(int h = 0; h < maxVt; h++) {
        for(int v = 0; v < maxHz; v++) {
            for(int rgb = 1; rgb <= nbComposantRGB; rgb++) {
                imageTableauRGB_int[h][v][rgb] = pixelInit(h, v, rgb);
            }
        }
    }
}

int main() { // Rewrite with size()!
    srand(time(NULL));       // No need for better init. // May be need to be reproductible.
    if(maxRGB >= 65536) {
        printf("\033[%dm", 31); // GNU/Linux only!
        cerr << "Err: maxRGB can't be more than 65536 for PPM." << endl;
        printf("\033[%dm", 0);
        cout << "End." << endl;
    } else {
        cout << "Pseudo-random tilable texture (ASCII PPM image)." << endl;
        cout << "maxHz = " << maxHz << " pixels." << endl;
        cout << "maxVt = " << maxVt << " pixels." << endl;
        cout << "maxRGB = " << maxRGB << " < 65536: ok." << endl;
        cout << "nbComposantRGB = " << nbComposantRGB << "." << endl;
        cout << "When needed, give the name without the extension, and with optional relative or absolute path." << endl;
// Create seamless trivial image (solid color), (init):



// Convert to file:
        string name_noext = "";
        while(name_noext == "") {
            cout << "\a\nThe name without extension, please?" << endl;
            getline(cin, name_noext);
        }
        cout << "\nRand:" << endl;
        initMatrixRandom(imageTableauRGB_int);
        vector2ppm(imageTableauRGB_int, name_noext);
        cout << "\nV:" << endl;
        lisseVt(imageTableauRGB_int, 0.05);
        vector2ppm(imageTableauRGB_int, name_noext + "V");
        cout << "\nB45:" << endl;
        lisseB45(imageTableauRGB_int, 0.05);
        vector2ppm(imageTableauRGB_int, name_noext + "B45");


        clog << "\nFile ok: " << name_noext;
    }
    return 0;
}
