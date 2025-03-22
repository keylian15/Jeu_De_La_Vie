#include "Grille.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Grille::Grille(int rows, int cols)
{
    // Initialisation des variables :
    this->rows = rows;
    this->cols = cols;
    this->isTorus = 0;

    // ====== Création Des Grilles ======
    grid.clear();
    nextGrid.clear();
    voisins.clear();

    // Initialisez la grille avec des lignes et colonnes
    initialiser();

    // ====== Fin Création Des Grilles ======
}

void Grille::initialiser()
{

    for (int i = 0; i < rows; ++i)
    {
        std::vector<int> row;
        for (int j = 0; j < cols; ++j)
        {
            row.push_back(0); // Ajoutez une cellule morte par défaut
        }
        grid.push_back(row);     // Ajoutez la ligne à la grille.
        nextGrid.push_back(row); // Faire de même pour la grille suivante.
        voisins.push_back(row);  // Farie de même pour les voisins.
    }
}

void Grille::initialiserVide()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            this->grid[i][j] = 0;
        }
    }
}

void Grille::initialiserPlein()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            this->grid[i][j] = 1;
        }
    }
}

void Grille::initialiserDamier()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            // Ligne pair :
            // Colone pair : Cellule morte.
            // Sinon : Cellule vivante.
            // Ligne impair :
            // COlone pair : Cellule vivante.
            // Sinon : Cellule morte.
            this->grid[i][j] = (i % 2 == 0) ? (j % 2) : ((j + 1) % 2);
        }
    }
}

void Grille::initialiserAleatoire()
{
    // Initialisation du générateur de nombres aléatoires avec une graine
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Utiliser l'heure actuelle comme graine

    int nb;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            // Générer un nombre aléatoire qui est soit 0 soit 1
            nb = std::rand() % 2;
            this->grid[i][j] = nb;
        }
    }
}

void Grille::resetVoisins()
{
    // Balayage de la grille :
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            this->voisins[i][j] = 0;
        }
    }
}

void Grille::compterVoisins()
{
    // Reset des voisins :
    resetVoisins();

    // Balayage de la grille :
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            // Si la cellule est vivante
            if (this->grid[i][j] == 1)
            {
                // Parcours les voisins 3x3 pour savoir lesquelles sont vivants :
                for (int di = -1; di <= 1; ++di)
                {
                    for (int dj = -1; dj <= 1; ++dj)
                    {
                        // On ignore la cellule elle meme :
                        if (di == 0 && dj == 0)
                            continue;
                        int ni = i + di;
                        int nj = j + dj;

                        // Gestion du Tore :
                        // printf("torus : %d",isTorus);
                        if (isTorus)
                        {
                            ni = (ni + this->rows) % this->rows;
                            nj = (nj + this->cols) % this->cols;
                        }
                        else
                        {
                            if (ni < 0 || ni >= rows || nj < 0 || nj >= cols)
                                continue; // Ignorer les bords
                        }

                        voisins[ni][nj]++;
                    }
                }
            }
        }
    }
}

void Grille::nextGen()
{
    compterVoisins();

    // Balayage de la grille :
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            // Si la cellule est vivante :
            if (grid[i][j] == 1)
            {
                // Si elle possede 2 ou 3 voisins :
                if (voisins[i][j] == 2 || voisins[i][j] == 3)
                {
                    // Elle reste vivante :
                    nextGrid[i][j] = 1;
                }
                else
                {
                    // Sinon elle meurt :
                    nextGrid[i][j] = 0;
                }
            } // Si la cellule est morte :
            else
            {
                if (voisins[i][j] == 3)
                {
                    // Elle née :
                    nextGrid[i][j] = 1;
                }
                else
                {
                    // Elle reste morte :
                    nextGrid[i][j] = 0;
                }
            }
        }
    }
    grid = nextGrid;
}

std::vector<std::vector<int>> Grille::getState() const
{
    return grid;
}

int Grille::getRowCount()
{
    return this->rows;
}

void Grille::setRowCount(int rows)
{
    this->rows = rows;
}

int Grille::getColCount()
{
    return this->cols;
}

void Grille::setColCount(int cols)
{
    this->cols = cols;
}

int Grille::getCell(int x, int y)
{
    return this->grid[x][y];
}

void Grille::setCell(int x, int y, int type)
{
    if (x >= 0 && x < rows && y >= 0 && y < cols)
    {
        grid[x][y] = type;
    }
}
bool Grille::getTorus()
{
    return this->isTorus;
}

void Grille::setTorus(bool isTorus)
{
    this->isTorus = isTorus;
}

int Grille::getRemplissage()
{
    return this->remplissage;
}

void Grille::setRemplissage(int remplissage)
{
    switch (remplissage)
    {
    case 0:
        initialiserVide();
        break;
    case 1:
        initialiserPlein();
        break;
    case 2:
        initialiserDamier();
        break;
    case 3:
        initialiserAleatoire();
        break;
    }
}

// Fin Fichier.