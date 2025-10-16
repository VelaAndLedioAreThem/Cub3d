**Cub3D Execution Engine – Presenter’s Guide**

This is a stage‑ready technical guide focused on two pillars: the raycasting engine and the movement model that drives it. It explains the math step‑by‑step, maps each concept to concrete code, and provides a presenter’s narrative. With it, someone who wrote 0% of the code can explain the project end‑to‑end.

Chapters
- 1) Executive Summary
- 2) Coordinates, Units, Angles
- 3) Movement Model (Keyboard + Mouse)
- 4) Collision & World Boundaries
- 5) Raycasting Overview
- 6) Horizontal Intersections (Derivation + Code)
- 7) Vertical Intersections (Derivation + Code)
- 8) Distance, Fish‑Eye, Projection
- 9) Texture Selection & Mapping
- 10) Render Pipeline (BG → Walls → Overlays)
- 11) Minimap & HUD
- 12) Fullscreen (X11)
- 13) Parsing Primer (How runtime config is built)
- 14) 42 Norm Structure & Design Choices
- 15) Difficulties & Tradeoffs (Mouse!)
- 16) Function Index (Execution)
- 17) Presenter’s Script
 - 18) Math Deep Dive (Derivations & Origins)
 - 19) Visual Walkthrough (ASCII)

—

1) Executive Summary
- 2D grid world (tiles of `TILE_SIZE=64`) is rendered as a 3D view by casting one ray per screen column and drawing the wall slice at the correct height.
- Each frame: read input → update player pose → cast `NUM_RAYS` over the field of view → draw background, walls, minimap/HUD → display.
- Entry point wires everything: `src/main.c:17`.
- The frame pipeline runs in: `src/execution/game_loop.c:15`, `src/execution/game_loop.c:21`, `src/execution/game_loop.c:33`.

—

2) Coordinates, Units, Angles
- World units are pixels; one grid tile = `64` pixels (`include/execution.h:46`). Player pose is `(player_x, player_y, player_angle)` in pixels + radians.
- Screen uses `SCREEN_WIDTH x SCREEN_HEIGHT` pixels (`include/execution.h:44`, `include/execution.h:45`). One ray per screen column (`include/execution.h:54`).
- FOV is in radians (`FOV_ANGLE`), here ≈ 60° (`include/execution.h:51`). Per‑column angle is centered on `player_angle`.
- Angles are normalized into `[0, 2π)` to make facing tests robust: `src/execution/ray_math.c:12`.

—

3) Movement Model (Keyboard + Mouse)
- Derived inputs:
  - Walk: forward/back from W/S → `walk_direction ∈ {−1, 0, 1}`.
  - Strafe: left/right from A/D → `side_direction ∈ {−1, 0, 1}`.
  - Turn: left/right arrows → `turn_direction ∈ {−1, 0, 1}`.
- Recompute on key events: `src/execution/input.c:15` and `src/execution/input.c:37`.
- Turn in radians per frame (deg→rad): `ROTATION_SPEED` degrees scaled and applied, then normalized: `src/execution/player.c:71`.
- Translate in player’s local frame using cos/sin:
  - Forward/back: add `cos(angle)*step` to x and `sin(angle)*step` to y `src/execution/player.c:43`.
  - Strafe: add `cos(angle+π/2)*step` and `sin(angle+π/2)*step` `src/execution/player.c:48`.
- Speed modifiers: SHIFT speeds up, CTRL slows down `src/execution/player.c:25`.
- Mouse look: per motion event, delta X rotates by `dx * mouse_sensitivity`, then normalize `src/execution/mouse.c:63`.

—

4) Collision & World Boundaries
- Candidate new `(x, y)` is tested separately on axes to allow sliding:
  - If X move alone is free, apply it; if Y move alone is free, apply it `src/execution/player.c:63`.
- World bounds are solid walls: any `(x, y)` outside `[0, map_w*tile) × [0, map_h*tile)` is treated as blocked `src/execution/utils.c:20`.
- Tile check picks grid cell at `(int)(x / TILE_SIZE), (int)(y / TILE_SIZE)` and compares to `CH_WALL` `src/execution/utils.c:23`.

—

