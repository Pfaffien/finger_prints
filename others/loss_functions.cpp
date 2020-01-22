#include <fstream>
#include <string>

#include "image.h"
#include "optimization.h"


int main()
{
    const string fileName("../misc/data_transx.txt");
    ofstream file(fileName.c_str());

    if (file) {
        Image finger("../img/clean_finger.png");
        Image finger_tx("../img/tx_finger.png");
        int size = finger().cols;
        file << 2 * size + 1 << std::endl;
        for (int p = -size; p < size; p++)
            file << l_tx(finger, finger_tx, p) << std::endl;
    } else {
        std::cerr << "Error: could not open file" << std::endl;
    }

    return 0;
}