#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>
#include <Eigen/Dense>
#include <vector>
#include <stdexcept>
#include <string>
#include <numbers>

using std::invalid_argument;
using std::log10;
using std::string;
using std::vector;
using std::numbers::pi;

// class defining a sound
class Sound
{
private:
    string file;
    Eigen::Vector3f p; // coordinates in world space
    float max_gain;
    float gain;
    float min_dist;
    float max_dist;
    MIX_Audio *audio;
    MIX_Track *track;
    MIX_Mixer *mixer;

public:
    // Sound();
    Sound(const string &_file, const Eigen::Vector3f &_p, const float &_max_gain,
          const float &_min_dist, const float &_max_dist, MIX_Mixer &_mixer);
    Sound(const Sound &);            // copy constructor
    ~Sound();                        // destructor
    Sound &operator=(const Sound &); // copy/assignment operator
    void start_sound();
    void set_gain(const Eigen::Vector3f &eye);
    void move(const float &dx, const float &dy, const float &dz,
              const float &roll, const float &pitch, const float &yaw, const string &order);
};

#endif