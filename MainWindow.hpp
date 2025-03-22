#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include "Grille.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    // Widgets de l'interface
    QSpinBox *boxX;
    QSpinBox *boxY;
    QCheckBox *checkTorus;
    QComboBox *comboRemplissage;
    QSpinBox *boxIteration;
    QGridLayout *layoutGrille;
    QLabel *labelIteration;
    QLabel *labelVie;
    QLabel *labelPourcentage;
    QSlider *sliderVitesse;

    // Variables
    int row = 10;
    int col = 10;
    bool isTorus = 1;
    int iterations = 1;
    int remplissage = 0;
    bool nextAuto = 0;
    int nbIterations = 0;
    double temps = 1000;

    Grille grille = Grille(row, col);

public:
    MainWindow();
    void dessinerGrille();
    void updateAffichage();

public slots:
    // void updateIterationValue();
    void updateGrille();
    void updateNextGen();
    int calculeVie();
    void updateNextGenAuto();
    void updateNextGenStop();
    void centerWindow();
    void handleCellClick();
    void updateTime();
};

#endif
