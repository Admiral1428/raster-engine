#include "sound.hpp"

// implementation
// Sound::Sound() {}    // Default constructor

Sound::Sound(const string &_file, const Eigen::Vector3f &_p, const float &_max_gain,
             const float &_min_dist, const float &_max_dist, MIX_Mixer &_mixer)
    : file(_file), p(_p), max_gain(_max_gain), min_dist(_min_dist), max_dist(_max_dist), mixer(&_mixer)
{
    gain = 0.0f;
    audio = MIX_LoadAudio(mixer, file.c_str(), true);
    if (audio == NULL)
    {
        SDL_Log("Failed to load audio.");
    }

    track = MIX_CreateTrack(mixer);
    if (track == NULL)
    {
        SDL_Log("Failed to create track.");
    }

    // Reset max gain if specified value exceeds one
    if (max_gain > 1.0f)
    {
        max_gain = 1.0f;
    }
}

Sound::Sound(const Sound &s) : mixer(s.mixer)
{
    file = s.file;
    p = s.p;
    max_gain = s.max_gain;
    min_dist = s.min_dist;
    max_dist = s.max_dist;
    gain = s.gain;
    audio = s.audio;
    track = s.track;

    // Deep copy: Create new audio and track resources
    audio = MIX_LoadAudio(mixer, file.c_str(), true);
    if (audio == NULL)
    {
        SDL_Log("Failed to load audio.");
    }

    track = MIX_CreateTrack(mixer);
    if (track == NULL)
    {
        SDL_Log("Failed to create track.");
    }
}

Sound::~Sound()
{
    if (track)
    {
        MIX_DestroyTrack(track);
    }
    if (audio)
    {
        MIX_DestroyAudio(audio);
    }
}

Sound &Sound::operator=(const Sound &s)
{
    if (this == &s)
    {
        return *this;
    }

    if (track)
    {
        MIX_DestroyTrack(track);
    }
    if (audio)
    {
        MIX_DestroyAudio(audio);
    }

    // Deep copy
    file = s.file;
    p = s.p;
    max_gain = s.max_gain;
    min_dist = s.min_dist;
    max_dist = s.max_dist;
    gain = s.gain;
    mixer = s.mixer; // mixer is a reference, so it's fine

    audio = MIX_LoadAudio(mixer, file.c_str(), true);
    if (audio == NULL)
    {
        SDL_Log("Failed to load audio during assignment: %s", SDL_GetError());
    }

    track = MIX_CreateTrack(mixer);
    if (track == NULL)
    {
        SDL_Log("Failed to create track during assignment: %s", SDL_GetError());
    }

    return *this;
}

void Sound::start_sound()
{
    // Set playback loop to infinite
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);

    MIX_SetTrackAudio(track, audio);
    MIX_PlayTrack(track, props);
    MIX_SetTrackGain(track, 0.0f); // start at zero gain

    SDL_DestroyProperties(props);
}

// Calculate and set gain based on the distance between the sound and the player
void Sound::set_gain(const Eigen::Vector3f &eye)
{
    float dist = (p - eye).norm();

    if (dist <= min_dist)
    {
        gain = max_gain;
    }
    else if (dist >= max_dist)
    {
        gain = 0.0f;
    }
    else
    {
        // Logarithmic falloff
        float distance_ratio = dist / min_dist;
        gain = max_gain * (1.0f - (log10(distance_ratio) / log10(max_dist / min_dist)));
        if (gain < 0.0f)
        {
            gain = 0.0f;
        }
    }

    MIX_SetTrackGain(track, gain);
}

// Move location of sound in world space
void Sound::move(const float &dx, const float &dy, const float &dz,
                 const float &roll, const float &pitch, const float &yaw, const string &order)
{
    float roll_rad = roll * pi / 180.0f;
    float pitch_rad = pitch * pi / 180.0f;
    float yaw_rad = yaw * pi / 180.0f;

    float cos_roll = cos(roll_rad);
    float sin_roll = sin(roll_rad);
    float cos_pitch = cos(pitch_rad);
    float sin_pitch = sin(pitch_rad);
    float cos_yaw = cos(yaw_rad);
    float sin_yaw = sin(yaw_rad);

    // rotation about x-axis (roll)
    Eigen::Matrix3f mat_rx = Eigen::Matrix3f::Identity();
    mat_rx(1, 1) = cos_roll;
    mat_rx(1, 2) = -sin_roll;
    mat_rx(2, 1) = sin_roll;
    mat_rx(2, 2) = cos_roll;

    // rotation about y-axis (pitch)
    Eigen::Matrix3f mat_ry = Eigen::Matrix3f::Identity();
    mat_ry(0, 0) = cos_pitch;
    mat_ry(0, 2) = sin_pitch;
    mat_ry(2, 0) = -sin_pitch;
    mat_ry(2, 2) = cos_pitch;

    // rotation about z-axis (yaw)
    Eigen::Matrix3f mat_rz = Eigen::Matrix3f::Identity();
    mat_rz(0, 0) = cos_yaw;
    mat_rz(0, 1) = -sin_yaw;
    mat_rz(1, 0) = sin_yaw;
    mat_rz(1, 1) = cos_yaw;

    // combined rotation matrix
    Eigen::Matrix3f rot_matrix;

    if (order == "yaw-pitch-roll") // yaw, then pitch, then roll
    {
        rot_matrix = mat_rx * mat_ry * mat_rz;
    }
    else if (order == "yaw-roll-pitch")
    {
        rot_matrix = mat_ry * mat_rx * mat_rz;
    }
    else if (order == "pitch-yaw-roll")
    {
        rot_matrix = mat_rx * mat_rz * mat_ry;
    }
    else if (order == "pitch-roll-yaw")
    {
        rot_matrix = mat_rz * mat_rx * mat_ry;
    }
    else if (order == "roll-yaw-pitch")
    {
        rot_matrix = mat_ry * mat_rz * mat_rx;
    }
    else if (order == "roll-pitch-yaw")
    {
        rot_matrix = mat_rz * mat_ry * mat_rx;
    }
    else
    {
        throw invalid_argument("Invalid rotation sequence.");
    }

    p = rot_matrix * p;

    // Perform translation after rotation
    p(0) += dx;
    p(1) += dy;
    p(2) += dz;
}