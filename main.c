#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/* Codurile de culoare au fost luate de aici: https://www.theurbanpenguin.com/4184-2/ */

struct Carte {
    char titlu[100];
    char autor[100];
    char tip[50];
    char locatie[50];
    int disponibila;
};

struct Librarie {
    struct Carte carti[200];
    int nrCarti;
};

// Functia pentru adaugarea unei carti
void adaugaCarte(struct Librarie *librarie) {
    if (librarie->nrCarti >= 200) {
        printf("\033[0;31mNu mai este loc in biblioteca pentru a adauga o carte.\033[0;37m\n");
        return;
    }

    struct Carte carteNoua;
    printf("\033[0;33mIntroduceti detaliile noii carti:\033[0;37m\n");
    printf("\033[0;33mTitlu: \033[0;37m");
    fgets(carteNoua.titlu, 100, stdin);
    carteNoua.titlu[strcspn(carteNoua.titlu, "\n")] = 0;
    printf("\033[0;33mAutor: \033[0;37m");
    fgets(carteNoua.autor, 100, stdin);
    carteNoua.autor[strcspn(carteNoua.autor, "\n")] = 0;
    printf("\033[0;33mTip: \033[0;37m");
    fgets(carteNoua.tip, 50, stdin);
    carteNoua.tip[strcspn(carteNoua.tip, "\n")] = 0;
    printf("\033[0;33mLocatie: \033[0;37m");
    fgets(carteNoua.locatie, 50, stdin);
    carteNoua.locatie[strcspn(carteNoua.locatie, "\n")] = 0;
    carteNoua.disponibila = 1; // Cartea este initial disponibila

    // Verificam daca cartea exista deja in biblioteca
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (strcmp(librarie->carti[i].titlu, carteNoua.titlu) == 0 && strcmp(librarie->carti[i].autor, carteNoua.autor) == 0) {
            printf("\033[0;33mCartea exista deja in biblioteca.\033[0;37m\n");
            return;
        }
    }

    // Adaugam cartea in biblioteca
    librarie->carti[librarie->nrCarti] = carteNoua;
    librarie->nrCarti++;
    printf("\033[0;33mCartea a fost adaugata cu succes!\033[0;37m\n");
}

// Functia pentru cautarea unei carti dupa titlu
void cautaDupaTitlu(struct Librarie *librarie) {
    char cautaTitlul[100];
    printf("\033[0;33mIntroduceti titlul cartii: \033[0;37m");
    fgets(cautaTitlul, 100, stdin);
    cautaTitlul[strcspn(cautaTitlul, "\n")] = 0;

    int maxTitlu = strlen("Titlu");
    int maxAutor = strlen("Autor");
    int maxTip = strlen("Tip");
    int maxLocatie = strlen("Locatie");
    int maxStatus = strlen("Status");

    // Lungimea maxima pentru fiecare celula din tabel
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (librarie->carti[i].disponibila) {
            if (strlen(librarie->carti[i].titlu) > maxTitlu)
                maxTitlu = strlen(librarie->carti[i].titlu);
            if (strlen(librarie->carti[i].autor) > maxAutor)
                maxAutor = strlen(librarie->carti[i].autor);
            if (strlen(librarie->carti[i].tip) > maxTip)
                maxTip = strlen(librarie->carti[i].tip);
            if (strlen(librarie->carti[i].locatie) > maxLocatie)
                maxLocatie = strlen(librarie->carti[i].locatie);
            if (strlen("Disponibila ") > maxStatus)
                maxStatus = strlen("Disponibila  ");
        }
    }

    // Generam separatorul pentru fiecare coloana
    char lineSeparatorTitlu[maxTitlu];
    char lineSeparatorAutor[maxAutor];
    char lineSeparatorTip[maxTip];
    char lineSeparatorLocatie[maxLocatie];
    char lineSeparatorStatus[maxStatus];
    memset(lineSeparatorTitlu, '-', maxTitlu);
    memset(lineSeparatorAutor, '-', maxAutor);
    memset(lineSeparatorTip, '-', maxTip);
    memset(lineSeparatorLocatie, '-', maxLocatie);
    memset(lineSeparatorStatus, '-', maxStatus);
    lineSeparatorTitlu[maxTitlu] = '\0';
    lineSeparatorAutor[maxAutor] = '\0';
    lineSeparatorTip[maxTip] = '\0';
    lineSeparatorLocatie[maxLocatie] = '\0';
    lineSeparatorStatus[maxStatus] = '\0';

    printf("\n\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m Cartile disponibile in urma cautarii \033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m\n");
    printf("+-%s-+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie, lineSeparatorStatus);
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n", maxTitlu, "Titlu", maxAutor, "Autor", maxTip, "Tip", maxLocatie, "Locatie", maxStatus, "Status");
    printf("+-%s-+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie, lineSeparatorStatus);

    int gasit = 0;
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (strcmp(librarie->carti[i].autor, cautaTitlul) == 0) {
            printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
                   maxTitlu, librarie->carti[i].titlu,
                   maxAutor, librarie->carti[i].autor,
                   maxTip, librarie->carti[i].tip,
                   maxLocatie, librarie->carti[i].locatie,
                   maxStatus, librarie->carti[i].disponibila ? "Disponibila" : "Indisponibila");
            printf("+-%s-+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie, lineSeparatorStatus);
            gasit = 1;
        }
    }

    if (librarie->nrCarti == 0 || !gasit) {
        printf("\033[0;33mNu s-au gasit carti dupa acest titlu sau tabelul este gol.\033[0;37m\n");
    }
}

