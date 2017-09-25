/***************************************************************
 * Name:      Ui_2Main.h
 * Purpose:   Defines Application Frame
 * Author:    tony ()
 * Created:   2017-09-24
 * Copyright: tony ()
 * License:
 **************************************************************/

#ifndef UI_2MAIN_H
#define UI_2MAIN_H

//(*Headers(Ui_2Frame)
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class Ui_2Frame: public wxFrame
{
    public:

        Ui_2Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Ui_2Frame();

    private:

        //(*Handlers(Ui_2Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnTextCtrl4Text(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton7Click(wxCommandEvent& event);
        void OnButton6Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(Ui_2Frame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON7;
        static const long ID_TEXTCTRL5;
        static const long ID_TEXTCTRL6;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Ui_2Frame)
        wxTextCtrl* TextCtrl3;
        wxStaticText* Valor;
        wxStatusBar* StatusBar1;
        wxButton* Button4;
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxStaticText* StaticText1;
        wxTextCtrl* TextCtrl5;
        wxStaticText* StaticText3;
        wxButton* Button5;
        wxTextCtrl* TextCtrl6;
        wxTextCtrl* TextCtrl1;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxButton* Button7;
        wxTextCtrl* TextCtrl4;
        wxTextCtrl* TextCtrl2;
        wxButton* Button6;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // UI_2MAIN_H
                                                                                                                                                                                                                    