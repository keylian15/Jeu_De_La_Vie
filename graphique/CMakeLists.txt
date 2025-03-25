cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 14)

# Activer l'automatisation de moc
set(CMAKE_AUTOMOC ON)

# Trouver Qt6 (Core, Gui, Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Ajouter le fichier source main.cpp
add_executable(main main.cpp MainWindow.cpp Grille.cpp)

# Lier les bibliothèques Qt6
target_link_libraries(main Qt6::Core Qt6::Gui Qt6::Widgets)
