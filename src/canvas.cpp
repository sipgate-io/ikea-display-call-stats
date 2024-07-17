#include "canvas.h"
#include "screen.h"

void Canvas_::gradientTest(){
    int brightness = 1;
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
           Screen.setPixel(i,j,1,this->scaleBrightness(brightness));
           brightness++;
        } 
    }
    Screen.setPixel(15,15,1);
}

void Canvas_::bootAnimation(){ 
    // shorthand for breathingAnimation with sipgate Logo
    this->breathingAnimation(sipgateLogo);
    Screen.clear();
}

void Canvas_::displayError(int cycles, int millisDelay){

    for (int i = 0; i < cycles; i++){
      Screen.clear();
      this->drawImage(wifiDot, 7, 12, 255, false);
      delay(millisDelay);
      this->drawImage(wifiBar1, 5 ,9, 255, false);
      delay(millisDelay);
      this->drawImage(wifiBar2, 2, 6, 255, false);
      delay(millisDelay);
      this->drawImage(wifiBar3, 0, 3, 255, false);
      delay(millisDelay);
    }
}
void Canvas_::displayIdle()
{
    Screen.clear();
    Screen.setPixel(4, 7, 1);
    Screen.setPixel(5, 7, 1);
    Screen.setPixel(7, 7, 1);
    Screen.setPixel(8, 7, 1);
    Screen.setPixel(10, 7, 1);
    Screen.setPixel(11, 7, 1);
}
int Canvas_::scaleBrightness(int brightness){
        // Ensure scaled brightness is within the expected range
    if (brightness < 0) brightness = 0;
    if (brightness > 255) brightness = 255;

    // Constants for logarithmic scaling
    const double minBrightness = 1.0;   // Minimum input brightness
    const double maxBrightness = 255.0; // Maximum input brightness
    const double logMin = 0.0;          // log(minBrightness)
    const double logMax = std::log(maxBrightness); // log(maxBrightness)

    // Calculate the original brightness using the inverse of the logarithmic scale
    double linearScale = brightness / 255.0;
    int scaledBrightness = static_cast<int>(std::exp(logMin + linearScale * (logMax - logMin)));

    // Ensure original brightness is within the valid range
    if (scaledBrightness < 1) scaledBrightness = 0;
    if (scaledBrightness > 255) scaledBrightness = 255;

    return scaledBrightness;
}


void Canvas_::drawImage(std::vector<std::vector<short>> image, int xOffset, int yOffset, int brightnessScale, bool overwrite){
    
    float scale = brightnessScale / 255.0;
    for (const auto& rows : image) {
        int x = xOffset;
        for(const auto& brightness: rows){
            int setPixel = 0;
            if(brightness > 0 ){
                setPixel = 1;
            }
            if (brightness != 0 || overwrite) {
              Screen.setPixel(x, yOffset, setPixel, this->scaleBrightness((int)(brightness*scale)));
            }
            x++;
        }
        yOffset++;
    }

}

std::vector<std::vector<short>> Canvas_::stringToPixelMatrix(std::string text, uint8_t fontid) {
  // lets determine the current font
  font currentFont = (fontid < fonts.size()) ? fonts[fontid] : fonts[0];
  std::vector<std::vector<short>> pixelMatrix;

  // int textWidth = text.length() * (currentFont.sizeX -3); // charsize + space

    int skippedChars = 0;

    for (std::size_t strPos = 0; strPos < text.length(); strPos++)
    { // since i need the pos to calculate, this is the best way to iterate here
      if (text[strPos] == 195)
      {
        // we skip the unicode char indicating special characters
        skippedChars++;
      }      
      else
      {
        // so are we somewhere on screen with the char?
        // ensure that we have a defined char, lets take the first
        uint8_t currentChar = (((text[strPos] - currentFont.offset) < currentFont.data.size()) && (text[strPos] >= currentFont.offset)) ? text[strPos] : currentFont.offset;

        auto pixels = this->toCustomPixel(currentFont.data[currentChar - currentFont.offset], 8);

        if (pixelMatrix.empty())
        {
          pixelMatrix = pixels;
        }
        else {
          pixelMatrix = this->horizontalConcat(pixelMatrix, pixels);
        }

        //Screen.drawCharacter(xPos, yPos, Screen.readBytes(currentFont.data[currentChar - currentFont.offset]), 8, overwrite);
      }
    }

    return pixelMatrix;
}

