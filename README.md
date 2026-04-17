# General Purpose Vectors
c++ library for game-engine vector calculations

This library provides a templated base vector class of arbitrary length and data type, and some derived types.

## Included Types

The base class has been used to make a **`Vector2`**, **`Vector3`**, and **`Vector4`** type, along with `int`, `double`, `short` and `long` variants of each. 

|  dim  | `float`        | `double`       | `int`          | `long`         | `short`        |
| :---: | -------------- | -------------- | -------------- | -------------- | -------------- | 
|   2   | **`Vector2`**  | **`Vector2D`** | **`Vector2I`** | **`Vector2L`** | **`Vector2S`** |
|   3   | **`Vector3`**  | **`Vector3D`** | **`Vector3I`** | **`Vector3L`** | **`Vector3S`** |
|   4   | **`Vector4`**  | **`Vector4D`** | **`Vector4I`** | **`Vector4L`** | **`Vector4S`** |

There is also a **`Colour`** and **`ColourRGB`** type.

|  dim  | type            |
| :---: | :-------------- |
|   4   | **`Colour`**    |
|   3   | **`ColourRGB`** |

Any of these types listed above can be arbitrarily converted to each other, if not implicitly then explicitly.

## Examples
### Memory Structure
The base class gives the user freedom to `union` elements in its data array with other tokens. The **`Vector3`** type stores it's data with the type `std::array<float, 3> data` and is unioned with `struct { float x, y, z }`.
```cpp
int main() {
    Vector3 foo;          // foo = Vector3(0,0,0)
    Vector3.x = 1;        // foo = Vector3(1,0,0)
    Vector3.data[0] = 2;  // foo = Vector3(2,0,0)
    Vector3[0] = 3;       // foo = Vector3(3,0,0)
}
```

### Inbuilt Vector Constants
Each Vector type has a direction constant in each cardinal direction. Each Vector type also has 
```cpp
int main() {
    Vector2I foo = Vector2I::Left;  // foo = Vector2I(-1,0)
    foo = Vector2I::Up;  // foo = Vector2I(0,1)
    foo = Vector2I::Zero;  // foo = Vector2I(0,0)

    Vector4  bar = Vector4::Kata;  // bar = Vector4(0,0,0,-1)
    bar = Vector4::One;  // bar = Vector4(1,1,1,1)
}
```

### Implicit Conversions
When performing arithmetic operations, conversions are done implicitly.
```cpp
int main() {
    Colour foo = Vector3::One * 2;  // foo = Colour(2, 2, 2, 0)
    ColourRGB bar(0.1, 1, 0);  // bar = ColourRGB(0.1, 1, 0)

    foo -= bar; // foo = Colour(1.9, 1, 2, 0)
}
```

### Explicit Conversions
Each of these types can also be explicitly converted to each other.
```cpp
int main() {
    Vector3 foo(1, 2, 3);
    Vector2 bar(3, 4);
    bar = (Vector2)foo; // bar = Vector2(1,2)
}
```

> [!CAUTION]
> You can add or subtract any vector type from any other, and the return type will always be the one with the largest dimentions. At the moment this leads to **IMPLICIT** data loss, as the operation **`Vector2`**` + `**`Vector4I`** will return as a **`Vector4I`** type, which shruncates the data of the **`Vector2`**.

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

## TODO
- [ ] Use `std::common_type` to ensure safe conversions when performing arithmetic operations with Vectors of different arithmetic types.
- [ ] Make **`Colour`** and **`ColourRGB`** types their own derived classes from the base class (they are currently just renamed **`Vector4`** and **`Vector3`** types), and replace **`Colour::Zero`** and **`Colour::One`** with **`Colour::Black`** and **`Colour::White`** respectively.
