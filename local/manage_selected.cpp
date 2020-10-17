#include "manage_selected2.h"

void clearBufLast (char * buf, unsigned int len, unsigned int nb) {
    int i;

    for (i = len; i >= len - nb; i--)
        buf[i] = 0;
    return;
}

// Envoi de la photo
void send_request (char *name) {
    printf("Requêtes\n");
    
    CURL *curl;
    CURLcode res;

    char * request_string = (char *) calloc(1000, sizeof(char));
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

unsigned int load_dossiers (char ** dossiers, const char * path, unsigned int * refs) {
    int k=0; //nb de fois ou on detecte les mots "le dossier"
    int l=0;
    int r=0;
    char TAB1[TMaxL] = ""; // va contenir tt le file.txt
    char tmp[100]={0};
    int tab[TMax]={0}; //liée  a k contient les indice de ou les mots "le dossier" sont dans le TAB1
    char code[TMax]=""; //contient les noms des dossiers separés par "+%+"
    char code1[500]="";                    
    char TAB2[]= "Le dossier";
    char TAB3[]="aucun";
    unsigned int * ks = (unsigned int*) calloc(10, sizeof(unsigned int));

    FILE * File;
    File = fopen(path, "r");
    if (File == NULL) {
        exit(0);
    }
  
    int rado = 0;
    int longeur = 0;
    // boucle for pour mettre dans TAB1 
    for(int aze=0; aze<50000; aze++) {
        fgets(tmp,2000,File);
        while(tmp[rado] != 0) { 
            TAB1[longeur] = tmp[rado];
            longeur = longeur+1;
            rado = rado + 1;
        }

        for(int zer=0; zer<100; zer++) {
            tmp[zer] = 0;
        }

        rado=0;
    }

    // compare "le dossier" et TAB1[X] parcour tout TAB1

    for(int c = 0;c < longeur; c++) {
        if(TAB1[c]==TAB2[0]) {
        if(TAB1[c+1]==TAB2[1]) {
        if(TAB1[c+2]==TAB2[2]) {
            if(TAB1[c+3]==TAB2[3])
            {
                if(TAB1[c+4]==TAB2[4])
                {if(TAB1[c+5]==TAB2[5])
                {if(TAB1[c+6]==TAB2[6])
                   {if(TAB1[c+7]==TAB2[7])

                   {
                    if(TAB1[c+8]==TAB2[8])
                     {
                        if(TAB1[c+9]==TAB2[9])    {  
                           
                            tab[k]=c+3;                   
                             k=k+1;
    }}} }}}}}}}}

    int g=0;
    for(int rty=0;rty<k;rty++) {
        g=tab[rty];
        for (int h=0;h<60;h++) {
            if(TAB1[g+h]==TAB3[0]) {
                if(TAB1[g+1+h]==TAB3[1]) {
                    if(TAB1[g+h+2]==TAB3[2]) {
                            if(TAB1[g+h+3]==TAB3[3]) {
                                tab[rty]=0; 
                            }
                        }
                    }
                }

            }
        }
    int q=0;
    int t=0;
    int qsd=0;
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int xk = 0;

    for(int s=0;s<k;s++) {
        if(tab[s] != 0) {
            ks[xk++] = s;
            strcpy(code, "");
            // printf("%d  ,,",tab[s]);
            t = tab[s];
            qsd=0;
            for (int a=0;a<15;a++) {
                if(TAB1[t+a]=='/') {
                    y = 0;
                    while(TAB1[t+a+qsd+2]!=' ') { 
                        code[q]=TAB1[t+a+qsd];
                        printf ("%c", code[q]);
                        dossiers[x][y++] = code[q];
                        qsd++;  
                        q=q+1;
                    }
                    printf ("1\n");
                    x++;
                }
            }

            // code[q]='+';code[q+1]='%';code[q+2]='+';q=q+3;
        }
    }

    t=0;
    int klm=0;
    int fdj=0;
    for(int jkl=0;jkl<k;jkl++) {
        if(tab[jkl]!=0) {
            printf("%d\n",tab[jkl]);
            klm=tab[jkl];
            for (int hjk=0;hjk<100;hjk++) {	
                if(TAB1[klm+hjk]=='#') {
                    while (TAB1[klm+hjk+fdj]!='I') {   
                        code1[t]=TAB1[klm+hjk+fdj];
                        fdj++;
                        t++;
                    }
                }
                fdj=0;
            }
        }
    }

    // for(int u=0;u<10000;u++) {
    //     printf("%c",code1[u]);
    // }


    unsigned int u = 0;
    char * number = (char*) calloc(5, sizeof(char));

    x = 0;

    while (code1[u] != 0) {
        // printf ("%c", code1[u]);
        strcpy(number, "");
        if (code1[u-1] == '#') {
            y = 0;
            while (code1[u] != ' ') {
                number[y++] = code1[u];
                // printf ("%c", code1[u]);
                u++;
            }

            sscanf(number, "%d", &refs[x]);

            // Calcul
            refs[x] = refs[x] + ks[x];
            x++;
        }
        
        u++;
    }

    free(number);
    free(ks);
    fclose(File);

    return x;
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
    int i;

    for (i = 0; i < lines; i++) {
        if (strcmp(historique[i], file) == 0) {
           return 1;
        }
    }

    return 0;
}

void mirroir (char * buf, unsigned int n) {
    int i = 0;
    char car;

    for (i = 0; i < (n+1)/2; i++) {
        car = buf[n-i-1];
        buf[n-i-1] = buf[i];
        buf[i] = car;
    }
}

char * getName (char * buf) {
    unsigned int n = strlen(buf), x = 0;
    char * buffer = (char*) calloc(100, sizeof(char));

    for (int i = n-1; buf[i] != '/'; i--) {
        buffer[x++] = buf[i];
    }

    printf ("%s %d\n", buffer, x);

    mirroir(buffer, x);

    return buffer;
}

// Pour l'envoi
void transferer_noms (char ** liste, unsigned int n_transferts) {
    printf ("Transferts\n\n\n");

    int i = 0;

    char commande[250] = "";
    int file_transfered = 0;

    FILE * HISTORIQUE = fopen("data/images/historique.txt", "a+");

    system("cd data/images/gets");

    char ** hist_lines = (char **) calloc(MAX_CAPTURES, sizeof(char*));

    int x;

    for (x = 0; x < MAX_CAPTURES; x++) {
        hist_lines[x] = (char *) calloc(TAILLE_NOM, sizeof(char));
    }

    x = 0;

    while (fgets(hist_lines[x++], TAILLE_NOM, HISTORIQUE));

    char * current_file = (char *) calloc(TAILLE_NOM, sizeof(char));

    for (i = 0; i < n_transferts; i++) {
        // Il y aura peut être besoin d'insérer les lignes précédentes dans cette boucle

        char * filename = getName(liste[i]);

        // A corriger
        file_transfered = compare_file_historique(liste[i], hist_lines, x);

        if (file_transfered == 0) {
            sprintf(commande, "./get.sh %s %s\n", liste[i], filename);

            printf ("%s\n", commande);

            // Envoyer le nom du nouveau fichier transféré au socket
            system(commande);

            // ÉCIRE DANS L'HISTORIQUE DES TRANSFERTS
            fprintf(HISTORIQUE, "%s\n", filename);

            send_request(filename);
        }

        free(filename);
    }

    for (x = 0; x < MAX_CAPTURES; x++) {
        free(hist_lines[x]);
    }

    free(current_file);
    fclose(HISTORIQUE);
    free(hist_lines);
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
    // system("cd data/images/gets;rm -f *;gphoto2 --get-all-files;ls *.JPG > ../gets.txt;cd ../../..");
    system("./rates.sh");
}

unsigned int parseRating (char * line) {
    int i;

    return line[0] - '0';
}

/*
unsigned int getRating (char * file) {
    char * commande = calloc(300, sizeof(char));
    printf ("Rating\n%s\nsize : %d\n", file, strlen(file));

    sprintf(commande, "cd data/images/gets;exiv2 %s -g Rating > ../tmp/exif.txt;cd ../../..", file);
    // sprintf(commande, "cd data/images/gets;echo $(exiftool -filename -imagesize -exif:fnumber -xmp:all %s) > ../tmp/exif.txt;cd ../../..", file);
    system(commande);
    // execl("/bin/bash", "bash", "-c", commande, (char *) NULL);
    printf ("%s\n", commande);

    // Lecture
    int x = 0;

    printf ("Getting lines\n");

    // Remplissage
    while (fgets(lignes[x], 999, RATING)) {
        printf ("%s\n", lignes[x++]);
    }

    unsigned int rating = parseRating(lignes);

    printf ("Finished\n");

    for (int i = 0; i < 10; i++) {
        free(lignes[i]);
    }

    fclose(RATING);
    free(lignes);
    free(commande);

    return rating;
}
*/

void parseRatings (int * ratings, char ** lines, unsigned int size) {
    // A coder
    // Lecture en imparité d'indexs

    int i = 0, x = 0;

    while (i < size) { // OU x < size
        ratings[x] = parseRating(lines[i]);        
        i++;
    }
}

unsigned int read_dir_list (char ** dossiers, unsigned int * refs) {
    unsigned int dirs_nb = load_dossiers(dossiers, "data/images/gets.txt", refs);

    for (unsigned int i = 0; i < dirs_nb; i++) {
        clearBufLast(dossiers[i], strlen(dossiers[i])-1, 1);
    }

    return dirs_nb; // Nombre de dossiers contenant des fichiers
}

unsigned int read_file_list (char ** files, char ** lines, unsigned int nb, unsigned int starts) {
    unsigned int line_size, x = 0, i, y;

    // Parser la liste de fichiers
    for (i = starts; i < nb; i++) {
        if (lines[i][0] == '#') {
            for (y = 7; y <= 18; y++) {
                files[x][y-7] = lines[i][y];
            }
            x++;
        }

        else if (x != 0) break;
    }

    return x;
}

void handleError(int status) {
    printf ("%d\n", status);
}

static void
ctx_error_func (GPContext *context, const char *str, void *data)
{
        fprintf  (stderr, "\n*** Contexterror ***              \n%s\n",str);
        fflush   (stderr);
}

static void
ctx_status_func (GPContext *context, const char *str, void *data)
{
        fprintf  (stderr, "%s\n", str);
        fflush   (stderr);
}

GPContext* sample_create_context() {
	GPContext *context;

	/* This is the mandatory part */
	context = gp_context_new();

	/* All the parts below are optional! */
        gp_context_set_error_func (context, ctx_error_func, NULL);
        gp_context_set_status_func (context, ctx_status_func, NULL);

	/* also:
	gp_context_set_cancel_func    (p->context, ctx_cancel_func,  p);
        gp_context_set_message_func   (p->context, ctx_message_func, p);
        if (isatty (STDOUT_FILENO))
                gp_context_set_progress_funcs (p->context,
                        ctx_progress_start_func, ctx_progress_update_func,
                        ctx_progress_stop_func, p);
	 */
	return context;
}

// Retourne le status, le reste, dans les pointeurs
int getPlacements(int * rating, char * dir, char * file, GPContext * context, Camera * camera)
{
    int status = 0;
    
    char * data = (char*) malloc(150000 * sizeof(char));
    
    uint64_t size_l = 64000;
      status = gp_camera_file_read(camera,
        dir,
        file,
        GP_FILE_TYPE_NORMAL,
        0,
        data,
        &size_l,
        context 
      );
      std::cout << status;

      try
  {

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open((const Exiv2::byte*) data, size_l);
    // std::cout << image;
    // assert (image.get() != 0);
    image->readMetadata();
 
    Exiv2::XmpData &xmpData = image->xmpData();
    if (xmpData.empty()) {
        std::string error(dir);
        error += ": No XMP data found in the file";
        throw Exiv2::Error(Exiv2::kerErrorMessage, error);
    }
    if (xmpData.empty()) 
      {
        return -1;
        // std::string error(argv[1]);
        // error += ": No XMP properties found in the XMP packet";
        // throw Exiv2::Error(Exiv2::kerErrorMessage, error);
      }
 
    std::string stars = "";

    for (Exiv2::XmpData::const_iterator md = xmpData.begin();
         md != xmpData.end(); ++md) 
      {
          stars = md->toString();
        std::cout //<< std::setfill(' ') << std::left
        //           << std::setw(44)
        //           << md->key() << " "
        //           << std::setw(9) << std::setfill(' ') << std::left
        //           << md->typeName() << " "
        //           << std::dec << std::setw(3)
        //           << std::setfill(' ') << std::right
        //           << md->count() << "\n"
                  << std::dec << stars
                  << std::endl;
      }

      *rating = std::stoi(stars);
 
    // Exiv2::XmpParser::terminate();
 
  }
catch (Exiv2::AnyError& e) 
  {
    std::cout << "Caught Exiv2 exception '" << e << "'\n";
    return -1;
  }

    return 0;

    // std::cout << data;

    // const std::vector<uint8_t> bytes = std::vector<uint8_t> vec(str.begin(), str.end());

    // std::vector<uint8_t> bytes = static_assert(std::is_same<uint8_t, char>::value, "uint8_t is not unsigned char");
    

  // Exiv2::XmpParser::initialize();
  // ::atexit(Exiv2::XmpParser::terminate);

}

unsigned int get_files_and_dirs (char *** dirs_b, char ** dirs_n, char ** lines, unsigned int nb, unsigned int * sizes_list) {
    // Executer read_dir_list, read_file_list puis blockerize ...
    unsigned int * ref_lines = (unsigned int*) calloc(MIN_DIRS, sizeof(unsigned int));
    char ** files = (char**) calloc(1000, sizeof(char*));
    unsigned int x, y, z;

    printf ("Parsing ...\n");

    for (int i = 0; i < 1000; i++) {
        files[i] = (char*) calloc(100, sizeof(char));
    }

    unsigned int lines_nb = read_dir_list(dirs_n, ref_lines);
    unsigned int tmp_size, tmp_y = 0;

    printf("%d", lines_nb);

    for (x = 0; x < lines_nb; x++) {
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 100; j++) {
                files[i][j] = 0;
            }
        }

        tmp_size = read_file_list(files, lines, nb, ref_lines[x]); // ref_line est la lignes où commencer

        for (y = 0; y < tmp_size; y++) {
            strcpy(dirs_b[x][y], files[y]);
        }

        // tmp_y += tmp_size;
        // z += tmp_size-1;

        x++;
    }

    for (int i = 0; i < 1000; i++) {
        free(files[i]);
    }

    free(files);

    printf ("1");

    return 1;
}

