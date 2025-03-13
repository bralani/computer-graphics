void DrawFigure(A00 *A) {
	// House base (square)
	A->Line(-0.5, 0.5, 0.5, 0.5, 0.6, 0.3, 0.1); // Top
	A->Line(-0.5, 0.5, -0.5, -0.2, 0.6, 0.3, 0.1); // Left wall
	A->Line(0.5, 0.5, 0.5, -0.2, 0.6, 0.3, 0.1); // Right wall
	A->Line(-0.5, -0.2, 0.5, -0.2, 0.6, 0.3, 0.1); // Bottom

	// Roof (triangle)
	A->Triangle(-0.6, -0.2, 0.6, -0.2, 0, -0.7, 0.8, 0, 0); // Red roof at the bottom

	// Door
	A->Line(-0.1, 0.5, -0.1, 0.1, 0.3, 0.1, 0); // Left side
	A->Line(0.1, 0.5, 0.1, 0.1, 0.3, 0.1, 0); // Right side
	A->Line(-0.1, 0.1, 0.1, 0.1, 0.3, 0.1, 0); // Bottom

	// Door knob (small point)
	A->Plot(0.05, 0.3, 1, 1, 0); // Yellow knob

	// Windows (left)
	A->Line(-0.4, 0.1, -0.2, 0.1, 0, 0, 1); // Top
	A->Line(-0.4, 0.3, -0.2, 0.3, 0, 0, 1); // Bottom
	A->Line(-0.4, 0.1, -0.4, 0.3, 0, 0, 1); // Left
	A->Line(-0.2, 0.1, -0.2, 0.3, 0, 0, 1); // Right
	A->Line(-0.3, 0.1, -0.3, 0.3, 0, 0, 1); // Middle Vertical
	A->Line(-0.4, 0.2, -0.2, 0.2, 0, 0, 1); // Middle Horizontal

	// Windows (right)
	A->Line(0.2, 0.1, 0.4, 0.1, 0, 0, 1); // Top
	A->Line(0.2, 0.3, 0.4, 0.3, 0, 0, 1); // Bottom
	A->Line(0.2, 0.1, 0.2, 0.3, 0, 0, 1); // Left
	A->Line(0.4, 0.1, 0.4, 0.3, 0, 0, 1); // Right
	A->Line(0.3, 0.1, 0.3, 0.3, 0, 0, 1); // Middle Vertical
	A->Line(0.2, 0.2, 0.4, 0.2, 0, 0, 1); // Middle Horizontal

	// STREET - Large Gray Rectangle
	A->Triangle(-1, 0.7, 1, 0.7, -1, 1, 0.3, 0.3, 0.3); // Left Triangle for the road
	A->Triangle(1, 0.7, 1, 1, -1, 1, 0.3, 0.3, 0.3); // Right Triangle for the road

	// Dashed white lines for the road
	for (float x = -0.9; x < 1.0; x += 0.3) {
		A->Line(x, 0.85, x + 0.15, 0.85, 1, 1, 1); // Short white dashes
	}
}
