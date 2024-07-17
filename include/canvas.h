#pragma once

#include "vector"
#include <string>

class Canvas_ {
    private:
    Canvas_() = default;

    public:

    std::vector<std::vector<short>> sipgateLogo = {{0,0,0,0,0,0,5,17,17,5,0,0,0,0,0,0},{0,0,0,9,86,163,208,225,225,208,163,84,8,0,0,0},{0,0,54,202,255,255,255,255,255,255,255,255,201,53,0,0},{0,45,234,255,255,255,255,255,255,255,255,255,255,233,48,0},{1,171,255,255,255,255,255,255,255,255,255,255,255,255,140,0},{10,221,255,255,255,255,255,255,255,255,255,255,202,92,13,0},{4,202,255,255,255,255,255,255,255,255,200,92,13,0,0,0},{0,99,255,255,255,255,255,255,198,95,28,26,45,35,1,0},{0,2,135,252,255,253,198,101,43,46,65,77,87,101,49,0},{0,0,0,74,200,128,73,80,97,107,114,122,130,140,123,7},{0,7,73,179,233,198,179,169,164,163,164,166,169,175,163,17},{0,117,255,255,255,253,244,229,217,208,202,200,199,208,154,3},{0,39,227,255,255,253,252,247,241,234,227,223,226,215,57,0},{0,0,46,197,255,255,255,254,251,248,248,246,203,67,0,0},{0,0,0,7,84,165,211,228,228,212,173,99,17,0,0,0},{0,0,0,0,0,0,7,22,23,11,0,0,0,0,0,0}};
    std::vector<std::vector<short>> wifiDot = {{255, 255},{255, 255}};
    std::vector<std::vector<short>> wifiBar1 = {{0,0,255,255,0,0},{0,255,0,0,255,0},{255,0,0,0,0,255}};
    std::vector<std::vector<short>> wifiBar2 = {{0,0,0,0,255,255,255,255,0,0,0,0},{0,0,255,255,0,0,0,0,255,255,0,0},{0,255,0,0,0,0,0,0,0,0,255,0},{255,0,0,0,0,0,0,0,0,0,0,255}};
    std::vector<std::vector<short>> wifiBar3 = {{0,0,0,0,255,255,255,255,255,255,255,255,0,0,0,0},{0,0,255,255,0,0,0,0,0,0,0,0,255,255,0,0},{0,255,0,0,0,0,0,0,0,0,0,0,0,0,255,0},{255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255}};
    std::vector<std::vector<short>> eggIcon = {{0,0,0,0,0,255,255,255,255,0,0,0,0,0},{0,0,0,255,255,0,0,0,0,255,255,0,0,0},{0,0,255,0,0,0,0,0,0,0,0,255,0,0},{0,255,0,0,0,0,0,0,0,0,0,0,255,0},{0,255,0,0,0,0,0,0,0,0,0,0,255,0},{255,0,0,0,0,0,255,255,0,0,0,0,0,255},{255,255,0,0,0,255,0,0,255,0,0,0,255,255},{255,0,255,255,255,255,0,0,255,255,255,255,0,255},{0,255,0,0,0,0,255,255,0,0,0,0,255,0},{0,255,0,0,0,0,0,0,0,0,0,0,255,0},{0,0,255,0,0,0,0,0,0,0,0,255,0,0},{0,0,0,255,255,0,0,0,0,255,255,0,0,0},{0,0,0,0,0,255,255,255,255,0,0,0,0,0}};
    std::vector<std::vector<short>> callIcon = {{0,255,255,0,0,255,0,0,255,0,0,255,0,0},{255,0,0,0,255,0,255,0,255,0,0,255,0,0},{255,0,0,0,255,0,255,0,255,0,0,255,0,0},{255,0,0,0,255,255,255,0,255,0,0,255,0,0},{255,0,0,0,255,0,255,0,255,0,0,255,0,0},{0,255,255,0,255,0,255,0,255,255,0,255,255,0}};
    std::vector<std::vector<short>> faxIcon = {{0,0,0,0,0,0,255,255,255,255,255,0,0,0},{0,0,0,0,0,255,0,0,0,0,0,255,0,0},{0,0,0,0,0,255,0,255,255,255,0,255,0,0},{0,0,0,0,0,255,0,0,0,0,0,255,0,0},{0,0,0,0,0,255,0,255,255,255,0,255,0,0},{0,255,255,0,255,255,0,0,0,0,0,255,255,0},{255,0,0,255,0,0,255,255,255,255,255,0,0,255},{255,0,0,255,0,0,0,0,0,0,0,0,0,255},{255,0,0,255,0,0,255,0,255,0,255,0,0,255},{255,0,0,255,0,0,0,0,0,0,0,0,0,255},{255,0,0,255,0,0,255,0,255,0,255,0,0,255},{255,0,0,255,0,0,0,0,0,0,0,0,0,255},{255,0,0,255,0,0,212,0,255,0,255,0,0,255},{255,0,0,255,0,0,0,0,0,0,0,0,0,255},{0,255,255,0,255,255,255,255,255,255,255,255,255,0}};
    std::vector<std::vector<short>> smsIcon = {{255,255,255,255,255,255,255,255,255,255,255,255,255,255, 0},{255,255,0,0,0,0,0,0,0,0,0,0,255,255},{255,0,255,0,0,0,0,0,0,0,0,255,0,255},{255,0,0,255,0,0,0,0,0,0,255,0,0,255},{255,0,0,0,255,255,255,255,255,255,0,0,0,255},{255,255,255,255,255,255,255,255,255,255,255,255,255,255}};
    std::vector<std::vector<short>> errorIcon = {{0,0,0,0,0,255,255,255,255,0,0,0,0,0},{0,0,0,255,255,0,0,0,0,255,255,0,0,0},{0,0,255,0,0,0,0,0,0,0,0,255,0,0},{0,255,0,255,0,0,0,0,0,0,255,0,255,0},{0,255,0,0,255,0,0,0,0,255,0,0,255,0},{255,0,0,0,0,255,0,0,255,0,0,0,0,255},{255,0,0,0,0,0,255,255,0,0,0,0,0,255},{255,0,0,0,0,255,0,0,255,0,0,0,0,255},{0,255,0,0,255,0,0,0,0,255,0,0,255,0},{0,255,0,255,0,0,0,0,0,0,255,0,255,0},{0,0,255,0,0,0,0,0,0,0,0,255,0,0},{0,0,0,255,255,0,0,0,0,255,255,0,0,0},{0,0,0,0,0,255,255,255,255,0,0,0,0,0}};

