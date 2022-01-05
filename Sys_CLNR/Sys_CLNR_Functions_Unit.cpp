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
*      Modification       : samedi 13 d�cembre 2008                            *
*******************************************************************************/

//---------------------------------------------------------------------------


#pragma hdrstop
#include "Sys_CLNR_Functions_Unit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/**----------------------------------------------------------------------------*
*                                Fonction : Auto_Start                         *
*       D�scription :                                                          *
*               Le but de cette fonction est de cr�er la valeur 'Value_Name'   *
*               dans la base de registre, exactement dans la cl� (Run) pour    *
*               permet au programme dont le chemin est 'Program_Path' de       *
*               d�marrer avec l'ordinateur.                                    *
*       Param�tres :                                                           *
*               - char Program_Path[MAXPATH] : le chemin complet du programme. *
*               - char Value_Name[25] : le nom de la valeur � ajouter dans la  *
*                                       de registre.                           *
*       Valeurs retourn�es :                                                   *
*               - true : la fonction a r�ussi.                                 *
*               - false: la fonction a �chou�.                                 *
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
*       D�scription :                                                          *
*               Le but de cette fonction est de supprimer la valeur'Value_Name'*
*               de la base de registre, exactement de la cl� (Run)             *
*       Param�tres :                                                           *
*               - char Value_Name[25] : le nom de la valeur � supprimer de la  *
*                                       base de registre.                      *
*       Valeurs retourn�es :                                                   *
*               - true : la fonction a r�ussi.                                 *
*               - false: la fonction a �chou�.                                 *
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
*       D�scription :                                                          *
*               le but de cette fonction est la r�paration de l'affichage des  *
*               fichiers cach�s et syst�mes.en r�parant deux valeurs dans la   *
*               base de registre.                                              * 
*       Valeurs retourn�es :                                                   *
*               - true : la fonction a r�ussi.                                 *
*               - false : la fonction a �chou�.                                *
*-----------------------------------------------------------------------------*/

bool __fastcall Repair_Files_Posting()
{
        TRegistry *Reg = new TRegistry();
        bool Function_Statut = true;// l'�tat de la fonction

        Reg->RootKey = HKEY_LOCAL_MACHINE;

        // fichiers syst�mes
        if(Reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\Folder\\SuperHidden",false))
        {
                Reg->WriteInteger("UncheckedValue",1);// modifier la valeur en 1
                Reg->CloseKey();
        }
        else
        {
                Function_Statut = false;
        }

        // fichiers cach�s
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
*       D�scription :                                                          *
*               Cette fonction permet de terminer un processus                 *
*       Param�tres :                                                           *
*               - char *Process_Name : le nom du processus � terminer          *
*       Valeurs retourn�es :                                                   *
*               - true : la fonction a r�ussi.                                 *
*               - false : la fonction a �chou�.                                *
*       Remarque :                                                             *
*               le code de cette fonction est Distribu� par :                  *
*               http://www.developpez.com ; Auteur : MiGoN                     *
*                                                                              *
*-----------------------------------------------------------------------------*/
bool __fastcall  Kill_Process(char *Process_Name)
{
        //Recherche du processus:
        HANDLE hSnapShot;
        PROCESSENTRY32 uProcess;
        bool r;
        unsigned int PID = 0; //variable qui va stocker l'ID du processus de l'application que l'on d�sire fermer.

        hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);
        uProcess.dwSize = (DWORD) sizeof(PROCESSENTRY32);

        r = Process32First(hSnapShot, &uProcess);
        do   // Cette boucle �nnum�re tout les processus
        {
                //on cherche le nom de notre application dans le chemin d'acc�s de l'�x�cutable du processus.
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
*       D�scription : permet d'inverser un bit (0-->1 et 1-->0)	               *
*       Param�tres  : - unsigned char bit : le bit � inverser 0 ou 1	       *
*       Valeur retourn�e : bit invers�				               *
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
*       D�scription : cette fonction crypte un caract�re en mofifiant ses bits *
*       Param�tres  : - char caractere : le cract�re � crypter                 *
*		   - char cle  : le caract�re cl� du cryptage                  *
*       Valeur retourn�e : un caract�re crypter			               *
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

        
	TSChar Char_Character;// pour repr�senter le cract�re � crypter
	TSChar Char_Key;// pour repr�senter le cract�re 'cl�' du cryptage

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
*       D�scription :                                                          *
*               Le but de cette fonction est de charger la base de donn�es     *
*               des virus.                                                     *
*       Param�tres :                                                           *
*               - char ZMVDB_File_Name[MAXPATH] : le chemin complet du fichier *
*               de la base de donn�es.                                         *
*               - char Crypt_Key[100]: la cl� de cryptage utilis�e pour crypter*
*                 les donn�es.                                                 *
*       Valeurs retourn�es :                                                   *
*               - un pointeur vers la listes des signatures si la fonction est *
*                 r�ussi.                                                      *
*               - NULL si un probl�me est rencontr�.                           *
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

                if(Crypted_Virus_DB->Count>0 && Crypted_Virus_DB->Strings[0]!="�����")
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



