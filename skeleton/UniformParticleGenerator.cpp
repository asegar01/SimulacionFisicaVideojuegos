#include "UniformParticleGenerator.h"

list<Particle*> UniformParticleGenerator::generateParticles()
{
    list<Particle*> particles;

    random_device rnd;

    uniform_real_distribution<float> const std_dis_posX(_pos.x - _posWidth.x, _pos.x + _posWidth.x);
    uniform_real_distribution<float> const std_dis_posY(_pos.y - _posWidth.y, _pos.y + _posWidth.y);
    uniform_real_distribution<float> const std_dis_posZ(_pos.z - _posWidth.z, _pos.z + _posWidth.z);

    uniform_real_distribution<float> const std_dis_velX(_vel.x - _velWidth.x, _vel.x + _velWidth.x);
    uniform_real_distribution<float> const std_dis_velY(_vel.y - _velWidth.y, _vel.y + _velWidth.y);
    uniform_real_distribution<float> const std_dis_velZ(_vel.z - _velWidth.z, _vel.z + _velWidth.z);

    for (size_t i = 0; i < _numParticles; ++i)
    {
        Particle* p = _model->clone();

        if (p != nullptr)
        {
            p->setPosition({ std_dis_posX(rnd), std_dis_posY(rnd), std_dis_posZ(rnd) });
            p->setVelocity({ std_dis_velX(rnd), std_dis_velY(rnd), std_dis_velZ(rnd) });

            particles.push_back(p);
        }
    }

    return particles;
}