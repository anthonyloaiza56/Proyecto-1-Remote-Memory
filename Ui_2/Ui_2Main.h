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
        void OnTextCtrl5Text(wxCommandEvent& event);
        void OnClose1(wxCloseEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnButton8Click(wxCommandEvent& event);
        void OnButton2Click1(wxCommandEvent& event);
        void OnButton10Click(wxCommandEvent& event);
        void OnButton9Click(wxCommandEvent& event);
        void OnLlave_1Text(wxCommandEvent& event);
        void OnButton3Click1(wxCommandEvent& event);
        void OnValor_2Text(wxCommandEvent& event);
        void OnButton2Click2(wxCommandEvent& event);
        void OnButton10Click1(wxCommandEvent& event);
        void OnButton10Click2(wxCommandEvent& event);
        //*)

        //(*Identifiers(Ui_2Frame)
        static const long ID_BUTTON1;
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
        static const long ID_BUTTON8;
        static const long ID_BUTTON9;
        static const long ID_TEXTCTRL7;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON10;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Ui_2Frame)
        wxTextCtrl* Puerto_SP;
        wxStaticText* Valor;
        wxStatusBar* StatusBar1;
        wxTextCtrl* IP_SP;
        wxButton* Button4;
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxTextCtrl* IP_SA;
        wxStaticText* StaticText1;
        wxButton* Button8;
        wxStaticText* StaticText3;
        wxTextCtrl* Llave_1;
        wxTextCtrl* Puerto_SA;
        wxButton* Button5;
        wxTextCtrl* Llave_2;
        wxButton* Button9;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxButton* Button7;
        wxTextCtrl* Valor_1;
        wxButton* Button6;
        wxButton* Button10;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // UI_2MAIN_H
                                                                                            