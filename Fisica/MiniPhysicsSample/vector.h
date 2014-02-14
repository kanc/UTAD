#ifndef	VECTOR_HEADER_H
#define VECTOR_HEADER_H
//-----------------------------------------------------------------------------
struct vec2 { float x, y; };
inline vec2  vmake (float x, float y) { vec2 r; r.x = x; r.y = y; return r; }
inline vec2  vadd  (vec2 v1, vec2 v2) { return vmake(v1.x + v2.x, v1.y + v2.y); }
inline vec2  vsub  (vec2 v1, vec2 v2) { return vmake(v1.x - v2.x, v1.y - v2.y); }
inline vec2  vscale(vec2 v, float f)  { return vmake(v.x * f, v.y * f); }
inline float vlen2 (vec2 v)           { return v.x * v.x + v.y * v.y; }
inline float vlen  (vec2 v)           { return (float)sqrt(vlen2(v)); }
inline float vdot  (vec2 v1, vec2 v2) { return v1.x * v2.x + v1.y * v2.y; }
inline vec2  vunit (float angle)      { return vmake((float)cos(angle), (float)sin(angle)); }

#endif