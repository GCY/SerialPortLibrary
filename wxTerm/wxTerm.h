#ifndef __WX_TERM__
#define __WX_TERM__

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/valnum.h>

#include "../Library/serialport.h"
#include "connectargsdlg.h"

#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>

class App:public wxApp
{
   public:
      bool OnInit();
};

class Frame:public wxFrame
{
   public:
      Frame(const wxString&);
      ~Frame();

      void OnSendData(wxCommandEvent&);
      void OnConnectDevice(wxCommandEvent&);
      void OnReleaseDevice(wxCommandEvent&);
      void OnADCOnOff(wxCommandEvent&);
      void OnTextEnter(wxCommandEvent&);
      void OnClear(wxCommandEvent&);
      void OnExit(wxCommandEvent&);

      void OnIdle(wxIdleEvent& event);

      void PrintSerial();

   private:

      enum{
	 ID_SEND_DATA = 100,
	 ID_CONNECT_DEVICE,
	 ID_RELEASE_DEVICE,
	 ID_EXIT,
	 ID_CLEAR,
	 ID_TEXT_ENTER,
	 ID_ADC_ON_OFF
      };    

      void SendData();
      void SendADCControl();

      bool is_open;

      wxMenu *device_path;

      SerialPort serial;

      wxTextCtrl *send_text_ctrl;
      wxTextCtrl *recive_text_ctrl;

      wxCheckBox *autoscroll;

      DECLARE_EVENT_TABLE()
};
#endif
