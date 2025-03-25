#include <iostream>
#include <vector>
#include "Grille.hpp"
#include <cstdlib>
#include <ctime>
#include <sstream>

Grille::Grille(int rows, int cols, bool isTorus)
{
    // Initialisation des variables :
    this->rows = rows;
    this->cols = cols;
    this->isTorus = isTorus;

    // ====== Création Des Grilles ======
    grid.clear();
    nextGrid.clear();
    voisins.clear();

    // Initialisez la grille avec des lignes et colonnes
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
    // ====== Fin Création Des Grilles ======
}

void Grille::initialiser()
{
    // Initialisation des variables :
    bool condition = true;

    int choix;
    std::cout << "Choisir le mode d'initialisation :\n(0 : Vide | 1 : Plein | 2 : Damier | 3 : Aleatoire | 4 : Liste" << std::endl;
    std::cin >> choix;
    while (condition)
    {

        switch (choix)
        {
        case 0:
            initialiserVide();
            condition = false;
            break;
        case 1:
            initialiserPlein();
            condition = false;
            break;
        case 2:
            initialiserDamier();
            condition = false;
            break;
        case 3:
            initialiserAleatoire();
            condition = false;
            break;
        case 4:
            initialiserListe();
            condition = false;
            break;
        default:
            std::cout << "Choix " << choix << " invalide, veuillez reessayer." << std::endl;
            std::cout << "Choisir le mode d'initialisation :\n(0 : Vide | 1 : Plein | 2 : Damier | 3 : Aleatoire | 4 : Liste" << std::endl;
            std::cin >> choix;
        }
    }

    // L'affichage :
    std::cout << "La taille de la grille est " << this->rows << " x " << this->cols << " soit " << this->rows * this->cols << " cases." << std::endl;
    std::cout << "Le mode Tore est " << this->isTorus << std::endl;
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

void Grille::initialiserListe()
{
    // exemple de liste a mettre : {{0, 1, 1, 1, 0}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 1, 1, 0}};

    // Initialisation des variables : 
    std::string input;
    std::cout << "Saissisez la liste sous forme { { .. , .. }, {.. , .. } } avec " << this->rows << " lignes et " << this->cols << " colones " << std::endl;

    std::cin.ignore();             // Ignore le caractère de nouvelle ligne
    std::getline(std::cin, input); // Pour lire toute la ligne.

    int lignes = 0;
    int colones = 0;

    for (char element : input)
    {
        if (element == '0' || element == '1')
        {
            if (lignes < this->rows && colones < this->cols)
            {
                this->grid[lignes][colones] = element - '0';
                colones++;
            }
        }
        if (element == '}')
        {
            lignes++;
            colones = 0;
            if (lignes >= this->rows)
                break;
        }
    }
}

void Grille::afficher()
{
    // Affiche une bordure supérieure
    std::cout << " ";
    for (int j = 0; j < this->cols; j++)
    {
        std::cout << "----";
    }
    std::cout << "-\n";

    // Affiche les valeurs
    for (int i = 0; i < this->rows; i++)
    {

        for (int j = 0; j < this->cols; j++)
        {
            std::cout << " | " << this->grid[i][j];
        }
        std::cout << " |\n";

        // Ligne de séparation entre les lignes
        std::cout << " ";
        for (int j = 0; j < this->cols; j++)
        {
            std::cout << "----";
        }
        std::cout << "-\n";
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

void Grille::donnerStat()
{
    // Initialisation de la variable de choix :
    std::string choix;
    std::cout << "Voulez vous voir les statistiques de la partie ? (oui | non) ";
    std::cin >> choix;

    if (choix == "oui")
    {
        // Initialisation des variables :
        int nbVie = 0;
        float pourcentage = 0;

        std::cout << "\t\t====== STATISTIQUES ======" << std::endl;

        // Balayage de la grille :
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                if (grid[i][j] == 1)
                {
                    nbVie++;
                }
            }
        }

        pourcentage = nbVie / float(this->rows * this->cols) * 100.0;

        std::cout << "Nombre de cellule en vie : " << nbVie << std::endl;
        std::cout << "Cela donne un pourcentage en vie de : " << pourcentage << " %." << std::endl;
    }

    std::cout << "Fin de partie." << std::endl;
}

void Grille::jeu()
{
    // Initialisatoin variables !
    std::string choix = ".";
    std::string tIteration = "-1";
    int nbIterations = -1;

    // Itérations :
    while (nbIterations < 1
    )
    {
        std::cout << "Choissisez le nombre d'iterations du jeu : ";
        std::cin >> nbIterations;
    }

    while (choix != "oui" && choix != "non")
    {
        std::cout << "Voulez vous afficher la grille durant l'execution ? (oui | non) ";
        std::cin >> choix;
    }

    if (choix == "oui" && tIteration == "-1")
    {
        while (tIteration < "1")
        {
            std::cout << "Tous les combiens d'iterations voulez vous affichez la grille ? ";
            std::cin >> tIteration;
        }
    }

    initialiser();
    afficher();

    for (int i = 0; i < nbIterations; i++)
    {
        if (choix == "oui")
        {
            if (i % std::stoi(tIteration) == 0)
            {
                std::cout << "\t\tIterations = " << i << std::endl;
                afficher();
            }
        }

        nextGen();
    }
    std::cout << "\t\tIterations = " << nbIterations << std::endl;
    afficher();

    donnerStat();
}

// Fin Fichier.