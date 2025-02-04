#include <stdio.h>
#include <assert.h>

#include "simulacija.h"


void test_simulate_no_abs() {
    Surface test_surface = {"Suv asfalt",0.9}; //testna podloga
    double initial_speed = 100.0;
    double braking_force = 1500.0;
    double vehicle_mass = 1200.0;

    //Ocekivani rezultati
    double expected_stopping_distance = 111.11; //ocekivani put
    double expected_stopping_time = 4.44; //ocekivano vreme

    //poziv Funkcije
    simulate_no_abs(initial_speed,braking_force,test_surface,vehicle_mass);

    assert(expected_stopping_distance-5.0<0); //tolerancija od pet metra
    assert(expected_stopping_time - 0.5 < 0);  // Tolerancija od 0.5 sekundi
    printf("Test simulate_no_abs je prosao.\n");
}

void test_simulate_with_abs()
{
    Surface test_surface = {"Mokar asfalt", 0.5};

    double initial_speed = 50.0;
    double braking_force = 1000.0;
    double vehicle_mass = 1000.0;

    // Očekivani rezultati
    double expected_stopping_distance = 40.0;
    double expected_stopping_time = 3.5;


    //poziv funkcije
    simulate_with_abs(initial_speed, braking_force, test_surface, vehicle_mass);

    assert(expected_stopping_distance - 5.0 < 0);  // Tolerancija od 5 metara
    assert(expected_stopping_time - 0.5 < 0);  // Tolerancija od 0.5 sekundi
    printf("Test simulate_with_abs je prosao.\n");
}

