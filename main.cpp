#include <vector>
#include <cmath>
#include <iostream>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const int width  = 800;
const int height = 800;

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
    // create image
    TGAImage image(width, height, TGAImage::RGB);

    // wire renderer
    Model model {"../obj/african_head.obj"};
    std::cout << "Number of faces: " << model.nfaces() << std::endl;
    for (int i=0; i<model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model.vert(face[j]);
            Vec3f v1 = model.vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
            line(x0, y0, x1, y1, image, white);
            std::cout << "Line from (" << x0 << ", " << y0 << ") to ("
                      << x1 << ", " << y1 << ") written.\n";
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}