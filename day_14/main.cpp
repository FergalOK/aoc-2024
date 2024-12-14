#include <iostream>
#include <fstream>
#include <cassert>
#include <regex>
#include <thread>

struct robot {
    int x;
    int y;
    int vx;
    int vy;
};

// https://stackoverflow.com/a/2654860
void createBMP(char* image, int w, int h, int index) {
    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

    img = (unsigned char *)malloc(3*w*h);
    memset(img,0,3*w*h);

    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            int colour = 0;
            if (image[x +y*w] != 0) colour = 255;
            img[(x+y*w)*3+2] = (unsigned char)colour;
            img[(x+y*w)*3+1] = (unsigned char)colour;
            img[(x+y*w)*3+0] = (unsigned char)colour;
        }
    }

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

    f = fopen(("imgs/" + std::to_string(index) + "_img.bmp").c_str(),"wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }

    free(img);
    fclose(f);
}

int main(int argc,  char** argv) {
    assert(argc == 2);
    std::ifstream file(argv[1]);
    int width = 101;
    int height = 103;
    if (strcmp(argv[1], "example.txt") == 0) {
        width = 11;
        height = 7;
    }

    std::vector<robot> robots;
    for (std::string line; std::getline(file, line);) {
        std::regex re("p=(.+),(.+) v=(.+),(.+)");
        std::smatch match;
        std::regex_search(line, match, re);

        robots.push_back({stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])});
    }

    int quadrants[4] {};
    for (long i = 0; i < 7500; i++) {
        if (i == 100) { // Part 1
            for (auto r : robots) {
                if (r.x == width / 2 || r.y == height / 2) continue;

                int n = 0;
                if (r.x > width / 2) n += 1;
                if (r.y > height / 2) n += 2;
                quadrants[n]++;
            }
        }

        char map[height][width] {};
        for (auto &r : robots) {
            r.x = ((r.x + r.vx) % width + width) % width;
            r.y = ((r.y + r.vy) % height + height) % height;

            map[r.y][r.x] = 1;
        }

        createBMP((char*)map, width, height, i+1);
    }

    int result = 1;
    for (int i = 0; i < 4; i++) { result *= quadrants[i]; }
    std::cout << "Result (part 1): " << result << std::endl;
    std::cout << "Result (part 2): " << "SEARCH the BMPs!!!" << std::endl;
}
