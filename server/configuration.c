//
// Created by pdata on 18.05.17.
//
#include <libconfig.h>
#include <stdlib.h>

config_t cfg;

const char *str;
const int *port;
config_setting_t *setting;

int init_configuration(char * config_path){


    config_init(&cfg);

    if(! config_read_file(&cfg, "/home/pdata/Podyplomowka/podstawy_c/zadanie/server/config"))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }


}
char *  get_config_option(char * option_name){

    if(config_lookup_string(&cfg, option_name, &str)){
        printf("Succesfully read of configuration variable  : %s : %s\n", option_name,str);
        return str;
    }
    else
        fprintf(stderr, "No 'port' setting in configuration file.\n");
        return "";

}

void destroy_configuration(){
    config_destroy(&cfg);

}