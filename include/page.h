#include "vector"

class Page 
{
public:
    void place(std::vector<std::vector<short>> icon, int xOffset = 0, int yOffset = 0);
    void clear();
    std::vector<std::vector<short>> getMatrix();

private:
    std::vector<std::vector<short>> page;
};