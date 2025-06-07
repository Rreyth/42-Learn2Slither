# Learn2Slither

**Learn2Slither** is a project from the 42 school that implements a Snake AI using Q-Learning.

## Overview

* The game features a snake, two green apples (bonus) that increase its length, and one red apple (malus) that decreases its length.
* The AI agent learns optimal movement policies using a discrete state representation and a Q-table stored in C++ (`std::unordered_map<State, std::vector<double>, StateHash>`).
* Key techniques: epsilon-greedy exploration, dynamic epsilon decay based on user-defined sessions, reward shaping, and Q-table persistence (save/load).

## Features

* **SFML-based rendering**.
* **State encoding** includes:

  * Direction of nearest green apple (up/down/left/right/none).
  * Distance to dangers (walls or snake body) and red apple within a 4-cell range.
* **Q-Learning implementation** with customizable hyperparameters:

  * Learning rate (alpha)
  * Discount factor (gamma)
  * Exploration rate (epsilon) with automated decay
* **Rewards**:

  * +50 for green apple
  * -30 for red apple
  * -100 for death
  * -1 per move (to discourage loops)
  * +5 for moving closer to a green apple
* **Persistence**: save/load Q-table.

## Build

```bash
# Clone the repository
git clone https://github.com/Rreyth/42-Learn2Slither.git
cd 42-Learn2Slither

# Build
make
```

## Usage

```bash
./snake [-h/--help] [-i/--info] [-v/--visual] [-s/--save {filename}] [-l/--load {filename}]
        [--dontlearn] [--stepmode] [-n/--size {10 <= int <= 25}] [--sessions {int > 0}]]

options:
  -h, --help		Show this help message
  -i, --info		Show AI vision and infos for each step
  -v, --visual		Turn on visual output
  -s, --save {file}	Save Q table to file
  -l, --load {file}	Load Q table from file
  --dontlearn		Run without learning
  --stepmode		Run in step-by-step mode
  -n, --size {int}	Size of the game grid between 10 and 25
  --sessions		Number of sessions Agent will run
```
---
