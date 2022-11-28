#include <iostream>
#include <vector>
#include <cmath>

class Particle;

class SystemParticles {
    std::vector <Particle> system;
    static float time;

public:
    explicit SystemParticles(int numberParticles) {
        for (int i = 0; i < numberParticles; ++i)
            system.emplace_back();
    }

    void update();

    static float getTime(){
        return time;
    }

    std::vector<Particle> getSys() {
        return system;
    }

    ~SystemParticles() = default;

};

float SystemParticles::time = 0.1;

class Particle {
    float x0;
    float y0;
    float velocity;
    float mass;

public:

    Particle(): x0(1), y0(1), velocity(0), mass(0) {}

    ~Particle() = default;

    ///updating the lifetime of a particle

    friend float SystemParticles::getTime();

    ///getters

    float getX() {
        x0 = x0*SystemParticles::getTime()/std::exp(SystemParticles::getTime());
        return x0;
    }

    float getY() {
        y0 = y0*SystemParticles::getTime()*SystemParticles::getTime()/std::exp(SystemParticles::getTime());
        return y0;
    }

    std::pair<float, float> getCoord() {
        return std::pair<float,float> (getX(), getY());
    }

    float getVelocity() const {
        return velocity;
    }

    ///setters

    void setX(float x) {
        x0 = x;
    }

    void setY(float y) {
        y0 = y;
    }

    void setVelocity(float v) {
        velocity = v;
    }

    void setMass(float m) {
        mass = m;
    }
};

void SystemParticles::update() {
    for (auto& item : system)
        std::cout << item.getX() << " " << item.getY() << std::endl;
    time+=0.1;
}

int main()
{
    SystemParticles sys(1);
    sys.getSys()[0].setVelocity(10);
    sys.getSys()[0].setMass(1);
    sys.getSys()[0].setX(1);
    sys.getSys()[0].setY(1);

    for (int i = 0; i < 10; ++i)
        sys.update();

    return 0;
}
