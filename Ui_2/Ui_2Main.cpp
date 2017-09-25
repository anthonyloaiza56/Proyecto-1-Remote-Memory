/***************************************************************
 * Name:      Ui_2Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    tony ()
 * Created:   2017-09-24
 * Copyright: tony ()
 * License:
 **************************************************************/

#include "Ui_2Main.h"
#include <wx/msgdlg.h>
#include "rmlib.h"

//(*InternalHeaders(Ui_2Frame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
//*)

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

//(*IdInit(Ui_2Frame)
const long Ui_2Frame::ID_BUTTON1 = wxNewId();
const long Ui_2Frame::ID_BUTTON2 = wxNewId();
const long Ui_2Frame::ID_BUTTON3 = wxNewId();
const long Ui_2Frame::ID_BUTTON4 = wxNewId();
const long Ui_2Frame::ID_BUTTON5 = wxNewId();
const long Ui_2Frame::ID_BUTTON6 = wxNewId();
const long Ui_2Frame::ID_STATICTEXT1 = wxNewId();
const long Ui_2Frame::ID_STATICTEXT2 = wxNewId();
const long Ui_2Frame::ID_STATICTEXT3 = wxNewId();
const long Ui_2Frame::ID_TEXTCTRL1 = wxNewId();
const long Ui_2Frame::ID_TEXTCTRL2 = wxNewId();
const long Ui_2Frame::ID_TEXTCTRL3 = wxNewId();
const long Ui_2Frame::ID_TEXTCTRL4 = wxNewId();
const long Ui_2Frame::ID_BUTTON7 = wxNewId();
const long Ui_2Frame::ID_TEXTCTRL5 = wxNewId();
const long Ui_2Frame::ID_TEXTCTRL6 = wxNewId();
const long Ui_2Frame::ID_STATICTEXT4 = wxNewId();
const long Ui_2Frame::ID_STATICTEXT5 = wxNewId();
const long Ui_2Frame::idMenuQuit = wxNewId();
const long Ui_2Frame::idMenuAbout = wxNewId();
const long Ui_2Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Ui_2Frame,wxFrame)
    //(*EventTable(Ui_2Frame)
    //*)
END_EVENT_TABLE()

Ui_2Frame::Ui_2Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Ui_2Frame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Remote Memory"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(881,450));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("/home/tony/Imágenes/memoria.png"))));
    	SetIcon(FrameIcon);
    }
    Button1 = new wxButton(this, ID_BUTTON1, _("Conectar"), wxPoint(456,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button2 = new wxButton(this, ID_BUTTON2, _("A"), wxPoint(632,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button3 = new wxButton(this, ID_BUTTON3, _("B"), wxPoint(752,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button4 = new wxButton(this, ID_BUTTON4, _("C"), wxPoint(632,160), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button5 = new wxButton(this, ID_BUTTON5, _("D"), wxPoint(752,160), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Button6 = new wxButton(this, ID_BUTTON6, _("E"), wxPoint(688,240), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Monitor de memoria"), wxPoint(664,64), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Puerto,IP server Activo"), wxPoint(24,40), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Puerto,IP server Pasivo:"), wxPoint(24,72), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(328,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxPoint(328,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxPoint(168,168), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl4 = new wxTextCtrl(this, ID_TEXTCTRL4, _("Text"), wxPoint(168,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    Button7 = new wxButton(this, ID_BUTTON7, _("Enviar"), wxPoint(168,264), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    TextCtrl5 = new wxTextCtrl(this, ID_TEXTCTRL5, _("Text"), wxPoint(224,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    TextCtrl6 = new wxTextCtrl(this, ID_TEXTCTRL6, _("Text"), wxPoint(224,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    Valor = new wxStaticText(this, ID_STATICTEXT4, _("Memoria"), wxPoint(40,168), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Valor"), wxPoint(48,224), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
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
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton1Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton6Click);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Ui_2Frame::OnTextCtrl4Text);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton7Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Ui_2Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Ui_2Frame::OnAbout);
    //*)
}

Ui_2Frame::~Ui_2Frame()
{
    //(*Destroy(Ui_2Frame)
    //*)
}

void Ui_2Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Ui_2Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void Ui_2Frame::OnButton3Click(wxCommandEvent& event)
{
}

void Ui_2Frame::OnClose(wxCloseEvent& event)
{
}

void Ui_2Frame::OnTextCtrl4Text(wxCommandEvent& event)
{
}

void Ui_2Frame::OnButton1Click(wxCommandEvent& event)
{
    rm_init("127.0.0.1",8654,"127.0.0.1",8790);
}

void Ui_2Frame::OnButton7Click(wxCommandEvent& event)
{
    enviar(1,"hola",1024);
    enviar(2,"hola",1024);
}

void Ui_2Frame::OnButton6Click(wxCommandEvent& event)
{
    wxMessageBox("enviado");
    peticion(1,"hola",1024);
    peticion(2,"hola",1024);
    wxMessageBox(buffer);
}

