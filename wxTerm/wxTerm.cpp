#include "wxTerm.h"

   IMPLEMENT_APP(App)
DECLARE_APP(App)

bool App::OnInit()
{
   wxFrame *frame = new Frame(wxT("wxTerm"));

   frame->Show(true);

   return true;
}

   BEGIN_EVENT_TABLE(Frame,wxFrame)
   EVT_MENU(ID_EXIT,Frame::OnExit)
   EVT_MENU(ID_CLEAR,Frame::OnClear)
   EVT_MENU(ID_CONNECT_DEVICE,Frame::OnConnectDevice)
   EVT_MENU(ID_RELEASE_DEVICE,Frame::OnReleaseDevice)
   EVT_MENU(ID_ADC_ON_OFF,Frame::OnADCOnOff)
   EVT_BUTTON(ID_SEND_DATA,Frame::OnSendData)
   EVT_IDLE(Frame::OnIdle)
   EVT_TEXT_ENTER(ID_TEXT_ENTER,Frame::OnTextEnter)
END_EVENT_TABLE()

Frame::Frame(const wxString &title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxDefaultSize,wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxSYSTEM_MENU)
{
   is_open = false;

   wxMenu *file = new wxMenu;
   file->Append(ID_EXIT,wxT("E&xit\tAlt-e"),wxT("Exit"));
   wxMenu *tools = new wxMenu;
   tools->Append(ID_CONNECT_DEVICE,wxT("C&onnect Device\tAlt-c"),wxT("Connect Device"));
   tools->Append(ID_RELEASE_DEVICE,wxT("R&elease Device\tAlt-r"),wxT("Release Device"));
   wxMenu *setting = new wxMenu;
   setting->AppendSeparator();
   setting->Append(ID_ADC_ON_OFF,wxT("A&DC On|Off\tAlt-a"),wxT("ADC Output"));
   setting->Append(ID_CLEAR,wxT("C&lear\tAlt-m"),wxT("Clear"));

   wxMenuBar *bar = new wxMenuBar;
   bar->Append(file,wxT("File"));
   bar->Append(tools,wxT("Tools"));
   bar->Append(setting,wxT("Setting"));
   SetMenuBar(bar);

   wxBoxSizer *top = new wxBoxSizer(wxVERTICAL);
   this->SetSizer(top);

   send_text_ctrl = new wxTextCtrl(this, ID_TEXT_ENTER, "", wxDefaultPosition, wxSize(460,20), wxTE_PROCESS_ENTER);
   wxBoxSizer *send_box = new wxBoxSizer(wxHORIZONTAL);
   top->Add(send_box,0,wxALIGN_CENTER_HORIZONTAL | wxALL,5);
   send_box->Add(send_text_ctrl,0,wxALIGN_CENTER_HORIZONTAL | wxALL,5);
   wxButton *button_send = new wxButton(this, ID_SEND_DATA, wxT("Send"));
   send_box->Add(button_send,0,wxALIGN_CENTER_HORIZONTAL | wxALL,5);

   recive_text_ctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(580,260), wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);
   top->Add(recive_text_ctrl,0,wxALIGN_CENTER_HORIZONTAL | wxALL,5);
   recive_text_ctrl->SetForegroundColour(wxColor(0, 0, 0));
   recive_text_ctrl->SetBackgroundColour(wxColor(255, 255, 255));
   wxFont font = wxFont(12, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
   recive_text_ctrl->SetFont(font);

   autoscroll = new wxCheckBox(this,wxID_ANY,"Auto Scroll",wxDefaultPosition,wxDefaultSize);
   top->Add(autoscroll,0,wxALIGN_LEFT | wxALL,5);

   CreateStatusBar(1);
   SetStatusText(wxT("wxTerm"));

   top->Fit(this);
   top->SetSizeHints(this);
}

Frame::~Frame()
{
   if(is_open){
      serial.Close();
   }
}

void Frame::OnSendData(wxCommandEvent &event)
{
   SendData();
}

void Frame::OnTextEnter(wxCommandEvent &event)
{
   SendData();
}

void Frame::SendData()
{
   if(!is_open){return;}
   wxString str = send_text_ctrl->GetValue();
   std::string std_str = str.ToStdString();
   unsigned char *write_str = new unsigned char[std_str.length()];
   strcpy((char*)write_str,std_str.c_str());
   serial.Write(write_str,str.length());
   delete [] write_str;
   send_text_ctrl->SetValue("");
   
}

void Frame::OnConnectDevice(wxCommandEvent &event)
{
   ConnectArgsDialog dlg(this,wxID_ANY,wxT("Connect"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE);

   if(dlg.ShowModal() == wxID_OK){
#ifdef _WIN_
      serial.Open(dlg.GetDevicePath().wc_str());
#elif _MAC_
      serial.Open(dlg.GetDevicePath().c_str());
#endif
      serial.SetBaudRate(wxAtoi(dlg.GetBaudRate()));
      serial.SetParity(8,1,'N');
      unsigned char ack[27] = "wxTerm - TonyGUO 20190721\n";
      serial.Write(ack,27);

      is_open = true;
   }
}

void Frame::OnReleaseDevice(wxCommandEvent &event)
{
   serial.Close();
   is_open = false;
}

void Frame::OnADCOnOff(wxCommandEvent &event)
{
   SendADCControl();
}

void Frame::SendADCControl()
{
   if(is_open){
      unsigned char adc_on_off_str[2];
      adc_on_off_str[0] = 0xC;
      serial.Write(adc_on_off_str,2);
   }   
}

void Frame::OnClear(wxCommandEvent &event)
{
   send_text_ctrl->SetValue("");
   recive_text_ctrl->SetValue("");
}

void Frame::PrintSerial()
{

   if(!is_open){return;}

   try{
      bool is_read = false;
      unsigned char serial_buffer[5000] = {0};
      int length = serial.Read(serial_buffer);
      if(length != -1){
	 is_read = true;
	 wxString str;
	 str.Printf(wxT("%s"), (char*)serial_buffer);
	 *recive_text_ctrl << str;
      }  
      if(autoscroll->GetValue() && is_read){
	 *recive_text_ctrl << wxT("\n");
      }
      
   }
   catch(std::exception &e){
      wxLogDebug(e.what());
   }
}

void Frame::OnIdle( wxIdleEvent& event )
{
   PrintSerial();
}

void Frame::OnExit(wxCommandEvent &event)
{
   Close();
}
