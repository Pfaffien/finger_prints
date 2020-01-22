#include <fstream>
#include <string>

#include "image.h"
#include "optimization.h"

using namespace std;


void loss_tx(string fileName)
{
    ofstream file(fileName.c_str());

    if (file) {
        Image img("../img/clean_finger.png");
        Image img_tx("../img/tx_finger.png");
        int size = img().cols;
        file << 2 * size - 1 << std::endl;
        for (int p = -size+1; p < size; p++)
            file << l_tx(img_tx, img, p) << std::endl;
        file.close();
    } else {
        std::cerr << "Error: could not open file" << std::endl;
    }
}


void loss_txy(string fileName)
{
    ofstream file(fileName.c_str());

    if (file) {
        Image img("../img/clean_finger.png");
        Image img_txy("../img/txy_finger.png");
        int size_x = img().cols;
        int size_y = img().rows;
        file << 2 * size_x - 1 << std::endl;
        file << 2 * size_y - 1 << std::endl;
        for (int p_x = -size_x+1; p_x < size_x; p_x++) {
            for (int p_y = -size_y+1; p_y < size_y; p_y++)
                file << l_txy(img_txy, img, p_x, p_y) << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error: could not open file" << std::endl;
    }
}


int main()
{
    loss_tx("../others/data_tx.txt");
    loss_txy("../others/data_txy.txt");

    return 0;
}