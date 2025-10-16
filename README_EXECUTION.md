Cub3D Execution – ELI7 Guide (Explain Like I’m in 7th Grade)

How to use this guide
- Kid‑friendly words, short steps, simple math signs, ASCII drawings.
- “Where in code?” pointers tell you the exact file:line to peek at.
- With this, you can present the project even if you wrote 0% of it.

Symbols cheat sheet
- π (pi) ≈ 3.14 → half a circle is π, full circle is 2π.
- cos(θ) → “left/right part” of a direction arrow.
- sin(θ) → “up/down part” of a direction arrow.
- tan(θ) = sin(θ)/cos(θ) → “rise over run” (slope).
- √(x) → square root → “length of the slanted side in a right triangle.”
- mod → remainder after dividing (e.g., 70 mod 64 = 6).

1) The Big Picture
- The world is squared paper (a grid). Each square is 64×64 pixels.
- You are a dot with a position (x, y) and a look direction (angle).
- To draw 3D, we throw many invisible straight lines (rays) in front of you, one per screen column. For each ray, we draw a skinny vertical slice of the wall it hits first.
- Every frame: read keys/mouse → update you → cast all rays → draw background + walls + minimap/HUD → show image.
- Where in code: main wiring src/main.c:17; frame flow src/execution/game_loop.c:15,21,33.

2) The Grid and Angles
- One map tile = TILE_SIZE=64 pixels (include/execution.h:46).
- Screen size and number of rays: include/execution.h:44–55 (one ray per screen column).
- Your facing arrow uses cos(θ) (x) and sin(θ) (y). Angles are radians in [0, 2π). We keep angles in range with normalize_angle (src/execution/ray_math.c:12–20).

3) Keys and Mouse: How You Move
- Keys set three direction flags: walk (W/S), strafe (A/D), turn (←/→). We recompute the directions on each key event (src/execution/input.c:15–48).
- Turning: add a tiny angle each frame (degrees→radians) and wrap to [0, 2π) (src/execution/player.c:71–76).
- Walking forward/back: x += cos(angle)*step; y += sin(angle)*step (src/execution/player.c:43–45).
- Strafing left/right: x += cos(angle+π/2)*step; y += sin(angle+π/2)*step (src/execution/player.c:48–50).
- SHIFT speeds up; CTRL slows down (src/execution/player.c:25–30).
- Mouse look: angle += dx * sensitivity; normalize angle (src/execution/mouse.c:63–67).
- Key flags set/clear: src/execution/keys.c:29–69. Hooks: src/execution/hooks.c:15–21.

4) Not Walking Through Walls (Collision)
- Check X and Y moves separately for “sliding” along walls: if new X is free, keep it; if new Y is free, keep it (src/execution/player.c:63–66).
- is_wall/has_wall_at converts (x,y) to tile (x/64, y/64) and checks the map; out‑of‑bounds counts as wall (src/execution/utils.c:15–31).

5) What Is a Ray?
- A ray is a straight line from you at some angle.
- For each screen column, angle = player_angle − FOV/2 + tiny_step*i (src/execution/raycasting.c:44–51).
- We test two ways: where the ray crosses horizontal grid lines and where it crosses vertical grid lines. We keep the closer hit (src/execution/raycasting.c:15–36).

6) How a Ray Meets Horizontal Lines (Step‑by‑step)
- Horizontal lines are y = 0, 64, 128, …
- First crossing: y0 = floor(py/64)*64; if looking down, add 64 (src/execution/raycast_h.c:23–27).
- Find x there: tan(θ) = (y−py)/(x−px) ⇒ x = px + (y0−py)/tan(θ) (src/execution/raycast_h.c:28–29).
- Step to next line: y += ±64; x += 64/tan(θ), signs fixed by facing (src/execution/raycast_h.c:32–41).
- Gridline gotcha: when looking up, sample y−1 so we check the correct cell (src/execution/raycast_h.c:51–55).
-   ASCII: sampling just above the gridline when looking up
    
      tiles above
      ####### <- checked when using y0-1
      ------- y0 (horizontal gridline)
      v ray hits gridline here (don’t sample at y0)
      tiles below
      .......

