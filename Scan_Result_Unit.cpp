/*******************************************************************************
*      Fichier            : Scan_Result_Unit.cpp                               *
*      Projet             : ZM Virus Cleaner- Cleaner                          *
*      Programmeur        : ZAGANE Mohammed                                    *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mercredi 19 novembre 2008                          *
*      Version source     : 1.15.12.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : lundi 15 décembre 2008                             *
/******************************************************************************/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Scan_Result_Unit.h"
#include "Main_Unit.h"
#include <comctrls.hpp>// pour la gestion des composés crés dynamiquement
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TResult_Scan_Form *Result_Scan_Form;
//---------------------------------------------------------------------------
__fastcall TResult_Scan_Form::TResult_Scan_Form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TResult_Scan_Form::Close_SpeedButtonClick(
      TObject *Sender)
{
        if(!Main_Form->Scan_Canceled && !Main_Form->Scan_Terminated)
        {
                MessageBeep(MB_ICONEXCLAMATION);
                if(MessageBox(Result_Scan_Form->Handle,"Analyse en cours, Voulez-vous annuler l'analyse et fermer la fenêtre?","ZM Virus CLeaNeR",MB_YESNO | MB_ICONQUESTION) == IDYES )
                {
                        Main_Form->Scan_Canceled = true;
                        Main_Form->Enabled = true;
                        Close();
                }
        }
        else
        {
                Main_Form->Scan_Canceled = true;
                Main_Form->Enabled = true;
                Close();
        }



}
//---------------------------------------------------------------------------
void __fastcall TResult_Scan_Form::Del_Infected_File_SpeedButtonClick(
      TObject *Sender)
{
        for(int i=0;i<Results_ListView->Items->Count;i++)
        {
                Results_ListView->Items->Item[i]->ImageIndex = 0;
                if(Results_ListView->Items->Item[i]->SubItems->Strings[1]!="")// élément infecté(nom de virus!="")
                {
                        if(FileExists(Results_ListView->Items->Item[i]->SubItems->Strings[0]))
                        {
                                SetFileAttributes(Results_ListView->Items->Item[i]->SubItems->Strings[0].c_str(),FILE_ATTRIBUTE_NORMAL );//éliminer les protection(fichier caché,fichier système, lecture seule)
                                if(DeleteFile(Results_ListView->Items->Item[i]->SubItems->Strings[0].c_str())!=0)
                                {
                                        Main_Form->Nbr_Repared_Files++;
                                        Results_ListView->Items->Item[i]->ImageIndex = 1;
                                        Results_ListView->Items->Item[i]->SubItems->Add("Supprimé");
                                        Result_Scan_Form->Results_ListView->Font->Color = clBlue;
                                        Result_Scan_Form->Result_Scan_Label->Refresh();
                                }
                                else
                                {
                                        Results_ListView->Items->Item[i]->ImageIndex = 2;
                                        Results_ListView->Items->Item[i]->SubItems->Add("Non Supprimé!");
                                }

                        }
                        else
                        {
                                Results_ListView->Items->Item[i]->ImageIndex = 2;
                                Results_ListView->Items->Item[i]->SubItems->Add("Fichier introuvable!");
                        }
                        if(FileExists("autorun.inf"))
                        {
                                SetFileAttributes("autorun.inf",FILE_ATTRIBUTE_NORMAL );
                                DeleteFile("autorun.inf");
                        }
                }

        }
        Nbr_Repared_Files_Label->Caption = "Fichiers réparés : " + IntToStr(Main_Form->Nbr_Repared_Files);
        Del_Infected_File_SpeedButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TResult_Scan_Form::Cancel_Scan_SpeedButtonClick(TObject *Sender)
{
        if(!Main_Form->Scan_Canceled && !Main_Form->Scan_Terminated)
        {
                MessageBeep(MB_ICONEXCLAMATION);
                if(MessageBox(Result_Scan_Form->Handle,"Voulez-vous vraiment annuler l'analyse en cours ?","ZM Virus CLeaNeR",MB_YESNO | MB_ICONQUESTION) == IDYES )
                {
                        Main_Form->Scan_Canceled = true;
                }
        }
        else
        {
                MessageBox(Result_Scan_Form->Handle,"Aucun analyse en cours à annuler!","ZM Virus CLeaNeR",MB_OK | MB_ICONINFORMATION);
        }
}
//---------------------------------------------------------------------------


void __fastcall TResult_Scan_Form::FormCreate(TObject *Sender)
{
        // intialisation de la liste où s'affiche le resultat de l'analyse
        TListColumn  *NewColumn;
        TListItem  *ListItem;
        Results_ListView = new TListView(this);
        Results_ListView->GridLines = true;
        Results_ListView->ReadOnly = true;
        Results_ListView->Parent = Results_GroupBox;
        Results_ListView->Align = alClient;
        Results_ListView->ViewStyle = vsReport;
        NewColumn = Results_ListView->Columns->Add();
        NewColumn->Caption = "Nom du fichier";
        NewColumn->Width = 80;
        NewColumn = Results_ListView->Columns->Add();
        NewColumn->Caption = "Chemin complet";
        NewColumn->Width = 260;
        NewColumn = Results_ListView->Columns->Add();
        NewColumn->Caption = "Nom du virus";
        NewColumn->Width = 80;
        NewColumn = Results_ListView->Columns->Add();
        NewColumn->Caption = "Etat";
        NewColumn->Width = 180;
        //---
        
}
//---------------------------------------------------------------------------

