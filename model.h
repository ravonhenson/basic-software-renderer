//
// Created by Ravon Henson on 4/1/24.
//

#ifndef BASIC_SOFTWARE_RENDERER_MODEL_H
#define BASIC_SOFTWARE_RENDERER_MODEL_H

#include <vector>
#include "geometry.h"

class Model {
private:
    std::vector<Vec3f> verts_;
    std::vector<std::vector<int> > faces_;
public:
    Model(const char *filename);
    ~Model();
    int nverts();
    int nfaces();
    Vec3f vert(int i);
    std::vector<int> face(int idx);
};

#endif //BASIC_SOFTWARE_RENDERER_MODEL_H
