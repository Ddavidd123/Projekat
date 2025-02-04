#include <stdio.h>
#include <stdlib.h>

//struktura za uslove puta
typedef struct {
    char *name;
    double friction_coefficient;
}Surface;

//Funkcija za izracunavanje kocenja bez ABS-a
void simulate_no_abs(double initial_speed, double braking_force,Surface surface,double vehicle_mass)
{
    //brzina u m/s
    double speed_mps = initial_speed*1000/3600;
    double friction = surface.friction_coefficient; //koeficijent treenja


    //Simulacija kocenja
    double deceleration = friction * 9.81; //usporenje
    double stopping_distance = (speed_mps*speed_mps) / (2 * deceleration); //Put kocenja
    double stopping_time = speed_mps / deceleration;

    //maksimalna sila trenja
    double maxFrictionForce = friction * vehicle_mass * 9.81;

    printf("[INFO] Pocetak simulacije kocenja bez ABS-a..\n");
    printf("Brzina: %.2f km/h\n",initial_speed);
    printf("Kociona sila: %.2f N",braking_force);
    printf("Podloga: %s\n",surface.name);
    printf("Koeficijent trenja: %.2f\n",friction);

    //ako je kociona sila veca od max sile trenja Blokirani
    if(braking_force > maxFrictionForce)
    {
        printf("[ALERT] Tockovi su blokirani!\n");
        printf("[ALERT] Vozilo proklizava!\n");
    }

    printf("Ukupno predjeni put do zaustavljanja: %.2f m\n",stopping_distance);
    printf("Vreme zaustavljanja: %.2f s\n",stopping_time);
}

//funkcija za izracunavanje kocenja sa ABS-om
void simulate_with_abs(double initial_speed,double braking_force, Surface surface,double vehicle_mass)
{
    double speed_mps = initial_speed * 1000 / 3600;
    double friction = surface.friction_coefficient;

    double deceleration = friction * 9.81;
    double stopping_distance = (speed_mps * speed_mps) / (2*deceleration);
    double stopping_time = speed_mps / deceleration;

    double maxFrictionForce = friction * vehicle_mass * 9.81;

    printf("[INFO] Pocetak simulacije kocenja sa ABS-om...\n");
    printf("Brzina: %.2f km/h\n", initial_speed);
    printf("Kociona sila: %.2f N\n", braking_force);
    printf("Podloga: %s\n", surface.name);
    printf("Koeficijent trenja: %.2f\n", friction);

    if(braking_force>maxFrictionForce)
    {
        printf("[ABS AKTIVAN] Prilagodjavanje kocione sile...\n");
        printf("[ABS AKTIVAN] Odrzavanje optimalnog prijanjanja...\n");

        // Simulacija periodicnog smanjenja i povecanja sile kocenja
        for (int i = 0; i < 5; i++)
        {
            printf("[ABS] Otpustanje kocnica...\n");
            printf("[ABS] Ponovno stezanje kocnica...\n");
        }
    }

    printf("[INFO] Vozilo se zaustavilo bez blokiranja tockova.\n");
    printf("Ukupno predjeni put do zaustavljanja: %.2f m \n", stopping_distance);
    printf("Vreme zaustavljanja: %.2f s\n",stopping_time);
}

int main()
{
    int pocetnaBrzina;
    int kocionaSila;
    int active=1;
    int vehicleMass;
    //Definisanje uslova puta
    Surface surfaces[] = {
        {"Suv asfalt",0.9},
        {"Mokar asfalt",0.5},
        {"Sneg/led",0.2}
    };

    printf("######################################\n");
    printf("Unesite pocetnu brzinu vozila (km/h): ");
    scanf("%d", &pocetnaBrzina);
    printf("Unesite kocionu silu (N): ");
    scanf("%d",&kocionaSila);
    printf("Unesite masu vozila: ");
    scanf("%d",&vehicleMass);


    int izbor;
    do{
        //Ispis Menia
        printf("\nIzaberite tip podloge: \n");

        printf("1 - Suv asfalt\n");
        printf("2 - Mokar asfalt\n");
        printf("3 - Sneg/led\n");
        printf("4 - Izadji\n");

        //vas izbor
        printf("Vas izbor: ");
        scanf("%d", &izbor);

        Surface selectedSurface;
        switch(izbor)
        {
        case 1:
            selectedSurface = surfaces[0];
            break;
        case 2:
            selectedSurface = surfaces[1];
            break;
        case 3:
            selectedSurface = surfaces[2];
            break;
        case 4:
            active = 0;
            break;
        default:
            printf("Izbor nije validan...\n");
            return 0;
        }
        //ako je aktivan ako nismo slucajno prekinuli
        if(active)
        {
            int sim_choice;
            printf("\nIzaberite tip simulacije kocenja:\n");
            printf("1 - Simulacija kocenja bez ABS-a\n");
            printf("2 - Simulacija kocenja sa ABS-om\n");
            printf("Vas izbor: ");
            scanf("%d",&sim_choice);

            switch(sim_choice)
            {
            case 1:
                simulate_no_abs(pocetnaBrzina,kocionaSila,selectedSurface,vehicleMass);
                break;
            case 2:
                simulate_with_abs(pocetnaBrzina,kocionaSila,selectedSurface,vehicleMass);
                break;
            default:
                printf("Nevalidan izbor simulacije.\n");
                break;
            }

        }
    }while(active);

    return 0;
}