- Parallel gotcha: if sin(θ)≈0, skip this path (src/execution/raycast_h.c:78–83).
-   ASCII: nearly horizontal ray (sin θ ≈ 0 ⇒ tan θ ≈ 0)
    
      →→→→→  ray almost flat
      =====  horizontal lines every 64 px
      x step uses 64/tan θ → huge/unstable, so skip H path

7) How a Ray Meets Vertical Lines (Step‑by‑step)
- Vertical lines are x = 0, 64, 128, …
- First crossing: x0 = floor(px/64)*64; if looking right, add 64 (src/execution/raycast_v.c:23–27).
- Find y there: y = py + (x0−px)*tan(θ) (src/execution/raycast_v.c:28–29).
- Step to next line: x += ±64; y += 64*tan(θ), signs fixed by facing (src/execution/raycast_v.c:32–41).
- Gridline gotcha: when looking left, sample x−1 (src/execution/raycast_v.c:49–55).
-   ASCII: sampling just left of the gridline when looking left
    
      ^ check at x0-1 (left side)
      |
      | x0 (vertical gridline)
      |
      v ray hits gridline here (don’t sample at x0)

- Parallel gotcha: if cos(θ)≈0, skip this path (src/execution/raycast_v.c:78–83).
-   ASCII: nearly vertical ray (cos θ ≈ 0 ⇒ tan θ very large)
    
      ↑
      ↑  ray almost straight up/down
      ↑
      |  vertical lines every 64 px
      y step uses 64*tan θ → huge/unstable, so skip V path

8) Distance, Fish‑Eye, Projection (Why walls look tall or short)
- Raw distance to hit: √((hit_x − px)² + (hit_y − py)²) (src/execution/ray_math.c:22–29).
- Fish‑eye fix: use only the “forward part” with cos(ray_angle − view_angle) (src/execution/render_walls.c:20–24).
- Projection distance (movie screen distance): D = (screen_width/2) / tan(FOV/2) (src/execution/render_walls.c:23).
- Column height: (TILE_SIZE / corrected_distance) * D (src/execution/render_walls.c:15–25), clamped to screen (src/execution/render_walls.c:27–35).

9) Textures = Stickers on Walls (Which part to draw)
- Pick texture (N/S/E/W) by which face the ray hit and which way you were facing (src/execution/texture.c:28–46).
- Texture X: how far along the tile face? offset = (wall_hit_axis mod 64); then scale to texture width (src/execution/texture.c:49–61).
- Texture Y while drawing: step = texture.height / line_height; add step each pixel down (src/execution/render_walls.c:44–59).

10) How One Frame Is Drawn
- Paint top half with sky (ceiling color) and bottom half with floor (src/execution/render_background.c:15–59).
- For each column: compute height; find top/bottom; pick texture; draw the skinny slice (src/execution/render_walls.c:62–75).
- Show the image (src/execution/game_loop.c:29); then draw HUD text (src/execution/hud.c:34–53).

11) Minimap & Crosshair & HUD
- Minimap: tiny tiles (gray walls, dark empty), a red player dot, and a short red direction line (src/execution/minimap.c:41–67, 94–119).
- Crosshair: a small + at screen center (src/execution/hud.c:15–32).
- HUD: text for position, angle (degrees), frame count (src/execution/hud.c:34–53).

12) Fullscreen (Linux/X11)
- We ask the window manager to toggle fullscreen with a special message called _NET_WM_STATE_FULLSCREEN (src/execution/fullscreen.c:23–43, 61–69).

