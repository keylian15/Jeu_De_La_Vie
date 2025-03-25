#include "MainWindow.hpp"
#include "Grille.hpp"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QString>
#include <QGridLayout>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow()
{
    // === Parametre Fenetre ===
    setWindowTitle("Jeu De La Vie");
    centerWindow();
    // === Fin Parametre Fenetre ===

    // === Layout ===
    QHBoxLayout *layoutMain = new QHBoxLayout();
    QVBoxLayout *layoutGrid = new QVBoxLayout();
    QVBoxLayout *layoutConf = new QVBoxLayout();

    setLayout(layoutMain);
    layoutMain->addLayout(layoutGrid);
    layoutMain->addLayout(layoutConf);

    layoutMain->setStretch(0, 1);
    layoutMain->setStretch(1, 0);
    // === Fin Layout ===

    // === Menu Configuration ===
    QLabel *labelTaille = new QLabel("Taille de la grille :");
    labelTaille->setAlignment(Qt::AlignCenter);

    QLabel *labelPosX = new QLabel("X : ");
    QLabel *labelPosY = new QLabel("Y : ");

    // -- Box X :
    boxX = new QSpinBox();
    boxX->setMaximum(100);
    boxX->setMinimum(1);
    boxX->setValue(10);

    // -- Box Y :
    boxY = new QSpinBox();
    boxY->setMaximum(100);
    boxY->setMinimum(1);
    boxY->setValue(10);

    // -- Torus :
    QLabel *labelTorus = new QLabel("Mode Torus :");
    labelTorus->setAlignment(Qt::AlignLeft);
    checkTorus = new QCheckBox();

    // -- Itérations :
    labelIteration = new QLabel("Itérations : ");
    labelIteration->setAlignment(Qt::AlignLeft);

    // -- Vie :
    labelVie = new QLabel("En Vie : ");
    labelVie->setAlignment(Qt::AlignLeft);

    // -- Pourcentage :
    labelPourcentage = new QLabel("Pourcentage : ");
    labelPourcentage->setAlignment(Qt::AlignLeft);

    // -- Remplisage :
    QLabel *labelRemplissage = new QLabel("Remplissage :");
    labelRemplissage->setAlignment(Qt::AlignCenter);
    labelRemplissage->setAlignment(Qt::AlignCenter);
    comboRemplissage = new QComboBox();
    comboRemplissage->addItems(QStringList{"Vide", "Plein", "Damier", "Aléatoire"});

    // -- Layout :
    // ~~ Position
    QHBoxLayout *layoutPosition = new QHBoxLayout();
    layoutPosition->addWidget(labelPosX);
    layoutPosition->addWidget(boxX);
    layoutPosition->addWidget(labelPosY);
    layoutPosition->addWidget(boxY);

    // ~~ Torus
    QHBoxLayout *layoutTorus = new QHBoxLayout();
    layoutTorus->addWidget(labelTorus);
    layoutTorus->addWidget(checkTorus);

    // // ~~ Itérations :
    QHBoxLayout *layoutIterations = new QHBoxLayout();
    layoutIterations->addWidget(labelIteration);

    // ~~ Remplissage :
    QHBoxLayout *layoutRemplissage = new QHBoxLayout();
    layoutRemplissage->addWidget(labelRemplissage, 1);
    layoutRemplissage->addWidget(comboRemplissage, 2);

    // ~~ Ajout :
    layoutConf->addWidget(labelTaille);
    layoutConf->addLayout(layoutPosition);
    layoutConf->addLayout(layoutTorus);
    layoutConf->addWidget(labelIteration);
    layoutConf->addWidget(labelVie);
    layoutConf->addWidget(labelPourcentage);
    layoutConf->addLayout(layoutRemplissage);
    // === Fin Menu Configuration ===

    // === Menu Grille ===
    grille = Grille(row, col);

    QPushButton *buttonIteration = new QPushButton("Next Gen !");
    QPushButton *buttonAuto = new QPushButton("Auto !");
    QPushButton *buttonStop = new QPushButton("Stop !");

    // -- Layout :
    layoutGrille = new QGridLayout();

    // ~~ Auto :
    QHBoxLayout *layoutAuto = new QHBoxLayout();
    layoutAuto->addWidget(buttonAuto);
    layoutAuto->addWidget(buttonStop);

    // ~~ Vitesse :
    sliderVitesse = new QSlider(Qt::Horizontal);
    sliderVitesse->setMinimum(1);
    sliderVitesse->setMaximum(20);
    sliderVitesse->setValue(10);

    // ~~ Ajout :
    layoutGrid->addLayout(layoutGrille);
    layoutGrid->addWidget(buttonIteration);
    layoutGrid->addLayout(layoutAuto);
    layoutGrid->addWidget(sliderVitesse);

    dessinerGrille();
    // === Fin Menu Grille ===

    // === Signeaux ===
    // -- Conf :
    connect(boxX, SIGNAL(valueChanged(int)), this, SLOT(updateGrille()));
    connect(boxY, SIGNAL(valueChanged(int)), this, SLOT(updateGrille()));
    connect(checkTorus, SIGNAL(stateChanged(int)), this, SLOT(updateGrille()));
    connect(comboRemplissage, SIGNAL(currentTextChanged(const QString &)), this, SLOT(updateGrille()));
    // -- Grille :
    connect(buttonIteration, &QPushButton::clicked, this, &MainWindow::updateNextGen);
    connect(buttonAuto, &QPushButton::clicked, this, &MainWindow::updateNextGenAuto);
    connect(buttonStop, &QPushButton::clicked, this, &MainWindow::updateNextGenStop);
    connect(sliderVitesse, &QSlider::valueChanged, this, &MainWindow::updateTime);
    // === Fin Signeaux ===
}

