# Medieval Village

This project is an **interactive real-time simulation** of a **Medieval Village**, developed as part of a **Computer Graphics course**. It features realistic rendering with **shadow mapping**, interactive camera controls, and dynamic scene components.

<div align="center">
  <img src="assets/preview.png" alt="Medieval Village Preview" width="600"/>
</div>

---
Authors:
- **Matteo Balice**
- **Antonio Giuseppe Doronzo**

---

## Build Instructions

This project uses CMake for cross-platform compilation.

### Build Steps

Open a terminal in the project root and run the following:

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
````

This will generate the executables needed to run the simulation.

---

## Run Instructions

### Step 1 – Generate Shadow Maps

You must first compute the shadow maps for the scene:

```bash
./compute_shadow
```

In the window that opens, **click "Play"** to generate the shadow maps. Close the window when the process is done.

---

### Step 2 – Launch Simulation

Once the shadows are computed, you can run the main simulation:

```bash
./exe
```

Enjoy exploring the medieval village with realistic lighting and shadows!

---

## Features

* **Shadow mapping**
* Collision detection with the environment
* Interactive **camera navigation**
* PBR materials
* Ambient lighting and directional shadows
* Dynamic lighting effects (torch lights)
* Boat navigation on the river

---

Feel free to explore the village, inspect lighting effects, and customize the scene!