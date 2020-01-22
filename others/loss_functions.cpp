#include <fstream>
#include <string>

#include "image.h"
#include "optimization.h"

using namespace std;


int main()
{
    const string fileName("../others/data_transx.txt");
    ofstream file(fileName.c_str());

    if (file) {
        Image finger("../img/clean_finger.png");
        Image finger_tx("../img/tx_finger.png");
        int size = finger().cols;
        file << 2 * size - 1 << std::endl;
        for (int p = -size+1; p < size; p++)
            file << l(finger_tx, finger, p) << std::endl;
    } else {
        std::cerr << "Error: could not open file" << std::endl;
    }

    return 0;
}