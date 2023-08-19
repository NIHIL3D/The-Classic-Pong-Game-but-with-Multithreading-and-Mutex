# Pong Game with Multithreading and Mutex

<img src="https://github.com/NIHIL3D/The-classic-Pong-game-but-using-mutex-Raylib-/assets/117014237/0fa8c55a-9949-4039-9960-9db9a21dc46a" width=50% height=50%>

## Table of Contents

- [Introduction](#introduction)
- [Project Overview](#project-overview)
- [Implementation](#implementation)
  - [Game Logic](#game-logic)
  - [Multithreading and Mutex](#multithreading-and-mutex)
  - [Graphics with Raylib](#graphics-with-raylib)
- [Usage](#usage)
- [Results and Analysis](#results-and-analysis)
- [Conclusion](#conclusion)

## Introduction

The Pong Game with Multithreading and Mutex project is a classic Pong game implementation enhanced with multithreading to handle game logic and user input concurrently using mutex for synchronization and the Raylib library for graphical rendering. This project showcases how multithreading can improve gameplay responsiveness while maintaining data consistency.

## Project Overview

The project aims to create an interactive Pong game where two players control paddles to hit the ball back and forth. What makes this implementation unique is the use of multithreading to manage game actions concurrently, allowing for smoother and more dynamic gameplay.

## Implementation

### Game Logic

The game logic includes ball movement, collision detection, scoring, and paddle control. Each of these aspects is managed by separate threads to ensure simultaneous execution, creating a more engaging user experience.

### Multithreading and Mutex

To avoid data conflicts arising from concurrent execution, mutex (short for mutual exclusion) is employed. Mutex ensures that only one thread can access a shared resource at a time, preventing conflicts and maintaining data integrity.

### Graphics with Raylib 
Raylib is employed to render the game's graphical elements, including the paddles, ball, and background. This library offers an easy-to-use interface for creating appealing visuals.

## Usage

1. Clone the repository.
2. Compile and build the project using the specified build tools.
3. Run the executable to start the Pong game.

## Results and Analysis

The incorporation of multithreading significantly enhances the gameplay experience. Players notice smoother ball movement, improved responsiveness to paddle controls, and overall better synchronization between game elements.

## Conclusion

The Pong Game with Multithreading and Mutex project successfully demonstrates the benefits of multithreading in game development. By using mutex for synchronization, the project achieves concurrent execution of game logic and ensures data consistency, leading to an enjoyable and immersive gaming experience.
