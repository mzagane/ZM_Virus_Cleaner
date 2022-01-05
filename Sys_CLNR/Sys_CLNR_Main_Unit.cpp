/*******************************************************************************
*      Fichier            : Sys_CLNR_Main_Unit.cpp                             *
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

#include <vcl.h>
#include <windows.h>
#include <dir.h>// pour MAXPATH,...
#include "Sys_CLNR_Functions_Unit.h"
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused

char Current_Dir[MAXDIR];//repertoire courant (où se trouve l'excutable)

/**----------------------------------------------------------------------------*
*                       Clean_System                                           *
*       Déscription :                                                          *
*               Le but de cette fonction est de rechercher des virus actives   *
*               et les désactiver et nettoyer la base de registre.             *
*                                                                              *
*-----------------------------------------------------------------------------*/
void __fastcall Clean_System()
{
        char  Path[MAXPATH];
        char Windows_Directory[MAXPATH];// le chemin complet du repertoire windows

        GetWindowsDirectory(Windows_Directory,MAXPATH);

        // yannh
        strcpy(Path,Windows_Directory);
        strcat(Path,"\\system32\\kamsoft.exe");

        if(FileExists(Path))
        {
                if(Scan_File(Path)==1)
                {
                        Kill_Process("explorer.exe");
                        Desable_Auto_Start("kamsoft");
                        Repair_Files_Posting();

                        SetFileAttributes(Path,FILE_ATTRIBUTE_NORMAL );
                        DeleteFile(Path);

                        for(int i=2;i<26;i++)
                        {
                                UINT oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);// pour desactiver le message d'erreur
                                setdisk(i);
                                SetErrorMode(oldErrorMode); // on restitue l'ancienne valeur (pour desactiver le message d'erreur)
                                UINT DriveType=GetDriveType(NULL);
                                if(DriveType!=DRIVE_CDROM)// si le lecteur pas un lecteur CD
                                {
                                        if(FileExists("yannh.cmd") && Scan_File("yannh.cmd")==1)
                                        {
                                                SetFileAttributes("yannh.cmd",FILE_ATTRIBUTE_NORMAL );
                                                DeleteFile("yannh.cmd");
                                                SetFileAttributes("autorun.inf",FILE_ATTRIBUTE_NORMAL );
                                                DeleteFile("autorun.inf");
                                        }
                                }
                        }
                }
        }
        // ratibe
        strcpy(Path,Windows_Directory);
        strcat(Path,"\\media\\SysteM.exe");

        if(FileExists(Path))
        {
                if(Scan_File(Path)==2)
                {
                        Kill_Process("SysteM.exe");
                        Kill_Process("images.exe");
                        Desable_Auto_Start("windows");
                        Repair_Files_Posting();

                        SetFileAttributes(Path,FILE_ATTRIBUTE_NORMAL );
                        DeleteFile(Path);

                        for(int i=2;i<26;i++)
                        {
                                UINT oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);// pour desactiver le message d'erreur
                                setdisk(i);
                                SetErrorMode(oldErrorMode); // on restitue l'ancienne valeur (pour desactiver le message d'erreur)
                                UINT DriveType=GetDriveType(NULL);
                                if(DriveType!=DRIVE_CDROM)// si le lecteur pas un lecteur CD
                                {
                                        if(FileExists("images.exe") && Scan_File("images.exe")==1)
                                        {
                                                SetFileAttributes("images.exe",FILE_ATTRIBUTE_NORMAL );
                                                DeleteFile("images.exe");
                                        }
                                }
                        }
                }
        }
}
/*-----------------------------------------------------------------------------*
*                       </Clean_System>                                        *
*-----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------*
*                                                                              *
*                               Scan_File                                      *
*       Déscription :                                                          *
*               le but de cette fonction est de scanner un fichier en comparent*
*               sa clef MD5 calculée avec les clefs MD5 des virus connus.      *
*       Paramètres :                                                           *
*               - char File_Name[MAXPATH] : le chemin complet du fichier à     *
*               scanaer.                                                       *
*       Valeurs retournées :                                                   *
*               -  -1: impossible d'ouvrir le fichier.                         *
*               -  -2: impossible de charger la base de données des virus.     *
*               -  0 : fichier non infecté                                     *
*               -  1 : virus Yannh                                             *
*               -  2 : virus Ratibe                                            *
*               -  3 : Copy_Host-Copy                                          *
*               -  4 : Copy_Host-Host                                          *
*               -  5 : SSVICHOSST                                              *
*               -  6 : Systems-Mypictures                                      *
*               -  ....                                                        *
*-----------------------------------------------------------------------------*/
int __fastcall Scan_File(char File_Name[MAXPATH])
{
        char Buffer[16];//buffer utiliser dans la lecture des données de fichier a scanner
        FILE * File_Pointer;// pointeur vers le fichier a acanner
        md5_state_t Stat;
        md5_byte_t Result[16];
        static char MD5[32 + 1];
        int Nbr;//utiliser dans la lecture des données de fichier a scanner
        //char Current_Dir[MAXDIR];//repertoire courant (où se trouve l'excutable)
        char VDB_Path[MAXPATH];// le chemin complet de la base de donnée

        TStringList *Virus_DB;//pointeur vers une liste de chaine de
                              //de caractères (la base de données des virus)


        if((File_Pointer = fopen(File_Name, "rb")) == NULL)
        {
                return -1;//impossible d'ouvrir le fichier
        }
        else
        {
                md5_init(&Stat);
		while((Nbr = fread(&Buffer, sizeof(char), 16, File_Pointer)))
		{
			md5_append(&Stat, (const md5_byte_t *)Buffer, Nbr);
		}
		md5_finish(&Stat, Result);
		fclose(File_Pointer);

	}
	for(int i=0;i<16;i++)
        {
                sprintf(MD5 + i * 2, "%02x", Result[i]);
        }
        
        strcpy(VDB_Path,Current_Dir);
        strcat(VDB_Path,"\\VDB.ZMVDB");

        Virus_DB = Load_Virus_DB(VDB_Path,"ZMVDB");

        if(Virus_DB!=NULL)
        {
                for(int i=1;i<Virus_DB->Count;i++)
                {
                        if(strcmp(Virus_DB->Strings[i].SubString(0,32).c_str(),MD5)==0)
                        {
                                delete Virus_DB;
                                return i;
                        }
                }
        }
        else//Virus_DB == NULL
        {
                delete Virus_DB;
                return -2;// impossible de charger la base de données des virus.
        }

        delete Virus_DB;
        return 0;

}
/*-----------------------------------------------------------------------------*
*                       </Scan_File>                                           *
*-----------------------------------------------------------------------------*/


WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
        GetCurrentDirectory(MAXDIR,Current_Dir);// repertoire courent.
        Clean_System();//
        return 0;
}
//---------------------------------------------------------------------------

/**----------------------------------------------------------------------------*
*       Remarques :                                                            *
*               j'ai écrit la fonction Scan_File ici ,et pas au fichier        *
*               Sys_CLNR_Functions_Unit.h avec les autres fonctions,pour éviter*
*               un problème du répertoire courant, dans le projet              *
*               ZM_Virus_CLeaNeR j'ai éviter ce problème en mettant la variable*
*               Current_Dir comme proprieté de la classe Main_Form pour la     *
*               rendre accéssible a partir tous les Modules (unit) du projet   *
*-----------------------------------------------------------------------------*/  
