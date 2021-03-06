/*****************************************************************************/
// For testing purposes
/*****************************************************************************/

// Function bodies
void check_random_uniformity(float max)
{
    float num;
    int N = 10000000;
    int n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
    float highest, lowest;
    highest = 0;
    lowest = max;
    n1 = n2 = n3 = n4 = n5 = n6 = n7 = n8 = n9 = n10 = 0;
    int div = max / 10;
    double sum = 0;
    int i;
    for(i=0; i<N; i++){
        num = random_number(max);
        sum += num;
        if(num < div) ++n1;
            else if(num < 2 * div) ++n2;
                else if(num < 3 * div) ++n3;
                    else if(num < 4 * div) ++n4;
                        else if(num < 5 * div) ++n5;
                            else if(num < 6 * div) ++n6;
                                else if(num < 7 * div) ++n7;
                                    else if(num < 8 * div) ++n8;
                                        else if(num < 9 * div) ++n9;
                                            else if(num < 10 * div) ++n10;
        if(num > highest) highest = num;
        if(num < lowest) lowest = num;
    }
    float result = sum / ((double) N);
    printf("%f\n", result);
    printf("n1=%f,", n1/(float)N);
    printf("n2=%f,", n2/(float)N);
    printf("n3=%f,", n3/(float)N);
    printf("n4=%f,", n4/(float)N);
    printf("n5=%f,", n5/(float)N);
    printf("n6=%f,", n6/(float)N);
    printf("n7=%f,", n7/(float)N);
    printf("n8=%f,", n8/(float)N);
    printf("n9=%f,", n9/(float)N);
    printf("n10=%f\n\n", n10/(float)N);
    printf("max=%f, min=%f\n", highest, lowest);
}

void check_random_uniformity2()
{
    unsigned char random_number;
    unsigned int num;
    int N = 10000000;
    long sum = 0;
    int i;
    for(i=0; i<N; i++){
        arc4random_buf(&random_number, sizeof(random_number));
        num = random_number / 256. * 8;
        sum += num;
    }
    float result = sum / ((float) N);
    printf("%f\n", result);
}

void view_selection(RouletteCompartments *genetic_roulette, int n_pop,
                    float random, int selection)
{
    int i;

    if(selection == 0)
        printf("-->\t0: (0.000000-%f)\tChosen: %i\n",
            genetic_roulette[0].delimiter,
            genetic_roulette[0].individual->chosen);
    else
        printf("\t0: (0.000000-%f)\tChosen: %i\n",
            genetic_roulette[0].delimiter,
            genetic_roulette[0].individual->chosen);

    for(i=1;i<n_pop;++i){
        if(i==selection)
            printf("-->\t%d: (%f-%f)\tChosen: %i\n", i,
                genetic_roulette[i-1].delimiter,
                genetic_roulette[i].delimiter,
                genetic_roulette[i].individual->chosen);
        else
            printf("\t%d: (%f-%f)\tChosen: %i\n", i,
                genetic_roulette[i-1].delimiter,
                genetic_roulette[i].delimiter,
                genetic_roulette[i].individual->chosen);
    }

    printf("Random: %f\tSelected: %d (Scorer %d)\n", random, selection,
        genetic_roulette[selection].individual->scorer);
}
