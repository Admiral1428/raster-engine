# raster-engine
*Raster Engine* is 3D graphics engine built from scratch using C++, employing CPU-based software rasterization. The virtual environment consists of two distinct islands in an ocean setting, with assets crafted meticulously by hand. These assets include a canyon, waterfall, flowing river, mountains, house, airport, bridge, trees, airplane, and a boat. 

## Video Demo

[![Raster Engine on YouTube](https://img.youtube.com/vi/8gWjE3Mqe1k/0.jpg)](https://youtu.be/8gWjE3Mqe1k)

## Installation

* Download the latest .zip file from the *Releases* page.
* Unzip the file and run the provided executable (`raster_engine.exe`) on a Windows PC, located in the `bin` folder.

## Overview

The purpose of this project was to improve my C++ skills and to gain a fundamental understanding of 3D graphics principles using a low-level approach.

The [*SDL3 library*](https://github.com/libsdl-org/SDL/releases) was used to handle window creation and pixel manipulation, but all rendering logic was implemented manually. By coding each step of the rendering pipeline from the ground up, I gained a clear understanding of the mathematical and algorithmic principles behind modern graphics APIs. These APIs rely on hardware-accelerated techniques powered by today’s GPUs. These hardware abstraction layers have been central to game engines since the late 1990s, but the low-level approach of a software renderer gave me a deeper understanding of the graphics pipleine.

My goal was to create an engine which could render triangular surfaces at any position and orientation, account for surface intersection and depth with z-buffering, map textures to surfaces, calculate basic diffuse lighting, and play basic sound effects in specific locations throughout the 3D space. 

Initially, I considered making a more primitive engine using ray-casting techniques, as seen in early 3D games such as *Hovertank 3-D (1991)*, *Catacomb 3-D (1992)* and *Wolfenstein 3D (1992)*. However ray-casting imposes limitations on map design and geometry, as it cannot represent diagonal walls, sloped surfaces, or multiple vertical levels. Fewer limitations were present in "2.5D" engines used to power *Doom (1993)* and *Duke Nukem 3D (1995)*. But the engine for *Quake (1996)* had both software and hardware-based solutions to represent its full 3D world and objects, without relying on 2D sprites. I aimed to achieve this early level of full 3D fidelity, excluding complex gameplay mechanics, by building my custom engine.

## Development

After spending several weeks refreshing my knoweldge of C++ fundamentals, I began by creating a basic window, plotting triangle vertices with white pixels, and connecting them with red edges using Bresenham's line algorithm:

<br>
<img width="960" height="540" alt="09-29-25_1800" src="https://github.com/user-attachments/assets/2fba9f00-90b3-4893-92c3-50760a9728b1" />
<br><br>

To represent a triangle in 3D space with vertices in any position and orientation, the next step was to use a projection transformation matrix to convert these $x$, $y$, $z$ coordinates into 2D camera space. This process introduced me to the concept of the viewing frustum, defined by six clipping planes - near, far, left, right, top, and bottom - and the use of a 4th coordinate $w$ to enable unified matrix operations. By specifying the horizontal field of view, aspect ratio (*width* / *height*), near ($n$), and far ($f$) clipping planes, I constructed the projection matrix, which ultimately transforms the homogeneous coordinates to normalized device coordinates (*ndc*):

$$S_x = {{1} \over {\text{tan}(\text{fov})}}$$

$$S_y = {S_x * {\text{width}} \over {\text{height}}}$$

$$M_{proj} = 
\begin{bmatrix}
S_x & 0 & 0 & 0 \\
0 & S_y & 0 & 0 \\
0 & 0 & {-f} \over {(f-n)} & {-(f * n)} \over {(f-n)} \\
0 & 0 & -1 & 0
\end{bmatrix}
$$

$$M_{proj}
\begin{bmatrix}
x \\
y \\
z \\
w = 1
\end{bmatrix} = 
\begin{bmatrix}
x' \\
y' \\
z' \\
w'
\end{bmatrix}$$

$$ndc = \begin{bmatrix}
x'/w' \\
y'/w' \\
z'/w' \\
w'/w'
\end{bmatrix}$$

<img width="2056" height="1065" alt="image" src="https://github.com/user-attachments/assets/96df2b06-48d4-4ef3-8db7-ae67f216f24c" />

These *ndc* were then rasterized into screen space using the specified render width and height:

$$r_x = \left({{x'} \over {w'}} + 1\right) * 0.5 * \text{width}$$
$$r_y = \left(1 - \left({{y'} \over {w'}} + 1\right) * 0.5\right) * \text{height}$$


The [*Eigen library*]((https://github.com/PX4/eigen)) was used for all matrix and vector operations. Note that *Eigen* uses column-major memory layout, so the projection matrix may appear transposed compared to some literature sources. The resulting render of a basic cube is shown below, assuming the camera *eye* is aligned with the $x-y$ plane and oriented along the $-z$ axis:

<br>
<img width="960" height="960" alt="10-01-25_1115" src="https://github.com/user-attachments/assets/d79be8a5-6659-4595-aced-f0c273826e08" />
<br><br>

At this stage, the approach still relied on Bresenham's line algorithm to draw edges between triangle vertices. To fill the surface, I initially attempted to use these calculated edges to identify which pixels lay within the triangle. However, I soon realized that to handle depth and intersection correctly, it was necessary to compute the z-depth of all points within the triangle. This led me to calculate the barycentric coordinates $\alpha$, $\beta$, and $\gamma$ for each point $r_p$ within the bounding box defined by the triangle vertices $0$, $1$, and $2$.

$$v_0 = r_1 - r_0$$
$$v_1 = r_2 - r_0$$
$$v_2 = r_p - r_0$$

$$\text{denom} = (v_0 \cdot v_0) * (v_1 \cdot v_1) - (v_0 \cdot v_1) * (v_0 \cdot v_1)$$

$$\beta = {{(v_1 \cdot v_1) * (v_2 \cdot v_0) - (v_0 \cdot v_1) * (v_2 \cdot v_1)} \over {\text{denom}}}$$

$$\gamma = {{(v_0 \cdot v_0) * (v_2 \cdot v_1) - (v_0 \cdot v_1) * (v_2 \cdot v_0)} \over {\text{denom}}}$$

$$\alpha = 1 - \beta - \gamma$$

Pixels inside the triangle were identified by checking which Barycentric coordinates were greater than zero - using a practical tolerance of $$-1 \times 10^{-3}$$. A z-depth buffer was initialized across all screen pixels with a default value of $1.0$ (the far clipping plane). The *ndc* z-depth for each relvant pixel was then computed by interpolating the homogeneous vertex positions using the corresponding barycentric weights:

$$\left({{z} \over {w}}\right)_{ndc} = \alpha \left({{z'_0} \over {w'_0}}\right) +  \beta \left({{z'_1} \over {w'_1}}\right) +  \gamma \left({{z'_2} \over {w'_2}}\right) $$ 

By iterating over each surface and rendering pixels whose *z-ndc* depth was lower than the previously stored value at that pixel, the cube was rendered correctly:

<br>
<img width="960" height="960" alt="10-02-25_1730" src="https://github.com/user-attachments/assets/e83bbfd0-b027-4bf6-b298-d0be2db073c3" />
<br><br>

Since the ultimate goal of the project was to support more complex geometry beyond simple triangles and cubes, new classes were introduced to construct rectangular prisms and pyramids of arbitrary dimensions. This enabled the creation of a basic scene featuring a grass surface, two trees, and a cloud. The update also added a diminished lighting effect—similar to the one used in *Doom (1993)* — where surface brightness decreases as a function of z-depth from the camera:

<br>
<img width="644" height="540" alt="10-06-25_1700" src="https://github.com/user-attachments/assets/86bdb687-5a77-4eef-b4e8-e906eb74f185" />
<br><br>

At this stage, the camera view was fixed in place, but individual surfaces could be moved to observe their behavior as they changed position. When surfaces intersected the edges of the screen—particularly the near and far viewing planes—undesired visual artifacts appeared. To resolve this, accurate clipping of triangular surfaces against the six boundaries of the viewing frustum was necessary.

The Sutherland-Hodgman algorithm was used for clipping, summarized as follows:

* If all points of a triangle are inside clip space, retain all points.
* If all points are outside a single clipping plane, discard the triangle.
* If all points are outside two or more clipping planes, proceed to the clipping algorithm.
* If one or two points are outside clip space, proceed to the clipping algorithm.

For each of the six clipping planes, the algorithm determines whether each vertex is inside or outside the plane and computes intersection points for edges that cross the boundary. If the resulting clipped shape has more than three vertices, a polygon-splitting function was applied:

* Use the first point $p_0$ as a pivot, and form a triangle using $p_0$, $p_1$, and $p_2$.
* Add this triangle to the output list.
* Remove $p_1$ from the list of remaining points, and repeat the process if more than three points remain.
* When only three points remain, this forms the final triangle.

The following animation demonstrates the clipping behvaior, with each newly formed triangle shown in a different color for illustration purposes. A maximum of five sub-triangles can result from the clipping process. Once the original triangle fully crosses behind the near clipping plane, it is no longer rendered.

<br>

![triangle_clip_five](https://github.com/user-attachments/assets/0c2e39fc-5ea8-4bc8-9f51-1b87bbbcf232)

<br>

In this second example, the original triangle is aligned with the y-z plane and gradually intersects the near clipping plane at an x-location that remains visible on screen. This intersection causes sub-triangles to be generated accordingly.

<br>

![triangle_clip_near_plane](https://github.com/user-attachments/assets/263bb798-df27-4e78-b831-2c2906e8bcea)

<br>

With clipping fully implemented, the next step was to implement camera movement and a first-person control scheme. A view matrix was constructed based on the following rotation and translation matrices, using a camera pitch angle $\theta$, yaw angle $\psi$, and *eye* position $x_{eye}$, $y_{eye}$, $z_{eye}$:

$$R_{x} = 
\begin{bmatrix}
1 & 0 & 0 & 0 \\
0 & \text{cos}(\theta) & -\text{sin}(\theta) & 0 \\
0 & \text{sin}(\theta) & \text{cos}(\theta) & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

$$R_{y} = 
\begin{bmatrix}
\text{cos}(\psi) & 0 & \text{sin}(\psi) & 0 \\
0 & 1 & 0 & 0 \\
-\text{sin}(\psi) & 0 & \text{cos}(\psi) & 0 \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

$$T = 
\begin{bmatrix}
1 & 0 & 0 & x_{eye} \\
0 & 1 & 0 & y_{eye} \\
0 & 0 & 1 & z_{eye} \\
0 & 0 & 0 & 1
\end{bmatrix}
$$

$$M_{view} = (T * R_y * R_x)^{-1} = (R_x)^{T} * (R_y)^{T} * (T)^{-1}$$

The triangle surface coordinates in world space are transformed into clip space by first multiplying them by the view matrix, followed by the projection matrix. This transformation is then followed by perspective division by $w'$ and screen-space rasterization as previously described.

$$M_{proj}*M_{view}
\begin{bmatrix}
x \\
y \\
z \\
w = 1
\end{bmatrix} = 
\begin{bmatrix}
x' \\
y' \\
z' \\
w'
\end{bmatrix}$$

To implement forward, backward, and left / right strafing right movement controls, a *forward* vector of $[0, 0,-1]$ and a *left* vector of $[-1, 0, 0]$ were multiplied by 3x3 rotation matrices derived from the camera's pitch and yaw angles. This produced adjusted unit vectors aligned with the camera orientation. These controls were mapped to the `W`, `S`, `A`, and `D` keys.

To ensure movement at a consistent speed regardless of framerate, the translation speed was multiplied by the frame's delta time. The resulting translation distance was then scaled by the appropriate unit vector to compute the corresponding $\Delta x$, $\Delta y$, and $\Delta z$ adjustments to the camera eye position. 

Camera rotation in the vertical and horizontal directions was mapped to the arrow keys or mouse movement, resulting in adjustments $\Delta \theta$ and $\Delta \psi$ to the camera rotation angles. Similar to translation, the rotation rate was defined as a fixed value and multiplied by the frame's delta time to maintain consistent panning speed across varying framerates.

<br>
<video src="https://github.com/user-attachments/assets/e0b9aa25-6a42-46c4-92c4-238dc887bf29" width="1200" height="900" controls></video>
<br><br>

The first performance optimization involved implementing back-face culling, where a surface is rendered only if it faces the camera. This check uses the dot product between the surface normal vector (evaluated before the projection transformation) and a vector from the camera position to the first vertex of the triangle.

<br>
<video src="https://github.com/user-attachments/assets/958ea38a-dd6c-4f7c-9948-58a30db190c8" width="1200" height="900" controls></video>
<br><br>

The second performance optimization involved computing barycentric coordinates, triangle inclusion checks, and z-depth values using vectorized math, rather than scalar per-pixel calcluations within nested `for` loops. The x-coordinates of each pixel were stored in a $p_x$ vector, and the y-coordinates in a $p_y$ vector. These vectors were then manipulated using the optimized operations provided by the Eigen template library. 

This optimization also invovled using the auto type where appropriate, minimizing division operations, and eliminating other redundant calculations.

The next step was to begin building a more detailed map environment, featuring a waterfall, canyon, river, beachfront, ocean, and mountain island. A *Shape* superclass was used in this process, with subclasses for a rectangle, rectangular prism, pyramid, and quadrilateral. These geometries could be translated and rotated into position in world space to allow for easier world-building. However, this required sketching the desired environment by hand and speciying coordinates and transformations manually. Some example sketches are shown below, in addition to the video depicting the first version of the detailed world map.

<br>

<img width="1933" height="1449" alt="image" src="https://github.com/user-attachments/assets/ac9032f6-5224-42aa-823d-58c234bb058c" />

<img width="2025" height="1059" alt="image" src="https://github.com/user-attachments/assets/88a7a9cc-f2ab-4abd-9a15-fde04adedd82" />

<video src="https://github.com/user-attachments/assets/05e6675a-0448-4e45-96c8-77123ea5a939" width="1200" height="900" controls></video>

<br>

The next series of updates added further map details, including a bridge, house, and multiple types of trees. These more complex geometries were implemented as subclasses of the *Shape* superclass, each with its own `make_shape` method.

<br>
<video src="https://github.com/user-attachments/assets/b6489036-77bf-479e-9bb4-740966cafb05" width="1200" height="900" controls></video>
<br>

To introduce dynamic behavior into the map, a boat object was created with a `move` method that performs translaation along the z-axis. Similar to the camera movement system, the boat was assigned a fixed speed value, which was multiplied by the frame's detla time to compute the translation disatnce - ensuring consistent movement speed regardless of framerate.

<br>
<video src="https://github.com/user-attachments/assets/0de527e5-ab02-4951-b638-21b2f3653ded" width="1200" height="900" controls></video>
<br>

The most ambitious geometry in the map was an *Airplane* object, constructed using a combination of rectangular prisms, triangles, quadrilaterals, pyrmaids, and a new class for an octogonal prism (used to approximate a cylinder). The following screenshot shows the underlying triangular mesh on the left, the final geometry on the right (including texture mapping, which is described later), and the source code used to build up this shape. 

<br>

<img width="3238" height="2160" alt="Plane_Components_Illustration" src="https://github.com/user-attachments/assets/1729cf4f-98f9-42c7-8f29-9888fe686c81" />

<br><br>

One airplane is parked on the ground next to newly added *Hangar* and *Runway* objects. A *Prop* object, representing a propeller, is seen rotating on this airplane - achieved through appopriate translation and rotation relative to both the world origin and airplane's position. Another airplane is flying above the islands, animated by rotation around a shifted y-axis to create an orbiting motion.

<br>
<video src="https://github.com/user-attachments/assets/a3e11884-cf88-4ccd-aa84-a259f39dad3c" width="1200" height="900" controls></video>
<br><br>

An important next update was decoupling the render resolution from the window resolution, achieved using the `SDL_LOGICAL_PRESENTATION_LETTERBOX` option. This allowed the window to be resized without compromising performance on high-resolution screens, while maintaining the correct aspect ratio.

Several function keys were mapped to enable dynamic modification of the field of view, render resolution, render mode, and windowed or fullscreen display mode. Toggling these options also triggered a temporary text box that displayed the current settings, along with frametime (in milliseconds) and framerate (in frames per second).

<br>

<img width="1926" height="1138" alt="image" src="https://github.com/user-attachments/assets/c7424907-e7c4-4fe8-96f7-eb9ced6e7bdd" />

<br><br>

The next major update to the engine was implementing texture mapping. A *Texture* class was defined to create an `SDL_Surface` object, loading a custom texture image. All textures were created by-hand using [*LibreSprite*](https://libresprite.github.io/#!/). The `SDL_ReadSurfacePixel` function was used to read the color value at a desired horizontal $u$ and vertical $v$ coordinate, with wrapping if necessary. The following sample texture shows the $(u, v)$ coordinates for the four corners, and how the red triangle would map to the left side of this texture:

<br>

<img width="1600" height="877" alt="image" src="https://github.com/user-attachments/assets/cb8badc4-f573-4653-b99c-6e3f2051c122" />

<br>

After the desired $(u, v)$ coordinates have been assigned to each vertex $0$, $1$, $2$ of a given triangle, the interpolated $(u, v)$ coordinates for a given point on the triangle is achieved using the previously computed Barycentric coordinates and perpective correction:

$$u' = \alpha \left({u_0} \over {w_0}\right) + \beta \left({u_1} \over {w_1}\right) + \gamma \left({u_2} \over {w_2}\right)$$
$$v' = \alpha \left({v_0} \over {w_0}\right) + \beta \left({v_1} \over {w_1}\right) + \gamma \left({v_2} \over {w_2}\right)$$

$$\left({1} \over {w} \right)' = \alpha \left({1} \over {w_0}\right) + \beta \left({1} \over {w_1}\right) + \gamma \left({1} \over {w_2}\right)$$

$$w' = \left[\left({1} \over {w} \right)'\right]^{-1}$$

$$u'_{corrected} = u' * w'$$
$$v'_{corrected} = v' * w'$$

These computations were optimized using vectorized math, leveraging the fact that the relevant barycentric coordinates were already stored in distinct vectors. Several updates were also made to the clipping algorithm to compute new $(u, v)$ coordinates for the clipped triangles. Additionally, each *Shape* subclass required specific logic to map textures in a way that allowed for flexible input—either by specifying coordinates directly or by providing scaling factors.

Another major performance improvement involved parallelizing the triangle drawing process. Previously, each pixel was processed in a traditional `for` loop: the z-depth was checked, the color was computed, and `SDL_RenderPoint` was called to draw the pixel to the renderer. This approach proved to be a significant bottleneck.

In the new parallel `for` loop, the same computations are performed, but instead of rendering pixels directly, their colors are written to a grid representing a frame buffer. After all surfaces are processed, this buffer is rendered to the screen using `SDL_RenderTexture`. This change yielded a 5x to 6x performance increase in many cases, enabling fully textured surfaces to render at an acceptable framerate.

<br>
<video src="https://github.com/user-attachments/assets/14342580-a99f-4822-ae97-c130a4e17662" width="1920" height="1080" controls></video>
<br><br>

To implement sounds into the game world, a *Sound* class was created to store world position and properties such as maximum gain, minimum distance for full gain, and maximum distance before silence. The `SDL_mixer` audio library was used to load custom sound files and perform mixing, adjusting volume based on distance criteria. A logarithmic falloff was applied when the sound source was between the minimum and maximum distances relative to the player. Sounds for the flying airplane and sailing boat were moved in world space using appropriate rotation matrices and translation increments, matching the behavior of their corresponding geometric objects.

The penultimate update to the engine was the implementation of a day-night cycle. To simulate this effect, sun and moon objects were created using textured octagonal prisms and animated in orbital paths through rotational transformations. The background color was interpolated between sky blue, salmon, and dark blue based on the rotation angle, creating a smooth transition that reflects the time of day.

<br>
<video src="https://github.com/user-attachments/assets/04213d9e-49dc-444f-9459-dc4933d7e412" width="1920" height="1080" controls></video>
<br><br>

The final update to the engine introduced diffuse lighting to simulate illumination from the sun and moon. The lighting model is based on Lambert's cosine law, where the brightness of a surface depends on the cosine of the angle between the surface's normal vector $N$ and the vector $L$ pointing from the center of the surface toward the light source:

$$\text{cos}(\theta) = N \cdot L$$

A *Light* class was used to store light position, brightness factors, and a set of height thresholds for interpolating between those factors. These values were used to produce varying levels of contrast depending on the height of the light source - simulating more uniform brightness of mid-day versus the stronger constrast seen at dawn and dusk. 

The light sources were positioned at the same angles as the sun and moon objects, but placed at a much greater distance. This extra distance ensured that multiple surfaces on the same plane received consistent lighting, since sunlight and moonlight are effectively directional and originate from an infinite distance. The following sketch illustrates this behavior: the green light object produces surface-to-light vectors with similar angles, resulting in consistent illumination across these surfaces. In contrast, the closer red light source does not, as the angles vary between surfaces which leads to uneven lighting.

<br>

<img width="1991" height="705" alt="image" src="https://github.com/user-attachments/assets/b6b555d4-b640-49fe-8e6f-a3d1c78f90ea" />

<br><br>

The following timelapses showcase how the lighting model responds to changes in light position and angle:

<br>
<video src="https://github.com/user-attachments/assets/5d354614-5838-4d2b-81a3-3a8e5ebe2e44" width="1920" height="1080" controls></video>
<br>
<video src="https://github.com/user-attachments/assets/739680aa-cd4b-4d47-99f6-e52414af68ea" width="1920" height="1080" controls></video>
<br><br>

## Compilation

The following batch file was used for compilation. The `cppbuild` command within the project's `tasks.json` file was modified to reference this batch file.

```
@echo off
set SOURCE_FILE=%1
set EXECUTABLE_NAME=%~n1.exe

REM --- Define build settings ---
REM Set paths to your SDL3 installation
set SDL_INCLUDE_DIR=C:\Projects\raster-engine\SDL\include
set SDL_LIB_DIR=C:\Projects\raster-engine\SDL3-x64\lib

REM Set paths for Eigen
set EIGEN_INCLUDE_DIR=C:\Projects\raster-engine\eigen-3.4.1

REM Specify the C++ standard
set CPP_STANDARD=-std=c++23

REM Common compile flags for object files
set CXXFLAGS=-g %CPP_STANDARD% -O3 -DNDEBUG -march=native -I"%SDL_INCLUDE_DIR%" -I"%EIGEN_INCLUDE_DIR%"
set LDFLAGS=-L"%SDL_LIB_DIR%" -lmingw32 -lSDL3 -lSDL3_image -lSDL3_mixer -mwindows

REM --- Compilation ---
echo Compiling object files...

REM List of all source files
set SOURCES=%SOURCE_FILE% lighting.cpp clipping.cpp point.cpp renderer.cpp surface.cpp input.cpp map.cpp shape.cpp rectprism.cpp rect.cpp pyramid.cpp quad.cpp tree.cpp house.cpp bridge.cpp boat.cpp airplane.cpp octprism.cpp runway.cpp hangar.cpp prop.cpp texture.cpp map_textures.cpp sound.cpp map_sounds.cpp light.cpp

REM Compile each source file to an object file
for %%f in (%SOURCES%) do (
    echo Compiling %%f...
    g++ -c "%%f" %CXXFLAGS%
    if !errorlevel! neq 0 (
        echo.
        echo --- Compilation of %%f failed! ---
        goto :end
    )
)

REM --- Linking ---
echo.
echo Linking executable...

REM List all generated object files for linking
set OBJECTS=%~n1.o lighting.o clipping.o point.o surface.o renderer.o input.o map.o shape.o rectprism.o rect.o pyramid.o quad.o tree.o house.o bridge.o boat.o airplane.o octprism.o runway.o hangar.o prop.o texture.o map_textures.o sound.o map_sounds.o light.o

REM Link all object files to create the executable
g++ %OBJECTS% -o "%EXECUTABLE_NAME%" %CXXFLAGS% %LDFLAGS%

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo --- Linking failed! ---
) else (
    echo.
    echo --- Compilation and linking successful! ---
)

:end
```

## Features Wishlist

This project was extremely rewarding and deepened my understanding of the graphics rendering pipeline at a fundamental level, while also strengthening my C++ skills.

With additional time, I would implement the following features:

1. **Further performance optimizations** to improve playability on lower-end systems
2. **Additional light sources**, such as runway lights or exterior house lamps
3. **Real-time shadow calculations** for dynamic lighting realism
4. **External file storage** for map asset definitions to improve modularity and scalability
5. **A map editor** for streamlined world building and asset placement
6. **Directional sound behavior** and **Doppler effect** for immersive audio
7. **Interactive gameplay mechanics** to enhance user engagement
8. **Player collision detection** with map geometry for physical realism
9. **Real-time physics simulations** to support dynamic interactions and environmental effects
