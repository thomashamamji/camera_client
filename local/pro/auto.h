// Header déstiné au développement des fonctions utilisées dans les scripts de transferts vidéo et photo
#ifndef __AUTO_H__
#define __AUTO_H__

// LIBS
#include "mods.h"

// Constantes
#include "constants.h"

// Fonctions
#include "scripts.h"
#include "errors.h"
#include "usb_transactions.h"
#include "transactions.h"

unsigned int filterPhotos (char ** photos_l, char ** files_l, unsigned int files_n);
unsigned int filterVideos (char ** videos_l, char ** files_l, unsigned int files_n);
unsigned int getImageNumber (char * buffer);
unsigned int save_clist_slist(char ** liste_captures, char ** files, unsigned int files_nb, unsigned int nb_list);
void afficher_liste(char ** transferts, unsigned int ret_comp);
int compareFilesLists(char ** transferts, char ** files, char ** liste_captures, int files_nb, int nb_list, unsigned int * indexs, Camera * camera, GPContext * context);
int getVideoDatas (char ** videos, char ** files, char ** liste_captures, unsigned int * files_nb, Camera* camera, GPContext * context, unsigned int * dir_sizes);
int getPhotoDatas (char ** photos, char ** files, char ** liste_captures, unsigned int * files_nb, Camera* camera, GPContext * context, unsigned int * dir_sizes);

#endif