#include "Source.h"

void Source::OnCreate()
{

}

void Source::OnUpdate()
{
    // Check input actions in game logic
    if (inp_m->IsActionPressed(InputAction::Jump)) {
        std::cout << "Jumped\n";
    }

    if (inp_m->IsActionPressed(InputAction::Shoot)) {
        // Perform the shooting action
        std::cout << "Shooted\n";
    }

    if (inp_m->IsActionPressed(InputAction::MoveForward)) {
        // Move the character forward
        std::cout << "Moved forward\n";
    }
}

void Source::OnDestroy()
{
}
