/***************************************************************
 * Name:      uiMain.h
 * Purpose:   Defines Application Frame
 * Author:    tony ()
 * Created:   2017-09-16
 * Copyright: tony ()
 * License:
 **************************************************************/

#ifndef UIMAIN_H
#define UIMAIN_H

//(*Headers(uiFrame)
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class uiFrame: public wxFrame
{
    public:

        uiFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~uiFrame();

    private:

        //(*Handlers(uiFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnButton1Click1(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnButton3Click1(wxCommandEvent& event);
        void OnButton4Click1(wxCommandEvent& event);
        void OnButton4Click2(wxCommandEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        void OnCache_EClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(uiFrame)
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT3;
        static const long ID_BUTTON1;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_BUTTON9;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL5;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(uiFrame)
        wxButton* Cache_D;
        wxTextCtrl* TextCtrl3;
        wxStatusBar* StatusBar1;
        wxButton* Cache_E;
        wxButton* Cache_A;
        wxButton* Button4;
        wxButton* Button1;
        wxButton* Cache_B;
        wxButton* Button2;
        wxButton* Button3;
        wxStaticText* StaticText1;
        wxButton* Cache_C;
        wxTextCtrl* TextCtrl5;
        wxStaticText* StaticText3;
        wxTextCtrl* TextCtrl1;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxStaticText* StaticText6;
        wxTextCtrl* TextCtrl4;
        wxTextCtrl* TextCtrl2;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // UIMAIN_H
                                                                                                                                                                                                                                                        