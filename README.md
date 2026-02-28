# 🍄 Super Mario Bros. - Core Mechanics Engine

A custom-built 2D platformer physics and collision engine replicating the iconic mechanics of the original Super Mario Bros. Developed entirely from scratch using **C++** and **SFML** to understand the low-level architecture of 2D game engines.

Instead of using modern drag-and-drop engines, this project focuses on raw mathematics, entity management, and frame-by-frame physics resolution.

## ✨ Engine Architecture & Features
* **Custom ECS (Entity-Component-System):** Implemented isolated components like `cTransform`, `cBoundingBox`,`cAnimation`, `cGravity`, and `cInput` for clean and scalable entity management.
* **AABB Collision Detection:** Grid-based Axis-Aligned Bounding Box (AABB) mathematics to perfectly handle player-to-wall and player-to-floor interactions without clipping or glitches.
* **Physics & Gravity:** Custom velocity vectors and gravity resolution to replicate the heavy, satisfying jump arcs of the original game.
* **State Management:** Handled dynamic state transitions (e.g., Small Mario to Super Mario logic).

## 🛠️ Tech Stack
* **Language:** C++ (Modern C++ practices)
* **Graphics & Windowing:** SFML (Simple and Fast Multimedia Library)
* **Design Pattern:** Data-driven ECS Architecture

## 🎮 How to Run (For Developers)
1. Clone this repository to your local machine.
2. Ensure you have **SFML** properly linked in your preferred C++ IDE (Visual Studio, CLion, or VS Code).
3. Include the source (`.cpp`) and header (`.h`) files into your project.
4. Build and compile the project in your environment to test the physics engine!

## 📸 Gameplay Debug View
<img width="1913" height="1080" alt="image" src="https://github.com/user-attachments/assets/64b60411-9b11-4165-b56e-4be4144c74d8" />
A screenshot of the debug features including collision boxes and grid view...

