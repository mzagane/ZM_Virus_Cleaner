//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main_Unit.cpp", Main_Form);
USEFORM("About_Unit.cpp", About_Form);
USEFORM("Scan_Result_Unit.cpp", Result_Scan_Form);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "ZM Virus Cleaner";
                 Application->CreateForm(__classid(TMain_Form), &Main_Form);
                 Application->CreateForm(__classid(TAbout_Form), &About_Form);
                 Application->CreateForm(__classid(TResult_Scan_Form), &Result_Scan_Form);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
