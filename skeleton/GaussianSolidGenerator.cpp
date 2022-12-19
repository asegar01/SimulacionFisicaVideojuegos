#include "GaussianSolidGenerator.h"

PxRigidDynamic* GaussianSolidGenerator::generateSolids() 
{
	random_device rnd;
    std::mt19937 gen(rnd());

    // Velocidad
    normal_distribution<float> std_dis_velX(_mean_vel.x, std_dev_vel.x);
    normal_distribution<float> std_dis_velY(_mean_vel.y, std_dev_vel.y);
    normal_distribution<float> std_dis_velZ(_mean_vel.z, std_dev_vel.z);

    // Rotacion
    uniform_real_distribution<float> const std_dis_rotX(0.0, 359.0);
    uniform_real_distribution<float> const std_dis_rotY(0.0, 359.0);
    uniform_real_distribution<float> const std_dis_rotZ(0.0, 359.0);

    std::uniform_real_distribution<double> const materialX(0.0, 1.0);
    std::uniform_real_distribution<double> const materialY(0.0, 1.0);
    std::uniform_real_distribution<double> const materialZ(0.0, 1.0);

    // Creacion del solido
    PxRigidDynamic* solid = _model->clone();

    if (solid != nullptr) 
    {
        // Creacion del material del solido
        PxMaterial* material = _gPhysics->createMaterial(materialX(rnd), materialY(rnd), materialZ(rnd)); // creacion del material
        PxShape* shape;

        // Material shape asociado al solido
        switch (getType())
        {
        case RBSPHERE: shape = PxRigidActorExt::createExclusiveShape(*solid, PxSphereGeometry(5.0), *material); break;
        case RBBOX: shape = PxRigidActorExt::createExclusiveShape(*solid, PxBoxGeometry(5.0, 5.0, 5.0), *material); break;
        default: break;
        }

        PxRigidBodyExt::updateMassAndInertia(*solid, rand() % 1000 + 1); // Densidad del solido (calcula la masa y el tensor de inercia)
        solid->setLinearVelocity({ std_dis_velX(rnd), std_dis_velY(rnd), std_dis_velZ(rnd) });
        solid->setAngularVelocity({ std_dis_rotX(rnd), std_dis_rotY(rnd), std_dis_rotZ(rnd) });

        auto itemSolid = new RenderItem(shape, solid, { 0.13, 0.7, 0.67, 1.0 });
    }

    return solid;
}