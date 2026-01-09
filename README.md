# SpringMass

A small spring–mass simulation built with **raylib** and **raygui**.

This project started as a hands-on follow-up to finishing differential equations: a simple 1D spring–mass–damper model you can poke and tune in real time. It also doubled as practice for structuring a slightly-larger C project (separating physics, rendering, UI, and the app/sim layer).

## Features

- 1D spring–mass–damper simulation (semi-implicit Euler stepping)
- Interactive parameter sliders (spring constant *k*, mass *m*, damping *c*, restitution *e*)
- Damping classification label (under/critical/overdamped via $c_{crit}=2\sqrt{km}$)
- Click-and-drag the mass to set initial conditions

![Example of Spring-Mass System](./readme_images/SpringMass.gif)

## Build & Run

### Prerequisites

- A C compiler (tested with `gcc`)
- `raylib` installed and linkable (the Makefile links with `-lraylib`)
- `raygui.h` available on the include path
  - This repo’s Makefile assumes `raygui.h` lives at `../raylib/examples/core`.

### Commands

- Build: `make`
- Run: `./springmass`
- Strict warnings: `make strict`
- Debug build: `make debug`

## Controls

- Drag the red mass with the mouse (left click) to reposition it.
- Use the on-screen sliders to tune parameters.
- Close the window to quit.

## Project Layout
```text
.
├── LICENSE
├── Makefile
├── README.md
└── src
    ├── UI              
    │   ├── ui.c
    │   └── ui.h
    ├── core 
    │   ├── consts.h
    │   ├── physics.c
    │   └── physics.h
    ├── renderer        
    │   ├── renderer.c
    │   └── renderer.h
    └── sim             
        ├── main.c
        ├── sim.c
        └── sim.h
```
- `src/core/` — physics and shared constants (no raylib dependency)
- `src/renderer/` — drawing code (raylib)
- `src/UI/` — UI controls (raygui)
- `src/sim/` — app/sim orchestration (input handling, stepping, draw loop glue)

## Next Step

The intent is for this to be a precursor to a **suspended** spring–mass system (e.g., gravity, vertical motion, and/or multiple degrees of freedom). The current codebase is set up to make that extension easier without turning into one giant file.

## License

See [LICENSE](LICENSE).
