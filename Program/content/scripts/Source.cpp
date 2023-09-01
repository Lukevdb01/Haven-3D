#include "Source.h"

void Source::OnCreate()
{
    
}

void Source::OnUpdate()
{
    // Check input actions in game logic
    if (inp_m->IsActionPressed("Jump")) {
        std::cout << "Jumped\n";
    }

    if (inp_m->IsActionPressed("Shoot")) {
        // Perform the shooting action
        std::cout << "Shooted\n";
    }

    if (inp_m->IsActionPressed("MoveForward")) {
        // Move the character forward
        std::cout << "Moved forward\n";
    }
}

void Source::OnDestroy()
{
}
