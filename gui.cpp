//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: gui.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "gui.h"


// Declare the bitmap loading function
extern void wxCDB31InitBitmapResources();

static bool bBitmapLoaded = false;


MainFrameBase::MainFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCDB31InitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* szMain = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(szMain);
    
    bmpPreview = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(-1,-1), 0 );
    
    szMain->Add(bmpPreview, 2, wxALL|wxEXPAND, 5);
    
    tcLog = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), wxTE_READONLY|wxTE_MULTILINE);
    
    szMain->Add(tcLog, 1, wxALL|wxEXPAND, 5);
    
    sdPosition = new wxSlider(this, wxID_ANY, 0, 0, 1024, wxDefaultPosition, wxSize(-1, -1), wxSL_HORIZONTAL);
    
    szMain->Add(sdPosition, 0, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* szNav = new wxBoxSizer(wxHORIZONTAL);
    
    szMain->Add(szNav, 0, wxEXPAND, 5);
    
    szNav->Add(0, 0, 1, wxEXPAND, 5);
    
    btRRR = new wxButton(this, wxID_ANY, _("<<<"), wxDefaultPosition, wxSize(-1,-1), 0);
    btRRR->SetToolTip(_("Back 100 MB [CTRL + Left]"));
    
    szNav->Add(btRRR, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btRRR->SetMinSize(wxSize(40,-1));
    
    btRR = new wxButton(this, wxID_ANY, _("<<"), wxDefaultPosition, wxSize(-1,-1), 0);
    btRR->SetToolTip(_("Back 10 MB [SHIFT + Left]"));
    
    szNav->Add(btRR, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btRR->SetMinSize(wxSize(35,-1));
    
    btR = new wxButton(this, wxID_ANY, _("<"), wxDefaultPosition, wxSize(-1,-1), 0);
    btR->SetToolTip(_("Previous key frame [Left]"));
    
    szNav->Add(btR, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btR->SetMinSize(wxSize(25,-1));
    
    btF = new wxButton(this, wxID_ANY, _(">"), wxDefaultPosition, wxSize(-1,-1), 0);
    btF->SetToolTip(_("Next key frame [Right]"));
    
    szNav->Add(btF, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btF->SetMinSize(wxSize(25,-1));
    
    btFF = new wxButton(this, wxID_ANY, _(">>"), wxDefaultPosition, wxSize(-1,-1), 0);
    btFF->SetToolTip(_("Forward 10 MB [SHIFT + Right]"));
    
    szNav->Add(btFF, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btFF->SetMinSize(wxSize(35,-1));
    
    btFFF = new wxButton(this, wxID_ANY, _(">>>"), wxDefaultPosition, wxSize(-1,-1), 0);
    btFFF->SetToolTip(_("Forward 100 MB [CTRL + Right]"));
    
    szNav->Add(btFFF, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btFFF->SetMinSize(wxSize(40,-1));
    
    szNav->Add(0, 0, 1, wxEXPAND, 5);
    
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    
    szMain->Add(szBottom, 0, wxEXPAND, 5);
    
    wxBoxSizer* szControls = new wxBoxSizer(wxVERTICAL);
    
    szBottom->Add(szControls, 3, wxEXPAND, 5);
    
    wxBoxSizer* szCuts = new wxBoxSizer(wxHORIZONTAL);
    
    szControls->Add(szCuts, 0, wxEXPAND, 5);
    
    btAddCut = new wxButton(this, wxID_ANY, _("+"), wxDefaultPosition, wxSize(-1, -1), 0);
    btAddCut->SetToolTip(_("Add cut"));
    
    szCuts->Add(btAddCut, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btAddCut->SetMinSize(wxSize(25,-1));
    
    btRemoveCut = new wxButton(this, wxID_ANY, _("-"), wxDefaultPosition, wxSize(-1, -1), 0);
    btRemoveCut->SetToolTip(_("Remove selected cut"));
    
    szCuts->Add(btRemoveCut, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btRemoveCut->SetMinSize(wxSize(25,-1));
    
    wxArrayString cbCutsArr;
    cbCuts = new wxComboBox(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), cbCutsArr, wxCB_SORT|wxCB_READONLY);
    
    szCuts->Add(cbCuts, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    
    btTestCut = new wxButton(this, wxID_ANY, _("Test"), wxDefaultPosition, wxSize(-1, -1), 0);
    btTestCut->Enable(false);
    
    szCuts->Add(btTestCut, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    btTestCut->SetMinSize(wxSize(40,-1));
    
    fpIn = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxSize(-1, -1), wxFLP_DEFAULT_STYLE|wxFLP_USE_TEXTCTRL|wxFLP_SMALL|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN);
    
    szControls->Add(fpIn, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    
    fpOut = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxSize(-1, -1), wxFLP_USE_TEXTCTRL|wxFLP_SMALL|wxFLP_SAVE);
    
    szControls->Add(fpOut, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    
    tcOptions = new wxTextCtrl(this, wxID_ANY, wxT("-c:v libx264 -c:a copy -crf:v 20"), wxDefaultPosition, wxSize(-1, -1), 0);
    #if wxVERSION_NUMBER >= 3000
    tcOptions->SetHint(wxT(""));
    #endif
    
    szControls->Add(tcOptions, 0, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* szAction = new wxBoxSizer(wxHORIZONTAL);
    
    szControls->Add(szAction, 1, wxEXPAND, 5);
    
    btScan = new wxButton(this, wxID_ANY, _("Scan for errors"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    szAction->Add(btScan, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    
    btCut = new wxButton(this, wxID_ANY, _("Cut selected streams"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    szAction->Add(btCut, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    
    wxArrayString clStreamsArr;
    clStreams = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), clStreamsArr, wxLB_SINGLE);
    
    szBottom->Add(clStreams, 1, wxALL|wxEXPAND, 5);
    
    sbStreamorder = new wxSpinButton(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxSP_VERTICAL);
    sbStreamorder->SetToolTip(_("Change stream order"));
    sbStreamorder->SetRange(0, 100);
    sbStreamorder->SetValue(0);
    
    szBottom->Add(sbStreamorder, 0, wxALL|wxEXPAND, 5);
    
    sbStatus = new wxStatusBar(this, wxID_ANY, wxST_SIZEGRIP);
    sbStatus->SetFieldsCount(3);
    this->SetStatusBar(sbStatus);
    
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    SetName(wxT("MainFrameBase"));
    SetSize(600,750);
    if (GetSizer()) {
         GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    this->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MainFrameBase::OnKeyDown), NULL, this);
    sdPosition->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MainFrameBase::OnSdpositionScrollChanged), NULL, this);
    btRRR->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btRRROnButtonClick), NULL, this);
    btRR->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btRROnButtonClick), NULL, this);
    btR->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btROnButtonClick), NULL, this);
    btF->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btFOnButtonClick), NULL, this);
    btFF->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btFFOnButtonClick), NULL, this);
    btFFF->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btFFFOnButtonClick), NULL, this);
    btAddCut->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btAddCutOnButtonClick), NULL, this);
    btRemoveCut->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btRemoveCutOnButtonClick), NULL, this);
    cbCuts->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(MainFrameBase::cbCutsOnCombobox), NULL, this);
    fpIn->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MainFrameBase::OnFpinFilepickerChanged), NULL, this);
    btScan->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btScanOnButtonClick), NULL, this);
    btCut->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btCutOnButtonClick), NULL, this);
    sbStreamorder->Connect(wxEVT_SPIN, wxSpinEventHandler(MainFrameBase::sbStreamorderOnSpin), NULL, this);
    
}

MainFrameBase::~MainFrameBase()
{
    this->Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(MainFrameBase::OnKeyDown), NULL, this);
    sdPosition->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MainFrameBase::OnSdpositionScrollChanged), NULL, this);
    btRRR->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btRRROnButtonClick), NULL, this);
    btRR->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btRROnButtonClick), NULL, this);
    btR->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btROnButtonClick), NULL, this);
    btF->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btFOnButtonClick), NULL, this);
    btFF->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btFFOnButtonClick), NULL, this);
    btFFF->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btFFFOnButtonClick), NULL, this);
    btAddCut->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btAddCutOnButtonClick), NULL, this);
    btRemoveCut->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btRemoveCutOnButtonClick), NULL, this);
    cbCuts->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(MainFrameBase::cbCutsOnCombobox), NULL, this);
    fpIn->Disconnect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MainFrameBase::OnFpinFilepickerChanged), NULL, this);
    btScan->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btScanOnButtonClick), NULL, this);
    btCut->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::btCutOnButtonClick), NULL, this);
    sbStreamorder->Disconnect(wxEVT_SPIN, wxSpinEventHandler(MainFrameBase::sbStreamorderOnSpin), NULL, this);
    
}
