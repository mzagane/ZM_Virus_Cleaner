/*******************************************************************************
*      Fichier            : Scan_Result_Unit.h                                 *
*      Projet             : ZM Virus Cleaner- Cleaner                          *
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

#ifndef Scan_Result_UnitH
#define Scan_Result_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TResult_Scan_Form : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TImage *Not_Infected_Image;
        TImage *Infected_Image;
        TLabel *Result_Scan_Label;
        TSpeedButton *Del_Infected_File_SpeedButton;
        TGroupBox *Results_GroupBox;
        TImageList *ImageList1;
        TGroupBox *Statistic_GroupBox;
        TLabel *Nbr_Files_Scaned_Label;
        TLabel *Nbr_Dirs_Scaned_Label;
        TLabel *Nbr_Infected_Files_Label;
        TLabel *Nbr_Repared_Files_Label;
        TSpeedButton *Close_SpeedButton;
        TSpeedButton *Cancel_Scan_SpeedButton;
        TPanel *Current_Object_Panel;
        TLabel *Current_Scaned_Dir_Label;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TLabel *Current_Scaned_File_Label;
        TLabel *Scan_Statut_Label;
        void __fastcall Close_SpeedButtonClick(TObject *Sender);
        void __fastcall Del_Infected_File_SpeedButtonClick(
          TObject *Sender);
        void __fastcall Cancel_Scan_SpeedButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TResult_Scan_Form(TComponent* Owner);
        TListView *Results_ListView;
};
//---------------------------------------------------------------------------
extern PACKAGE TResult_Scan_Form *Result_Scan_Form;
//---------------------------------------------------------------------------
#endif
