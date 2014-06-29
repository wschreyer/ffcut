///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 26 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	wxBoxSizer* szMain;
	szMain = new wxBoxSizer( wxVERTICAL );
	
	tcLog = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	tcLog->SetMaxLength( 0 ); 
	szMain->Add( tcLog, 1, wxALL|wxEXPAND, 5 );
	
	sdPosition = new wxSlider( this, wxID_ANY, 0, 0, 1024, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	szMain->Add( sdPosition, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* szNav;
	szNav = new wxBoxSizer( wxHORIZONTAL );
	
	
	szNav->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btRRR = new wxButton( this, wxID_ANY, _("<<<"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	btRRR->SetMinSize( wxSize( 40,-1 ) );
	
	szNav->Add( btRRR, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btRR = new wxButton( this, wxID_ANY, _("<<"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	btRR->SetMinSize( wxSize( 35,-1 ) );
	
	szNav->Add( btRR, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btR = new wxButton( this, wxID_ANY, _("<"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	btR->SetMinSize( wxSize( 25,-1 ) );
	
	szNav->Add( btR, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btPlay = new wxButton( this, wxID_ANY, _("Play"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	btPlay->SetMinSize( wxSize( 40,-1 ) );
	
	szNav->Add( btPlay, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btF = new wxButton( this, wxID_ANY, _(">"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	btF->SetMinSize( wxSize( 25,-1 ) );
	
	szNav->Add( btF, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btFF = new wxButton( this, wxID_ANY, _(">>"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	btFF->SetMinSize( wxSize( 35,-1 ) );
	
	szNav->Add( btFF, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btFFF = new wxButton( this, wxID_ANY, _(">>>"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	btFFF->SetMinSize( wxSize( 40,-1 ) );
	
	szNav->Add( btFFF, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	szNav->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	szMain->Add( szNav, 0, wxEXPAND, 5 );
	
	wxBoxSizer* szBottom;
	szBottom = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* szControls;
	szControls = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* szCuts;
	szCuts = new wxBoxSizer( wxHORIZONTAL );
	
	btAddCut = new wxButton( this, wxID_ANY, _("+"), wxDefaultPosition, wxDefaultSize, 0 );
	btAddCut->SetMinSize( wxSize( 25,-1 ) );
	
	szCuts->Add( btAddCut, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btRemoveCut = new wxButton( this, wxID_ANY, _("-"), wxDefaultPosition, wxDefaultSize, 0 );
	btRemoveCut->SetMinSize( wxSize( 25,-1 ) );
	
	szCuts->Add( btRemoveCut, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	cbCuts = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_SORT ); 
	szCuts->Add( cbCuts, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btTestCut = new wxButton( this, wxID_ANY, _("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	btTestCut->SetMinSize( wxSize( 40,-1 ) );
	
	szCuts->Add( btTestCut, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	szControls->Add( szCuts, 0, wxEXPAND, 5 );
	
	fpIn = new wxFilePickerCtrl( this, wxID_ANY, wxT("Transport stream"), _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL );
	szControls->Add( fpIn, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	fpOut = new wxFilePickerCtrl( this, wxID_ANY, wxT("Output file prefix"), _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	szControls->Add( fpOut, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	tcOptions = new wxTextCtrl( this, wxID_ANY, _("-c:v libx264 -c:a copy -crf:v 20"), wxDefaultPosition, wxDefaultSize, 0 );
	szControls->Add( tcOptions, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* szAction;
	szAction = new wxBoxSizer( wxHORIZONTAL );
	
	btScan = new wxButton( this, wxID_ANY, _("Scan for errors"), wxDefaultPosition, wxDefaultSize, 0 );
	szAction->Add( btScan, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btCut = new wxButton( this, wxID_ANY, _("Cut selected streams"), wxDefaultPosition, wxDefaultSize, 0 );
	szAction->Add( btCut, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	szControls->Add( szAction, 1, wxEXPAND, 5 );
	
	
	szBottom->Add( szControls, 3, wxEXPAND, 5 );
	
	wxArrayString clStreamsChoices;
	clStreams = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, clStreamsChoices, wxLB_SINGLE );
	szBottom->Add( clStreams, 1, wxALL|wxEXPAND, 5 );
	
	sbStreamorder = new wxSpinButton( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_VERTICAL );
	szBottom->Add( sbStreamorder, 0, wxALL|wxEXPAND, 5 );
	
	
	szMain->Add( szBottom, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( szMain );
	this->Layout();
	sbStatus = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	sdPosition->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrameBase::sdPositionOnScroll ), NULL, this );
	btRRR->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btRRROnButtonClick ), NULL, this );
	btRR->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btRROnButtonClick ), NULL, this );
	btR->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btROnButtonClick ), NULL, this );
	btF->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btFOnButtonClick ), NULL, this );
	btFF->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btFFOnButtonClick ), NULL, this );
	btFFF->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btFFFOnButtonClick ), NULL, this );
	btAddCut->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btAddCutOnButtonClick ), NULL, this );
	btRemoveCut->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btRemoveCutOnButtonClick ), NULL, this );
	cbCuts->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrameBase::cbCutsOnCombobox ), NULL, this );
	fpIn->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainFrameBase::fpInOnFileChanged ), NULL, this );
	btScan->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btScanOnButtonClick ), NULL, this );
	btCut->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btCutOnButtonClick ), NULL, this );
	sbStreamorder->Connect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( MainFrameBase::sbStreamorderOnSpin ), NULL, this );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	sdPosition->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrameBase::sdPositionOnScroll ), NULL, this );
	btRRR->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btRRROnButtonClick ), NULL, this );
	btRR->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btRROnButtonClick ), NULL, this );
	btR->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btROnButtonClick ), NULL, this );
	btF->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btFOnButtonClick ), NULL, this );
	btFF->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btFFOnButtonClick ), NULL, this );
	btFFF->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btFFFOnButtonClick ), NULL, this );
	btAddCut->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btAddCutOnButtonClick ), NULL, this );
	btRemoveCut->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btRemoveCutOnButtonClick ), NULL, this );
	cbCuts->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrameBase::cbCutsOnCombobox ), NULL, this );
	fpIn->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( MainFrameBase::fpInOnFileChanged ), NULL, this );
	btScan->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btScanOnButtonClick ), NULL, this );
	btCut->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::btCutOnButtonClick ), NULL, this );
	sbStreamorder->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( MainFrameBase::sbStreamorderOnSpin ), NULL, this );
	
}
