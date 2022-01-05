/*******************************************************************************
*      Fichier            : Main_Unit.h                                        *
*      Projet             : ZM Virus Cleaner-Cleaner                           *
*      Programmeur        : ZAGANE Mohammed                                    *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mercredi 19 novembre 2008                          *
*      Version source     : 1.14.12.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : dimanche 28 novembre 2008                          *
*******************************************************************************/
//---------------------------------------------------------------------------

#ifndef Main_UnitH
#define Main_UnitH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <dir.h>// pour MAXPATH,
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <FileCtrl.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TMain_Form : public TForm
{
__published:	// IDE-managed Components
        TPanel *Buttons_Panel;
        TSpeedButton *Quit_SpeedButton;
        TSpeedButton *About_SpeedButton;
        TSpeedButton *Scan_Computer_SpeedButton;
        TLabel *ZMVCLNR_Label;
        TLabel *Version_Label;
        TImage *Log_Image;
        TSpeedButton *Scan_Component_SpeedButton;
        TOpenDialog *File_To_Scan_OpenDialog;
        TGroupBox *Main_GroupBox;
        TGroupBox *Up_To_Date_GroupBox;
        TLabel *Label6;
        TLabel *Label5;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TPanel *Panel2;
        TLabel *Chck_For_Updt_Site_Label;
        TPanel *Buttons_Panel2;
        TSpeedButton *Start_Component_Scan_SpeedButton;
        TSpeedButton *Start_Computer_Scan_SpeedButton;
        TSpeedButton *Hid_Work_Space_SpeedButton;
        TGroupBox *Scan_Component_Options_GroupBox;
        TCheckBox *Clean_System_CheckBox;
        TGroupBox *Object_To_Scan_GroupBox;
        TSpeedButton *Brows_SpeedButton;
        TLabel *Object_To_Scan_Label;
        TEdit *Object_To_Scan_Edit;
        TPanel *Panel1;
        TRadioButton *Drive_Dir_RadioButton;
        TRadioButton *File_RadioButton;
        TCheckBox *Scan_All_Drive_CheckBox;
        TGroupBox *Complet_Scan_Descrption_GroupBox;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TSpeedButton *Up_To_Date_SpeedButton;
        TStatusBar *Main_StatusBar;
        TMainMenu *MainMenu1;
        TMenuItem *Application1;
        TMenuItem *Mettrejour1;
        TMenuItem *Quitter1;
        TMenuItem *Analyse1;
        TMenuItem *Analyseruncomposant1;
        TMenuItem *Analyserlordinateur1;
        TMenuItem *Aide1;
        TMenuItem *Apropos1;
        TCheckBox *Scan_Sub_Dirs_CheckBox;
        void __fastcall Quit_SpeedButtonClick(TObject *Sender);
        void __fastcall Scan_Computer_SpeedButtonClick(TObject *Sender);
        void __fastcall About_SpeedButtonClick(TObject *Sender);
        void __fastcall Start_Component_Scan_SpeedButtonClick(TObject *Sender);
        void __fastcall Scan_Component_SpeedButtonClick(TObject *Sender);
        void __fastcall Brows_SpeedButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Start_Computer_Scan_SpeedButtonClick(
          TObject *Sender);
        void __fastcall Hid_Work_Space_SpeedButtonClick(TObject *Sender);
        void __fastcall Chck_For_Updt_Site_LabelClick(TObject *Sender);
        void __fastcall Up_To_Date_SpeedButtonClick(TObject *Sender);
        void __fastcall Quitter1Click(TObject *Sender);
        void __fastcall Mettrejour1Click(TObject *Sender);
        void __fastcall Analyseruncomposant1Click(TObject *Sender);
        void __fastcall Analyserlordinateur1Click(TObject *Sender);
        void __fastcall Apropos1Click(TObject *Sender);
        void __fastcall Drive_Dir_RadioButtonClick(TObject *Sender);
        void __fastcall File_RadioButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMain_Form(TComponent* Owner);

        //variables
        char Current_Dir[MAXDIR];//repertoire courant (où se trouve l'excutable)
        bool Scan_Canceled;// pour annuler l'analyse
        bool Scan_Terminated;// pour connaitre l'état de l'analyse
        int Nbr_Files_Scaned;//le nombre des fichier analysés,
        int Nbr_Dirs_Scaned;//le nombre de dossiers analysés
        int Nbr_Infected_Files;//le nombre des fichier infectés,
        int Nbr_Repared_Files;//le nombre des fichier réparés,

        // méthodes
        void __fastcall Intialization();

};
//---------------------------------------------------------------------------
extern PACKAGE TMain_Form *Main_Form;
//---------------------------------------------------------------------------
#endif
