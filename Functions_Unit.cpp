/*******************************************************************************
*      Fichier            : Functions_Unit.cpp                                 *
*      Projet             : ZM Virus Cleaner- Cleaner                          *
*      Programmeur        : ZAGANE Mohammed                                    *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mercredi 19 novembre 2008                          *
**      Version source     : 1.15.12.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : lundi 15 d�cembre 2008                             *
*******************************************************************************/

//---------------------------------------------------------------------------


#pragma hdrstop
#include "Functions_Unit.h"
#include "Main_Unit.h"// pour utiliser la variable globalle 'Current_Dir'
#include "Scan_Result_Unit.h"

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
*               - un pointeur vers la listes des signatures si la fonction a   *
*                 r�ussi.                                                      *
*               - NULL si un probl�me a �t� rencontr�.                         *
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


/**----------------------------------------------------------------------------*
*                                                                              *
*                               Scan_File                                      *
*       D�scription :                                                          *
*               le but de cette fonction est de scanner un fichier en comparent*
*               sa clef MD5 calcul�e avec les clefs MD5 des virus connus.      *
*       Param�tres :                                                           *
*               - char File_Name[MAXPATH] : le chemin complet du fichier �     *
*               scanaer.                                                       *
*       Valeurs retourn�es :                                                   *
*               -  -1: impossible d'ouvrir le fichier.                         *
*               -  -2: impossible de charger la base de donn�es des virus.     *
*               -  0 : fichier non infect�                                     *
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
        char Buffer[16];//buffer utiliser dans la lecture des donn�es de fichier a scanner
        FILE * File_Pointer;// pointeur vers le fichier a acanner
        md5_state_t Stat;
        md5_byte_t Result[16];
        static char MD5[32 + 1];
        int Nbr;//utiliser dans la lecture des donn�es de fichier a scanner
        //char Current_Dir[MAXDIR];//repertoire courant (o� se trouve l'excutable)
        char VDB_Path[MAXPATH];// le chemin complet de la base de donn�e

        TStringList *Virus_DB;//pointeur vers une liste de chaine de
                              //de caract�res (la base de donn�es des virus)


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

        strcpy(VDB_Path,Main_Form->Current_Dir);
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
                return -2;// impossible de charger la base de donn�es des virus.
        }

        delete Virus_DB;
        return 0;
}
/*-----------------------------------------------------------------------------*
*                       </Scan_File>                                           *
*-----------------------------------------------------------------------------*/


/**----------------------------------------------------------------------------*
*                               Scan_Directory                                 *
*       D�scription :                                                          *
*               Cette fonction permet de scanner les fichiers d'un dossier     *
*               et tous ses sous-dossier.                                      *
*       Param�tres :                                                           *
*               - AnsiString Directory_Name : le chemin complet du dossier �   *
*               scanner.                                                       *
*               - bool Scan_Sub_Dirs : pour indiquer au programme qu'il doit   *
*               scanner les sou-dossier ou non.                                *
*-----------------------------------------------------------------------------*/
void Scan_Directory(AnsiString Directory_Name, bool Scan_Sub_Dirs)
{
        TSearchRec sr;
        Main_Form->Nbr_Dirs_Scaned++;
        Result_Scan_Form->Current_Scaned_Dir_Label->Caption ="Dossier : " + Directory_Name + "\\*.*";
        if(FindFirst(Directory_Name + "\\*.*", faAnyFile , sr) == 0)
        {
                do
                {       if((sr.Attr & faDirectory) == faDirectory)
                        {
                                if(sr.Name !="." && sr.Name!="..")
                                {
                                        if(Scan_Sub_Dirs)
                                        {
                                                Scan_Directory(Directory_Name+"\\"+sr.Name,Scan_Sub_Dirs);
                                                Application->ProcessMessages();
                                        }
                                }

                        }
                        else
                        {
                                Main_Form->Nbr_Files_Scaned++ ;
                                AnsiString Path = Directory_Name;
                                Path = Path +"\\"+ sr.Name;
                                Result_Scan_Form->Current_Scaned_File_Label->Caption = "Fichier : " + Path;
                                int Scan_Result = Scan_File(Path.c_str());
                                switch (Scan_Result)
                                {
                                        case 0 : // fichier non infect�
                                        {
                                                //--
                                        }
                                        break;
                                        case -1:// impossible d'ouvrir le fichier
                                        {
                                                /*
                                                int Index = Result_Scan_Form->Results_ListView->Items->Count;
                                                Result_Scan_Form->Results_ListView->Items->Add();
                                                Result_Scan_Form->Results_ListView->Font->Color = clRed;
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->ImageIndex=2;
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->Caption = sr.Name;
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->SubItems->Add(Directory_Name +"\\"+sr.Name);
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->SubItems->Add("");
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->SubItems->Add("Non v�rifi�(impossible d'ouvrir le fichier)"); // l'etat
                                                Main_Form->Nbr_Files_Scaned--;
                                                */
                                        }
                                        break;
                                        case -2: // impossibvle de charger la base de donn�es des virus
                                        {
                                                Main_Form->Nbr_Files_Scaned--;
                                                MessageDlg("impossible de charger la base de donn�es des virus!",mtError,TMsgDlgButtons() <<mbOK,0);
                                                FindClose(sr);
                                                return;
                                        }
                                        break;
                                        default : // fichier infect�
                                        {
                                                TStringList * VDB;
                                                int Index = Result_Scan_Form->Results_ListView->Items->Count;
                                                Main_Form->Nbr_Infected_Files++;
                                                AnsiString VDB_Path;
                                                VDB_Path = Main_Form->Current_Dir;
                                                VDB_Path = VDB_Path + "\\VDB.ZMVDB";
                                                VDB = Load_Virus_DB(VDB_Path.c_str(),"ZMVDB");
                                                AnsiString Virus_Name = VDB->Strings[Scan_Result].SubString(34,VDB->Strings[Scan_Result].Length()-1);
                                                delete VDB;

                                                Result_Scan_Form->Infected_Image->Visible = true;
                                                Result_Scan_Form->Not_Infected_Image->Visible = false;
                                                Result_Scan_Form->Result_Scan_Label->Caption = "Virus trouv�(s)";
                                                Result_Scan_Form->Result_Scan_Label->Font->Color = clRed;
                                                Result_Scan_Form->Result_Scan_Label->Visible = true;

                                                Result_Scan_Form->Results_ListView->Items->Add();
                                                Result_Scan_Form->Results_ListView->Font->Color = clRed;
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->ImageIndex=3;
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->Caption = sr.Name;
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->SubItems->Add((Directory_Name +"\\"+sr.Name).c_str());
                                                Result_Scan_Form->Results_ListView->Items->Item[Index]->SubItems->Add(Virus_Name);
                                        }
                                        break;
                                }
                                Result_Scan_Form->Nbr_Dirs_Scaned_Label->Caption = "Dossiers analys�s : " + IntToStr(Main_Form->Nbr_Dirs_Scaned);
                                Result_Scan_Form->Nbr_Files_Scaned_Label->Caption = "Fichiers analys�s : " + IntToStr(Main_Form->Nbr_Files_Scaned);
                                Result_Scan_Form->Nbr_Infected_Files_Label->Caption = "Fichiers infect�s : " + IntToStr(Main_Form->Nbr_Infected_Files);
                                Application->ProcessMessages();
                        }

                } while (FindNext(sr) == 0 && !Main_Form->Scan_Canceled);
                FindClose(sr);
        }
}
/*-----------------------------------------------------------------------------*
*                       </Scan_Directory>                                      *
*-----------------------------------------------------------------------------*/
