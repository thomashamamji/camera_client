#ifndef __MODEL_H__
#define __MODEL_H__

#include <curl/curl.h>

#include "mods.h"

int getModel (char * model, Camera * camera, int * send);
int sendModelHTTP (char * model);

#endif