// Default y_pos value is 0 -> top left
// Bottom left y value is 9
void Canvas_::printText( std::string text,int xOffset, int yOffset, uint8_t brightness, uint8_t fontid, bool overwrite)
{

  auto pixelMatrix =  this->stringToPixelMatrix(text, fontid);
  this->drawImage(pixelMatrix, xOffset, yOffset, brightness, overwrite);
  
}


 std::vector<std::vector<short>> Canvas_::toCustomPixel(std::vector<int> oldPixel, int oldWidth, int brightness, int ignoreLast) {
        int maxY = oldPixel.size();
        int maxX = oldWidth;
        
        // Create a new 2D vector to store custom pixels
        std::vector<std::vector<short>> newPixel = this->emptyImage(0, maxX-ignoreLast, maxY);
        
        // Read binary data from oldPixel (assuming it's already in binary format)
        std::vector<int> binary = Screen.readBytes(oldPixel);

        int x = 0;
        int y = 0;

        // Iterate through binary data and populate newPixel
        for (int i : binary) {
            // Apply brightness adjustment
            if (x < maxX - ignoreLast ) {
              newPixel[y][x] = static_cast<short>(i * brightness);
            }
            
            // Move to the next column
            x++;
            
            // If we reach maxX columns, move to the next row
            if (x >= maxX) {
                x = 0;
                y++;
            }
            
        }

        return newPixel;
    }

// Animations

void Canvas_::animate(std::vector<std::vector<std::vector<short>>> frames, int timems)
{
    for (const auto& frame : frames){
        this->drawImage(frame);
        delay(timems);
    }
}

void Canvas_::horizontalWipeAnimation(std::vector<std::vector<short>> image, int timems, bool invertDirection){
    if (invertDirection){
        for( int i = ((int)image.size()-16)*-1; i < 0; i++){
            Screen.clear();
            drawImage(image, i);
            delay(timems);
        }
        return;
    }


    for( int i = 0; i > ((int)image[0].size()-16)*-1; i--){
        Screen.clear();
        drawImage(image, i);
        delay(timems);
    }
}

void Canvas_::verticalWipeAnimation(std::vector<std::vector<short>> image,int timems, bool invertDirection){
    if (invertDirection){
        for( int i = ((int)image.size()-16)*-1; i < 0; i++){
            Screen.clear();
            drawImage(image, 0, i);
            delay(timems);
        }

        return;
    }

    for( int i = 0; i > ((int)image.size()-15)*-1; i--){
        Screen.clear();
        drawImage(image, 0, i);
        delay(timems);
    }
}

void Canvas_::diagonalWipeAnimation(std::vector<std::vector<short>> part1,int timems, bool invertDirection){
    if (invertDirection){
        for( int i = ((int)part1.size()-16)*-1; i < 0; i++){
            Screen.clear();
            drawImage(part1, i, i);
            delay(timems);
        }
        return;
    }
    for( int i = 0; i > ((int)part1.size()-15)*-1; i--){
        Screen.clear();
        drawImage(part1, i, i);
        delay(timems);
    }
}



std::vector<std::vector<short>> Canvas_::emptyImage(int brightness, int sizeX, int sizeY){
    std::vector<short> row(sizeX, brightness);
    std::vector<std::vector<short>> filled(sizeY, row);
    return filled;

}

std::vector<std::vector<short>> Canvas_::verticalConcat(std::vector<std::vector<short>> part1,std::vector<std::vector<short>> part2){
    if(part1[0].size()<part2[0].size()){
        std::vector<short> someVector(part2[0].size()-part1[0].size(), 0);

        for(auto& row : part1){
            row.insert(row.end(), someVector.begin(), someVector.end());
        }
        
    }

    part1.insert(part1.end(), part2.begin(), part2.end());
    return part1;

}

std::vector<std::vector<short>> Canvas_::horizontalConcat(std::vector<std::vector<short>> part1, std::vector<std::vector<short>> part2) {
    // Find the length of the longest row
    int length = 0;
    for (const auto& row : part1) {
        if (row.size() > length) {
            length = row.size();
        }
    }

    // Fill rows in part1 to make them consistent in size
    for (auto& row : part1) {
        if (row.size() < length) {
            row.insert(row.end(), length - row.size(), 0);
        }
    }

    // Fill y values to make part1 and part2 the same height
    while (part1.size() < part2.size()) {
        part1.emplace_back(length, 0);
    }

    // Concatenate rows from part2 to part1
    for (size_t r = 0; r < part2.size(); ++r) {
        part1[r].insert(part1[r].end(), part2[r].begin(), part2[r].end());
    }

    return part1;
}

std::vector<std::vector<short>> Canvas_::diagonalConcat(std::vector<std::vector<short>> part1,std::vector<std::vector<short>> part2, bool invert){
    std::vector<std::vector<short>> first = this->horizontalConcat(part1, this->emptyImage());
    std::vector<std::vector<short>> second = this->horizontalConcat(this->emptyImage(), part2);


    if(invert){
        return this->verticalConcat(second, first);
    }
    return this->verticalConcat(first, second);

}


void Canvas_::breathingAnimation(std::vector<std::vector<short>> image, int cycles, int millisDelay){
    for(int j = 0; j < cycles; j++){
        for(int i = 0; i<255; i++){
            this->drawImage(image, 0, 0, i);
            delay(millisDelay);
        }
        for(int k = 255; k>1; k--){
            this->drawImage(image, 0, 0, k);
            delay(millisDelay);
    }
  }

}

void Canvas_::clear(){
    Screen.clear();
}

Canvas_ &Canvas_::getInstance()
{
  static Canvas_ instance;
  return instance;
}

Canvas_ &Canvas = Canvas.getInstance();

