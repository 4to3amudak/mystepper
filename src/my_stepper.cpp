#include "my_stepper.hpp"
#include <wiringPi.h>
#include <cmath>

using namespace std;

Stepper::Stepper(long spr, int st_p, int dir_p,
    double sd, double a, double j, double hr) :
    m_angle(0), rev_cnt(0), u_angle(0),
    step_per_rev(spr), handle_ratio(hr),
    st_pin(st_p), dir_pin(dir_p),
    speed_default(sd), accel(a), jerk(j)
{
    pinMode(st_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
}

void Stepper::_reduce_angle()   {
    long long diff = m_angle / 360.0;
    rev_cnt += diff;
    m_angle -= diff * 360.0;
    u_angle -= diff * 360.0;
    if(m_angle < 0) {
        m_angle += 360.0;
        u_angle += 360.0;
        rev_cnt--;
    } 
}

void Stepper::_make_step(unsigned int us)
{
    digitalWrite(st_pin, 1);
    delayMicroseconds(us);
    digitalWrite(st_pin, 0);
    delayMicroseconds(us);
}

void Stepper::_rotate_routine(long long steps, double speed)
{
    digitalWrite(dir_pin, ((steps<0)^(speed<0)) ? 1 : 0);
    speed = fabs(speed);
    steps = fabs(steps);
    double jerk_a = jerk;
    if(speed < jerk) jerk_a = speed;
    long long half = steps / 2;
    long long i, j;
    unsigned int vel;
    double sust = (handle_ratio * step_per_rev) / 360.0;
    long long dist_f_s = 
        fmin(sust * (speed * speed - jerk_a * jerk_a) / (2.0 * accel), half);
    vel = ceil(5e5 / (speed * sust));
    for(i = 1; i <= dist_f_s; ++i)  {
        vel = ceil(5e5 / (sust * 
            sqrt((2.0*accel*(double(i) / sust))+(jerk_a * jerk_a))));
        _make_step(vel);
    }
    for(j = i--; j<=steps-i; ++j)  {
        _make_step(vel);
    }
    for(; j<=steps; ++j)    {
        vel = ceil(5e5 / (sust *
            sqrt((2.0*accel*(double(steps - j + 1) / sust))+(jerk_a * jerk_a))));
        _make_step(vel);
    }
}

void Stepper::rotate_rel(double angle, double speed)
{
    m_angle += angle;
    long long steps = (handle_ratio * step_per_rev *
        (m_angle - u_angle)) / 360;
    _rotate_routine(steps, speed);
    u_angle += 360.0 * double(steps) /
        (handle_ratio * step_per_rev);
    _reduce_angle();
}

void Stepper::rotate_to_ang(double angle, double speed)
{
    if(angle < 0 || angle > 360) return;
    rotate_rel(angle - u_angle, speed);
}

void Stepper::rotate_full_rel(int revs, double speed)
{
    rotate_rel(360.0 * revs, speed);
}
