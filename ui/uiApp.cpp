/***************************************************************
 * Name:      uiApp.cpp
 * Purpose:   Code for Application Class
 * Author:    tony ()
 * Created:   2017-09-16
 * Copyright: tony ()
 * License:
 **************************************************************/

#include "uiApp.h"

//(*AppHeaders
#include "uiMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(uiApp);

bool uiApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	uiFrame* Frame = new uiFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
        