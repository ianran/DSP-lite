# DSP-lite

DSP-lite is a standalone DSP module written in C++.
It is designed to require no dependencies, and should run
on any device that can compile C++ code.
The library makes use of templates to allow any type to be used for the filters.

Each file will place at the top what other files it depends on to be compiled individually.


Example usage:
```
int16_t gains[] = {1,1,1,1,1};
FIRFilter<int16_t> filter(gains, 5);

int16_t out;
while (true) {
    int16_t in = // Some input;
    out = filter.filter(in);
}
```