5) Raycasting Overview
- For each column i, compute its ray angle over the FOV around `player_angle` and cast it: `src/execution/raycasting.c:44`.
- A ray is evaluated twice: against horizontal grid lines and vertical grid lines. Pick the nearer result and remember if it was a vertical hit: `src/execution/raycasting.c:15`.
- Core helpers: normalize angles `src/execution/ray_math.c:12`, compute Euclidean distance `src/execution/ray_math.c:22`.

—

6) Horizontal Intersections (Derivation + Code)
- Facing flags from θ: up if `0 ≥ θ ≥ π` is false; down if `0 < θ < π`; right if `θ < π/2 or θ > 3π/2`; left otherwise `src/execution/raycast_h.c:15`.
- First intersection with horizontal grid line at y:
  - Base y: `floor(py / TILE) * TILE`; if facing down, add one tile `src/execution/raycast_h.c:23`.
  - Compute x at that y using similar triangles: `x = px + (y − py) / tan(θ)` `src/execution/raycast_h.c:28`.
- Step deltas between successive horizontal grid lines:
  - `Δy = ±TILE` (negative when facing up), `Δx = TILE / tan(θ)` with sign corrected by facing `src/execution/raycast_h.c:32`.
- Sampling fudge on the gridline: when facing up, sample at `y − 1` so the tile above the line is tested `src/execution/raycast_h.c:51`.
- March until a wall or out‑of‑bounds; compute hit distance and record `(wall_hit_x, wall_hit_y)` `src/execution/raycast_h.c:55`.
- Guard for near‑parallel rays: if `|sin θ|` is tiny, skip with a large distance `src/execution/raycast_h.c:78`.

—

7) Vertical Intersections (Derivation + Code)
- Facing flags from θ: right if `θ < π/2 or θ > 3π/2`; down if `0 < θ < π` `src/execution/raycast_v.c:15`.
- First intersection with vertical grid line at x:
  - Base x: `floor(px / TILE) * TILE`; if facing right, add one tile `src/execution/raycast_v.c:23`.
  - Compute y at that x: `y = py + (x − px) * tan(θ)` `src/execution/raycast_v.c:28`.
- Step deltas between successive vertical lines:
  - `Δx = ±TILE` (negative when facing left), `Δy = TILE * tan(θ)` with sign corrected by facing `src/execution/raycast_v.c:32`.
- Sampling fudge: when facing left, sample at `x − 1` so the tile to the left is tested `src/execution/raycast_v.c:49`.
- March until a wall or OOB; compute distance and record hit point `src/execution/raycast_v.c:55`.
- Guard for near‑parallel: if `|cos θ|` tiny, skip `src/execution/raycast_v.c:79`.

—

8) Distance, Fish‑Eye, Projection
- Raw distance is Euclidean `sqrt((hx − px)^2 + (hy − py)^2)` `src/execution/ray_math.c:22`.
- Fish‑eye correction uses the ray’s angle relative to the view direction: `corr = d * cos(ray_angle − player_angle)` `src/execution/render_walls.c:20`.
- Projection plane distance: `dist_proj_plane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2)` `src/execution/render_walls.c:23`.
- Column height in pixels: `(TILE_SIZE / corr) * dist_proj_plane` and clamped to screen `src/execution/render_walls.c:15`.

Why these formulas work (intuition):
- Pinhole camera model: imagine an imaginary vertical screen at distance `dist_proj_plane` from the camera. A wall of physical height `TILE_SIZE` at perpendicular distance `corr` subtends an angle whose image height is proportional to `TILE_SIZE / corr`. The proportionality constant depends on the projection plane’s distance; solving similar triangles yields `dist_proj_plane = (W/2)/tan(FOV/2)`.
- Fish‑eye arises because the distance along an oblique ray is larger than the perpendicular distance to the same wall; projecting the ray length onto the forward direction via `cos(Δθ)` gives the true perpendicular distance.

—

9) Texture Selection & Mapping
- Texture source selection depends on which face of the grid cell was hit:
  - Vertical hit: facing right → West texture; facing left → East texture `src/execution/texture.c:28`.
  - Horizontal hit: facing down → North texture; facing up → South texture `src/execution/texture.c:35`.
- Compute texture X coordinate from the hit offset inside the tile:
  - Vertical: `offset = wall_hit_y mod TILE`; Horizontal: `offset = wall_hit_x mod TILE` `src/execution/texture.c:55`.
  - Scale to texture width: `tex_x = offset * tex.width / TILE_SIZE` `src/execution/texture.c:60`.
