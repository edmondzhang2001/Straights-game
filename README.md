---

# Straights Game

Straights is a card game recreated in C++ for 4 players, where the goal is to achieve the lowest score by the time a player reaches 80 points. Players take turns to either discard or play cards to one of four suit-specific piles, accumulating points in the process. For more information, refer to demo.pdf and design.pdf

## Getting Started

To play the game, compile the source code using the provided Makefile and run the executable with an optional seed for card shuffling.

```bash
make
./straights [seed]
```

### Prerequisites

- A C++14 compatible compiler
- Standard C++ libraries

## Game Rules

- The game consists of rounds where each player either discards or plays a card to a pile.
- Points are accumulated for cards in the discard pile, and the aim is to have the lowest score.
- The game ends when a player reaches or exceeds 80 points, and the player with the lowest score wins.

## Features

- **Card, Deck, and Pile Management**: Classes to manage cards, decks, and piles reflect the game's physical elements.
- **Player Interaction**: Support for human and computer players, with human players entering commands to play or discard cards.
- **Game Flow Control**: The game class controls the round progression, player turns, and score calculation.
- **Robust Error Handling**: The system remains responsive to incorrect inputs, guiding the player to make legal moves.

## Design Principles

The project follows the Model-View-Controller (MVC) architectural pattern with high emphasis on abstraction, encapsulation, and resilience to change. This approach allows for a modular design where components like game rules and player types can be easily modified or extended.

## Testing

Various test cases are provided to ensure the game's functionality, including human player interaction, CPU behavior, and end-game scenarios.

## Authors

- Edmond Zhang - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- Inspiration from the traditional Straights card game
- Utilization of C++ features and design patterns

---
