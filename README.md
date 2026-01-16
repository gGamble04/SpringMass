# SpringMass

A real-time 1D spring–mass–damper simulation built with **raylib** and **raygui**.

This project started as a hands-on follow-up to finishing differential equations: a simple spring–mass–damper model you can interact with and tune in real time. It also served as practice for structuring a larger C project with clean separation of concerns (physics, rendering, UI, and simulation layers).

## Features

- **1D spring–mass–damper physics** with semi-implicit Euler integration
- **Real-time parameter tuning** via interactive sliders (spring constant *k*, mass *m*, damping *c*, restitution *e*)
- **Damping classification** display (underdamped/critically damped/overdamped via $c_{crit}=2\sqrt{km}$)
- **Interactive mass dragging** to set initial conditions
- **Displacement vs. time graph** for visual analysis
- **Customizable themes** with color picker and preset options
- **Pause/settings menu** with ESC key
- **Boundary collisions** with configurable restitution

![Example of Spring-Mass System](./readme_images/SpringMass2.gif)

## Build & Run

### Prerequisites

- **C compiler** (tested with `gcc` and `clang`)
- **raylib** installed and linkable (Makefile links with `-lraylib`)
- **raygui.h** available on the include path
  - This repo's Makefile assumes `raygui.h` is at `../raylib/examples/core`

### Commands

```bash
make              # Build the project
./springmass      # Run the simulation
make strict       # Build with strict warnings
make debug        # Build with debug symbols
make clean        # Clean build artifacts
```

## Controls

- **Left Click + Drag** — Grab and reposition the mass
- **Sliders** — Adjust spring constant (k), mass (m), damping (c), and restitution (e)
- **ESC** — Pause simulation and open menu
- **Settings** — Change theme colors
- **Close Window** — Exit simulation

## Project Layout
```text
.
├── LICENSE
├── Makefile
├── README.md
├── .clang-format          # Code formatting configuration (Microsoft style)
└── src
    ├── core/              # Physics and shared constants (no raylib dependency)
    │   ├── consts.h       # Project-wide constants and types
    │   ├── physics.c      # Spring-mass physics implementation
    │   └── physics.h
    ├── renderer/          # Drawing and visualization (raylib)
    │   ├── renderer.c     # Main rendering functions
    │   ├── renderer.h
    │   ├── graph.c        # Displacement vs. time graph
    │   └── graph.h
    ├── UI/                # User interface controls (raygui)
    │   ├── ui.c           # Sliders, dialogs, theme system
    │   └── ui.h
    └── sim/               # Simulation orchestration
        ├── main.c         # Entry point and main loop
        ├── sim.c          # Simulation state management
        └── sim.h
```

### Architecture

- **Core layer** — Pure physics logic with no rendering dependencies
- **Renderer layer** — Visualization using raylib (spring, mass, floor, graph)
- **UI layer** — Interactive controls and menus using raygui
- **Sim layer** — Orchestrates physics, rendering, and input handling

## License

See [LICENSE](LICENSE).
