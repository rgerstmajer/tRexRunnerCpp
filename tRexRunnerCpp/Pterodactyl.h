#pragma once
#include "Obstacle.h"
class Pterodactyl :
    public Obstacle
{
public:
    Pterodactyl();

    void Draw();

    void Move();

    void Init();

    void Update();

    ~Pterodactyl();
};