void MainWindow::dessinerGrille()
{
    // Effacer l'ancienne grille
    QLayoutItem *child;
    while ((child = layoutGrille->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }

    const QString vivant = "background-color: black;";
    const QString mort = "background-color: white;";

    int x = 350 / grille.getColCount();
    int y = 350 / grille.getRowCount();

    for (int row = 0; row < grille.getRowCount(); ++row)
    {
        for (int col = 0; col < grille.getColCount(); ++col)
        {
            QPushButton *button = new QPushButton;
            button->setFixedSize(x, y);

            // Appliquer l'état initial
            if (grille.getCell(row, col) == 1)
            {
                button->setStyleSheet(vivant);
            }
            else
            {
                button->setStyleSheet(mort);
            }

            // Stocker les coordonnées comme propriétés
            button->setProperty("row", row);
            button->setProperty("col", col);

            // Connecter le signal du clic au slot
            connect(button, &QPushButton::clicked, this, &MainWindow::handleCellClick);

            layoutGrille->addWidget(button, row, col);
        }
    }
}


void MainWindow::updateGrille()
{
    grille = Grille(boxX->value(), boxY->value());
    grille.setRemplissage(comboRemplissage->currentIndex());
    grille.setTorus(checkTorus->isChecked());
    dessinerGrille();
    nbIterations = 0;
    updateAffichage();
}

void MainWindow::updateNextGen()
{
    grille.nextGen();
    dessinerGrille();
    nbIterations++;
    updateAffichage();
}

int MainWindow::calculeVie()
{
    auto state = grille.getState();
    int nbVie = 0;
    for (int row = 0; row < grille.getRowCount(); ++row)
    {
        for (int col = 0; col < grille.getColCount(); ++col)
        {
            if (state[row][col] == 1)
            {
                nbVie++;
            }
        }
    }
    return nbVie;
}

void MainWindow::updateAffichage()
{
    int n = calculeVie();
    int t = grille.getColCount() * grille.getRowCount();

    labelIteration->setText(QString("Itérations : %1").arg(nbIterations));
    labelVie->setText(QString("En Vie : %1").arg(n));
    labelPourcentage->setText(QString("Pourcentage : %1\%").arg(n * 100 / t));
}

void MainWindow::updateNextGenAuto()
{
    nextAuto = true;
    QTimer::singleShot(temps, this, [&]()
                       {
        if (nextAuto) {
            updateNextGen();
            updateNextGenAuto();
        } });
}

void MainWindow::updateNextGenStop()
{
    nextAuto = false;
}

void MainWindow::updateTime()
{
    this->temps = sliderVitesse->value()*100;
}

void MainWindow::centerWindow()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    int windowWidth = width();
    int windowHeight = height();

    int x = (screenGeometry.width() - windowWidth) / 2;
    int y = (screenGeometry.height() - windowHeight) / 2;

    setGeometry(x, y, windowWidth, windowHeight);
    setFixedSize(windowWidth, windowHeight);
}

void MainWindow::handleCellClick()
{
    // Récupérer le bouton qui a déclenché l'événement
    QObject *senderObj = sender();
    QPushButton *button = qobject_cast<QPushButton *>(senderObj);

    if (!button) return;

    // Récupérer les coordonnées stockées dans les propriétés du bouton
    int row = button->property("row").toInt();
    int col = button->property("col").toInt();

    // Inverser l'état de la cellule dans la grille
    int currentState = grille.getCell(row, col);
    grille.setCell(row, col, 1 - currentState); // 1 devient 0 et 0 devient 1

    // Redessiner uniquement cette cellule
    const QString vivant = "background-color: black;";
    const QString mort = "background-color: white;";
    button->setStyleSheet(currentState == 0 ? vivant : mort);
}

// Fin du fichier.
