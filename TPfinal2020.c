#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int jour;
    int mois;
    int annee;
};

struct vaccin
{
    char labo[35];
    int intervalle;
    float efficacite;
    struct Date date;
};

struct vaccin saisir()
{
    struct vaccin v;
    printf("nom du laboratoire:\n");
    scanf("%s", v.labo);
    fflush(stdin);
    printf("nombre de jour entre deux doses:\n");
    scanf("%d", &v.intervalle);
    fflush(stdin);
    printf("efficacite:\n");
    scanf("%f", &v.efficacite);
    fflush(stdin);
    printf("jour de sortie:\n");
    scanf("%d", &v.date.jour);
    fflush(stdin);
    printf("mois de sortie:\n");
    scanf("%d", &v.date.mois);
    fflush(stdin);
    printf("annee de sortie:\n");
    scanf("%d", &v.date.annee);
    fflush(stdin);
    return v;
}

void ajouter()
{
    struct vaccin v = saisir();
    FILE*fichier = fopen("vaccin.dat", "a");
    fwrite(&v, sizeof(v), 1, fichier);
    fclose(fichier);
}

void afficher(struct vaccin v)
{
    printf("nom du labo: %s \n", v.labo);
    printf("intervalle entre deux doses: %d \n", v.intervalle);
    printf("efficacite du vaccin: %f \n", v.efficacite);
    printf("date de sortie: %d/%d/%d \n", v.date.jour, v.date.mois, v.date.annee);
}

void all_afficher()
{
    int i=1;
    struct vaccin v;
    FILE*fichier = fopen("vaccin.dat", "r");
    while(!feof(fichier) && fread(&v, sizeof(v), 1, fichier))
    {
        printf("le vaccin numero %d: \n", i++);
        afficher(v);
    }
}

void meilleur()
{
    struct vaccin v;
    int eff=0;
    FILE*fichier = fopen("vaccin.dat", "r");
    while(!feof(fichier) && fread(&v, sizeof(v), 1, fichier))
    {
        if(v.efficacite>eff)
        {
            eff=v.efficacite;
        }
    }
    fclose(fichier);
    fichier = fopen("vaccin.dat", "r");
    while(!feof(fichier) && fread(&v, sizeof(v), 1, fichier))
    {
        if(v.efficacite==eff)
        {
            afficher(v);
        }
    }
    fclose(fichier);
}

struct vaccin saisir2()
{
    struct vaccin v;
    printf("nouvelle efficacite:");
    scanf("%f", &v.efficacite);
    return v;
}

void maj_eff()
{
    struct vaccin v;
    char labo[35];
    FILE*fichier = fopen("vaccin.dat", "r");
    FILE*fichier2=fopen("vaccin2.dat", "a");
    printf("nom du labo a modifier: \n");
    scanf("%s", labo);
    while(!feof(fichier) && fread(&v, sizeof(v), 1, fichier))
    {
        if(strcmp(v.labo, labo)==0)
        {
            printf("ancienne efficacite %f \n", v.efficacite);
            printf("nouvelle efficacite:");
            scanf("%f", &v.efficacite);
            fwrite(&v, sizeof(v), 1, fichier2);
        }
    }
    fclose(fichier);
    fclose(fichier2);
    remove("vaccin.dat");
    rename("vaccin2.dat", "vaccin.dat");

}

void supprimer()
{
    struct vaccin v;
    int eff;
    FILE*fichier=fopen("vaccin.dat", "r");
    FILE*fichier2=fopen("vaccin2.dat", "a");
    printf("efficacite minimale:");
    scanf("%d", &eff);
    while(!feof(fichier) && fread(&v, sizeof(v), 1, fichier))
    {
        if(v.efficacite>eff)
        {
            fwrite(&v, sizeof(v), 1, fichier2);
        }
    }
    fclose(fichier);
    fclose(fichier2);
    remove("vaccin.dat");
    rename("vaccin2.dat", "vaccin.dat");
}

int main()
{
    struct vaccin v;
    int choix;
    do
    {
        printf("<1> saisir un nouveau vaccin\n");
        printf("<2> afficher les vaccins\n");
        printf("<3> afficher le meilleur vaccin\n");
        printf("<4> mettre a jour une efficacite\n");
        printf("<5> supprimer les moins bon vaccins\n");
        printf("<6> quitter le programme\n");
        scanf("%d", &choix);
        fflush(stdin);
        switch(choix)
        {
        case 1:
            ajouter();
            break;
        case 2:
            all_afficher();
            break;
        case 3:
            meilleur(v);
            break;
        case 4:
            maj_eff(v);
            break;
        case 5:
            supprimer(v);
            break;

        }


    }while(choix!=6);
    return 0;
}
