#include "GaussianParticleGenerator.h"

list<Particle*> GaussianParticleGenerator::generateParticles()
{
    list<Particle*> particles;

    random_device rnd;

    normal_distribution<float> std_dis_posX(_mean_pos.x, std_dev_pos.x);
    normal_distribution<float> std_dis_posY(_mean_pos.y, std_dev_pos.y);
    normal_distribution<float> std_dis_posZ(_mean_pos.z, std_dev_pos.z);

    normal_distribution<float> std_dis_velX(_mean_vel.x, std_dev_vel.x);
    normal_distribution<float> std_dis_velY(_mean_vel.y, std_dev_vel.y);
    normal_distribution<float> std_dis_velZ(_mean_vel.z, std_dev_vel.z);

    uniform_real_distribution<double> std_dis_time(std_dev_t - std_dev_t / 2, std_dev_t + std_dev_t / 2);

    for (size_t i = 0; i < _num_particles; ++i) 
    {
        Particle* p = _model->clone();

        if (p != nullptr) 
        {
            p->setPosition({ std_dis_posX(rnd), std_dis_posY(rnd), std_dis_posZ(rnd) });
            p->setVelocity({ std_dis_velX(rnd), std_dis_velY(rnd), std_dis_velZ(rnd) });

            p->setRemainingTime(std_dis_time(rnd));

            particles.push_back(p);
        }
    }

    return particles;
}