    static Canvas_ &getInstance();

    void displayError(int cycles, int millisDelay);
    void bootAnimation();
    void displayIdle();
    void gradientTest();
    int scaleBrightness(int);
    std::vector<std::vector<short>> stringToPixelMatrix(std::string text, uint8_t fontid= 0);
    // default ignoreLast = 3 because last three values are 0 and should be ignored
    std::vector<std::vector<short>> toCustomPixel(std::vector<int> oldPixel, int oldWidth, int brightness = 255, int ignoreLast = 3);
    void printText(std::string text,int xPos = 0,int yPos = 0,  uint8_t brightness = 255, uint8_t fontid= 0, bool overwrite = true);
    void drawImage(std::vector<std::vector<short>> part, int xOffset = 0, int yOffset = 0, int brightnessScale = 255, bool overwrite = true);

    void animate(std::vector<std::vector<std::vector<short>>> frames, int timems);
    std::vector<std::vector<short>> emptyImage(int brightness = 0, int sizeX = 16, int sizeY= 16);
    std::vector<std::vector<short>> verticalConcat(std::vector<std::vector<short>> part1,std::vector<std::vector<short>> part2);
    std::vector<std::vector<short>> horizontalConcat(std::vector<std::vector<short>> part1,std::vector<std::vector<short>> part2);
    std::vector<std::vector<short>> diagonalConcat(std::vector<std::vector<short>> part1,std::vector<std::vector<short>> part2, bool invert = false);

    // Animations
    void horizontalWipeAnimation(std::vector<std::vector<short>> part, int timems, bool invertDirection = false);
    void verticalWipeAnimation(std::vector<std::vector<short>> part, int timems, bool invertDirection = false);
    void diagonalWipeAnimation(std::vector<std::vector<short>> part1,int timems, bool invertDirection = false);
    void fireworkAnimation(std::vector<std::vector<short>> part);
    void fadeToBlackAnimation(std::vector<std::vector<short>> part1,std::vector<std::vector<short>> part2);
    void breathingAnimation(std::vector<std::vector<short>> part, int cycles = 1, int millisDelay = 1); // linear for now maybe customizable via lambda function
    void clear();
};

extern Canvas_ &Canvas;