#include <drakon/scene>

drakon::scene::Scene::Scene(const Uint8 _red, const Uint8 _green,
                            const Uint8 _blue, const Uint8 _alpha)
    : red(_red), green(_green), blue(_blue), alpha(_alpha) {}

drakon::scene::Scene::~Scene() {}
