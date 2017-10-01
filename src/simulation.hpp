//
// Created by Jack Purvis
//

#ifndef POSITIONBASEDDYNAMICS_SIMULATION_HPP
#define POSITIONBASEDDYNAMICS_SIMULATION_HPP

#include <GL/glew.h>
#include <camera.hpp>
#include <mesh.hpp>

class Simulation {

public:
    Simulation();
    ~Simulation();

    void reset();

    void update();
    void simulate(Mesh* mesh);
    void render();
    void renderGUI();

    // Variables
    int solverIterations = 10;
    float timeStep = 0.05f;
    float gravity = 0.981f;
    float windSpeed = 1.0f;
    float velocityDamping = 1.0f;
    float stretchFactor = 1.0f;
    float bendFactor = 1.0f;
    bool wireframe = false;

    // Camera variables
    float pitch, yaw, roll;

private:

    // Camera
    Camera* camera;

    // Objects
    vector<Mesh*> staticObjects;
    vector<Mesh*> simulatedObjects;

};

#endif //POSITIONBASEDDYNAMICS_SIMULATION_HPP
