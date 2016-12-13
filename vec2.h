
#ifndef VEC
#define VEC
#define PI 3.141592654
class vec2
{
      public:
             double xPos, yPos;
             const double zPos;
             double boxRadius;
			 vec2() : zPos(0) {};
			 enum tType{GRASS, FENCE};
		     tType TerrainType;
			 vec2 operator= (vec2);
			 vec2 operator= (int);
};
#endif
