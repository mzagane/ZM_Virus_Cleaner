/*******************************************************************************
*      Fichier            : Sys_CLNR_Functions_Unit.h                          *
*      Projet             : ZM Virus Cleaner- Cleaner                          *
*      Programmeur        : ZAGANE Mohammed                                    *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mercredi 19 novembre 2008                          *
*      Version source     : 1.13.12.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : samedi 13 décembre 2008                            *
*******************************************************************************/
//---------------------------------------------------------------------------

#ifndef Functions_UnitH
#define Functions_UnitH
//---------------------------------------------------------------------------
#endif
#include <vcl.h>
#include <Registry.hpp>
#include <tlhelp32.h>// pour fonctions utilisées dans la fonction qui termine un programme
#include <dir.h>// pour MAXPATH
#include <stdio.h>// pour FILE,..
#include "md5.h"

// déclaration des fonctions
bool __fastcall Auto_Start(char Program_Path[MAXPATH],char Value_Name[25]);
bool __fastcall Desable_Auto_Start(char Value_Name[50]);
bool __fastcall Repair_Files_Posting();//réparer l'affichage des fichiers.
bool __fastcall Kill_Process(char *Process_Name);
int  __fastcall Scan_File(char File_Name[MAXPATH]);
TStringList *Load_Virus_DB(char ZMVDB_File_Name[MAXPATH],char Crypt_Key[100]);
TStringList *Scan_Directory(char Directory_Name[MAXPATH], bool Scan_Sub_Dirs);

