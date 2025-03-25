# 🧬 Jeu de la Vie - Conway's Game of Life

Ce projet implémente le célèbre **Jeu de la Vie** de John Conway en **C++**, avec deux modes :

- **Graphique** 🎨 (via la bibliothèque graphique utilisée)
- **Terminal** 💻 (interface en mode console)

## 📂 Contenu du dépôt

- **`/graphique`** : Version avec affichage graphique.
- **`/terminal`** : Version jouable directement dans le terminal.

## 🚀 Installation et Exécution

### 🔧 Prérequis

Avant d’installer ce projet, assure-toi d’avoir :

- Un **compilateur C++** (GCC, Clang, MSVC...)
- **CMake** si nécessaire
- Les bibliothèques requises pour la version graphique (**préciser ici**)

### ⚙️ Compilation

#### 🔹 Mode Terminal

```bash
cd terminal
cmake -G "MinGW Makefiles" .
cmake --build .
.\Main.exe
```

#### 🔹 Mode Graphique

```bash
cd graphique
cmake -G "MinGW Makefiles" .
cmake --build .
.\Main.exe
```
