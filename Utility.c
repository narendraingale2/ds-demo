#include <stdlib.h>
#include <time.h>



float getRandomCoord(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}
