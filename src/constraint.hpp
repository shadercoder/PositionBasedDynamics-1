//
// Created by Jack Purvis
//

#ifndef POSITIONBASEDDYNAMICS_CONSTRAINT_HPP
#define POSITIONBASEDDYNAMICS_CONSTRAINT_HPP

#include <vector>
#include <Eigen>
#include <mesh.hpp>
#include <scene.hpp>

using namespace std;
using namespace Eigen;

// Forward declaration
class Mesh;
struct Configuration;

struct Params {
    int solverIterations;
    float stretchFactor;
    float bendFactor;
};

class Constraint {

public:
    Constraint(Mesh* mesh, int cardinality) :
            mesh(mesh), cardinality(cardinality) {}
    virtual void preCompute() {}
    virtual void project(Configuration* configuration, Params params) {}

    int cardinality;
    vector<int> indices;
    Mesh* mesh;
    MatrixXf coefficients;

};

class FixedConstraint : public Constraint {

public:
    FixedConstraint(Mesh* mesh, int cardinality, Vector3f target) :
            Constraint(mesh, cardinality), target(target) {}
    void project(Configuration* configuration, Params params);

    Vector3f target;

};

class DistanceConstraint : public Constraint {

public:
    DistanceConstraint(Mesh* mesh, int cardinality, float distance) :
            Constraint(mesh, cardinality), distance(distance) {}
    void preCompute();
    void project(Configuration* configuration, Params params);

    float distance;

};

class BendConstraint : public Constraint {

public:
    BendConstraint(Mesh* mesh, int cardinality, float angle) :
            Constraint(mesh, cardinality), angle(angle) {}
    void project(Configuration* configuration, Params params);

    float angle;

};

class CollisionConstraint : public Constraint {

public:
    CollisionConstraint(Mesh* mesh, int cardinality, Vector3f normal) :
            Constraint(mesh, cardinality), normal(normal) {}
    virtual void project(Configuration* configuration, Params params) {}

    Vector3f normal;

};

class StaticCollisionConstraint : public CollisionConstraint {

public:
    StaticCollisionConstraint(Mesh* mesh, int cardinality, Vector3f normal, Vector3f position) :
        CollisionConstraint(mesh, cardinality, normal), position(position) {}
    void project(Configuration* configuration, Params params);

    Vector3f position;
};

class TriangleCollisionConstraint : public CollisionConstraint {

public:
    TriangleCollisionConstraint(Mesh* mesh, int cardinality, Vector3f normal, float height) :
        CollisionConstraint(mesh, cardinality, normal), height(height) {}
    void project(Configuration* configuration, Params params);

    float height;

};

// Constraint building
void buildEdgeConstraints(Configuration* configuration, Mesh* mesh);
void buildBendConstraints(Configuration* configuration, Mesh* mesh);
FixedConstraint* buildFixedConstraint(Mesh* mesh, int index, Vector3f target);
DistanceConstraint* buildDistanceConstraint(Mesh* mesh, int indexA, int indexB, float distance);
BendConstraint* buildBendConstraint(Mesh* mesh, int indexA, int indexB, int indexC, int indexD, float angle);
StaticCollisionConstraint* buildStaticCollisionConstraint(Mesh* mesh, int index, Vector3f normal, Vector3f position);
TriangleCollisionConstraint* buildTriangleCollisionConstraint(Mesh *mesh, int vertexIndex, Vector3f normal, float height, int indexA, int indexB, int indexC);

#endif //POSITIONBASEDDYNAMICS_CONSTRAINT_HPP
