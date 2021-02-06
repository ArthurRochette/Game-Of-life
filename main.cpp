#include <iostream>
#include <SFML/Graphics.hpp>

//Ration 4 pxl -> 1 case tableau

//regle
/*
 * si une cellule morte est entourer de 3 cellules en vie -> elle prend vie
 * si une cellule vivante possede deux ou trois voisines vivantes elle le reste, sinon non
 * */

const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 800;
//TODO: on modifie le tableau en temps reel, ne faudrait
// il pas faire une copie du tableau pour creer le nouveau a partir d'une version static de l'ancien ??
bool *array;
int arraySizeX, arraySizeY;

void lifeChecker();

int neighborCount(int x, int y);

int main() {
    std::cout << "Hello, World!" << std::endl;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Game of Life");
    arraySizeX = WINDOW_SIZE_X / 4;
    arraySizeY = WINDOW_SIZE_Y / 4;
    array = new bool[arraySizeX * arraySizeY];

    return 0;

}

void lifeChecker() {
    for (int y = 0; y < arraySizeY; y++) {
        for (int x = 0; x < arraySizeX; x++) {
            int neighbor = neighborCount(x, y);
            if (!array[x + y * arraySizeY] && neighbor == 3) {

            } else if (array[x + y * arraySizeY] && (neighbor < 2 || neighbor > 3)) {
                array[x + y * arraySizeY] = false;//she dies
            }

        }
    }
}

int neighborCount(int x, int y) {
    int neighbor = 0;
    if ((x != arraySizeX - 1 && x != 0) && (y != arraySizeY - 1 && y != 0)) {// case where square isn't in a limit
        if (array[x + 1 + y * arraySizeY]) {//right
            neighbor++;
        }
        if (array[x + 1 + y * arraySizeY] + 1) {// bottom right
            neighbor++;
        }
        if (array[x + 1 + y * arraySizeY] + -1) {// top right
            neighbor++;
        }
        if (array[x - 1 + y * arraySizeY]) {//left
            neighbor++;
        }
        if (array[x - 1 + y * arraySizeY] - 1) {//top left
            neighbor++;
        }
        if (array[x - 1 + y * arraySizeY] + 1) {//bottom left
            neighbor++;
        }
        if (array[x + y * arraySizeY + 1]) {//below
            neighbor++;
        }
        if (array[x + 1 + y * arraySizeY - 1]) {//above
            neighbor++;
        }
    } else if (x == arraySizeX - 1) {//square in full right position limit
        if (y == arraySizeY - 1) {
            if (array[x - 1 + y * arraySizeY] + 1) {//bottom left
                neighbor++;
            }
            if (array[x + y * arraySizeY + 1]) {//below
                neighbor++;
            }
        }
        if (array[x - 1 + y * arraySizeY]) {//left
            neighbor++;
        }
        if (array[x - 1 + y * arraySizeY] - 1) {//top left
            neighbor++;
        }
        if (array[x + 1 + y * arraySizeY - 1]) {//above
            neighbor++;
        }
    } else if (x == 0) {
        if (y != 0) {
            if (array[x + 1 + y * arraySizeY - 1]) {//above
                neighbor++;
            }
            if (array[x + 1 + y * arraySizeY] - 1) {// top right
                neighbor++;
            }
        }
        if (array[x + 1 + y * arraySizeY]) {//right
            neighbor++;
        }
        if (array[x + 1 + y * arraySizeY] + 1) {// bottom right
            neighbor++;
        }

        if (array[x + y * arraySizeY + 1]) {//below
            neighbor++;
        }

    }

}




