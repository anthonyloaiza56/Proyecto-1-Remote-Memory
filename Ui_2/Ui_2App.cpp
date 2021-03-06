/***************************************************************
 * Name:      Ui_2App.cpp
 * Purpose:   Code for Application Class
 * Author:    tony ()
 * Created:   2017-09-24
 * Copyright: tony ()
 * License:
 **************************************************************/

#include "Ui_2App.h"

//(*AppHeaders
#include "Ui_2Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Ui_2App);

bool Ui_2App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Ui_2Frame* Frame = new Ui_2Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
        