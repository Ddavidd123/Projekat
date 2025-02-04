#ifndef SIMULACIJA_H_INCLUDED
#define SIMULACIJA_H_INCLUDED

//struktura za uslove puta
typedef struct {
    char *name;
    double friction_coefficient;
}Surface;

void simulate_no_abs(double initial_speed, double braking_force, Surface surface, double vehicle_mass);
void simulate_with_abs(double initial_speed, double braking_force, Surface surface, double vehicle_mass);

#endif // SIMULACIJA_H_INCLUDED