int eachFileRating (char *** dossiers, char ** dirs, char ** transferts, unsigned int * dir_sizes, unsigned int nb_dirs, Camera * camera, GPContext * context) {
    printf("For each rating\n");
    int y = 0;

    char * commande = (char*) calloc(300, sizeof(char));
    char * nom = (char*) calloc(15, sizeof(char));
    char * files = (char*) calloc(10000, sizeof(char));

    printf ("Allocating size : %d\n", nb_dirs);

    int * ratings = (int*) calloc(nb_dirs, sizeof(int));

    FILE * RATING = fopen("data/images/rating.txt", "w");
    FILE * RATINGS = fopen("data/images/tmp/exif.txt", "r");

    // Vider le fichier
    system("echo "" > ./data/tmp/exif.txt");
    system(commande);

    unsigned int i = 0, x = 0;

    for (int y = 0; y < nb_dirs; y++) {
        while (dossiers[y][i][0] != 0) {
            // Commande
            getPlacements(&ratings[y], dirs[y], dossiers[y][i], context, camera);
            if (ratings[y] == 5) {
                sprintf(transferts[x++], "%s/%s", dirs[y], dossiers[y][i]);
            }

            fprintf(RATING, "%s : %d\n", dirs[y], ratings[y]);
            i++;
        }
    }

    printf ("Lancement de la commande.\n");
    printf ("Commande lancée.\n");

    // Traiter chaque image
    i = 0;
    unsigned int rating = 0;

    char ** lignes = (char**) calloc(10000, sizeof(char*));

    for (int i = 0; i < 10000; i++) {
        lignes[i] = (char*) calloc(100, sizeof(char));
    }

    // while (fgets(lignes[i++], 99, RATINGS));

    // parseRatings(ratings, lignes, nb_dirs);

    // for (y = 0; y < nb_dirs; y++) {
    //     for (i = 0; i < dir_sizes[y]; i++) {
    //         // Pour chaque rating recus

    //         if (ratings[i+y] == 5) {
    //             strcpy(transferts[x++], dossiers[y][i]);
    //         }

    //         fprintf(RATING, "%s : %s\n", dirs[i], dossiers[y][i]);
    //     }
    // }

    fclose(RATING);
    fclose(RATINGS);

    for (int i = 0; i < 10000; i++) {
        free(lignes[i]);
    }

    free(lignes);
    free(commande);
    free(nom);
    free(ratings);
    free(files);

    return x;
}