// Defines a zig-like try operator, where if a called function returns an error code, then this function returns -1.

#define try(expr) if ((expr) < 0) { return -1; }