- Texture Y is advanced per screen pixel using `step = tex.height / line_height` from the column’s top bound `src/execution/render_walls.c:44`.

Why modulo and scaling:
- The hit point’s local offset inside its tile is in `[0, TILE_SIZE)`. Modulo (`fmod`) computes that fractional position reliably even across tiles; scaling by `tex.width / TILE_SIZE` maps world‑space tile offset to texture texel X.
- The Y advancement emulates perspective‑correct sampling along the vertical slice in screen space; since walls are axis‑aligned with a pinhole projection, simple linear stepping matches the projected vertex interpolation along that column.

—

10) Render Pipeline (BG → Walls → Overlays)
- Background: paint ceiling to midline, floor below `src/execution/render_background.c:15`.
- Walls: for each column, compute height, bounds, texture, then draw the slice `src/execution/render_walls.c:62`.
- Present: blit the image to the window `src/execution/game_loop.c:29`.
- Overlays: minimap and crosshair drawn around the blit; HUD strings via MLX `src/execution/game_loop.c:30`.

—

11) Minimap & HUD
- Minimap draws tiny tiles with different colors for walls vs free space and overlays a player marker + facing line `src/execution/minimap.c:15`.
- HUD shows position, angle (deg), and frame count `src/execution/hud.c:34`.

—

12) Fullscreen (X11)
- Toggle by sending `_NET_WM_STATE_FULLSCREEN` to the WM using MLX internals `src/execution/fullscreen.c:23`.
- Platform specific; relies on X11 atoms and may vary per WM `src/execution/fullscreen.c:61`.

—

13) Parsing Primer (How runtime config is built)
- Main calls `parse_config`, which fills `t_config` with textures, colors, map, and player spawn `src/main.c:25`.
- Config defaults are set in `init_configs` and cleaned via `destroy_configs` `src/parsing/init_config.c:15`.
- Identifiers and textures are parsed, colors validated, and the map is checked as closed; this ensures the execution engine always gets a valid grid.

—

14) 42 Norm Structure & Design Choices
- Small focused functions and `static` helpers in C files (raycast_h/v split) to control length and complexity.
- All mutable state is in `t_game`; functions take explicit arguments instead of globals.
- Constants via defines; types via structs; explicit prototypes in headers.
- Side‑effects (drawing, MLX calls) are isolated in helpers like `put_pixel`, `load_textures`.

—

15) Difficulties & Tradeoffs (Mouse!)
- Why mouse look feels rough and is hard to perfect in MLX:
  - No raw input or pointer lock; recenters generate extra motion events and jitter.
  - OS pointer acceleration skews deltas; backend differences across platforms.
  - Cursor can leave the window; events get clipped/dropped.
- Mitigations used and options:
  - Edge‑only recenter and optional lower sensitivity `src/execution/mouse.c:15`.
  - Ignore the first delta after a warp; apply light smoothing (can be added).
  - Arrow‑key turning remains a steady fallback.

—

16) Function Index (Execution)
- Entry & lifecycle:
  - `src/main.c:17` main wiring (parse → init → hooks → loop)
  - `src/execution/game.c:92` init_game (structs, window, textures, mouse)
  - `src/execution/hooks.c:15` setup_hooks (keys, mouse, close, loop)
  - `src/execution/game_loop.c:15` update_game (player, rays)
  - `src/execution/game_loop.c:21` render_game (bg, walls, overlays)
- Input & movement:
  - `src/execution/input.c:15` recompute walk/strafe
  - `src/execution/input.c:37` recompute turn
  - `src/execution/keys.c:29` apply_keypress
  - `src/execution/keys.c:51` apply_keyrelease
  - `src/execution/player.c:69` update_player (turn + translate)
  - `src/execution/mouse.c:48` handle_mousemove (dx to angle)
- Raycasting & math:
  - `src/execution/raycasting.c:38` cast_all_rays (per‑column angle)
  - `src/execution/raycasting.c:15` cast_ray (H/V and pick nearest)
  - `src/execution/raycast_h.c:72` cast_horizontal
  - `src/execution/raycast_v.c:72` cast_vertical
  - `src/execution/ray_math.c:12` normalize_angle
  - `src/execution/ray_math.c:22` distance_between_points
