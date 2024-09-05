#include <iostream>

struct Map {
    int map[7][7] = {
        {1, 1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 1, 0},
        {1, 0, 1, 0, 0, 0, 1}
    };
};

struct BooleanMap {
    bool visited[7][7] = { false };
};

struct ValidCell {
    int positionX;
    int positionY;
    ValidCell* next = nullptr;
};

ValidCell* pathStack = nullptr;

void push(ValidCell* cell) {
    cell->next = pathStack;
    pathStack = cell;
}

ValidCell* pop() {
    if (pathStack == nullptr) return nullptr;
    ValidCell* temp = pathStack;
    pathStack = pathStack->next;
    return temp;
}

void printPath() {
    ValidCell* cell = pathStack;
    while (cell != nullptr) {
        std::cout << "(" << cell->positionX << "," << cell->positionY << ") ";
        cell = cell->next;
    }
    std::cout << std::endl;
}
bool checkMap(Map& map, BooleanMap& booleanMap, int startX, int startY, int endX, int endY) {
    if (map.map[startX][startY] == 0 || map.map[endX][endY] == 0) {
        return false; 
    }
    ValidCell* localStack = nullptr;
    push(new ValidCell{ startX, startY, nullptr });
    booleanMap.visited[startX][startY] = true;

    while (pathStack != nullptr) {
        ValidCell* current = pop();
        int x = current->positionX;
        int y = current->positionY;

        if (x == endX && y == endY) {
            push(new ValidCell{ x, y, nullptr });
            return true;
        }
        if (x > 0 && map.map[x - 1][y] == 1 && !booleanMap.visited[x - 1][y]) {
            booleanMap.visited[x - 1][y] = true;
            push(new ValidCell{ x - 1, y, nullptr });
        }
        if (x < 6 && map.map[x + 1][y] == 1 && !booleanMap.visited[x + 1][y]) {
            booleanMap.visited[x + 1][y] = true;
            push(new ValidCell{ x + 1, y, nullptr });
        }
        if (y > 0 && map.map[x][y - 1] == 1 && !booleanMap.visited[x][y - 1]) {
            booleanMap.visited[x][y - 1] = true;
            push(new ValidCell{ x, y - 1, nullptr });
        }
        if (y < 6 && map.map[x][y + 1] == 1 && !booleanMap.visited[x][y + 1]) {
            booleanMap.visited[x][y + 1] = true;
            push(new ValidCell{ x, y + 1, nullptr });
        }
    }

    while (pathStack != nullptr) {
        ValidCell* temp = pop();
        delete temp;
    }

    return false;
}
bool explore(Map& map, BooleanMap& booleanMap, int x, int y, int endX, int endY) {
    if (x == endX && y == endY) {
        push(new ValidCell{ x, y, nullptr });
        return true;
    }
    if (x < 0 || x >= 7 || y < 0 || y >= 7 || map.map[x][y] == 0 || booleanMap.visited[x][y]) {
        return false;
    }
    booleanMap.visited[x][y] = true;
    push(new ValidCell{ x, y, nullptr });

    if (explore(map, booleanMap, x - 1, y, endX, endY)) return true;

    if (explore(map, booleanMap, x + 1, y, endX, endY)) return true;

    if (explore(map, booleanMap, x, y - 1, endX, endY)) return true;

    if (explore(map, booleanMap, x, y + 1, endX, endY)) return true;
    pop();
    return false;
}
void printMaze(Map map) {
    for (int i = 0; i < 7; i++) {{
            for (int j = 0; j < 7; j++) {
                std::cout <<" "<< map.map[i][j]<<" ";
            }
            std::cout << std::endl;
        }
    }
}
int main() {
    
    char choice;
    do {
        Map map;
        BooleanMap booleanMap;
        printMaze(map);
        int startX, startY, endX, endY;
        std::cout << "Ingrese la posicion inicial (x y): ";
        std::cin >> startX >> startY;
        std::cout << "Ingrese la posicion final (x y): ";
        std::cin >> endX >> endY;

        if (startX < 0 || startX >= 7 || startY < 0 || startY >= 7 ||
            endX < 0 || endX >= 7 || endY < 0 || endY >= 7) {
            std::cerr << "Las coordenadas estan fuera del rango valido." << std::endl;
            continue;
        }
        std::cout << "Elija el metodo de busqueda:\n";
        std::cout << "1. Busqueda recursiva\n";
        std::cout << "2. Busqueda iterativa\n";
        std::cout << "0. Salir\n";
        std::cin >> choice;

        switch (choice) {
        case '1':
            if (explore(map, booleanMap, startX, startY, endX, endY)) {
                std::cout << "Existe un camino valido desde (" << startX << "," << startY << ") hasta (" << endX << "," << endY << ")." << std::endl;
                printPath();
            }
            else {
                std::cout << "No existe un camino valido." << std::endl;
            }
            break;
        case '2':
            if (checkMap(map, booleanMap, startX, startY, endX, endY)) {
                std::cout << "Existe un camino valido desde (" << startX << "," << startY << ") hasta (" << endX << "," << endY << ")." << std::endl;
                printPath();
            }
            else {
                std::cout << "No existe un camino valido." << std::endl;
            }
            break;
        case '0':
            std::cout << "Saliendo del programa." << std::endl;
            continue;
        default:
            std::cerr << "Opcion no valida." << std::endl;
        }

    } while (choice != '0');
}