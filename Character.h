

class Character
{
protected:
    double position_x{};
    double position_y{};
    int lives{};
    double speed{};

public:
    virtual move();
};