- Rendering & textures:
  - `src/execution/render_background.c:55` render_background
  - `src/execution/render_walls.c:62` render_wall_strip / render_walls
  - `src/execution/texture.c:15` get_texture_color
  - `src/execution/texture.c:42` select_wall_texture
  - `src/execution/texture.c:49` calculate_texture_x
  - `src/execution/minimap.c:108` render_minimap
  - `src/execution/hud.c:15` render_crosshair; `src/execution/hud.c:34` render_hud
- Utilities & cleanup:
  - `src/execution/utils.c:33` load_textures
  - `src/execution/utils.c:63` put_pixel
  - `src/execution/utils.c:15` is_wall; `src/execution/utils.c:28` has_wall_at
  - `src/execution/cleanup.c:11` cleanup_and_exit
  - `src/execution/fullscreen.c:61` toggle_fullscreen

—

17) Presenter’s Script
- Start with the idea: “We render a 3D scene from a 2D grid by casting one ray per screen column.”
- Define units: tiles are 64px; player has (x, y, angle). Screen is W×H; FOV≈60°.
- Movement: keys set direction flags; `update_player` turns by a small radian step and translates forward/back and strafe using cos/sin. Collision checks X and Y separately so the player slides along walls.
- Raycasting per column: compute the ray angle in the FOV; cast against horizontal grid lines (derive first intercept and step) and vertical grid lines (same idea). For each, march step‑by‑step until a wall; take the nearer hit.
- Avoid fish‑eye: multiply the hit distance by `cos(ray_angle − player_angle)`.
- Projection: “Imagine a screen at a fixed distance in front of the camera.” Column height is proportional to tile height over corrected distance and the projection plane distance.
- Texture mapping: choose texture by which face was hit; compute texture X by the offset inside the tile; walk texture Y down the slice by a precomputed step.
- Rendering: draw ceiling and floor colors, then each wall column, then minimap/crosshair and HUD, then blit the image buffer to the window.
- Mouse: delta‑based rotation; explain why MLX makes raw input difficult and what we do to mitigate it.
- Finish with constraints: 42 Norm structure, portable MLX approach, and where the complexity lives (intersections, corrections, sampling).

Appendix: Texture Orientation Rationale
- Vertical hit, facing right → the face you see belongs to the tile on the right, which is its West face → West texture `src/execution/texture.c:28`.
- Horizontal hit, facing down → you see the top of the tile below you, which is its North face → North texture `src/execution/texture.c:35`.

Notes on PDFs & Makefile
- Subject PDFs define allowed features and constraints; this engine follows the standard spec (XPM textures, closed map, MLX rendering).
- Makefile builds parsing and execution, links libft/mlx, and has a `test` target. An older alternative `src/input/input.c` exists but is not compiled.

End.

—

18) Math Deep Dive (Derivations & Origins)

18.1 Trigonometry & Similar Triangles
- Direction vectors: `(cos θ, sin θ)` form the unit vector pointing at angle θ. That’s why movement splits into cos/sin components and rays step along axes using tan/cot.
- Similar triangles underpin both the first‑intercept formulas and the projection plane distance. If two right triangles share one acute angle, their side ratios match.

18.2 Horizontal Intercepts (Derivation)
- Given player `(px, py)` and ray angle θ, the first horizontal gridline is `y0 = floor(py/TILE)*TILE (+ TILE if facing down)`.
- Along the ray, the x displacement matches y displacement via `tan θ = (y − py)/(x − px)`. Solve for x:
  - `x = px + (y0 − py)/tan θ` → `src/execution/raycast_h.c:28`.
- Step to the next horizontal gridline by adding `Δy = ±TILE` and `Δx = TILE/tan θ` with sign corrections → `src/execution/raycast_h.c:32`.
- Sampling at `y0 − 1` when facing up avoids double‑counting a cell exactly on a gridline (the “which cell do we mean?” ambiguity).

18.3 Vertical Intercepts (Derivation)
- First vertical gridline `x0 = floor(px/TILE)*TILE (+ TILE if facing right)`.
- Using `tan θ = (y − py)/(x − px)` again, but solve for y at x0:
  - `y = py + (x0 − px)*tan θ` → `src/execution/raycast_v.c:28`.
- Step with `Δx = ±TILE` and `Δy = TILE*tan θ` with sign corrections → `src/execution/raycast_v.c:32`.
- Sample at `x0 − 1` when facing left to probe the tile truly left of the gridline.

