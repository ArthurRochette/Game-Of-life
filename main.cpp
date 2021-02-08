#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

//Ration 4 pxl -> 1 case tableau

//regle
/*
 * si une cellule morte est entourer de 3 cellules en vie -> elle prend vie
 * si une cellule vivante possede deux ou trois voisines vivantes elle le reste, sinon non
 * */

const int WINDOW_SIZE_X = 200;
const int WINDOW_SIZE_Y = 200;
//TODO: on modifie le tableau en temps reel, ne faudrait
// il pas faire une copie du tableau pour creer le nouveau a partir d'une version static de l'ancien ??
bool *array;
int arraySizeX, arraySizeY;

void lifeChecker();

int neighborCount(int x, int y);

void draw(sf::RenderWindow *window);

void fullFill();

bool arraytest[] = {false, true, false, false};

std::vector <sf::Sprite> sprites;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Game of life");
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    arraySizeX = WINDOW_SIZE_X / 4;
    arraySizeY = WINDOW_SIZE_Y / 4;
    array = new bool[arraySizeX * arraySizeY];

    fullFill();
    int nbr;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }
        if (elapsed >= sf::seconds(1.0f)) {
            elapsed = sf::Time::Zero;
            std::cout << "$$$$$$$$$$a second" << std::endl;
            window.clear(sf::Color::Black);

            lifeChecker();
        }
        draw(&window);
        elapsed = clock.getElapsedTime();

    }
    //draw array
    return 0;
}

void fullFill() {
    std::srand(std::time(nullptr));
    for (int y = 0; y < arraySizeY; y++) {
        for (int x = 0; x < arraySizeX; x++) {
            if ((std::rand() % 5) == 0) {
                array[x + y * arraySizeY] = true;
            }
        }
    }
}

void draw(sf::RenderWindow *window) {
    //lire array
    sf::RectangleShape rec(sf::Vector2f(2, 2));

    rec.setFillColor(sf::Color::White);

    for (int y = 0; y < arraySizeY; y++) {
        for (int x = 0; x < arraySizeX; x++) {
            if (array[x + y * arraySizeY]) {
                rec.setPosition(x, y);
                window->draw(rec);
                std::cout << "1";

            } else {
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    //donner pour chaque valeur true un carré de position correspondante
}

void lifeChecker() {
    bool *buffer = new bool[arraySizeX * arraySizeY];
    for (int y = 0; y < arraySizeY; y++) {
        for (int x = 0; x < arraySizeX; x++) {
            //std::cout << "case " << x << ":" << y;
            int neighbor = neighborCount(x, y);
            //std::cout << " neigh " << neighbor;
            if (!array[x + y * arraySizeY] && neighbor == 3 ||
                array[x + y * arraySizeY] && (neighbor == 2 || neighbor == 3)) {
                //std::cout << " alive" << std::endl;
                buffer[x + y * arraySizeY] = true;
            } else if (array[x + y * arraySizeY] && (neighbor < 2 || neighbor > 3)) {
                //std::cout << " dead" << std::endl;
                buffer[x + y * arraySizeY] = false;//she dies
            } else {
                //std::cout << std::endl;
                buffer[x + y * arraySizeY] = array[x + y * arraySizeY];
            }
        }
    }
    delete array;
    array = buffer;
}

int neighborCount(int x, int y) {
    int neighbor = 0;
    if ((x != arraySizeX - 1 && x != 0) && (y != arraySizeY - 1 && y != 0)) {// case where square isn't in a limit
        if (array[(x + 1) + y * arraySizeY]) {//right
            //std::cout << "14";
            neighbor++;
        }
        if (array[(x + 1) + (y + 1) * arraySizeY]) {// bottom right
            //std::cout << "15";
            neighbor++;
        }
        if (array[(x + 1) + (y - 1) * arraySizeY]) {// top right
            //std::cout << "16";
            neighbor++;
        }
        if (array[(x - 1) + y * arraySizeY]) {//left
            //std::cout << "17";
            neighbor++;
        }
        if (array[(x - 1) + (y - 1) * arraySizeY]) {//top left
            //std::cout << "18";
            neighbor++;
        }
        if (array[(x - 1) + (y + 1) * arraySizeY]) {//bottom left
            //std::cout << "19";
            neighbor++;
        }
        if (array[x + (y + 1) * arraySizeY]) {//below
            //std::cout << "20";
            neighbor++;
        }
        if (array[x + (y - 1) * arraySizeY]) {//above
            //std::cout << "21";
            neighbor++;
        }
    } else if (x == arraySizeX - 1) {//si a droite
        if (y != arraySizeY - 1) {
            if (array[(x - 1) + (y + 1) * arraySizeY]) {//bottom left
                //std::cout << "22";
                neighbor++;
            }
            if (array[x + (y + 1) * arraySizeY]) {//below
                //std::cout << "23";
                neighbor++;
            }
        }
        if (array[(x - 1) + y * arraySizeY]) {//left
            //std::cout << "24";
            neighbor++;
        }
        if (array[(x - 1) + (y - 1) * arraySizeY]) {//top left
            //std::cout << "25";
            neighbor++;
        }
        if (array[x + (y - 1) * arraySizeY]) {//above
            //std::cout << "26";
            neighbor++;
        }
    } else if (x == 0) {//si a droite
        if (y != 0) {
            if (array[x + (y - 1) * arraySizeY]) {//above
                //std::cout << "98";
                neighbor++;
            }
            if (array[(x + 1) + (y - 1) * arraySizeY]) {// top right
                //std::cout << "99" ;
                neighbor++;
            }
        }
        if (array[(x + 1) + y * arraySizeY]) {//right
            //std::cout << "97" ;
            neighbor++;
        }
        if (array[(x + 1) + (y + 1) * arraySizeY]) {// bottom right
            //std::cout << "96";
            neighbor++;
        }

        if (array[x + (y + 1) * arraySizeY]) {//below
            //std::cout << "94" ;
            neighbor++;
        }

    } else if (y == 0) {//si tout en haut
        if (array[(x + 1) + y * arraySizeY]) {//right
            //std::cout << "14";
            neighbor++;
        }
        if (array[(x + 1) + (y + 1) * arraySizeY]) {// bottom right
            // std::cout << "15";
            neighbor++;
        }
        if (array[(x - 1) + y * arraySizeY]) {//left
            //std::cout << "17";
            neighbor++;
        }
        if (array[(x - 1) + (y + 1) * arraySizeY]) {//bottom left
            //std::cout << "19";
            neighbor++;
        }
        if (array[x + (y + 1) * arraySizeY]) {//below
            //std::cout << "20";
            neighbor++;
        }
    } else if (y == arraySizeY - 1) {
        if (array[(x + 1) + y * arraySizeY]) {//right
            //std::cout << "14";
            neighbor++;
        }
        if (array[(x + 1) + (y - 1) * arraySizeY]) {// top right
            //std::cout << "16";
            neighbor++;
        }
        if (array[(x - 1) + y * arraySizeY]) {//left
            //std::cout << "17";
            neighbor++;
        }
        if (array[(x - 1) + (y - 1) * arraySizeY]) {//top left
            //std::cout << "18";
            neighbor++;
        }

        if (array[x + (y - 1) * arraySizeY]) {//above
            //std::cout << "21";
            neighbor++;
        }
    }
    return neighbor;
}




