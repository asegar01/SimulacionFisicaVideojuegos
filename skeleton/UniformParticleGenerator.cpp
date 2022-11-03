#include "UniformParticleGenerator.h"

list<Particle*> UniformParticleGenerator::generateParticles() 
{
    list<Particle*> particles;

    random_device rnd;

    uniform_real_distribution<float> const std_dis_posX(_mean_pos.x - _pos_width.x, _mean_pos.x + _pos_width.x);
    uniform_real_distribution<float> const std_dis_posY(_mean_pos.y - _pos_width.y, _mean_pos.y + _pos_width.y);
    uniform_real_distribution<float> const std_dis_posZ(_mean_pos.z - _pos_width.z, _mean_pos.z + _pos_width.z);

    uniform_real_distribution<float> const std_dis_velX(_mean_vel.x - _vel_width.x, _mean_vel.x + _vel_width.x);
    uniform_real_distribution<float> const std_dis_velY(_mean_vel.y - _vel_width.y, _mean_vel.y + _vel_width.y);
    uniform_real_distribution<float> const std_dis_velZ(_mean_vel.z - _vel_width.z, _mean_vel.z + _vel_width.z);

    for (size_t i = 0; i < _num_particles; ++i) 
    {
        Particle* p = _model->clone();

        if (p != nullptr) 
        {
            p->setPosition({ std_dis_posX(rnd), std_dis_posY(rnd), std_dis_posZ(rnd) });
            p->setVelocity({ std_dis_velX(rnd), std_dis_velY(rnd), std_dis_velZ(rnd) });

            p->setRemainingTime(5);

            particles.push_back(p);
        }
    }

    return particles;
}