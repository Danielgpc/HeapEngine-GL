# HeapEngine-GL

A small C++ game engine template with a separate engine/game layout and a simple hello-world example.

## Project Structure

```
HeapEngine-GL/
├── engine/            # Engine code
│   ├── hello_engine.h
│   └── hello_engine.cpp
├── game/              # Game entry point
│   └── main.cpp
├── third_party/       # Third-party or vendored dependencies
│   └── README.md
├── bin/               # Build output
├── lib/               # Static library output
└── Makefile           # Build system
```

## Build System

This project uses `make` with C++.

### Build commands

```bash
make all
make engine
make game
make run
make clean
```

## How it works

- The engine code lives under [engine](engine).
- The game entry point lives under [game](game).
- The engine exposes a class with `init()`, `run()`, and `cleanup()` methods.
- The example prints a simple hello-world message when run.

## Running

```bash
make run
```

The resulting executable will be created in `bin/hello_game`.

