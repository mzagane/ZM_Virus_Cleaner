/*******************************************************************************
*      Fichier            : Sys_CLNR_Functions_Unit.cpp                        *
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


#pragma hdrstop
#include "Sys_CLNR_Functions_Unit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/**----------------------------------------------------------------------------*
*                                Fonction : Auto_Start                         *
*       Déscription :                                                          *
*               Le but de cette fonction est de créer la valeur 'Value_Name'   *
*               dans la base de registre, exactement dans la clé (Run) pour    *
*               permet au programme dont le chemin est 'Program_Path' de       *
*               démarrer avec l'ordinateur.                                    *
*       Paramètres :                                                           *
*               - char Program_Path[MAXPATH] : le chemin complet du programme. *
*               - char Value_Name[25] : le nom de la valeur à ajouter dans la  *
*                                       de registre.                           *
*       Valeurs retournées :                                                   *
*               - true : la fonction a réussi.                                 *
*               - false: la fonction a échoué.                                 *
*-----------------------------------------------------------------------------*/
bool __fastcall Auto_Start(char Program_Path[MAXPATH],char Value_Name[25])
{
        TRegistry *Reg = new TRegistry();
        Reg->RootKey = HKEY_LOCAL_MACHINE;

        if(Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
        {
                Reg->WriteString(Value_Name,Program_Path);
                Reg->CloseKey();
                delete Reg;
                return true;
        }
        else
        {
                delete Reg;
                return false;
        }
}
/*-----------------------------------------------------------------------------*
*                                 </Auto_Start>                                *
*-----------------------------------------------------------------------------*/


/**----------------------------------------------------------------------------*
*                                Fonction : Desable_Auto_Start                 *
*       Déscription :                                                          *
*               Le but de cette fonction est de supprimer la valeur'Value_Name'*
*               de la base de registre, exactement de la clé (Run)             *
*       Paramètres :                                                           *
*               - char Value_Name[25] : le nom de la valeur à supprimer de la  *
*                                       base de registre.                      *
*       Valeurs retournées :                                                   *
*               - true : la fonction a réussi.                                 *
*               - false: la fonction a échoué.                                 *
*-----------------------------------------------------------------------------*/
bool __fastcall Desable_Auto_Start(char Value_Name[50])
{
        TRegistry *Reg = new TRegistry();
        bool Function_Statut=true;// l'etat de la fonction

        // Local Machine
        Reg->RootKey = HKEY_LOCAL_MACHINE;
        //Run
        if(Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
        {
                if(Reg->ValueExists(Value_Name))
                {
                        if(Reg->DeleteValue(Value_Name))
                        {
                                Reg->CloseKey();
                        }
                        else
                        {
                                Function_Statut = false;
                                Reg->CloseKey();
                        }
                }
                else
                {
                        Reg->CloseKey();
                }
        }
        else
        {
                Function_Statut = false;
        }
        //RunBackup
        if(Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\RunBackup", false))
        {
                if(Reg->ValueExists(Value_Name))
                {
                        if(Reg->DeleteValue(Value_Name))
                        {
                                Reg->CloseKey();
                        }
                        else
                        {
                                Function_Statut = false;
                                Reg->CloseKey();
                        }
                }
                else
                {
                        Reg->CloseKey();
                }
        }
        else
        {
                Function_Statut = false;
        }

        // Current User
        Reg->RootKey = HKEY_CURRENT_USER;
        //Run
        if(Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
        {
                if(Reg->ValueExists(Value_Name))
                {
                        if(Reg->DeleteValue(Value_Name))
                        {
                                Reg->CloseKey();
                        }
                        else
                        {
                                Function_Statut = false;
                                Reg->CloseKey();
                        }
                }
                else
                {
                        Reg->CloseKey();
                }
        }
        else
        {
                Function_Statut = false;
        }
        //RunBackup
        if(Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\RunBackup", false))
        {
                if(Reg->ValueExists(Value_Name))
                {
                        if(Reg->DeleteValue(Value_Name))
                        {
                                Reg->CloseKey();
                        }
                        else
                        {
                                Function_Statut = false;
                                Reg->CloseKey();
                        }
                }
                else
                {
                        Reg->CloseKey();
                }
        }
        else
        {
                Function_Statut = false;
        }

        delete Reg;
        return Function_Statut;
}
/*-----------------------------------------------------------------------------*
*                                 </Desable_Auto_Start>                        *
*-----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------*
*                      Repair_Files_Posting                                    *
*                                                                              *
*       Déscription :                                                          *
*               le but de cette fonction est la réparation de l'affichage des  *
*               fichiers cachés et systèmes.en réparant deux valeurs dans la   *
*               base de registre.                                              * 
*       Valeurs retournées :                                                   *
*               - true : la fonction a réussi.                                 *
*               - false : la fonction a échoué.                                *
*-----------------------------------------------------------------------------*/

bool __fastcall Repair_Files_Posting()
{
        TRegistry *Reg = new TRegistry();
        bool Function_Statut = true;// l'état de la fonction

        Reg->RootKey = HKEY_LOCAL_MACHINE;

        // fichiers systèmes
        if(Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\Folder\\SuperHidden",false))
        {
                Reg->WriteInteger("UncheckedValue",1);// modifier la valeur en 1
                Reg->CloseKey();
        }
        else
        {
                Function_Statut = false;
        }

        // fichiers cachés
        if(Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\Folder\\Hidden\\SHOWALL",false))
        {
                Reg->WriteInteger("CheckedValue",1);// modifier la valeur en 1
                Reg->CloseKey();
        }
        else
        {
                Function_Statut = false;
        }

        delete Reg;
        return Function_Statut;
}

/*-----------------------------------------------------------------------------*
*                       </Repair_Files_Posting>                                *
*-----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------*
*                     Kill_Process                                             *
*       Déscription :                                                          *
*               Cette fonction permet de terminer un processus                 *
*       Paramètres :                                                           *
*               - char *Process_Name : le nom du processus à terminer          *
*       Valeurs retournées :                                                   *
*               - true : la fonction a réussi.                                 *
*               - false : la fonction a échoué.                                *
*       Remarque :                                                             *
*               le code de cette fonction est Distribué par :                  *
*               http://www.developpez.com ; Auteur : MiGoN                     *
*                                                                              *
*-----------------------------------------------------------------------------*/
bool __fastcall  Kill_Process(char *Process_Name)
{
        //Recherche du processus:
        HANDLE hSnapShot;
        PROCESSENTRY32 uProcess;
        bool r;
        unsigned int PID = 0; //variable qui va stocker l'ID du processus de l'application que l'on désire fermer.

        hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);
        uProcess.dwSize = (DWORD) sizeof(PROCESSENTRY32);

        r = Process32First(hSnapShot, &uProcess);
        do   // Cette boucle énnumère tout les processus
        {
                //on cherche le nom de notre application dans le chemin d'accès de l'éxécutable du processus.
                if ( !strcmp(uProcess.szExeFile, Process_Name) )
                PID = (unsigned int) uProcess.th32ProcessID;

                r = Process32Next(hSnapShot, &uProcess);
        } while ( r );

        CloseHandle(hSnapShot);

        if ( PID == 0)
        {
                return false;
        }

        //Fermeture du processus:
        HANDLE hTemp = OpenProcess(PROCESS_ALL_ACCESS, false, (DWORD) PID);
        TerminateProcess(hTemp,0);

        return true;
}
/*-----------------------------------------------------------------------------*
*                       </Kill_Process>                                        *
*-----------------------------------------------------------------------------*/




/**----------------------------------------------------------------------------*
*       Fonction    : unsigned char Reverse_Bit(unsigned char bit)	       *
*       Déscription : permet d'inverser un bit (0-->1 et 1-->0)	               *
*       Paramètres  : - unsigned char bit : le bit à inverser 0 ou 1	       *
*       Valeur retournée : bit inversé				               *
*-----------------------------------------------------------------------------*/
unsigned char Reverse_Bit(unsigned char bit)
{

	if(bit==0)
	{
	        return 1;
	}
	else if(bit==1)
	{
	        return 0;
	}
}

/**----------------------------------------------------------------------------*
*       Fonction    : char Crypter_Char(char caractere, char cle)	       *
*       Déscription : cette fonction crypte un caractère en mofifiant ses bits *
*       Paramètres  : - char caractere : le cractère à crypter                 *
*		   - char cle  : le caractère clé du cryptage                  *
*       Valeur retournée : un caractère crypter			               *
*-----------------------------------------------------------------------------*/
char Crypter_Char(char Character,char Key)
{
        union TSChar
        {
                char chr;
                struct
                {
                        unsigned char Bit0 : 1;
	                unsigned char Bit1 : 1;
	                unsigned char Bit2 : 1;
	                unsigned char Bit3 : 1;
	                unsigned char Bit4 : 1;
	                unsigned char Bit5 : 1;
	                unsigned char Bit6 : 1;
	                unsigned char Bit7 : 1;
                };
        };

        
	TSChar Char_Character;// pour représenter le cractère à crypter
	TSChar Char_Key;// pour représenter le cractère 'clé' du cryptage

	Char_Character.chr=Character;
	Char_Key.chr=Key;

        // Bit0
        if(Char_Key.Bit0==1)
        {
	        Char_Character.Bit0=Reverse_Bit(Char_Character.Bit0);
	}

	// Bit1
	if((Char_Key.Bit1==1) || (Char_Key.Bit0==1))
	{
	        Char_Character.Bit1=Reverse_Bit(Char_Character.Bit1);
	}

	// Bit2
	if((Char_Key.Bit2==1) || (Char_Key.Bit1==1) || (Char_Key.Bit0==1))
	{
	        Char_Character.Bit2=Reverse_Bit(Char_Character.Bit2);
	}

	// Bit3
	if((Char_Key.Bit3==1) || (Char_Key.Bit2==1) || (Char_Key.Bit1==1) || (Char_Key.Bit0==1))
	{
	        Char_Character.Bit3=Reverse_Bit(Char_Character.Bit3);
	}

	// Bit4
	if((Char_Key.Bit4==1) || (Char_Key.Bit3==1) || (Char_Key.Bit2==1) || (Char_Key.Bit1==1) || (Char_Key.Bit0==1))
	{
	        Char_Character.Bit4=Reverse_Bit(Char_Character.Bit4);
	}

	// Bit5
	if((Char_Key.Bit5==1) || (Char_Key.Bit4==1) || (Char_Key.Bit3==1) || (Char_Key.Bit2==1) || (Char_Key.Bit1==1) || (Char_Key.Bit0==1))
	{
	        Char_Character.Bit5=Reverse_Bit(Char_Character.Bit5);
	}

	// Bit6
        if((Char_Key.Bit6==1) || (Char_Key.Bit5==1) || (Char_Key.Bit4==1) || (Char_Key.Bit3==1) || (Char_Key.Bit2==1) || (Char_Key.Bit1==1) || (Char_Key.Bit0==1))
	{
	        Char_Character.Bit6=Reverse_Bit(Char_Character.Bit6);
	}

	// Bit7
	if((Char_Key.Bit7==1) || (Char_Key.Bit6==1) || (Char_Key.Bit5==1) ||(Char_Key.Bit4==1) || (Char_Key.Bit3==1) || (Char_Key.Bit2==1) || (Char_Key.Bit1==1) || (Char_Key.Bit0==1))
	{
	        Char_Character.Bit7=Reverse_Bit(Char_Character.Bit7);
	}

	return Char_Character.chr;

}

/**----------------------------------------------------------------------------*
*                               Load_Virus_DB                                  *
*								               *
*       Déscription :                                                          *
*               Le but de cette fonction est de charger la base de données     *
*               des virus.                                                     *
*       Paramètres :                                                           *
*               - char ZMVDB_File_Name[MAXPATH] : le chemin complet du fichier *
*               de la base de données.                                         *
*               - char Crypt_Key[100]: la clé de cryptage utilisée pour crypter*
*                 les données.                                                 *
*       Valeurs retournées :                                                   *
*               - un pointeur vers la listes des signatures si la fonction est *
*                 réussi.                                                      *
*               - NULL si un problème est rencontré.                           *
*-----------------------------------------------------------------------------*/
TStringList *Load_Virus_DB(char ZMVDB_File_Name[MAXPATH],char Crypt_Key[100])
{

        TStringList *Virus_DB = new TStringList();
        TStringList *Crypted_Virus_DB = new TStringList();

        char Buffer[512];
        AnsiString Line;

        if(FileExists(ZMVDB_File_Name))
        {
                Crypted_Virus_DB->LoadFromFile(ZMVDB_File_Name);

                if(Crypted_Virus_DB->Count>0 && Crypted_Virus_DB->Strings[0]!="¤²¨¸¼")
                {
                        return NULL;// fichier incorrect.
                }
                for(int i=0;i<Crypted_Virus_DB->Count;i++)
                {
                        int Index=0;

                        for(int j=0;j<Crypted_Virus_DB->Strings[i].Length();j++)
                        {
                                Buffer[j]=Crypter_Char(Crypted_Virus_DB->Strings[i].c_str()[j],Crypt_Key[Index]);
                                if(Index<(int)strlen(Crypt_Key)-1)
                                {
                                        Index++;
                                }
                                else
                                {
                                        Index=0;
                                }
                        }
                        
                        for(int k=0;k<Crypted_Virus_DB->Strings[i].Length();k++)
                        {
                                Line.Insert(Buffer[k],k+1);
                        }

                        Virus_DB->Add(Line);
                        Line="";
                }

        }
        else
        {
                return NULL;
                //MessageDlg("Fichier incorrect!",mtError, TMsgDlgButtons() << mbOK,0);
        }

        delete Crypted_Virus_DB;
        return Virus_DB;
}



