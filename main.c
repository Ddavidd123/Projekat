#include <stdio.h>
#include <stdlib.h>
#include "simulacija.h"
#include <time.h>

#define NUM_SAMPLES 100
#define TEMP_MIN -40
#define TEMP_MAX 125
#define TEMP_THRESHOLD 80


//funkcija za upis rezultata u fajl
void log_results(const char* filename, double initial_speed, double braking_force, Surface surface,double stopping_distance,double stopping_time,int abs_active)
{
    FILE *file = fopen(filename,"a"); //otvaranje fajla
    if(file == NULL)
    {
        printf("Greska pri otvaranju fajla!\n");
        return;
    }
    fprintf(file,"----------------------------\n");
    fprintf(file,"Simulacija kocenja %s ", abs_active ? " sa ABS-om\n" : "bez ABS-a\n");
    fprintf(file,"Brzina vozila: %.2f km/h\n",initial_speed);
    fprintf(file,"Kociona sila: %.2f N\n",braking_force);
    fprintf(file,"Podloga: %s\n",surface.name);
    fprintf(file,"Koeficijent trenja: %.2f\n",surface.friction_coefficient);
    fprintf(file,"Put zaustavljanja: %.2f m\n",stopping_distance);
    fprintf(file,"Vreme zaustavljanja: %.2f s\n",stopping_time);
    fprintf(file,"----------------------------\n");

    fclose(file);

}
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
    printf("Kociona sila: %.2f N\n",braking_force);
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

    //pozivanje funkcije za upis u fajl
    log_results("simulacija_log.txt",initial_speed,braking_force,surface,stopping_distance,stopping_time,0);
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
    log_results("simulacija_log.txt",initial_speed,braking_force,surface,stopping_distance,stopping_time,0);
}
double read_sensor()
{
    return (rand() % (TEMP_MAX - TEMP_MIN + 1)) + TEMP_MIN + ((rand() % 100) / 100.0);

}
int validate_sensor_data(double temp)
{
    if(temp<TEMP_MIN || temp > TEMP_MAX)
    {
        printf("[ERROR] Nevalidna temperatura: %.2fC\n",temp);
        return 0;
    }
    return 1;
}
int detect_anomaly(double prev_temp, double curr_temp)
{
    if(abs(curr_temp-prev_temp)> TEMP_THRESHOLD)
    {
        printf("[WARNING] Moguca anomalija! Prethodna: %.2fC, Trenutna: %.2fC\n",prev_temp,curr_temp);
        return 1;

    }
    return 0;
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


    int izbor;
    do{
        printf("######################################\n");
        printf("Unesite pocetnu brzinu vozila (km/h): ");
        scanf("%d", &pocetnaBrzina);
        printf("Unesite kocionu silu (N): ");
        scanf("%d",&kocionaSila);
        printf("Unesite masu vozila: ");
        scanf("%d",&vehicleMass);


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
            printf("3 - Testiraj senzor\n");
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
            case 3:
                srand(time(NULL)); //svaki put se generisu razlciiti brojevi
                FILE *file = fopen("sensor.txt","w");
                if(!file)
                {
                    printf("Greska pri otvaranju fajla!\n");
                    return 1;
                }
                double temperature = read_sensor();
                //Upis u fajl
                fprintf(file,"***Sample***, ***Temperature (°C) ***, ***Valid***, ***Anomaly***\n");
                for(int i=0;i<NUM_SAMPLES;i++)
                {
                    double current_temperature = read_sensor();
                    int valid = validate_sensor_data(current_temperature);
                    int anomaly = detect_anomaly(temperature,current_temperature);
                    fprintf(file,"%d, %.2f, %s, %s\n",i+1,current_temperature, valid ? "YES" : "NO", anomaly ? "YES" : "NO");
                    temperature = current_temperature;
                }
                fclose(file);
                printf("Testiranje senzora zavrseno. Rezultati sacuvani u sensor.txt\n");
                break;
            default:
                printf("Nevalidan izbor simulacije.\n");

                break;
            }

        }
    }while(active);



    return 0;
}
