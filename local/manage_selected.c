#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include <time.h>
#define MAX 80 

#define MAX_CAPTURES 1000000
#define TAILLE_NOM 30

// Envoi de la photo
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
    printf ("\n");
}

void vider_buffer (char *buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        buffer[i] = 0;
    }
}

void afficher_tab2 (char ** tab) {
    for (int i = 0; i < MAX_CAPTURES; i++) {
        for (int j = 0; j < TAILLE_NOM; j++) {
            printf ("%c", tab[i][j]);
        }
        printf ("\n");
    }
}

// Il faut enlever l'extension
void transform_noms (char ** liste, char ** nouvelleListe, int size) {
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

int compare_file_historique (char * file, char ** historique, int lines) {

}

// Pour l'envoi
void transferer_noms (char ** liste, char ** old) {
    int i = 0;

    char commande[250] = "";
    int file_transfered = 0;

    char * title = calloc(100, sizeof(char));

    time_t seconds; 
    time(&seconds);

    FILE * HISTORIQUE = fopen("data/images/historique.txt", "w");
    FILE * RHISTORIQUE = fopen("data/images/historique.txt", "r");

    char ** hist_lines = calloc(MAX_CAPTURES, sizeof(char*));

    int x;

    for (x = 0; x < MAX_CAPTURES; x++) {
        hist_lines[x] = calloc(TAILLE_NOM, sizeof(char));
    }

    x = 0;

    while (fgets(hist_lines[x++], TAILLE_NOM, RHISTORIQUE));

    char * current_file = calloc(TAILLE_NOM, sizeof(char));

    while (liste[i][0] != 0) {
        // Il y aura peut être besoin d'insérer les lignes précédentes dans cette boucle

        sprintf(current_file, "%s.JPG", liste[i]);

        file_transfered = compare_file_historique(current_file, hist_lines, x);

        if (file_transfered == 0) {
            sprintf(title, "media_%ld.jpg", seconds);

            sprintf(commande, "mv ./data/images/tmp/%s ./data/images/tmp/%s;mv ./data/images/tmp/%s /home/thomas/camera_server/public", old[i], title, title);

            // Envoyer le nom du nouveau fichier transféré au socket
            system(commande);

            // ÉCIRE DANS L'HISTORIQUE DES TRANSFERTS
            fprintf(HISTORIQUE, "%s\n", title);

            send_request(title);
            
            i++;
        }
    }

    for (x = 0; x < MAX_CAPTURES; x++) {
        free(hist_lines[x]);
    }

    free(current_file);
    free(title);
    title = NULL;
    fclose(HISTORIQUE);
    fclose(RHISTORIQUE);
}

void enlever_last_car(char *chaine) {
    chaine[strlen(chaine)-1] = 0;
}

void select_medias () {
    system("cd data/images/cloud;ls *.JPG > ../cloud.txt;cd ../../..");
    FILE * CLOUD = fopen("./data/images/cloud.txt", "r");

    fclose(CLOUD);
}

void getFiles (void) {
    system("cd data/images/gets;gphoto2 --get-all-files;ls *.JPG > ../gets.txt;cd ../../..");
}

unsigned int parseRating (char ** lines, int size) {
    unsigned int i, x, y;
    int result;

    char * buf = calloc(100, sizeof(char));

    for (i = 0; i < size; i++) {
        x = 0;
        y = 0;

        while (lines[i][x] != ':') {
            buf[y++] = lines[i][x++];
        }

        x++;

        if (strncmp(buf, "Rating", 6) == 0) {
            y = 0;
            strcpy(buf, "");
            while (lines[i][x] != 0) {
                buf[y++] = lines[i][x++];
            }

            y = strlen(lines[i]);

            // sscanf(lines[i], "%d", &result);
            sscanf(buf, "%d", &result);
            return result;
            break;
        }

        strcpy(buf, "");
    }

    free(buf);
    return -1;
}

unsigned int getRating (char * file) {
    char commande[200] = "";

    sprintf(commande, "cd data/images/gets;exiftool -filename -imagesize -exif:fnumber -xmp:all %s.JPG > ../tmp/exif.txt;cd ../../..", file);
    system(commande);

    FILE * RATING = fopen("data/images/tmp/exif.txt", "r");

    char ** lignes = calloc(10, sizeof(char*));

    for (int i = 0; i < 10; i++) {
        lignes[i] = calloc(1000, sizeof(char));
    }

    // Lecture
    int x = 0;

    // Remplissage
    while (fgets(lignes[x++], 999, RATING));

    unsigned int rating = parseRating(lignes, x);

    for (int i = 0; i < 10; i++) {
        free(lignes[i]);
    }

    fclose(RATING);
    free(lignes);

    return rating;
}

int eachFileRating (char ** liste, char ** transferts, unsigned int size) {
    // Traiter chaque image
    int i, rating = -1, x = 0;
    FILE * RATING = fopen("data/images/rating.txt", "w");

    for (i = 0; i < size; i++) {
        rating = getRating(liste[i]);

        if (rating == 5) {
            transferts[x++] = liste[i];
        }

        fprintf(RATING, "%s : %d\n", liste[i], rating);
    }

    fclose(RATING);

    return x;
}

int main (void) {
    getFiles();
    FILE * GETS = fopen("./data/images/gets.txt", "r");

    char ** liste_captures = calloc(MAX_CAPTURES, sizeof(char*));
    char ** transferts = calloc(MAX_CAPTURES, sizeof(char*));
    char ** nouvelles_captures = calloc(MAX_CAPTURES, sizeof(char*));

    int i, j, number = 0;

    for (i = 0; i < MAX_CAPTURES; i++) {
        liste_captures[i] = calloc(TAILLE_NOM, sizeof(char));
        transferts[i] = calloc(TAILLE_NOM, sizeof(char));
        nouvelles_captures[i] = calloc(TAILLE_NOM, sizeof(char));
    }

    i = 0;

    while (fgets(liste_captures[i], TAILLE_NOM, GETS) != NULL) {
        // Remplissage
        enlever_last_car(liste_captures[i++]);
        number++;
    }

    if (strcmp(liste_captures[0], "ls: cannot access '*.JPG': No such file or directory") == 0) {
        printf ("OK\n");
	    return 1;
    }

    i = 0;
    
    int transferts_nb = eachFileRating(nouvelles_captures, transferts, number);

    transform_noms(transferts, nouvelles_captures, transferts_nb);

    transferer_noms(nouvelles_captures, transferts);

    fclose(GETS);

    for (i = 0; i < MAX_CAPTURES; i++) {
        free(liste_captures[i]);
        free(transferts[i]);
        free(nouvelles_captures[i]);
    }

    free(liste_captures);
    free(transferts);
    free(nouvelles_captures);

    return 0;
}