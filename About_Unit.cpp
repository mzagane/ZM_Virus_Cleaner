/*******************************************************************************
*      Fichier            : About_Unit.cpp                                     *
*      Projet             : ZM Virus Cleaner- Cleaner                          *
*      Programmeur        : ZAGANE Mohammed                                    *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mercredi 19 novembre 2008                          *
*      Version source     : 1.28.11.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : vendredi 28 novembre 2008                          *
*******************************************************************************/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbout_Form *About_Form;
//---------------------------------------------------------------------------
__fastcall TAbout_Form::TAbout_Form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAbout_Form::Web_Site_LabelClick(TObject *Sender)
{
        ShellExecute(0,"open","http://zaagane-mohammed.ifrance.com",0,0,SW_SHOWNORMAL);        
}
//---------------------------------------------------------------------------
void __fastcall TAbout_Form::EMail_LabelClick(TObject *Sender)
{
        ShellExecute(0,"open","mailto:zagmoh2005@yahoo.fr",0,0,SW_SHOWNORMAL);        
}
//---------------------------------------------------------------------------
void __fastcall TAbout_Form::OK_SpeedButtonClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
