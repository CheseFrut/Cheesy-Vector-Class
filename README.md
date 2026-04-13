# General Purpose Vectors
c++ library for game-engine vector calculations

This library provides a templated base vector class of arbitrary length and data type. 

It has been used to make a **`Vector2`**, **`Vector3`**, and **`Vector4`** type, along with `int`, `double`, `short` and `long` variants of each. These types are shown below

|         | `float`        | `double`       | `int`          | `long`         | `short`        |
| ------- | -------------- | -------------- | -------------- | -------------- | -------------- | 
| 2D      | **`Vector2`**  | **`Vector2D`** |  **`Vector2I`** | **`Vector2L`** | **`Vector2S`** |
| 3D      | **`Vector3`**  | **`Vector3D`** |   **`Vector3I`** |**`Vector3L`** | **`Vector3S`** |
| 4D      | **`Vector4`**  | **`Vector4D`** |   **`Vector4I`** |**`Vector4L`** | **`Vector4S`** |

| Number of <br>dimentions    | type   |
| --- | --------- |
| 4   | Colour    |
| 3   | ColourRGB |

```cpp
int main() {
    Vector3 foo(1, 2, 3); // floating point 3D Vector
    Vector2I bar(3, 4); // integer 2D Vector

    foo.x = bar.y; // foo = (4,2,3)
    foo += bar; // foo = (7,6,3)
}
```
The base class also gives the user freedom to, for example, union the first value with `x`.

The base class was also used to make a **`Colour`** and **`ColourRGB`** type (with 4 and 3 dimentions respectively).
```cpp
int main() {
    Colour foo = Vector::Forward; // Vector(0,0,1)
    ColourRGB bar = Colour(0.1, 1, 0);

    foo += bar; // foo = Colour(0.1,1,1,0)
}
```

Each of these types can also be explicitly converted to each other.

## Vector3 Examples
```cpp
#include "Vector3.h"
#include <iostream>

int main() {

    Vector3 foo(1,2,3);
    Vector3 bar(4,5);

    std::cout << foo <<       std::endl;
    std::cout << bar <<       std::endl;
    std::cout << foo + bar << std::endl;
    std::cout << foo - bar << std::endl;
    std::cout << foo * 2 <<   std::endl;
    std::cout << foo / 2 <<   std::endl;
}
```
#### Output
```console
(1, 2, 3)
(4, 5, 0)
(5, 7, 3)
(-3, -3, 3)
(2, 4, 6)
(0.5, 1, 1.5)
```
Check out [Vector3.h](includes/structs/Vector3.h) to see how a specialised vector struct is made using the base class, and feel free to use the specialised vector structs I have already made.

---
<sub> 
**TODO:** Show vector2 + Vector4 and some explicit conversions in the README 
</sub>
