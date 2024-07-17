#include "utilities.h"

std::string aggregate_numbers(std::string number) {
    int len = number.length();

    if (len > 5) {
        return "LOL";
    } else if (len > 3) {
        return number.substr(0, len - 3) + "k";
    } else {
        return number;
    }
}

// useful for debugging
String pixelMatrixToString(std::vector<std::vector<short>> pixelMatrix) {
    int yOffset = 0;
    String str = "";
    for (const auto& rows : pixelMatrix) {
        int x = 0;
        for(const auto& brightness: rows){
            int setPixel = 0;
            if(brightness > 0 ){
                setPixel = 1;
            }
            if (brightness != 0) {
                str += "x";
            }
            else
            {
                str += "o";
            }
            
            x++;
        }
        yOffset++;
        str += "\n";
    }
    return str;
}