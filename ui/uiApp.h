/***************************************************************
 * Name:      uiApp.h
 * Purpose:   Defines Application Class
 * Author:    tony ()
 * Created:   2017-09-16
 * Copyright: tony ()
 * License:
 **************************************************************/

#ifndef UIAPP_H
#define UIAPP_H

#include <wx/app.h>

class uiApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // UIAPP_H
