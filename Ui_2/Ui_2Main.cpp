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
#include <string.h>
#include <thread>
//(*InternalHeaders(Ui_2Frame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
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
const long Ui_2Frame::ID_BUTTON8 = wxNewId();
const long Ui_2Frame::ID_BUTTON9 = wxNewId();
const long Ui_2Frame::ID_TEXTCTRL7 = wxNewId();
const long Ui_2Frame::ID_BUTTON2 = wxNewId();
const long Ui_2Frame::ID_BUTTON3 = wxNewId();
const long Ui_2Frame::ID_BUTTON10 = wxNewId();
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

    Create(parent, wxID_ANY, _("Remote Memory"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(750,400));
    Move(wxPoint(-1,-1));
    SetBackgroundColour(wxColour(238,238,238));
    Button1 = new wxButton(this, ID_BUTTON1, _("Conectar"), wxPoint(456,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button1->SetBackgroundColour(wxColour(63,81,181));
    Button4 = new wxButton(this, ID_BUTTON4, _("Ver Memoria"), wxPoint(608,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button4->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button4->SetBackgroundColour(wxColour(121,85,72));
    Button5 = new wxButton(this, ID_BUTTON5, _("Ver Cache"), wxPoint(616,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Button5->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button5->SetBackgroundColour(wxColour(121,85,72));
    Button6 = new wxButton(this, ID_BUTTON6, _("Aumentar referencia"), wxPoint(120,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    Button6->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button6->SetBackgroundColour(wxColour(0,150,136));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Monitor de memoria:"), wxPoint(584,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Puerto,IP server Activo :"), wxPoint(24,40), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Puerto,IP server Pasivo:"), wxPoint(24,72), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    IP_SA = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(328,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    IP_SP = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxPoint(328,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    Llave_1 = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxPoint(120,120), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    Valor_1 = new wxTextCtrl(this, ID_TEXTCTRL4, _("Text"), wxPoint(120,160), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    Button7 = new wxButton(this, ID_BUTTON7, _("Enviar"), wxPoint(120,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    Button7->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button7->SetBackgroundColour(wxColour(0,150,136));
    Puerto_SA = new wxTextCtrl(this, ID_TEXTCTRL5, _("Text"), wxPoint(224,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    Puerto_SP = new wxTextCtrl(this, ID_TEXTCTRL6, _("Text"), wxPoint(224,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    Valor = new wxStaticText(this, ID_STATICTEXT4, _("Llave :"), wxPoint(40,120), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Valor :"), wxPoint(40,168), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    Button8 = new wxButton(this, ID_BUTTON8, _("Eliminar"), wxPoint(120,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    Button8->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button8->SetBackgroundColour(wxColour(0,150,136));
    Button9 = new wxButton(this, ID_BUTTON9, _("Comparar igualdad"), wxPoint(248,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Button9->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button9->SetBackgroundColour(wxColour(103,58,183));
    Llave_2 = new wxTextCtrl(this, ID_TEXTCTRL7, _("Text"), wxPoint(248,120), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    Button2 = new wxButton(this, ID_BUTTON2, _("Copiar valor"), wxPoint(248,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button2->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button2->SetBackgroundColour(wxColour(103,58,183));
    Button3 = new wxButton(this, ID_BUTTON3, _("Comparar desigualdad"), wxPoint(376,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button3->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    Button3->SetBackgroundColour(wxColour(103,58,183));
    Button10 = new wxButton(this, ID_BUTTON10, _("Label"), wxPoint(664,208), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
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
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton4Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton5Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton6Click);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Ui_2Frame::OnLlave_1Text);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Ui_2Frame::OnTextCtrl4Text);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton7Click);
    Connect(ID_TEXTCTRL5,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&Ui_2Frame::OnTextCtrl5Text);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton8Click);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton9Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton2Click2);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton3Click1);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Ui_2Frame::OnButton10Click2);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Ui_2Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Ui_2Frame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&Ui_2Frame::OnClose1);
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
    wxString mensaje=IP_SA->GetValue();
    std::string ip_sa = std::string(mensaje.mb_str());//IP SA
    wxString mensaje2=IP_SP->GetValue();
    std::string ip_sp = std::string(mensaje2.mb_str());//IP SP
    wxString mensaje3=Puerto_SA->GetValue();
    std::string puerto_sa = std::string(mensaje3.mb_str());//Puerto SA
    wxString mensaje4=Puerto_SP->GetValue();
    std::string puerto_sp = std::string(mensaje4.mb_str());//Puerto SP


    //pasa de string a char* los ip
    char * ip1 = new char[ip_sa.size() + 1];
    std::copy(ip_sa.begin(), ip_sa.end(), ip1);
    ip1[ip_sa.size()] = '\0';
    char * ip2 = new char[ip_sp.size() + 1];
    std::copy(ip_sp.begin(), ip_sp.end(), ip1);
    ip2[ip_sp.size()] = '\0';
    // paso de string a int los puertos
    int puerto1 = atoi(puerto_sa.c_str());
    int puerto2 = atoi(puerto_sp.c_str());
    size_memoria=0;
    rm_init(ip1,puerto1,ip2,puerto2);
}

void Ui_2Frame::OnButton7Click(wxCommandEvent& event)
{
    wxString mensaje=Llave_1->GetValue();
    std::string mensaje_s = std::string(mensaje.mb_str());//Llave
    wxString mensaje2=Valor_1->GetValue();
    std::string mensaje_s2 = std::string(mensaje2.mb_str());//Valor
    size_memoria+=1;
    rm_new(mensaje_s,mensaje_s2,sizeof(mensaje_s2));
    string dato_enviar="1"+mensaje_s+"_"+mensaje_s2+"*";

}

void Ui_2Frame::OnButton6Click(wxCommandEvent& event)
{
    wxString mensaje=Llave_1->GetValue();
    std::string mensaje_s = std::string(mensaje.mb_str());//Llave
    rm_delete(mensaje_s);
    int x=0;
    while(x<size_memoria+1){
        peticion("7","null");
        x+=1;
    }
   bufferToString(buffer,10240,mensaje_s);
    wxMessageBox(mensaje_s);
    bufferToString(buffer2,10240,mensaje_s);
    wxMessageBox(mensaje_s);
}


void Ui_2Frame::OnTextCtrl5Text(wxCommandEvent& event)
{
}

void Ui_2Frame::OnClose1(wxCloseEvent& event)
{
}

void Ui_2Frame::OnButton5Click(wxCommandEvent& event)
{
    int x=0;
     string mensaje;
    // peticion("4","null","null");
    peticion("4","null");
   while(x<size_memoria+1){
        peticion("7","null");
        x+=1;
    }
    string data="Largo"+to_string(size_memoria);
    wxMessageBox(data);
    bufferToString(buffer,10240,mensaje);
    wxMessageBox(mensaje);
    bufferToString(buffer2,10240,mensaje);
    wxMessageBox(mensaje);


}

void Ui_2Frame::OnButton2Click(wxCommandEvent& event)
{
    wxMessageBox("Cache:A , Valor: mensaje \n Size: 8 \n Referencias: 1");
}

void Ui_2Frame::OnButton4Click(wxCommandEvent& event)
{

    int x=0;
     string mensaje;
     string mensaje2;
    peticion("3","null");
    while(x<size_memoria+1){
        peticion("7","null");
        x+=1;
    }

    bufferToString(buffer,10240,mensaje);
    wxMessageBox(mensaje);
    bufferToString(buffer2,10240,mensaje2);
    wxMessageBox(mensaje2);

}

void Ui_2Frame::OnButton8Click(wxCommandEvent& event)
{
    wxString mensaje=Llave_1->GetValue();
    std::string mensaje_s = std::string(mensaje.mb_str());//Llave
    peticion("2",mensaje_s);
    int x=0;
    while(x<size_memoria+1){
        peticion("7","null");
        x+=1;
    }

   bufferToString(buffer,10240,mensaje_s);
    wxMessageBox(mensaje_s);
    bufferToString(buffer2,10240,mensaje_s);
    wxMessageBox(mensaje_s);
}

void Ui_2Frame::OnButton2Click1(wxCommandEvent& event)
{
    string m="Cache:A , Valor: mensaje \n Size: 8 \n Referencias:0 \n Cache:B , Valor: mensaje \n Size: 8 \n Referencias: 1 \n Cache:C , Valor: mensaje \n Size: 8 \n Referencias: 1";
    wxMessageBox(m);
}

void Ui_2Frame::OnButton10Click(wxCommandEvent& event)
{
    iniciar_cliente_SA();
}

void Ui_2Frame::OnButton9Click(wxCommandEvent& event)
{
    string val1_A;
    string val2_A;
    string val1_P;
    string val2_P;
    rmRef_h A;
    rmRef_h B;
    rmRef_h A_P;
    rmRef_h B_P;

    wxString mensaje=Llave_1->GetValue();
    std::string mensaje_s = std::string(mensaje.mb_str());//Llave
    A.llave=mensaje_s;
    A_P.llave=mensaje_s;
    peticion("9",mensaje_s);
    int x=0;
    while(x<size_memoria+1){
        peticion("7","null");
        x+=1;
    }
    bufferToString(buffer,10240,mensaje_s);
    val1_A=mensaje_s;
    A.valor=mensaje_s;

    bufferToString(buffer2,10240,mensaje_s);
    val1_P=mensaje_s;
    A_P.valor=val1_P;

    //********************************************//
    wxString mensaje2=Llave_2->GetValue();
    std::string mensaje_s2 = std::string(mensaje2.mb_str());//Llave2 para comparar
    B.llave=mensaje_s;
    B_P.llave=mensaje_s;
    peticion("9",mensaje_s2);
    x=0;
    while(x<size_memoria+1){
        peticion("7","null");
        x+=1;
    }
    bufferToString(buffer,10240,mensaje_s2);
    val2_A=mensaje_s2;
    B.valor=val2_A;


    bufferToString(buffer2,10240,mensaje_s2);
    val2_P=mensaje_s2;
    B_P.valor=val2_P;

    A==B;
}

void Ui_2Frame::OnLlave_1Text(wxCommandEvent& event)
{
}

void Ui_2Frame::OnButton3Click1(wxCommandEvent& event)
{
    string val1_A;
    string val2_A;
    string val1_P;
    string val2_P;
    rmRef_h A;
    rmRef_h B;
    rmRef_h A_P;
    rmRef_h B_P;

    wxString mensaje=Llave_1->GetValue();
    std::string mensaje_s = std::string(mensaje.mb_str());//Llave
    A.llave=mensaje_s;
    A_P.llave=mensaje_s;
    peticion("9",mensaje_s);
    int x=0;
    while(x<size_memoria+1){
        peticion("7","null");
        x+=1;
    }
    bufferToString(buffer,10240,mensaje_s);
    val1_A=mensaje_s;
    A.valor=mensaje_s;

    bufferToString(buffer2,10240,mensaje_s);
    val1_P=mensaje_s;
    A_P.valor=val1_P;

    //********************************************//
    wxString mensaje2=Llave_2->GetValue();
    std::string mensaje_s2 = std::string(mensaje2.mb_str());//Llave2 para comparar
    B.llave=mensaje_s;
    B_P.llave=mensaje_s;
    peticion("9",mensaje_s2);
    x=0;
    while(x<size_memoria+1){
        peticion("7","null");
        x+=1;
    }
    bufferToString(buffer,10240,mensaje_s2);
    val2_A=mensaje_s2;
    B.valor=val2_A;


    bufferToString(buffer2,10240,mensaje_s2);
    val2_P=mensaje_s2;
    B_P.valor=val2_P;

    A!=B;
}

void Ui_2Frame::OnValor_2Text(wxCommandEvent& event)
{
}

void Ui_2Frame::OnButton2Click2(wxCommandEvent& event)
{
    wxString mensaje=Llave_1->GetValue();
    std::string mensaje_s = std::string(mensaje.mb_str());//Llave
    wxString mensaje2=Llave_2->GetValue();
    std::string mensaje_s2 = std::string(mensaje2.mb_str());//Llave2 para comparar

}

void Ui_2Frame::OnButton10Click2(wxCommandEvent& event)
{
    iniciar_cliente_SA();
}
