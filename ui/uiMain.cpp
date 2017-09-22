/***************************************************************
 * Name:      uiMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    tony ()
 * Created:   2017-09-16
 * Copyright: tony ()
 * License:
 **************************************************************/

#include "uiMain.h"
#include <wx/msgdlg.h>
#include <iostream>
#include <wx/textctrl.h> //get valor de cajas
using namespace std;
//(*InternalHeaders(uiFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)
#include "rmlib.h"


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(uiFrame)
const long uiFrame::ID_BUTTON2 = wxNewId();
const long uiFrame::ID_STATICTEXT1 = wxNewId();
const long uiFrame::ID_TEXTCTRL1 = wxNewId();
const long uiFrame::ID_TEXTCTRL2 = wxNewId();
const long uiFrame::ID_STATICTEXT2 = wxNewId();
const long uiFrame::ID_BUTTON3 = wxNewId();
const long uiFrame::ID_BUTTON4 = wxNewId();
const long uiFrame::ID_STATICTEXT3 = wxNewId();
const long uiFrame::ID_BUTTON1 = wxNewId();
const long uiFrame::ID_BUTTON5 = wxNewId();
const long uiFrame::ID_BUTTON6 = wxNewId();
const long uiFrame::ID_BUTTON7 = wxNewId();
const long uiFrame::ID_BUTTON8 = wxNewId();
const long uiFrame::ID_BUTTON9 = wxNewId();
const long uiFrame::ID_STATICTEXT4 = wxNewId();
const long uiFrame::ID_TEXTCTRL3 = wxNewId();
const long uiFrame::ID_TEXTCTRL4 = wxNewId();
const long uiFrame::ID_STATICTEXT5 = wxNewId();
const long uiFrame::ID_STATICTEXT6 = wxNewId();
const long uiFrame::ID_TEXTCTRL5 = wxNewId();
const long uiFrame::idMenuQuit = wxNewId();
const long uiFrame::idMenuAbout = wxNewId();
const long uiFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(uiFrame,wxFrame)
    //(*EventTable(uiFrame)
    //*)
END_EVENT_TABLE()

uiFrame::uiFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(uiFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(913,450));
    SetBackgroundColour(wxColour(255,255,255));
    Button2 = new wxButton(this, ID_BUTTON2, _("Enviar"), wxPoint(320,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Puerto SA"), wxPoint(24,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(144,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxPoint(144,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Puerto SP"), wxPoint(24,48), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    Button3 = new wxButton(this, ID_BUTTON3, _("Conectar"), wxPoint(392,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button4 = new wxButton(this, ID_BUTTON4, _("msj SA"), wxPoint(24,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Puntaje:"), wxPoint(352,264), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    Button1 = new wxButton(this, ID_BUTTON1, _("msj SP"), wxPoint(136,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Cache_A = new wxButton(this, ID_BUTTON5, _("A"), wxPoint(800,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Cache_B = new wxButton(this, ID_BUTTON6, _("B"), wxPoint(800,128), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    Cache_C = new wxButton(this, ID_BUTTON7, _("C"), wxPoint(800,168), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    Cache_D = new wxButton(this, ID_BUTTON8, _("D"), wxPoint(800,208), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    Cache_E = new wxButton(this, ID_BUTTON9, _("E"), wxPoint(800,248), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Monitorde memoria"), wxPoint(680,16), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxPoint(264,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl4 = new wxTextCtrl(this, ID_TEXTCTRL4, _("Text"), wxPoint(264,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("0"), wxPoint(432,264), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Ingrese palabra:"), wxPoint(64,152), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    TextCtrl5 = new wxTextCtrl(this, ID_TEXTCTRL5, _("Text"), wxPoint(208,152), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uiFrame::OnButton2Click);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&uiFrame::OnTextCtrl1Text);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uiFrame::OnButton3Click1);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uiFrame::OnButton1Click1);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uiFrame::OnButton5Click);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uiFrame::OnCache_EClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&uiFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&uiFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&uiFrame::OnClose);
    //*)
}

uiFrame::~uiFrame()
{
    //(*Destroy(uiFrame)
    //*)
}

void uiFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void uiFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void uiFrame::OnClose(wxCloseEvent& event)
{

}

void uiFrame::OnButton2Click(wxCommandEvent& event)
{
    double n1;
    double n2;
    double resultado;

    wxString puerto1=TextCtrl1->GetValue();
    wxString puerto2=TextCtrl2->GetValue();
    wxMessageBox(puerto1);
    wxMessageBox(puerto2);

}

void uiFrame::OnButton1Click(wxCommandEvent& event)
{

}

void uiFrame::OnTextCtrl1Text(wxCommandEvent& event)
{

}

void uiFrame::OnButton1Click1(wxCommandEvent& event)
{
    enviar(1,"hh",1024);
}

void uiFrame::OnButton3Click1(wxCommandEvent& event)
{

    rm_init("127.0.0.1",35511,"127.0.0.1",33133);
}

void uiFrame::OnButton4Click1(wxCommandEvent& event)
{
    enviar(2,"hh",1024);
}

void uiFrame::OnButton4Click2(wxCommandEvent& event)
{
}

void uiFrame::OnButton5Click(wxCommandEvent& event)
{
}

void uiFrame::OnCache_EClick(wxCommandEvent& event)
{
}
