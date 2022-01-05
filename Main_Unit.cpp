/*******************************************************************************
*      Fichier            : Main_Unit.cpp                                      *
*      Projet             : ZM Virus Cleaner- Cleaner                          *
*      Programmeur        : ZAGANE Mohammed                                    *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mercredi 19 novembre 2008                          *
*      Version source     : 1.15.12.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : lundi 15 décembre 2008                             *
*******************************************************************************/

//---------------------------------------------------------------------------

#pragma hdrstop

#include "Main_Unit.h"
#include "Functions_Unit.h"
#include "About_Unit.h"
#include "Scan_Result_Unit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain_Form *Main_Form;
//---------------------------------------------------------------------------
__fastcall TMain_Form::TMain_Form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Quit_SpeedButtonClick(TObject *Sender)
{
       Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Scan_Computer_SpeedButtonClick(TObject *Sender)
{
        Scan_Component_Options_GroupBox->Visible = true;
        Object_To_Scan_GroupBox->Visible = false;
        Start_Component_Scan_SpeedButton->Visible = false;
        Complet_Scan_Descrption_GroupBox->Visible = true;
        Start_Computer_Scan_SpeedButton->Visible = true;
        Scan_All_Drive_CheckBox->Visible = true;
        Buttons_Panel2->Visible = true;
        Result_Scan_Form->Current_Object_Panel->Visible = true;
        Up_To_Date_GroupBox->Visible = false;
        Main_GroupBox->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::About_SpeedButtonClick(TObject *Sender)
{
        MessageBeep(MB_ICONASTERISK);
        About_Form->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Start_Component_Scan_SpeedButtonClick(TObject *Sender)
{
        TStringList * VDB;
        int Scan_Result;// le résultat de scan.
        AnsiString Virus_Name;// le nom de virus
        char VDB_Path[MAXPATH];// le chemin complet de la base de donnée
        bool Object_Exists = true;

        //intialisation
        Intialization();
        //--

        if(Object_To_Scan_Edit->Text!="")
        {
                Result_Scan_Form->Caption = "Analyse de : "+Object_To_Scan_Edit->Text;
                Result_Scan_Form->Result_Scan_Label->Caption ="";
                Result_Scan_Form->Show();
                Main_Form->Enabled = false;

                if(File_RadioButton->Checked)
                {

                        if(Clean_System_CheckBox->Checked)
                        {
                                ShellExecute(0,"open","Sys_CLNR.exe",0,0,SW_SHOWNORMAL);
                        }
                        Scan_Result = Scan_File(Object_To_Scan_Edit->Text.c_str());
                        Nbr_Files_Scaned++;
                        switch (Scan_Result)
                        {
                                case -1 :
                                {
                                        Main_Form->Nbr_Files_Scaned--;
                                        MessageBox(Main_Form->Handle,"Impossible d'ouvrir le fichier!","ZM Virus CLeaNeR",MB_OK | MB_ICONERROR);
                                }
                                break;
                                case -2 :
                                {
                                        Main_Form->Nbr_Files_Scaned--;
                                        MessageBox(Main_Form->Handle,"impossible de charger la base de données des virus!","ZM Virus CLeaNeR",MB_OK | MB_ICONERROR);
                                }
                                break;
                                case 0 :
                                {
                                        //MessageDlg("Fichier non infecté",mtInformation,TMsgDlgButtons() <<mbOK,0);
                                        Result_Scan_Form->Not_Infected_Image->Visible = true;
                                        Result_Scan_Form->Infected_Image->Visible = false;
                                        Result_Scan_Form->Result_Scan_Label->Caption = "Fichier non infecté";
                                        Result_Scan_Form->Result_Scan_Label->Font->Color = clBlue;
                                        //Result_Scan_Form->Del_Infected_File_SpeedButton->Enabled = false;
                                }
                                break;
                                default :
                                {
                                        //décomposition du chemin du fichier.
                                        char drive[3]=""; // lecteur (c:,d:,...)
                                        char dir[260]="";// repertoire
                                        char file[256]="";// fichier
                                        char ext[256]=""; // l'extancien
                                        _splitpath(Object_To_Scan_Edit->Text.c_str(),drive,dir,file,ext);
                                        strcat(file,ext);

                                        strcpy(VDB_Path,Current_Dir);
                                        strcat(VDB_Path,"\\VDB.ZMVDB");
                                        VDB = Load_Virus_DB(VDB_Path,"ZMVDB");
                                        Virus_Name = VDB->Strings[Scan_Result].SubString(34,VDB->Strings[Scan_Result].Length()-1);

                                        delete VDB;
                                        Nbr_Infected_Files++;
                                        Result_Scan_Form->Not_Infected_Image->Visible = false;
                                        Result_Scan_Form->Infected_Image->Visible = true;
                                        Result_Scan_Form->Result_Scan_Label->Caption = "Fichier infecté";
                                        Result_Scan_Form->Result_Scan_Label->Font->Color = clRed;
                                        Result_Scan_Form->Results_ListView->Clear();
                                        Result_Scan_Form->Results_ListView->Items->Add();
                                        Result_Scan_Form->Results_ListView->Font->Color = clRed;
                                        Result_Scan_Form->Results_ListView->Items->Item[0]->ImageIndex=3;
                                        Result_Scan_Form->Results_ListView->Items->Item[0]->Caption = file;
                                        Result_Scan_Form->Results_ListView->Items->Item[0]->SubItems->Add(Object_To_Scan_Edit->Text.c_str());
                                        Result_Scan_Form->Results_ListView->Items->Item[0]->SubItems->Add(Virus_Name);
                                        Result_Scan_Form->Del_Infected_File_SpeedButton->Enabled = true;
                                }
                                break;
                        }
                }
                else if(Drive_Dir_RadioButton->Checked)
                {
                        if(DirectoryExists(Object_To_Scan_Edit->Text))
                        {
                                if(Object_To_Scan_Edit->Text.Length() == 3 && Object_To_Scan_Edit->Text[2]==':' && Object_To_Scan_Edit->Text[3]=='\\')
                                {
                                        Object_To_Scan_Edit->Text = Object_To_Scan_Edit->Text.SubString(0,Object_To_Scan_Edit->Text.Length()-1);// un lecteur (exemple c:\ devient c:)
                                }
                                Scan_Directory(Object_To_Scan_Edit->Text,Scan_Sub_Dirs_CheckBox->Checked);
                        }
                        else
                        {
                                MessageBox(Main_Form->Handle,"Le dossier que vous avez entré n'existe pas!","ZM Virus CLeaNeR",MB_OK | MB_ICONERROR);
                        }

                }

                if(Nbr_Files_Scaned==0)
                {
                        Result_Scan_Form->Close();
                        Main_Form->Enabled = true;
                        return;
                }

                //Result_Scan_Form->Nbr_Dirs_Scaned_Label->Caption = "Dossiers analysés : " + IntToStr(Nbr_Dirs_Scaned);
                Result_Scan_Form->Nbr_Files_Scaned_Label->Caption = "Fichiers analysés : " + IntToStr(Nbr_Files_Scaned);
                Result_Scan_Form->Nbr_Infected_Files_Label->Caption = "Fichiers infectés : " + IntToStr(Nbr_Infected_Files);
                Result_Scan_Form->Current_Scaned_File_Label->Caption = "Fichier : ";
                Result_Scan_Form->Current_Scaned_Dir_Label->Caption = "Fichier : ";

                Scan_Terminated = true;

                if(Nbr_Infected_Files==0)
                {
                        Result_Scan_Form->Not_Infected_Image->Visible = true;
                        Result_Scan_Form->Infected_Image->Visible = false;
                        Result_Scan_Form->Result_Scan_Label->Font->Color = clBlue;
                        Result_Scan_Form->Result_Scan_Label->Visible = true;

                        if(File_RadioButton->Checked)
                        {
                                Result_Scan_Form->Result_Scan_Label->Caption = "Fichier non infecté";
                        }
                        else
                        {
                                Result_Scan_Form->Result_Scan_Label->Caption = "Aucun Virus trouvé";
                        }

                }
                else
                {
                        Result_Scan_Form->Infected_Image->Visible = true;
                        Result_Scan_Form->Not_Infected_Image->Visible = false;
                        Result_Scan_Form->Result_Scan_Label->Font->Color = clRed;
                        Result_Scan_Form->Result_Scan_Label->Visible = true;
                        Result_Scan_Form->Del_Infected_File_SpeedButton->Enabled = true;
                        
                        if(File_RadioButton->Checked)
                        {
                                Result_Scan_Form->Result_Scan_Label->Caption = "Fichier infecté";
                        }
                        else
                        {
                                Result_Scan_Form->Result_Scan_Label->Caption = "Virus trouvé(s)";
                        }

                }

                if(Scan_Canceled)
                {
                        Result_Scan_Form->Scan_Statut_Label->Visible = true;
                        Result_Scan_Form->Scan_Statut_Label->Caption = "Analyse interrompu!";
                        Result_Scan_Form->Scan_Statut_Label->Font->Color = clGreen;
                }
                else       
                {
                        Result_Scan_Form->Scan_Statut_Label->Visible = true;
                        Result_Scan_Form->Scan_Statut_Label->Caption = "Analyse terminé";
                        Result_Scan_Form->Scan_Statut_Label->Font->Color = clBlue;
                        MessageBox(Result_Scan_Form->Handle,"Analyse terminé","ZM Virus CLeaNeR",MB_OK | MB_ICONINFORMATION);
                }


        }
        else
        {       
                MessageBox(Main_Form->Handle,"Veuillez entrer le chemin du composant à analyser","ZM Virus CLeaNeR",MB_OK | MB_ICONWARNING);
        }
}
//---------------------------------------------------------------------------


void __fastcall TMain_Form::Scan_Component_SpeedButtonClick(
      TObject *Sender)
{
        Scan_Component_Options_GroupBox->Visible = true;
        Object_To_Scan_GroupBox->Visible = true;
        Complet_Scan_Descrption_GroupBox->Visible = false;
        Scan_All_Drive_CheckBox->Visible = false;
        Buttons_Panel2->Visible = true;
        Start_Computer_Scan_SpeedButton->Visible = false;
        Start_Component_Scan_SpeedButton->Visible = true;
        Result_Scan_Form->Current_Object_Panel->Visible = true;
        Main_GroupBox->Visible = true;        
}
//---------------------------------------------------------------------------




void __fastcall TMain_Form::Brows_SpeedButtonClick(TObject *Sender)
{
        AnsiString Object_Path;
        if(Drive_Dir_RadioButton->Checked)
        {
                if(SelectDirectory("Choisir le Lecteur ou le dossier à analyser","",Object_Path))
                {
                        Object_To_Scan_Edit->Text = Object_Path;
                }
        }
        else if(File_RadioButton->Checked)
        {
                File_To_Scan_OpenDialog->Title = "Ouvrir un fichier à analsyer";

                if(File_To_Scan_OpenDialog->Execute())
                {
                        Object_To_Scan_Edit->Text = File_To_Scan_OpenDialog->FileName;
                }
        }
        //delete VDB;
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::FormCreate(TObject *Sender)
{
        GetCurrentDirectory(MAXDIR,Current_Dir);// repertoire courent.        
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Start_Computer_Scan_SpeedButtonClick(
      TObject *Sender)
{
        // intialisation
        Intialization();
        //--

        if(Clean_System_CheckBox->Checked)
        {
                ShellExecute(0,"open","Sys_CLNR.exe",0,0,SW_SHOWNORMAL);
        }
        else if(!Scan_All_Drive_CheckBox->Checked)
        {
                MessageBox(Main_Form->Handle,"Veuillez sélectionner au moins une opération!","ZM Virus CLeaNeR",MB_OK | MB_ICONWARNING);
                return;
        }

        if(Scan_All_Drive_CheckBox->Checked)
        {
               Result_Scan_Form->Caption = "Analyse complet de l'ordinateur";
               Result_Scan_Form->Show();
               Main_Form->Enabled = false;
               for(int i=3;i<=26;i++)
               {
                        UINT oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);// pour desactiver le message d'erreur
                        setdisk(i);
                        SetErrorMode(oldErrorMode); // on restitue l'ancienne valeur (pour desactiver le message d'erreur)
                        UINT DriveType=GetDriveType(NULL);
                        SetErrorMode(oldErrorMode); // on restitue l'ancienne valeur (pour desactiver le message d'erreur)
                        if(DriveType != DRIVE_REMOVABLE )// si le lecteur n'est pas amovible
                        {
                                switch (i)
                                {
                                        /*
                                        case 1 :
                                        {
                                                Scan_Directory("a:\\",true);
                                        }
                                        break;
                                        case 2 :
                                        {
                                                Scan_Directory("b:",true);
                                        }
                                        break;
                                        */
                                        case 3 :
                                        {
                                                Scan_Directory("c:",true);
                                        }
                                        break;
                                        case 4 :
                                        {
                                                Scan_Directory("d:",true);
                                        }
                                        break;
                                        case 5 :
                                        {
                                                Scan_Directory("e:",true);
                                        }
                                        break;
                                        case 6 :
                                        {
                                                Scan_Directory("f:",true);
                                        }
                                        break;
                                        case 7 :
                                        {
                                                Scan_Directory("g:",true);
                                        }
                                        break;
                                        case 8 :
                                        {
                                                Scan_Directory("h:",true);
                                        }
                                        break;
                                        case 9 :
                                        {
                                                Scan_Directory("i:",true);
                                        }
                                        break;
                                        case 10 :
                                        {
                                                Scan_Directory("j:",true);
                                        }
                                        break;
                                        case 11 :
                                        {
                                                Scan_Directory("k:",true);
                                        }
                                        break;
                                        case 12 :
                                        {
                                                Scan_Directory("l:",true);
                                        }
                                        break;
                                        case 13 :
                                        {
                                                Scan_Directory("m:",true);
                                        }
                                        break;
                                        case 14 :
                                        {
                                                Scan_Directory("n:",true);
                                        }
                                        break;
                                        case 15 :
                                        {
                                                Scan_Directory("o:",true);
                                        }
                                        break;
                                        case 16 :
                                        {
                                                Scan_Directory("p:",true);
                                        }
                                        break;
                                        case 17 :
                                        {
                                                Scan_Directory("q:",true);
                                        }
                                        break;
                                        case 18 :
                                        {
                                                Scan_Directory("r:",true);
                                        }
                                        break;
                                        case 19 :
                                        {
                                                Scan_Directory("s:",true);
                                        }
                                        break;
                                        case 20 :
                                        {
                                                Scan_Directory("t:",true);
                                        }
                                        break;
                                        case 21 :
                                        {
                                                Scan_Directory("u:",true);
                                        }
                                        break;
                                        case 22 :
                                        {
                                                Scan_Directory("v:",true);
                                        }
                                        break;
                                        case 23 :
                                        {
                                                Scan_Directory("x:",true);
                                        }
                                        break;
                                        case 24 :
                                        {
                                                Scan_Directory("w:",true);
                                        }
                                        break;
                                        case 25 :
                                        {
                                                Scan_Directory("y:",true);
                                        }
                                        break;
                                        case 26 :
                                        {
                                                Scan_Directory("z:",true);
                                        }
                                        break;
                                }
                        }

               }
                Result_Scan_Form->Nbr_Dirs_Scaned_Label->Caption = "Dossiers analysés : " + IntToStr(Nbr_Dirs_Scaned);
                Result_Scan_Form->Nbr_Files_Scaned_Label->Caption = "Fichiers analysés : " + IntToStr(Nbr_Files_Scaned);
                Result_Scan_Form->Nbr_Infected_Files_Label->Caption = "Fichiers infectés : " + IntToStr(Nbr_Infected_Files);
                Result_Scan_Form->Current_Scaned_File_Label->Caption = "Fichier : ";
                Result_Scan_Form->Current_Scaned_Dir_Label->Caption = "Fichier : ";

                Scan_Terminated = true;

                if(Scan_Canceled)
                {
                        Result_Scan_Form->Scan_Statut_Label->Visible = true;
                        Result_Scan_Form->Scan_Statut_Label->Caption = "Analyse interrompu!";
                        Result_Scan_Form->Scan_Statut_Label->Font->Color = clGreen;
                }
                else
                {
                        Result_Scan_Form->Scan_Statut_Label->Visible = true;
                        Result_Scan_Form->Scan_Statut_Label->Caption = "Analyse terminé";
                        Result_Scan_Form->Scan_Statut_Label->Font->Color = clBlue;
                        MessageBox(Result_Scan_Form->Handle,"Analyse terminé","ZM Virus CLeaNeR",MB_OK | MB_ICONINFORMATION);

                }

                if(Nbr_Infected_Files==0)
                {
                        Result_Scan_Form->Not_Infected_Image->Visible = true;
                        Result_Scan_Form->Infected_Image->Visible = false;
                        Result_Scan_Form->Result_Scan_Label->Caption = "Aucun Virus trouvé";
                        Result_Scan_Form->Result_Scan_Label->Font->Color = clBlue;
                        Result_Scan_Form->Result_Scan_Label->Visible = true;
                }
                else
                {
                        Result_Scan_Form->Infected_Image->Visible = true;
                        Result_Scan_Form->Not_Infected_Image->Visible = false;
                        Result_Scan_Form->Result_Scan_Label->Caption = "Virus trouvé(s)";
                        Result_Scan_Form->Result_Scan_Label->Font->Color = clRed;
                        Result_Scan_Form->Result_Scan_Label->Visible = true;
                        Result_Scan_Form->Del_Infected_File_SpeedButton->Enabled = true;
                }

        }
}
//---------------------------------------------------------------------------




void __fastcall TMain_Form::Hid_Work_Space_SpeedButtonClick(
      TObject *Sender)
{       
        Main_GroupBox->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Chck_For_Updt_Site_LabelClick(TObject *Sender)
{
        ShellExecute(0,"open","http://zaagane-mohammed.ifrance.com/zm_vclnr.php",0,0,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Up_To_Date_SpeedButtonClick(TObject *Sender)
{
        Main_GroupBox->Visible = true;
        Scan_Component_Options_GroupBox->Visible = false;
        Up_To_Date_GroupBox->Visible = true;
        Start_Component_Scan_SpeedButton->Visible = false;
        Start_Computer_Scan_SpeedButton->Visible = false;
        Buttons_Panel2->Visible = true;
}
//---------------------------------------------------------------------------
//intialisation
void __fastcall TMain_Form::Intialization()
{
        Scan_Terminated = false;
        Scan_Canceled = false;
        Nbr_Files_Scaned = 0;
        Nbr_Dirs_Scaned = 0;
        Nbr_Repared_Files = 0;
        Nbr_Infected_Files = 0;
        if(Result_Scan_Form->Results_ListView->Items->Count!=0)
        {
                Result_Scan_Form->Results_ListView->Clear();
        }
        Result_Scan_Form->Nbr_Dirs_Scaned_Label->Caption = "Dossiers analysés : ";
        Result_Scan_Form->Nbr_Files_Scaned_Label->Caption = "Fichiers analysés : ";
        Result_Scan_Form->Nbr_Infected_Files_Label->Caption = "Fichiers infectés : ";
        Result_Scan_Form->Nbr_Repared_Files_Label->Caption = "Fichiers réparés : ";
        Result_Scan_Form->Current_Scaned_Dir_Label->Caption = "Dossier :";
        Result_Scan_Form->Current_Scaned_File_Label->Caption = "Fichier :";
        Result_Scan_Form->Infected_Image->Visible = false;
        Result_Scan_Form->Not_Infected_Image->Visible = false;
        Result_Scan_Form->Result_Scan_Label->Caption = "";
        Result_Scan_Form->Result_Scan_Label->Font->Color = clBlue;
        Result_Scan_Form->Result_Scan_Label->Visible = false;
        Result_Scan_Form->Scan_Statut_Label->Visible = false;
        Result_Scan_Form->Del_Infected_File_SpeedButton->Enabled = false;
        //--
}
void __fastcall TMain_Form::Quitter1Click(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Mettrejour1Click(TObject *Sender)
{
        Up_To_Date_SpeedButtonClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Analyseruncomposant1Click(TObject *Sender)
{
        Scan_Component_SpeedButtonClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Analyserlordinateur1Click(TObject *Sender)
{
        Scan_Computer_SpeedButtonClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Apropos1Click(TObject *Sender)
{
        About_SpeedButtonClick(Sender);        
}
//---------------------------------------------------------------------------


void __fastcall TMain_Form::Drive_Dir_RadioButtonClick(TObject *Sender)
{
        Scan_Sub_Dirs_CheckBox->Visible = true;        
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::File_RadioButtonClick(TObject *Sender)
{
        Scan_Sub_Dirs_CheckBox->Visible = false;        
}
//---------------------------------------------------------------------------





