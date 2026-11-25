# Tetris

A Tetris clone built in **C++** using the **SFML** graphics library — my Programming Fundamentals course project (Fall 2022, BS Computer Science).

## Features

- All seven classic tetromino pieces with rotation
- Line clearing with scoring: 10 / 30 / 60 / 100 points for 1–4 lines cleared at once
- Multiple difficulty levels
- Pause menu, game over screen, and high-score tracking (top 4 scores)
- Sprite-based rendering in a 320×480 window with custom tile art and fonts

## Project Structure

| File | Description |
|------|-------------|
| `i220989_project.cpp` | Main driver — game loop, window setup, texture loading |
| `functionality.h` | Core gameplay logic (rotation, line clearing, scoring, high scores) |
| `pieces.h` | Tetromino shape definitions as coordinate arrays |
| `utils.h` | Global game constants and board state |
| `img/` | Sprites, menu screens, and fonts |

## Building & Running

Requires a C++ compiler and [SFML](https://www.sfml-dev.org/) (2.x).

```bash
g++ i220989_project.cpp -o tetris -lsfml-graphics -lsfml-window -lsfml-system
./tetris
```

Make sure the `img/` directory is present in the working directory when running, as textures are loaded at startup.

---

**Author:** Mattee ul haq Ghauri (22i-0989)
