# General Purpose Vectors
c++ library for game-engine vector calculations

This library takes the 

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
