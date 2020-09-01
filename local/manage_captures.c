#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include <time.h>
#define MAX 80 

#define MAX_CAPTURES 10000
#define TAILLE_NOM 30

void mirroir (char *chaine);

void send_request (char *name) {
    CURL *curl;
    CURLcode res;

    char * request_string = calloc(10000000, sizeof(char));
    sprintf(request_string, "name=%s", name);
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/transfert/photo");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_string);
    
        res = curl_easy_perform(curl); 
        if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
    
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void vider_buffer (char *buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        buffer[i] = 0;
    }
}

void afficher_tab2 (char tab[MAX_CAPTURES][TAILLE_NOM]) {
    for (int i = 0; i < MAX_CAPTURES; i++) {
        for (int j = 0; j < TAILLE_NOM; j++) {
            printf ("%c", tab[i][j]);
        }
        printf ("\n");
    }
}

// Il faut enlever l'extension
void transform_noms (char liste[MAX_CAPTURES][TAILLE_NOM], char nouvelleListe[MAX_CAPTURES][TAILLE_NOM], int size) {
    int i = 0, j;

    for (i = 0; i < size; i++) {
        j = 0;
        while (liste[i][j] != '.') {
            nouvelleListe[i][j] = liste[i][j];
            printf ("%c", nouvelleListe[i][j]);
            j++;
        }
        printf ("\n");
    }
}

void linearize (char *base, char **lines) {
    int i = 0, j = 0, x = 0;

    while (lines[i][0] != 0) {
        j = 0;
        while (lines[i][j] != 0 && lines[i][j+1] != '\n') {
            base[x++] = lines[i][j++];
        }
        i++;
    }
}

void transferer_noms (char liste[MAX_CAPTURES][TAILLE_NOM], char old[MAX_CAPTURES][TAILLE_NOM]) {
    int i = 0;

    char commande[250] = "";
    printf ("1\n");

    char * title = calloc(100, sizeof(char));

    time_t seconds;
    time(&seconds);

    sprintf(title, "media_%ld.jpg", seconds);

    while (liste[i][0] != 0) {
        sprintf(commande, "mv ./data/images/tmp/%s ./data/images/tmp/%s;mv ./data/images/tmp/%s /home/thomas/camera_server/public", old[i], title, title);

        // Envoyer le nom du nouveau fichier transféré au socket
        system(commande);

        send_request(title);
        free(title);
        title = NULL;
        
        i++;
    }
}

void enlever_last_car(char *chaine) {
    chaine[strlen(chaine)-1] = 0;
}

int main (void) {
    system("cd data/images/tmp;ls capt* > ../liste.txt;cd ../../..");

    FILE * CAPTURES = fopen("./data/images/liste.txt", "r");

    printf ("1\n");

    char liste_captures[MAX_CAPTURES][TAILLE_NOM];
    char nouvelles_captures[MAX_CAPTURES][TAILLE_NOM];

    int i, j, number = 0;

    for (i = 0; i < MAX_CAPTURES; i++) {
        for (j = 0; j < TAILLE_NOM; j++) {
            liste_captures[i][j] = 0;
            nouvelles_captures[i][j] = 0;
	    }
    }

    i = 0;

    while (fgets(liste_captures[i], TAILLE_NOM, CAPTURES) != NULL) {
        // Remplissage
        enlever_last_car(liste_captures[i++]);
        number++;
    }

    if (strcmp(liste_captures[i], "ls: cannot access 'cloud/capt*': No such file or directory") == 0) {
	    return 1;
    }

    i = 0;

    printf ("1\n");

    transform_noms(liste_captures, nouvelles_captures, number);

    printf("%d\n", number);

    transferer_noms(nouvelles_captures, liste_captures);

    fclose(CAPTURES);

    system("ls ./data/images/tmp > ./data/images/liste.txt");

    return 0;
}
