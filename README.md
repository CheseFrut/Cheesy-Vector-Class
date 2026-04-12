# General Purpose Vectors
c++ library for game-engine vector calculations

This library provides a templated vector class of arbitrary length and type. 

It has been used to make a Vector2, Vector3, and Vector4 type, along with integer, short, and double variants of each.

```cpp
{
    Vector3 foo(1, 2, 3);
    Vector2I bar(3, 4);

    foo.x = bar.y; // 4
}
```
It has also been used to make a Colour and ColourRGB type. Colour has 4 dimensions and ColourRGB has 3.
```cpp
{
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

---
TODO: Show vector2 + Vector4 and some explicit conversions in the README