13) Where Map/Textures Come From
- The program reads a .cub file and builds a config (textures, colors, map, player start). Execution uses that ready setup (src/main.c:22–27; parsing in src/parsing/*).

14) Why Files Look Like This (42 Norm)
- Many small, focused functions; helpers marked static; clear headers; short bodies. No global game state: everything lives in a t_game struct.

15) Mouse: Why It Can Feel “Wiggly”
- MLX doesn’t provide raw mouse or pointer lock. Re‑centering can cause extra motion events. We reduce it with edge‑only recenter and small sensitivity. Arrow‑key turning is always steady (src/execution/mouse.c:15–24, 48–69).

16) Quick Function Finder (Where in code?)
- Frame: update → render → blit (src/execution/game_loop.c:15,21,33–43).
- Input: recompute directions (src/execution/input.c:15–48); set/clear (src/execution/keys.c:29–69); hooks (src/execution/hooks.c:15–21).
- Movement: src/execution/player.c:21–77.
- Rays: cast all/one (src/execution/raycasting.c:15–53); math (src/execution/ray_math.c:12–29).
- Horizontal/Vertical: src/execution/raycast_h.c:15–87; src/execution/raycast_v.c:15–88.
- Rendering: background (src/execution/render_background.c); walls (src/execution/render_walls.c).
- Textures: src/execution/texture.c.
- Minimap/HUD: src/execution/minimap.c; src/execution/hud.c.
- Cleanup/Fullscreen: src/execution/cleanup.c; src/execution/fullscreen.c.

17) Presenter’s Script (Kid‑Friendly)
- “World = squared paper. You stand somewhere and look in a direction.”
- “For each screen column, shoot a straight line at a slightly different angle across your field of view.”
- “Find where that line first hits a wall square by stepping across the grid horizontally and vertically. Keep the closer one.”
- “Fix the distance (no fish‑eye), compute how tall to draw using D, and draw a skinny wall slice with the right texture column.”
- “Repeat for all columns. Add sky and floor, draw minimap/crosshair and HUD, and show the image.”
- “Keys move/strafe/turn with cos and sin; collision stops you from going into walls.”
- “Mouse turns you; it can feel a bit jittery without raw input. That’s normal in MLX.”

18) Extra: Where These Ideas Came From (Kid version)
- Distance √(dx²+dy²): Pythagoras (right triangles) → shortest slanted line.
- cos/sin/tan: Trigonometry, grown over centuries (Greeks, Indians, Islamic mathematicians; standardized by Euler). Split directions into x/y and get slopes.
- Angle wrap [0, 2π): modular arithmetic (Gauss) → don’t let angles grow forever.
- Fish‑eye fix (cos difference): vector dot product idea (19th‑century vector math) → take the forward part only.
- Pinhole camera/projection: Renaissance perspective (Brunelleschi/Alberti) → how to draw 3D on flat paper.
- Grid stepping (DDA): efficient line/voxel traversal (Amanatides & Woo, 1987) → hop gridlines instead of per‑pixel.
- Game raycasting: famous in Wolfenstein 3D (1992, id Software) → simple, fast 3D look.

19) Visual Walkthrough (ASCII)

Top‑down ray on a grid

  (y↑)
   6 ───────────────────────────────────────────────
   5 ─────■───────■───────■───────■───────■───────  ← gridlines (every 64 px)
   4 ─────■───────■───────■───────■───────■───────
   3 ─────■───────■───────■───────■───────■───────
   2 ─────■───────■───────■───────■───────■───────
   1 ─────■───────■───────■───────■───────■───────
   0 ─────────────────────────────────────────────── (x→)

  P = player at (px, py)
  → Horizontal stepping uses x = px + (y − py)/tan(θ).
  → Vertical stepping uses y = py + (x − px)*tan(θ).

Projection plane (why walls get tall/short)

     screen plane (distance D)
           │
           │      right edge
           │       ·
           │     ·   \
           │   ·       \
           │ ·           \
  camera ● ┼───────────────┐  (top view)
           │   W/2      
           │
         D = (W/2) / tan(FOV/2)

Texture X from hit offset

  Tile (size = 64)
  ┌───────────────────┐
  │                   │
  │   hit ●           │  offset = (hit_axis mod 64)
  │                   │  tex_x = offset * tex.width / 64
  └───────────────────┘

20) Tiny Quiz (check yourself)
- If θ = 0° (pointing right), what is sin(θ)? 0. What is cos(θ)? 1.
- If FOV gets smaller, do walls look bigger or smaller? Bigger (zoom in).
- Why do we use y−1 or x−1 at grid lines? To choose the correct neighbor square and avoid double‑counting.

21) Why These Files/Functions Exist (ELI7 tour)
- src/execution/init.c
  - init_game_struct: put safe zeros everywhere so nothing crashes if used early (63–78).
  - init_rays/init_textures_arr: clear arrays so rays/textures start empty (24–61).
  - create_rgb: pack (R,G,B) into one number the screen understands (105–107).
- src/execution/game.c
  - init_game: the “kitchen setup” — stove (window), pan (image), ingredients (textures/colors), mouse state (92–100).
  - Also centers player in tile and sets angle from N/S/E/W (55–67).
- src/execution/hooks.c
  - setup_hooks: wire key press/release, mouse move, window close, and per‑frame loop (15–21).
- src/execution/game_loop.c
  - update_game: move player then cast rays (15–19). render_game: draw everything (21–31). game_loop: run each frame (33–44).
- src/execution/utils.c
  - is_wall/has_wall_at (15–31), load_textures (33–52), put_pixel (63–72), free_game_data (85–102).
- src/execution/render_background.c
  - Paint sky/floor. Simple, fast start for each frame.
- src/execution/render_walls.c
  - corrected_height (15–25), wall bounds (27–35), render_wall_strip (62–75).
- src/execution/texture.c
  - choose texture (28–46), pick tex X (49–61), read tex pixel (15–26).
- src/execution/raycast*.c, ray_math.c
  - The heart: cross grid lines, pick nearest hit, handle angle/distance math.
- src/execution/minimap.c
  - Little world map in a corner: squares + player dot + direction line.
- src/execution/hud.c
  - Crosshair and on‑screen text.
- src/execution/mouse.c
  - Turn view by mouse dx; recenter near edges.
- src/execution/keys.c & input.c
  - Flip key flags; recompute walk/strafe/turn directions.
- src/execution/fullscreen.c
  - Ask window manager to go fullscreen.
- src/execution/cleanup.c
  - Show mouse, free things, quit.
- src/stubs/*.c
  - Fake MLX so code can compile without a real window.

22) Why These Equations? Where They Come From (ELI7 history)
- Distance √(dx²+dy²): Pythagoras (ancient geometry). Shortest slanted line.
- cos/sin/tan: trigonometry (grown across cultures; standardized by Euler). Split directions and measure slopes.
- Angle wrap [0, 2π): modular thinking (Gauss). Keep angles tidy.
- Fish‑eye fix (cos difference): dot product idea (19th‑century vectors). Keep only the forward part of a slanted distance.
- Pinhole camera/projection: Renaissance perspective (Brunelleschi/Alberti) and later projective geometry. Map real sizes to screen sizes.
- DDA grid stepping: efficient traversal (Amanatides & Woo, 1987). Hop gridlines quickly.
- Game raycasting: popular in Wolfenstein 3D (1992). Fast 3D look without full 3D math.

23) MLX Hooks & Event Loop (ELI7)
- MLX loop is a heartbeat; hooks are “call me when X happens.”
- We hook: key down (2), key up (3), mouse move (6), window close (17) (src/execution/hooks.c:15–21).
- mlx_loop_hook calls our game_loop every tick.

24) Memory & Cleanup (ELI7)
- We create one big screen image and a few texture images. We draw into the screen image.
- On exit we destroy textures, the screen image, the window, and the display so nothing leaks (src/execution/utils.c:85–102; src/execution/cleanup.c:11–18).

25) Performance & Why “One Ray per Column”
- Simple rule = simple code: one column → one ray. Looks good enough and is fast enough for this project.
- Wider screens mean more rays. If it’s slow, lower width or FOV.

26) Common Pitfalls (and how the code avoids them)
- tan near 0 or ∞: skip the unstable path (raycast_h.c:78–83; raycast_v.c:78–83).
- Exactly on gridlines: peek one pixel into the correct cell (raycast_h.c:51–55; raycast_v.c:49–55).
- Texture edges: clamp and modulo (texture.c:49–61; render_walls.c:50–55).
- World edge: out‑of‑bounds is a wall (utils.c:20–26).

27) Tiny Timeline (fun context)
- 500 BCE–1500 CE: triangles and trig ideas grow.
- 1400s: perspective rules for drawing 3D on flat paper.
- 1800s: vectors/dot product become standard math tools.
- 1987: fast grid stepping (Amanatides & Woo).
- 1992: Wolf3D popularizes game raycasting.
- Today: we practice these ideas in C with MLX.

28) Glossary (ELI7 quick terms)
- Ray: a straight line that starts at you and goes into the scene.
- Tile: one square of the map (64×64 pixels).
- Texture: a picture glued on a wall.
- FOV: how wide your view is.
- Projection: turning real sizes into on‑screen sizes.
- Fish‑eye: stretched look at the edges we fix with cosine.
- Hook: a function that MLX calls when something happens.
