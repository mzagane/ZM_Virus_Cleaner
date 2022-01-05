/*******************************************************************************
*      Fichier            : About_Unit.h                                       *
*      Projet             : ZM Virus Cleaner- Cleaner                          *
*      Programmeur        : ZAGANE Mohammed                                    *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mercredi 19 novembre 2008                          *
*      Version source     : 1.27.11.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : jeudi 27 novembre 2008                             *
*******************************************************************************/
//---------------------------------------------------------------------------

#ifndef About_UnitH
#define About_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAbout_Form : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        TSpeedButton *OK_SpeedButton;
        TPanel *Panel1;
        TLabel *Label3;
        TLabel *Web_Site_Label;
        TLabel *Label5;
        TLabel *EMail_Label;
        TLabel *ZMVCLNR_Label;
        TLabel *Version_Label;
        TImage *Log_Image;
        void __fastcall Web_Site_LabelClick(TObject *Sender);
        void __fastcall EMail_LabelClick(TObject *Sender);
        void __fastcall OK_SpeedButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAbout_Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAbout_Form *About_Form;
//---------------------------------------------------------------------------
#endif
