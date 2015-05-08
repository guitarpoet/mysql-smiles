#ifndef MYSQL_SMILES

#define MYSQL_SMILES

#include "config.h"
#include <mysql/plugin.h>

int mysql_smiles_fragmentor_parse(MYSQL_FTPARSER_PARAM *param);
int mysql_smiles_fragmentor_init(MYSQL_FTPARSER_PARAM *param __attribute__((unused)));
int mysql_smiles_fragmentor_deinit(MYSQL_FTPARSER_PARAM *param __attribute__((unused)));

struct st_mysql_ftparser mysql_smiles_fragmentor_descriptor =
{
  MYSQL_FTPARSER_INTERFACE_VERSION,     /* interface version      */
  mysql_smiles_fragmentor_parse,                /* parsing function       */
  (mysql_smiles_fragmentor_init),               /* parser init function   */
  (mysql_smiles_fragmentor_deinit)              /* parser deinit function */
};

char current_status[255];

struct st_mysql_show_var mysql_smiles_fragmentor_status[] =
{
  {"mysql_smiles_fragmentor_status", (char *)&current_status, SHOW_CHAR}
};

mysql_declare_plugin(mysql_smiles_fragmentor) {
  MYSQL_FTPARSER_PLUGIN,                    		/* type                            */
  &mysql_smiles_fragmentor_descriptor,      		/* descriptor                      */
  "mysql_smiles_fragmentor",                		/* name                            */
  "Jack <guitarpoet@gmail.com>",            		/* author                          */
  "Smiles Fragmentor Plugin",            			/* description                     */
  PLUGIN_LICENSE_GPL,                       		/* plugin license                  */
  (int (*)(void*))mysql_smiles_fragmentor_init,     /* init function (when loaded)     */
  (int (*)(void*))mysql_smiles_fragmentor_deinit,   /* deinit function (when unloaded) */
  0x0001,                                   		/* version                         */
  NULL,                          					/* status variables                */
  NULL,                                     		/* system variables                */
  NULL
}
mysql_declare_plugin_end;

#endif
