# raster-engine
*Raster Engine* is 3D graphics engine built from scratch using C++, employing CPU-based software rasterization. 

[![Raster Engine on YouTube](https://img.youtube.com/vi/_y8U2036gHo/0.jpg)](https://youtu.be/_y8U2036gHo)

The purpose of this project was to improve my C++ skills and to gain a fundamental understanding of 3D graphics principles. The [*SDL3 library*](https://github.com/libsdl-org/SDL/releases) was used to achieve basic window creation and pixel manipulation, but no other external libraries for graphical rendering were utilized. By coding each step of the rendering pipeline from the ground up, I was able to better grasp the mathematical principles which are the basis for modern graphics APIs which use hardware-accelerated techniques on today's powerful GPUs.

My goal was to create an engine which could render triangular surfaces at any position and orientation, account for surface intersection and depth, map textures to surfaces, and play basic sound effects in specific locations throughout the 3D space. Initially, I considered making a more primitive engine using ray-casting techniques, as seen in early 3D games such as *Hovertank 3-D (1991)*, *Catacomb 3-D (1992)* and *Wolfenstein 3D (1992)*. However ray-casting imposes limitations on map design and geometry, due to the inability to representing diagonal walls, sloped surfaces, or multiple vertical levels. Fewer limitations were present in "2.5D" engines used to power *Doom (1993)* and *Duke Nukem 3D (1995)*. But the engine for *Quake (1996)* had a both a software and hardware-based solution to represent its full 3D world and objects. This early level of "full 3D" fidelity without sprites is what I sought to achieve in my custom engine, excluding complex lighting calculations and gameplay mechanics.

After spending several weeks refreshing my knoweldge of C++ fundamentals, the first step was creating a basic window, drawing triangle vertices to this window, and drawing edges between these vertices using Bresenham's line algorithm:

<br>
<img width="960" height="540" alt="09-29-25_1800" src="https://github.com/user-attachments/assets/2fba9f00-90b3-4893-92c3-50760a9728b1" />
<br><br>

To represent a triangle in 3D space with vertices in any position and orientation, the next step required using a projection transformation matrix to convert these $x$, $y$, $z$ coordinates into 2D camera space. This is where I familiarized myself with the viewing frustrum, defined by clipping planes on six sides (near, far, left, right, top, and bottom), and the use of a 4th coordinate $w$ to enable a single set of matrix operations. By specifying the horizontal field of view, aspect ratio (*width* / *height*), near ($n$), and far ($f$) clipping planes, the projection transformation matrix could be built, and ultimately used to transform the homogeneous coordinates to normalized device coordinates:

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

<br>
<img width="1977" height="1060" alt="image" src="https://github.com/user-attachments/assets/52a5f79a-8a66-458e-ae20-af9c517c98db" />
<br><br>

These *ndc* points could then be rasterized into screen space using the render width and height:

$$r_x = (ndc(0) + 1) * 0.5 * \text{width}$$
$$r_y = (1 - (ndc(1) + 1) * 0.5) * \text{height}$$


The [*Eigen library*]((https://github.com/PX4/eigen)) was used for all matrix and vector math. Note that *Eigen* uses column-major layout in memory, so the layout of the projection transformation matrix may appear transposed compared to some literature sources. The resulting render of a basic cube is achieved below, assuming the camera *eye* is aligned with the $x-y$ plane, pointed along the $-z$ axis:

<br>
<img width="960" height="960" alt="10-01-25_1115" src="https://github.com/user-attachments/assets/d79be8a5-6659-4595-aced-f0c273826e08" />
<br><br>

This approach was still relying on Bresenham's line algorithm to draw edges between vertices. Initially, I attempted to use these calculated edges to determine which points were within the triangle, so that these surfaces could be filled. But this is when I realized the need to compute the z-depth of all points within the triangle to ensure intersections were handled correctly. This is where I transitioned to calculating Barycentric coordinates $\alpha$, $\beta$ and $\gamma$ for a point $r_p$, to determine if such a pixel was within the vertices $0$, $1$, and $2$ of the triangle:

$$v_0 = r_1 - r_0$$
$$v_1 = r_2 - r_0$$
$$v_2 = r_p - r_0$$

$$\text{denom} = (v_0 \cdot v_0) * (v_1 \cdot v_1) - (v_0 \cdot v_1) * (v_0 \cdot v_1)$$

$$\beta = {{(v_1 \cdot v_1) * (v_2 \cdot v_0) - (v_0 \cdot v_1) * (v_2 \cdot v_1)} \over {\text{denom}}}$$

$$\gamma = {{(v_0 \cdot v_0) * (v_2 \cdot v_1) - (v_0 \cdot v_1) * (v_2 \cdot v_0)} \over {\text{denom}}}$$

$$\alpha = 1 - \beta - \gamma$$

The pixels inside the triangle could be found by isolating which Barycentric coordinates were greater than zero (which in practice meant using a tolerance of $$-1 \times 10^{-3}$$). A z-depth buffer across all screen pixels was initialized to $1.0$ (far clipping plane), after which the *ndc* z-depth for the relevant Barycentric coordinates could be computed using interpolation with the homogeneous vertex points:

$$\left({{z} \over {w}}\right)_{ndc} = \alpha \left({{z'_0} \over {w'_0}}\right) +  \beta \left({{z'_1} \over {w'_1}}\right) +  \gamma \left({{z'_2} \over {w'_2}}\right) $$ 

By looping through each surface and rendering the pixels if their *z-ndc* depth was lower than the previous value at that pixel, the resulting cube shape was rendered as expected:

<br>
<img width="960" height="960" alt="10-02-25_1730" src="https://github.com/user-attachments/assets/e83bbfd0-b027-4bf6-b298-d0be2db073c3" />
<br><br>
