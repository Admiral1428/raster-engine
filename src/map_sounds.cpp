#include "map_sounds.hpp"

unordered_map<string, Sound> SOUNDS;

void load_sounds(MIX_Mixer &mixer)
{
    SOUNDS.emplace("waterfall", Sound("../assets/sounds/waterfall.wav", Eigen::Vector3f(25.0f, -2.0f, -14.5),
                                      1.0f, 2.0f, 30.0f, mixer));
    SOUNDS.emplace("river", Sound("../assets/sounds/river.wav", Eigen::Vector3f(-15.0f, -2.0f, -10.0f),
                                  1.0f, 2.0f, 45.0f, mixer));
    SOUNDS.emplace("airplane_idle", Sound("../assets/sounds/airplane_idle.wav", Eigen::Vector3f(-5.0f, -1.25f, 18.5f),
                                          0.5f, 1.0f, 15.0f, mixer));
    SOUNDS.emplace("airplane_flying", Sound("../assets/sounds/airplane_flying.wav", Eigen::Vector3f(-30.0f, 20.0f, 0.0f),
                                            1.0f, 1.0f, 50.0f, mixer));
    SOUNDS.emplace("boat", Sound("../assets/sounds/boat.wav", Eigen::Vector3f(-32.0f, -3.0f, 60.0f),
                                 1.0f, 1.0f, 20.0f, mixer));
}

void start_sounds()
{
    for (auto &snd : SOUNDS)
    {
        snd.second.start_sound();
    }
}

void set_sound_gains(const Eigen::Vector3f &eye)
{
    for (auto &snd : SOUNDS)
    {
        snd.second.set_gain(eye);
    }
}

void move_sound(const string sound_name, const float &dx, const float &dy, const float &dz,
                const float &roll, const float &pitch, const float &yaw, const string &order)
{
    auto it = SOUNDS.find(sound_name);
    if (it != SOUNDS.end())
    {
        Sound &sound_object = it->second;
        sound_object.move(dx, dy, dz, roll, pitch, yaw, order);
    }
}

void destroy_sounds()
{
    for (auto &snd : SOUNDS)
    {
        SOUNDS.erase(snd.first);
    }
}