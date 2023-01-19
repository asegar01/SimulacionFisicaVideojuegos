#include "SolidDragGenerator.h"

void SolidDragGenerator::updateForceRB(PxRigidDynamic* solid, double t) 
{
	// Check that the solid has Finite Mass
	if (fabs(solid->getInvMass()) < 1e-10) return;

	// Compute the drag force
	Vector3 v = solid->getLinearVelocity();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;

	// Apply the drag force
	cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << endl;
	solid->addForce(dragF);
}
