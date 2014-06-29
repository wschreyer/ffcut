///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 26 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/slider.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/filepicker.h>
#include <wx/checklst.h>
#include <wx/spinbutt.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxTextCtrl* tcLog;
		wxSlider* sdPosition;
		wxButton* btRRR;
		wxButton* btRR;
		wxButton* btR;
		wxButton* btPlay;
		wxButton* btF;
		wxButton* btFF;
		wxButton* btFFF;
		wxButton* btAddCut;
		wxButton* btRemoveCut;
		wxComboBox* cbCuts;
		wxButton* btTestCut;
		wxFilePickerCtrl* fpIn;
		wxFilePickerCtrl* fpOut;
		wxTextCtrl* tcOptions;
		wxButton* btScan;
		wxButton* btCut;
		wxCheckListBox* clStreams;
		wxSpinButton* sbStreamorder;
		wxStatusBar* sbStatus;
		
		// Virtual event handlers, overide them in your derived class
		virtual void sdPositionOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void btRRROnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btRROnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btROnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btFOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btFFOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btFFFOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btAddCutOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btRemoveCutOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void cbCutsOnCombobox( wxCommandEvent& event ) { event.Skip(); }
		virtual void fpInOnFileChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void btScanOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void btCutOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void sbStreamorderOnSpin( wxSpinEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("ffcut"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 547,404 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrameBase();
	
};

#endif //__GUI_H__