// Functia pentru cautarea unei carti dupa autor
void cautaDupaAutor(struct Librarie *librarie) {
    char cautaAutorul[100];
    printf("\033[0;33mIntroduceti autorul cartii: \033[0;37m");
    fgets(cautaAutorul, 100, stdin);
    cautaAutorul[strcspn(cautaAutorul, "\n")] = 0;

    int maxTitlu = strlen("Titlu");
    int maxAutor = strlen("Autor");
    int maxTip = strlen("Tip");
    int maxLocatie = strlen("Locatie");

    // Lungimea maxima pentru fiecare celula din tabel
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (librarie->carti[i].disponibila) {
            if (strlen(librarie->carti[i].titlu) > maxTitlu)
                maxTitlu = strlen(librarie->carti[i].titlu);
            if (strlen(librarie->carti[i].autor) > maxAutor)
                maxAutor = strlen(librarie->carti[i].autor);
            if (strlen(librarie->carti[i].tip) > maxTip)
                maxTip = strlen(librarie->carti[i].tip);
            if (strlen(librarie->carti[i].locatie) > maxLocatie)
                maxLocatie = strlen(librarie->carti[i].locatie);
        }
    }

    // Generam separatorul pentru fiecare coloana
    char lineSeparatorTitlu[maxTitlu];
    char lineSeparatorAutor[maxAutor];
    char lineSeparatorTip[maxTip];
    char lineSeparatorLocatie[maxLocatie];
    memset(lineSeparatorTitlu, '-', maxTitlu);
    memset(lineSeparatorAutor, '-', maxAutor);
    memset(lineSeparatorTip, '-', maxTip);
    memset(lineSeparatorLocatie, '-', maxLocatie);
    lineSeparatorTitlu[maxTitlu] = '\0';
    lineSeparatorAutor[maxAutor] = '\0';
    lineSeparatorTip[maxTip] = '\0';
    lineSeparatorLocatie[maxLocatie] = '\0';

    printf("\n\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m Cartile disponibile in urma cautarii \033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m\n");
    printf("+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie);
    printf("| %-*s | %-*s | %-*s | %-*s |\n", maxTitlu, "Titlu", maxAutor, "Autor", maxTip, "Tip", maxLocatie, "Locatie");
    printf("+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie);

    int gasit = 0;
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (strcmp(librarie->carti[i].autor, cautaAutorul) == 0) {
            printf("| %-*s | %-*s | %-*s | %-*s |\n",
                   maxTitlu, librarie->carti[i].titlu,
                   maxAutor, librarie->carti[i].autor,
                   maxTip, librarie->carti[i].tip,
                   maxLocatie, librarie->carti[i].locatie);
            printf("+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie);
            gasit = 1;
        }
    }

    if (librarie->nrCarti == 0 || !gasit) {
        printf("\033[0;33mNu s-au gasit carti scrise de autor sau tabelul este gol.\033[0;37m\n");
    }
}

// Functia pentru afisarea cartilor disponibile
void cautaCartiDisponibile(struct Librarie *librarie) {
    int maxTitlu = strlen("Titlu");
    int maxAutor = strlen("Autor");
    int maxTip = strlen("Tip");
    int maxLocatie = strlen("Locatie");

    // Lungimea maxima pentru fiecare celula din tabel
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (librarie->carti[i].disponibila) {
            if (strlen(librarie->carti[i].titlu) > maxTitlu)
                maxTitlu = strlen(librarie->carti[i].titlu);
            if (strlen(librarie->carti[i].autor) > maxAutor)
                maxAutor = strlen(librarie->carti[i].autor);
            if (strlen(librarie->carti[i].tip) > maxTip)
                maxTip = strlen(librarie->carti[i].tip);
            if (strlen(librarie->carti[i].locatie) > maxLocatie)
                maxLocatie = strlen(librarie->carti[i].locatie);
        }
    }

    // Generam separatorul pentru fiecare coloana
    char lineSeparatorTitlu[maxTitlu];
    char lineSeparatorAutor[maxAutor];
    char lineSeparatorTip[maxTip];
    char lineSeparatorLocatie[maxLocatie];
    memset(lineSeparatorTitlu, '-', maxTitlu);
    memset(lineSeparatorAutor, '-', maxAutor);
    memset(lineSeparatorTip, '-', maxTip);
    memset(lineSeparatorLocatie, '-', maxLocatie);
    lineSeparatorTitlu[maxTitlu] = '\0';
    lineSeparatorAutor[maxAutor] = '\0';
    lineSeparatorTip[maxTip] = '\0';
    lineSeparatorLocatie[maxLocatie] = '\0';

    printf("\n\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m Cartile disponibile \033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m\n");
    printf("+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie);
    printf("| %-*s | %-*s | %-*s | %-*s |\n", maxTitlu, "Titlu", maxAutor, "Autor", maxTip, "Tip", maxLocatie, "Locatie");
    printf("+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie);

    for (int i = 0; i < librarie->nrCarti; i++) {
        if (librarie->carti[i].disponibila) {
            printf("| %-*s | %-*s | %-*s | %-*s |\n",
                   maxTitlu, librarie->carti[i].titlu,
                   maxAutor, librarie->carti[i].autor,
                   maxTip, librarie->carti[i].tip,
                   maxLocatie, librarie->carti[i].locatie);
            printf("+-%s-+-%s-+-%s-+-%s-+\n", lineSeparatorTitlu, lineSeparatorAutor, lineSeparatorTip, lineSeparatorLocatie);
        }
    }

    if (librarie->nrCarti == 0) {
        printf("\033[0;33mTabelul este gol. Fisierul nu a fost citit sau fisierul este gol!\033[0;37m\n");
    }
}

// Functia pentru imprumutul unei carti
void imprumutaCartea(struct Librarie *librarie) {
    char titlulImprumutat[100];
    printf("\033[0;33mIntroduceti titlul cartii de imprumutat:\033[0;37m ");
    fgets(titlulImprumutat, 100, stdin);
    titlulImprumutat[strcspn(titlulImprumutat, "\n")] = 0;

    int gasit = 0;
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (strcmp(librarie->carti[i].titlu, titlulImprumutat) == 0 && librarie->carti[i].disponibila) {
            librarie->carti[i].disponibila = 0; // Cartea este imprumutata
            printf("\n\033[0;31m!!! \033[0;33mAti imprumutat cu succes cartea \033[0;37m\"%s\". \033[0;33mVa rugam sa o returnati in maxim 10 zile. \033[0;31m!!!\033[0;37m\n", titlulImprumutat);
            gasit = 1;
            break;
        }
    }
    if (!gasit)
        printf("\n\033[0;31m!!! \033[0;33mNu s-a putut realiza imprumutul. Cartea nu exista sau nu este disponibila. \033[0;31m!!!\033[0;37m\n");
}

// Functia pentru returnarea unei carti
void returneazaCartea(struct Librarie *librarie) {
    char returneazaTitlulCartii[100];
    printf("\033[0;33mIntroduceti titlul cartii de returnat:\033[0;37m ");
    fgets(returneazaTitlulCartii, 100, stdin);
    returneazaTitlulCartii[strcspn(returneazaTitlulCartii, "\n")] = 0;
    int gasit = 0;
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (strcmp(librarie->carti[i].titlu, returneazaTitlulCartii) == 0 && !librarie->carti[i].disponibila) {
            librarie->carti[i].disponibila = 1; // Cartea este returnata
            printf("\033[0;33mAti returnat cu succes cartea\033[0;37m \"%s\".\n", returneazaTitlulCartii);
            gasit = 1;
            break;
        }
    }
    if (!gasit)
        printf("\033[0;33mNu s-a putut realiza returnarea. Cartea nu a fost imprumutata sau nu exista.\033[0;37m\n");
}