18.4 DDA Grid Traversal: Why It’s Robust
- The stepping described above is a form of DDA (Digital Differential Analyzer): from one grid boundary to the next with constant increments. It guarantees O(N) steps where N is number of gridlines crossed.
- Historical note: The ray‑grid traversal popular in realtime rendering was refined by Amanatides & Woo (1987) for voxel traversal. Earlier DDAs go back to 1960s/70s graphics; in games, Wolfenstein 3D (1992, John Carmack et al.) popularized the tile‑based raycaster.

18.5 Angle Normalization: Why `[0, 2π)`
- Normalizing angles avoids branch explosions and numeric drift when classifying facing (up/down/left/right) and when comparing angles modulo full rotations. Implemented by adding/subtracting `2π` until within range `src/execution/ray_math.c:12`.

18.6 Euclidean Distance & Fish‑Eye
- Euclidean distance is basic Pythagoras: `sqrt(dx^2 + dy^2)` `src/execution/ray_math.c:22`.
- Fish‑eye correction projects the ray vector onto the camera forward axis using the dot product identity: `|v| cos Δθ = v · f_hat`. Here, `Δθ = ray − view` and `f_hat` is the unit forward vector. That’s exactly the cosine factor seen in `src/execution/render_walls.c:20`.

18.7 Projection Plane Distance Derivation
- Let half the screen width be `W/2` and half FOV be `α = FOV/2`. The ray through the right edge forms angle α with the forward axis. In the right triangle formed by the camera, the screen center, and the right edge, `tan α = (W/2)/D`. Thus `D = (W/2)/tan α` → `src/execution/render_walls.c:23`.

18.8 Texture Coordinate Mapping
- For axis‑aligned walls, the u‑coordinate (horizontal in texture space) is simply the fractional distance along the wall face within a tile. The modulo yields `[0, TILE)` and divides by `TILE` to get `[0,1)`; then multiply by `texture.width` → `src/execution/texture.c:49`.
- The v‑coordinate advances uniformly down the screen column. Because walls are vertical planes perpendicular to the floor, the perspective projection maps them linearly along that column.

18.9 Movement as Vector Composition
- Local forward = `(cos θ, sin θ)`; local right = `(cos(θ+π/2), sin(θ+π/2))`. Summing `forward*fw_step + right*side_step` yields the intended strafe + forward motion `src/execution/player.c:39`–`src/execution/player.c:50`.
- Axis‑separated collision tests implement a simple form of collision response: project motion onto axes and accept components that don’t penetrate `src/execution/player.c:63`–`src/execution/player.c:66`.

18.10 Numerical Stability
- Near `θ ≈ 0 or π`, `sin θ` ≈ 0 makes `TILE/tan θ` unstable; code guards with an epsilon and bails to “very far” distance `src/execution/raycast_h.c:78`.
- Near `θ ≈ π/2 or 3π/2`, `cos θ` ≈ 0 makes vertical stepping unstable; guarded similarly `src/execution/raycast_v.c:79`.
- Using `fmod` and clamping texture coordinates avoids over/underflow and off‑by‑one in texture sampling `src/execution/texture.c:55`–`src/execution/texture.c:61` and `src/execution/render_walls.c:50`–`src/execution/render_walls.c:55`.

18.11 Historical Attributions (Plain‑language)
- Raycasting in games: Popularized by id Software’s Wolfenstein 3D (1992). Their engine used lookup tables and fixed‑point math for speed on early PCs. Our code mirrors the conceptual approach with modern C and `math.h`.
- Grid traversal (DDA): The efficient voxel DDA traversal is widely credited to Amanatides & Woo (1987) in computer graphics literature; variations are common in CPU raytracers and tile engines.
- Pinhole camera & projection math: Standard perspective projection from classical projective geometry underpinning all 3D graphics.

—

19) Visual Walkthrough (ASCII)

19.1 Top‑down Ray vs Grid

  (y↑)
   6 ───────────────────────────────────────────────
   5 ─────■───────■───────■───────■───────■───────  ← gridlines (every TILE)
   4 ─────■───────■───────■───────■───────■───────
   3 ─────■───────■───────■───────■───────■───────
   2 ─────■───────■───────■───────■───────■───────
   1 ─────■───────■───────■───────■───────■───────
   0 ─────────────────────────────────────────────── (x→)

  P = player at (px,py)
  → Ray at angle θ crosses a horizontal line at y0 first, then y0 ± TILE, …
    x at each crossing is px + (y − py)/tan θ (horizontal stepping).
    Similarly for vertical stepping at x0 using y = py + (x − px)*tan θ.

