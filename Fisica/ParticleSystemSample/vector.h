#ifndef	VECTOR_HEADER_H
#define VECTOR_HEADER_H
//-----------------------------------------------------------------------------
struct tVector { float x, y; };
inline tVector  vmake (float x, float y) { tVector r; r.x = x; r.y = y; return r; }
inline tVector  vadd  (tVector v1, tVector v2) { return vmake(v1.x + v2.x, v1.y + v2.y); }
inline tVector  vsub  (tVector v1, tVector v2) { return vmake(v1.x - v2.x, v1.y - v2.y); }
inline tVector  vscale(tVector v, float f)  { return vmake(v.x * f, v.y * f); }
inline float vlen2 (tVector v)           { return v.x * v.x + v.y * v.y; }
inline float vlen  (tVector v)           { return (float)sqrt(vlen2(v)); }
inline float vdot  (tVector v1, tVector v2) { return v1.x * v2.x + v1.y * v2.y; }
inline tVector  vunit (float angle)      { return vmake((float)cos(angle), (float)sin(angle)); }

#endif