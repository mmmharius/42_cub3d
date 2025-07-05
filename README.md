# CUB3D ![CUB3D](https://img.shields.io/badge/Game-CUB3D-blue) ![42](https://img.shields.io/badge/42-Project-brightgreen)
Real-time 3D visualization using raycasting, textures, and keyboard input – 42 project

## 📝 Description

CUB3D est une implémentation du raycasting inspirée du célèbre jeu Wolfenstein 3D. Ce projet fait partie du cursus de l'école 42 et se concentre sur les techniques de rendu 3D en temps réel avec la bibliothèque MiniLibX.

## 🚀 Fonctionnalités

- Rendu 3D en temps réel utilisant la technique du raycasting
- Déplacement et rotation du joueur
- Textures directionnelles pour chaque mur
- Couleurs personnalisables pour le sol et le plafond
- Parsing de cartes au format `.cub`
- Détection de collision

## 🛠️ Installation

### Prérequis
- Compilateur CC
- Make
- Bibliothèque MiniLibX

### Compiler
```bash
# Pour Linux
make

# Pour macOS
make mac
```

## 🔍 Utilisation

### Lancer le jeu
```bash
./CUB3D maps/good/map_good.cub
```

### Contrôles
- **W, A, S, D** : Déplacement
- **Flèches gauche/droite** : Rotation
- **ESC** : Quitter

### Format de carte
```
NO wall.xpm
SO wall.xpm
WE wall.xpm
EA wall.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

## ⚙️ Architecture

- **Parsing** : Analyse des fichiers de carte
- **Raycasting** : Calcul des rayons et rendu 3D
- **Contrôles** : Gestion des mouvements du joueur
- **Rendu** : Affichage et gestion des textures

## 👥 Auteurs
- BERENGER Ambroise
- PAPIN Marius

---

*Projet réalisé dans le cadre du cursus de l'école 42*