// Functia pentru salvarea bibliotecii intr-un fisier
void salveazaTotul(struct Librarie *librarie, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\033[0;31mEroare la salvarea bibliotecii in fisier.\033[0;37m\n");
        return;
    }
    for (int i = 0; i < librarie->nrCarti; i++) {
        fprintf(file, "Titlu: %s\n", librarie->carti[i].titlu);
        fprintf(file, "Autor: %s\n", librarie->carti[i].autor);
        fprintf(file, "Tip: %s\n", librarie->carti[i].tip);
        fprintf(file, "Locatie: %s\n", librarie->carti[i].locatie);
        fprintf(file, "Disponibila: %d\n", librarie->carti[i].disponibila);
        fprintf(file, "\n");
    }
    fclose(file);
}

// Functia pentru incarcarea bibliotecii dintr-un fisier
void incarcamBiblioteca(struct Librarie *librarie, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\033[0;31mEroare la incarcarea bibliotecii din fisier.\033[0;37m\n");
        return;
    }

    librarie->nrCarti = 0;
    while (!feof(file)) {
        struct Carte carte;
        fscanf(file, "Titlu: %[^\n]\n", carte.titlu);
        fscanf(file, "Autor: %[^\n]\n", carte.autor);
        fscanf(file, "Tip: %[^\n]\n", carte.tip);
        fscanf(file, "Locatie: %[^\n]\n", carte.locatie);
        fscanf(file, "Disponibila: %d\n", &carte.disponibila);
        librarie->carti[librarie->nrCarti++] = carte;
        fscanf(file, "\n");
    }
    fclose(file);
}

// Functia pentru stergerea unei carti dupa titlu
void stergeCarte(struct Librarie *librarie) {
    char titluDeSters[100];
    printf("\033[0;33mIntroduceti titlul cartii de sters:\033[0;37m ");
    fgets(titluDeSters, 100, stdin);
    titluDeSters[strcspn(titluDeSters, "\n")] = 0;

    int pozitie = -1;
    for (int i = 0; i < librarie->nrCarti; i++) {
        if (strcmp(librarie->carti[i].titlu, titluDeSters) == 0) {
            pozitie = i;
            break;
        }
    }

    if (pozitie != -1) {
        // Mutam toate cartile care urmeaza dupa pozitia gasita o pozitie inapoi
        for (int i = pozitie; i < librarie->nrCarti - 1; i++) {
            librarie->carti[i] = librarie->carti[i + 1];
        }
        librarie->nrCarti--; // Scadem numarul total de carti
        printf("\033[0;33mCartea a fost stearsa cu succes.\033[0;37m\n");
    } else {
        printf("\033[0;33mCartea nu a fost gasita.\033[0;37m\n");
    }
}


// Functia pentru afisarea meniului principal
void AfiseazaMeniulPrincipal() {
    printf("\n");
    printf("\033[0;33m██████╗"); printf("\033[0;32m  ██████╗"); printf("\033[0;36m██╗   ██╗"); printf("\033[0;31m████████╗\n");
    printf("\033[0;33m██╔══██╗"); printf("\033[0;32m██╔════╝"); printf("\033[0;36m██║   ██║"); printf("\033[0;31m╚══██╔══╝\n");
    printf("\033[0;33m██████╔╝"); printf("\033[0;32m██║     "); printf("\033[0;36m██║   ██║"); printf("\033[0;31m   ██║   \n");
    printf("\033[0;33m██╔══██╗"); printf("\033[0;32m██║     "); printf("\033[0;36m██║   ██║"); printf("\033[0;31m   ██║   \n");
    printf("\033[0;33m██████╔╝"); printf("\033[0;32m╚██████╗"); printf("\033[0;36m╚██████╔╝"); printf("\033[0;31m   ██║   \n");
    printf("\033[0;33m╚═════╝ "); printf("\033[0;32m ╚═════╝"); printf("\033[0;36m ╚═════╝ "); printf("\033[0;31m   ╚═╝   \n");

    printf("\n\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;37m CONECTARE \033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;37m\n");
    printf("1. Utilizator\n");
    printf("2. Administrator\n");
    printf("0. Iesire\n");
    printf("\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;37m\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;37m\n");
}

void MeniulCautareAvansataUser() {
    printf("\n\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m CAUTARE AVANSATA \033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m\n");
    printf("                            \033[0;33mConectat> \033[0;36mUtilizator\033[0;37m\n");
    printf("1. Cauta carte dupa titlu\n");
    printf("2. Cauta carte dupa autor\n");
    printf("3. Cauta carti disponibile\n");
    printf("0. Inapoi\n");
    printf("\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;37m\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;37m\n");
}

void MeniulCautareAvansataAdmin() {
    printf("\n\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m CAUTARE AVANSATA \033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m\n");
    printf("                            \033[0;33mConectat> \033[0;36mAdministrator\033[0;37m\n");
    printf("1. Cauta carte dupa titlu\n");
    printf("2. Cauta carte dupa autor\n");
    printf("3. Cauta carti disponibile\n");
    printf("0. Inapoi\n");
    printf("\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;37m\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;37m\n");
}

void AfiseazaMeniulOperativUtilizator() {
    printf("\n\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m OPERATII CU CARTI \033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m\n");
    printf("                            \033[0;33mConectat> \033[0;36mUtilizator\033[0;37m\n");
    printf("1. Cautare avansata\n");
    printf("2. Imprumuta carte\n");
    printf("3. Returneaza carte\n");
    printf("0. Deconectare\n");
    printf("\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;37m\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;37m\n");
}

void AfiseazaMeniulOperativAdministrator() {
    printf("\n\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m OPERATII CU CARTI \033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;37m\n");
    printf("                            \033[0;33mConectat> \033[0;36mAdministrator\033[0;37m\n");
    printf("1. Adauga carte\n");
    printf("2. Sterge carte\n");
    printf("3. Cautare avansata\n");
    printf("4. Imprumuta carte\n");
    printf("5. Returneaza carte\n");
    printf("0. Deconectare\n");
    printf("\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;37m\033[0;31m=\033[0;32m=\033[0;33m=\033[0;34m=\033[0;35m=\033[0;36m=\033[0;37m=\033[0;31m=\033[0;32m=\033[0;31m=\033[0;37m\n");
}

void ContinuaConectarea() {
    char ParolaSistemului[] = "suntocarte";
    char IntroducereaParolei[100];
    int i = 0;
    char c;

    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON); // Dezactivează afișarea caracterelor și modul canonic
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("\033[0;33mIntroduceti parola: \033[0;37m");
    fflush(stdout); // Asigură afișarea promptului

    while (1) {
        c = getchar(); // Citește caracterul fără buffering

        if (c == '\n' || c == '\r') { // Dacă Enter, termină parola
            IntroducereaParolei[i] = '\0';
            break;
        } else if (c == 127 && i > 0) { // Backspace (127 pe Unix/macOS)
            i--;
            printf("\b \b"); // Șterge ultimul caracter afișat
            fflush(stdout);
        } else if (i < sizeof(IntroducereaParolei) - 1) { // Evităm buffer overflow
            IntroducereaParolei[i++] = c;
            printf("*"); // Afișează "*" în timp real
            fflush(stdout);
        }
    }

    // Restaurăm setările terminalului
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    printf("\n"); // Nouă linie după introducerea parolei

    // Verifică parola introdusă
    if (strcmp(IntroducereaParolei, ParolaSistemului) == 0) {
        printf("\n\033[0;32mAcces permis!\033[0;37m\n");
    } else {
        printf("\n\033[0;31mParola este incorecta. Reintrati in program.\033[0;37m\n\n");
        exit(0);
    }
}


int main() {
    struct Librarie librarie;
    librarie.nrCarti = 0;

    // Incarcam biblioteca din fisier (daca exista)
    incarcamBiblioteca(&librarie, "biblioteca.txt");

    int alegereMain, alegereCarte;
    do {
        AfiseazaMeniulPrincipal();
        printf("\033[0;37m\033[0;33mAlegeti o optiune: \033[0;37m");
        scanf("%d", &alegereMain);
        getchar();

        switch (alegereMain) {
            case 1:
                do {
                    AfiseazaMeniulOperativUtilizator();
                    printf("\033[0;33mAlegeti o optiune: \033[0;37m");
                    scanf("%d", &alegereCarte);
                    getchar();

                    switch (alegereCarte) {
                        case 1:
                            MeniulCautareAvansataUser();
                            int alegereCautare;
                            printf("\033[0;33mAlegeti o optiune: \033[0;37m");
                            scanf("%d", &alegereCautare);
                            getchar();

                            switch (alegereCautare) {
                                case 1:
                                    cautaDupaTitlu(&librarie);
                                    break;
                                case 2:
                                    cautaDupaAutor(&librarie);
                                    break;
                                case 3:
                                    cautaCartiDisponibile(&librarie);
                                    break;
                                case 0:
                                    printf("\033[0;33mRevenire la meniul anterior...\033[0;37m\n");
                                    break;
                                default:
                                    printf("\033[0;33mOptiune invalida! Va rugam sa alegeti din nou.\033[0;37m\n");
                            }
                            break;
                        case 2:
                            imprumutaCartea(&librarie);
                            break;
                        case 3:
                            returneazaCartea(&librarie);
                            break;
                        case 0:
                            printf("\033[0;33mTe-ai deconectat cu succes! Revenire la meniul principal...\033[0;37m\n");
                            break;
                        default:
                            printf("\033[0;33mOptiune invalida! Va rugam sa alegeti din nou.\033[0;37m\n");
                    }
                } while (alegereCarte != 0);
                break;
            case 2:
                ContinuaConectarea();
                do {
                    //ContinuaConectarea();
                    AfiseazaMeniulOperativAdministrator();
                    printf("\033[0;33mAlegeti o optiune: \033[0;37m");
                    scanf("%d", &alegereCarte);
                    getchar();

                    switch (alegereCarte) {
                        case 1:
                            adaugaCarte(&librarie);
                            break;
                        case 2:
                            stergeCarte(&librarie);
                            break;
                        case 3:
                            MeniulCautareAvansataAdmin();
                            int alegereCautare;
                            printf("\033[0;33mAlegeti o optiune: \033[0;37m");
                            scanf("%d", &alegereCautare);
                            getchar();

                            switch (alegereCautare) {
                                case 1:
                                    cautaDupaTitlu(&librarie);
                                    break;
                                case 2:
                                    cautaDupaAutor(&librarie);
                                    break;
                                case 3:
                                    cautaCartiDisponibile(&librarie);
                                    break;
                                case 0:
                                    printf("\033[0;33mRevenire la meniul anterior...\033[0;37m\n");
                                    break;
                                default:
                                    printf("\033[0;33mOptiune invalida! Va rugam sa alegeti din nou.\033[0;37m\n");
                            }
                            break;
                        case 4:
                            imprumutaCartea(&librarie);
                            break;
                        case 5:
                            returneazaCartea(&librarie);
                            break;
                        case 0:
                            printf("\033[0;33mTe-ai deconectat cu succes! Revenire la meniul principal...\033[0;37m\n");
                            break;
                        default:
                            printf("\033[0;33mOptiune invalida! Va rugam sa alegeti din nou.\033[0;37m\n");
                    }
                } while (alegereCarte != 0);
                break;
            case 0:
                printf("\033[0;33mSalvare biblioteca in fisier...\033[0;37m\n");
                salveazaTotul(&librarie, "biblioteca.txt");
                printf("\033[0;33mInchidere aplicatie.\033[0;37m\n");
                break;
            default:
                printf("\033[0;33mOptiune invalida! Va rugam sa alegeti din nou.\033[0;37m\n");
        }
    } while (alegereMain != 0);

    return 0;
}