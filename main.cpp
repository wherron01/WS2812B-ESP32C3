#include <iostream>
#include <Magick++.h>
#include <cstring>

/**
 * Uses ImageMagick to convert a gif into a string of bytes for the display driver to read.
 * Reminds me a bit of the image of the guy cutting a cake with a broadsword, but there doesn't seem to be a better tool for the job.
 * Willow Herron
 */

int main(int argc, char* argv[]) {
    if(argc < 2) return 1;
    FILE* file;
    file = fopen(argv[1], "wb");
    Magick::InitializeMagick(NULL);
    std::list<Magick::Image> frames;
    Magick::readImages(&frames, strcat(argv[1], ".gif"));
    for(Magick::Image image : frames) {
        unsigned w = image.columns();
        unsigned h = image.rows();
        for(unsigned i = 0; i < w*h; i++) {
            unsigned x = 0; unsigned y = h;
            y = i/w;
            x = i%w;
            x = (y%2) ? (w-1)-x : x;
            y = (h-1)-y;
            Magick::ColorRGB c = image.pixelColor(x,y);
            unsigned char color[3] = {(unsigned char)(c.red()*255), (unsigned char)(c.green()*255), (unsigned char)(c.blue()*255)};
            fwrite(color, 1, 3, file);
        }
    }
    fclose(file);
    file = fopen(argv[1], "rb");
    unsigned char color[3];
    while(fread(color, 1, 3, file)) {
        printf("%X %X %X\n",  color[0], color[1], color[2]);
    }
    fclose(file);
    return 0;
}
