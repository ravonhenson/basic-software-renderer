#include <iostream>

#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
    bool steep { abs(y1 - y0) > abs(x1 - x0) };
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    else {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx {x1 - x0};
    int dy {abs(y1 - y0)};
    int yi {(y0 < y1) ? 1 : -1};
    int D  {2 * dy - dx};
    int y  {y0};

    for (int x = x0; x <= x1; x++) {
        if (steep) {
            image.set(y, x, color); // Swap x and y back for steep lines
        } else {
            image.set(x, y, color);
        }
        if (D > 0) {
            y += yi;
            D -= 2*dx;
        }
        D += 2*dy;
    }
}

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    line(0, 0, 50, 100, image, red);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    std::cout << "Complete!" << std::endl;
    return 0;
}