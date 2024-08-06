#include "Tree.h"
#include <random>
#define HEIGHT_MAX 8
#define HEIGHT_MIN 4



Tree::Tree(float noise) {
    int treeHeight = HEIGHT_MIN + static_cast<int>((HEIGHT_MAX - HEIGHT_MIN) * noise);
    treeHeight = fmax(HEIGHT_MIN, fmin(HEIGHT_MAX, treeHeight));


    int leafRadius = 2;
    for (int lx = -leafRadius; lx <= leafRadius; ++lx) {
        for (int lz = -leafRadius; lz <= leafRadius; ++lz) {
            for (int ly = -leafRadius / 2; ly <= leafRadius / 2; ++ly) {
                blocks.push_back(std::make_tuple(glm::ivec3(lx , treeHeight + ly, lz), LEAF));


            }
        }
    }

    for (int h = 0; h < treeHeight; ++h) {
        blocks.push_back(std::make_tuple(glm::ivec3(0, h, 0), WOOD));
    }
}