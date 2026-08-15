// Macro implementations of min, max, and clamp

#ifndef CLAMP_H
#define CLAMP_H

#define Min(a, b) (((a) < (b)) ? (a) : (b))
#define Max(a, b) (((a) > (b)) ? (a) : (b))
#define Clamp(a, x, b) (((x) < (a)) ? (a) : ((b) < (x)) ? (b) \
                                                        : (x))

#endif // !CLAMP_H