19.2 Projection Plane Geometry

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

19.3 Texture X From Hit Offset

  Tile (size = TILE)
  ┌───────────────────┐
  │                   │
  │   hit ●           │  offset = fmod(hit_axis, TILE)
  │                   │  tex_x = offset * tex.width / TILE
  └───────────────────┘

19.4 Movement Vectors

  forward = (cos θ, sin θ)
  right   = (cos(θ+π/2), sin(θ+π/2))
  new_pos = pos + forward*fw_step + right*side_step

—

20) ELI7: The Kid‑Friendly Guide to the Math

Think of the world as squared paper (a grid). You stand somewhere on it and look in some direction. To “see” walls, we throw invisible straight lines (rays) forward and check where they hit a square that is a wall.

Words for symbols
- π (pi) ≈ 3.14: half a pizza is π radians; a full circle is 2π.
- cos (cosine): the “left/right” amount of your direction arrow.
- sin (sine): the “up/down” amount of your direction arrow.
- tan (tangent): “rise over run” = sin ÷ cos. Handy for slopes.
- √ (square root): the length of a right triangle’s slanted side when you know the other two sides (Pythagoras).
- mod (remainder): what’s left after dividing. Example: 70 mod 64 = 6.

20.1 Moving the player (arrows math)
- Your facing direction is an arrow with length 1 that points where you look.
  - Its left/right piece is cos(angle).
  - Its up/down piece is sin(angle).
- Walking forward by “step” means: x += cos(angle)*step, y += sin(angle)*step.
- Strafing (sideways) is the same but with a 90° turn: x += cos(angle+90°)*step, y += sin(angle+90°)*step.
- SHIFT makes step bigger (faster), CTRL makes it smaller (slower).

20.2 What a ray does (step‑by‑step)
1) Start at your position (px, py) and pick a direction (angle).
2) Find the next “grid line” ahead:
   - Horizontal line (like a floor line): y is at the next multiple of TILE.
   - Vertical line (like a wall line): x is at the next multiple of TILE.
3) Use tan(angle) to find where the ray hits that line:
   - Horizontal: x = px + (y − py) / tan(angle).
   - Vertical: y = py + (x − px) * tan(angle).
4) Step to the next line (add TILE each time) and repeat until you find a wall square.
5) You’ll get two candidates (one from horizontal lines, one from vertical). Keep the one that’s closer.

20.3 Distance and “fish‑eye”
- Raw distance = √((hit_x − px)^2 + (hit_y − py)^2). That is straight‑line distance.
- But if you look to the side, things look stretched (fish‑eye effect). Fix: use only the “forward part” of the distance by multiplying with cos(ray_angle − view_angle). That shrinks the sideways rays back to where they should be.

20.4 Why things on screen get taller or shorter
- Imagine a movie screen standing in front of you at distance D.
- A real wall of height TILE looks taller on the screen if it’s close, and shorter if it’s far. The relationship is simple: height_on_screen ≈ (TILE / distance) * D.
- D is chosen from the field‑of‑view (zoom). Halving the field‑of‑view makes D bigger (zoom in), so walls look taller.

20.5 How we pick the part of the texture to draw
- Each wall picture (texture) is like wallpaper with width in pixels.
- When a ray hits a tile, we find how far along the tile’s face the hit was: that’s “remainder after dividing by TILE” (the mod).
  - Example: If TILE=64 and your hit is 70 pixels into the wall from its start, 70 mod 64 = 6 → you want column 6 inside the texture (scaled to texture width).

20.6 Small gotchas (why the code looks picky)
- When a ray hits exactly on a grid line, which square do we mean? The one above or the one below? To avoid “double counting”, the code peeks one pixel into the correct side (y−1 when looking up, x−1 when looking left).
- When tan(angle) would explode (looking almost straight up or straight right), we skip that path and use the other direction’s test.

20.7 Mini quiz (sanity checks)
- Q: If angle = 0° (pointing right), what’s sin(angle)? A: 0. What’s cos(angle)? A: 1.
- Q: If you strafe right at angle 0°, which way do you move? A: Down on the screen (positive y) because sin(90°)=1.
- Q: If FOV gets smaller, do walls look bigger or smaller? A: Bigger (like zooming in).
