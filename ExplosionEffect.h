#include <SFML/Graphics.hpp>
#include "EnergyEffect.h"
#include <Windows.h>
#include <gl/GL.h>

class Particle_ExplosionEffect : public Particle_EnergyEffect
{
public:
	Particle_ExplosionEffect();
	~Particle_ExplosionEffect();
	void randomizeExplosions(double xPos, double yPos);
	void updateEffect(double timePassed);
};