/*********************************************************************
 * Name:      	main.cpp
 * Purpose:   	Implements simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note that all GUI creation code is implemented in
 * 				gui.cpp source file which is generated by wxFormBuilder.
 *********************************************************************/

#include "main.h"

#include <limits>
#include <sstream>
#include <iomanip>

#include "wx/stdpaths.h"
#include "wx/dnd.h"

#define PREVIEW_WIDTH 640
#define PREVIEW_HEIGHT 360

#ifndef AV_ERROR_MAX_STRING_SIZE
#define AV_ERROR_MAX_STRING_SIZE 64
#endif

// initialize the application
IMPLEMENT_APP(MainApp);

////////////////////////////////////////////////////////////////////////////////
// application class implementation 
////////////////////////////////////////////////////////////////////////////////

bool MainApp::OnInit()
{
	SetTopWindow( new MainFrame( NULL ) );
	GetTopWindow()->Show();
	
	// true = enter the main loop
	return true;
}

wxTimeSpan PTStoWXTime(int64_t PTS, AVRational time_base){
	if (PTS == (int64_t)AV_NOPTS_VALUE)
		return wxTimeSpan(0, 0, 0, 0);
	return wxTimeSpan(0, 0, 0, PTS*time_base.num*1000/time_base.den);
}

wxString errstr;

void av_log_callback(void* ptr, int level, const char* fmt, va_list vl)
{
	if (level > AV_LOG_VERBOSE && strncmp(fmt, "Continuity", 10))
		return;
	wxString str;
	str.PrintfV(fmt, vl);
	errstr += str;
}

////////////////////////////////////////////////////////////////////////////////
// main application frame implementation 
////////////////////////////////////////////////////////////////////////////////

class MyDropTarget: public wxFileDropTarget{
	wxFilePickerCtrl *owner;
	
public:
	MyDropTarget(wxFilePickerCtrl *aowner){
		owner = aowner;
	}
	
	bool OnDropFiles(wxCoord x,	wxCoord	y, const wxArrayString &filenames){
		if (filenames.size() == 1){
			owner->SetPath(filenames[0]);
			wxFileDirPickerEvent ev(wxEVT_COMMAND_FILEPICKER_CHANGED, owner, owner->GetId(), filenames[0]);
			owner->GetEventHandler()->ProcessEvent(ev);
			return true;
		}
		return false;
	}
};

MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent )
{
	av_register_all();	
	
	MyDropTarget *dt = new MyDropTarget(fpIn);
	SetDropTarget(&(*dt));

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		*tcLog << "Could not init video\n";
	window = NULL;
	renderer = NULL;
	texture = NULL;
}

MainFrame::~MainFrame()
{
	if (fc)
		avformat_close_input(&fc);
	if (texture)
		SDL_DestroyTexture(texture);
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
}

void MainFrame::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void MainFrame::OnExitClick(wxCommandEvent& event)
{
	Destroy();
}

void MainFrame::Scan(){
	if (!fc)
		return;
		
	
	wxString str;
	clStreams->Clear();
	int defstr = av_find_best_stream(fc, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	if (defstr < 0){
		char errbuf[AV_ERROR_MAX_STRING_SIZE];
		av_strerror(defstr, errbuf, AV_ERROR_MAX_STRING_SIZE);
		*tcLog << "Could not find stream for preview: " << errbuf << '\n';
	}
	
	for (int i = 0; i < (int)fc->nb_streams; i++){
		AVStream *stream = fc->streams[i];
		AVCodecContext *cc = stream->codec;
		if (cc){
			AVCodec *c = avcodec_find_decoder(cc->codec_id);
			if (c){
				if (cc->codec_type == AVMEDIA_TYPE_VIDEO){
					str.Printf("%d: %s (%dx%d)", i, c->name, cc->width, cc->height);
				}
				else if (cc->codec_type == AVMEDIA_TYPE_AUDIO){
					str.Printf("%d: %s (%d channels)", i, c->name, cc->channels);
				}
				else{
					str.Printf("%d: %d", i, c->name);
				}
			}
			else{
				str.Printf("%d: codec not found", i);
			}
			int *streamindex = new int(i);
			int clindex = clStreams->Append(str, streamindex);
			if (i == defstr || cc->codec_type == AVMEDIA_TYPE_AUDIO)
				clStreams->Check(clindex);
		}
	}
		
//	clStreams->AppendString(fc->iformat->long_name);
//	if (fc->iformat->priv_class)
//		clStreams->AppendString(fc->iformat->priv_class->class_name);
		
	if (texture)
		SDL_DestroyTexture(texture);
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
		
	int x,y;
	GetScreenPosition(&x, &y);
	y -= PREVIEW_HEIGHT + 30;
	if (y < 0)
		y = 30;
	window = SDL_CreateWindow("ffcut Preview", x, y, PREVIEW_WIDTH, PREVIEW_HEIGHT, 0);
	if (!window)
		*tcLog << "Could not create preview window: " << SDL_GetError();
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
		*tcLog << "Could not create preview renderer: " << SDL_GetError();
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STATIC, PREVIEW_WIDTH, PREVIEW_HEIGHT);
	if (!texture)
		*tcLog << "Could not create preview texture: " << SDL_GetError();		
}

int MainFrame::NextPacket(int stream_index, AVPacket *pkt, int flags){
	int ret;
	for (;;){
		av_init_packet(pkt);
		ret = av_read_frame(fc, pkt);
		if (ret < 0){
			char errbuf[AV_ERROR_MAX_STRING_SIZE];
			av_strerror(ret, errbuf, AV_ERROR_MAX_STRING_SIZE);
			*tcLog << "Cannot read frame: " << errbuf << '\n';
			av_packet_unref(pkt);
			return ret;
		}
		if (pkt->stream_index == stream_index){
			if (!flags || (pkt->flags & flags))
				return ret;
		}
		av_packet_unref(pkt);
	}
}

void MainFrame::Preview(){
	if (!fc)
		return;	
		
		
	previewedStream = NULL;
	for (unsigned int i = 0; i < clStreams->GetCount(); i++){
		if (clStreams->IsChecked(i) && fc->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
			previewedStream = fc->streams[i];
			break;
		}
	}
	if (!previewedStream){
		*tcLog << "No video stream selected\n";
		return;
	}
		
	AVPacket pkt;
	pkt.data = NULL;
	pkt.size = 0;
	int ret;
	
	if (NextPacket(previewedStream->index, &pkt, AV_PKT_FLAG_KEY) < 0)
		return;
	
	sdPosition->SetValue(fc->pb->pos * sdPosition->GetMax() / avio_size(fc->pb));		

//	*tcLog << "Found keyframe\n";
	previewedPos = pkt.pos;
	previewedPTS = PTStoWXTime(pkt.pts, previewedStream->time_base);

	wxString str;
	wxNumberFormatter nf;
	sbStatus->SetStatusText("File position: " + nf.ToString(pkt.pos));
	wxTimeSpan start_time = PTStoWXTime(fc->start_time, AV_TIME_BASE_Q);
	str << previewedPTS.Format("%H:%M:%S.%l") << "(~ "
		<< (previewedPTS - start_time).Format("%H:%M:%S.%l") << ")";
	sbStatus->SetStatusText(str, 1);
	str.clear();
	str << "Duration: " << pkt.duration << " ms";
	sbStatus->SetStatusText(str, 2);
	str.clear();

	AVCodec *c = avcodec_find_decoder(previewedStream->codec->codec_id);
	if (!c){
		*tcLog << "Decoder not found\n";
		av_packet_unref(&pkt);
		return;
	}
	ret = avcodec_open2(previewedStream->codec, c, NULL);
	if (ret < 0){
		char errbuf[AV_ERROR_MAX_STRING_SIZE];
		av_strerror(ret, errbuf, AV_ERROR_MAX_STRING_SIZE);
		*tcLog << "Could not open decoder: " << errbuf << '\n';
		av_packet_unref(&pkt);
		return;
	}

	AVFrame *fr = av_frame_alloc();
	if (!fr){
		*tcLog << "Cannot allocate frame\n";
		avcodec_close(previewedStream->codec);
		av_packet_unref(&pkt);
		return;
	}

	int pic = 0;
	for (;;){
		if (pkt.flags & AV_PKT_FLAG_CORRUPT){
			*tcLog << "Corrupt Frame\n";
		}		
		ret = avcodec_decode_video2(previewedStream->codec, fr, &pic, &pkt);
//						*tcLog << "Decoding " << ret << " bytes\n";
		if (ret <= 0){
			char errbuf[AV_ERROR_MAX_STRING_SIZE];
			av_strerror(ret, errbuf, AV_ERROR_MAX_STRING_SIZE);
			*tcLog << "Cannot decode video: " << errbuf << '\n';
			break;
		}
		av_packet_unref(&pkt);
		
		if (pic){
			uint8_t *pixels[4];
			int linesizes[4];
			ret = av_image_alloc(pixels, linesizes, PREVIEW_WIDTH, PREVIEW_HEIGHT, AV_PIX_FMT_YUV420P, 16);
			if (ret < 0){
				char errbuf[AV_ERROR_MAX_STRING_SIZE];
				av_strerror(ret, errbuf, AV_ERROR_MAX_STRING_SIZE);
				*tcLog << "Cannot allocate pic buffer: " << errbuf << '\n';
				break;
			}
			SwsContext *sc = sws_getContext(fr->width, fr->height, (AVPixelFormat)fr->format, PREVIEW_WIDTH, PREVIEW_HEIGHT, AV_PIX_FMT_YUV420P, SWS_BILINEAR, NULL, NULL, NULL);
			if (sc){
				sws_scale(sc, fr->data, fr->linesize, 0, fr->height, pixels, linesizes);
				ret = SDL_UpdateYUVTexture(texture, NULL, pixels[0], linesizes[0], pixels[1], linesizes[1], pixels[2], linesizes[2]);
	//			ret = SDL_UpdateYUVTexture(texture, NULL, fr->data[0], fr->linesize[0], fr->data[1], fr->linesize[1], fr->data[2], fr->linesize[2]);
				if (ret < 0);
					*tcLog << SDL_GetError();
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, texture, NULL, NULL);
				SDL_RenderPresent(renderer);
				sws_freeContext(sc);
			}
			av_freep(&pixels[0]);
/*			
			if (NextPacket(previewedStream->index, &pkt, AV_PKT_FLAG_KEY) >= 0){
				wxTimeSpan PTS2(0, 0, 0, pkt.pts*previewedStream->time_base.num*1000/previewedStream->time_base.den);
				str << "Duration: " << (PTS2-PTS).GetMilliseconds() << " ms";
				sbStatus->SetStatusText(str, 2);
				av_seek_frame(fc, previewedStream->index, pkt.pos, AVSEEK_FLAG_BYTE);
			}*/
			break;
		}
		else if (NextPacket(previewedStream->index, &pkt) < 0)
			break;
			
	}
	av_free(fr);
	avcodec_close(previewedStream->codec);
	av_packet_unref(&pkt);
}

void MainFrame::Seek(int64_t bytepos, wxTimeSpan timepos){
	if (!fc)
		return;
		
	int ret;
	if (fc->iformat->flags & AVFMT_NO_BYTE_SEEK){
		int64_t PTSpos;
		if (timepos.IsNull())
			PTSpos = previewedStream->start_time + previewedStream->duration*bytepos/avio_size(fc->pb);
		else
			PTSpos = (timepos.GetMilliseconds()*previewedStream->time_base.den/1000/previewedStream->time_base.num).GetValue();
		ret = av_seek_frame(fc, previewedStream->index, PTSpos, 0);		
	}
	else
		ret = av_seek_frame(fc, previewedStream->index, bytepos, AVSEEK_FLAG_BYTE);
		
	if (ret < 0){
		char errbuf[AV_ERROR_MAX_STRING_SIZE];
		av_strerror(ret, errbuf, AV_ERROR_MAX_STRING_SIZE);
		*tcLog << "Cannot seek file: " << errbuf << '\n';
		return;
	}
}


void MainFrame::OnFpinFilepickerChanged(wxFileDirPickerEvent& event)
{
	tcLog->Clear();
	
	if (fc)
		avformat_close_input(&fc);
		
	cbCuts->Clear();
		
	wxString fn = event.GetPath();
	fpOut->SetFileName(fn);
	
	fc = NULL;
	int ret = avformat_open_input(&fc, fn.c_str(), NULL, NULL);
	if (ret < 0){
		char errbuf[AV_ERROR_MAX_STRING_SIZE];
		av_strerror(ret, errbuf, AV_ERROR_MAX_STRING_SIZE);
		*tcLog << "Cannot open input file: " << errbuf << '\n';
		return;
	}
	
	fc->error_recognition = 0x7FFFFFFF;
//	fc->debug = FF_FDEBUG_TS;
	fc->flags |= AVFMT_FLAG_GENPTS;
	
	ret = avformat_find_stream_info(fc, NULL);
	if (ret < 0){
		char errbuf[AV_ERROR_MAX_STRING_SIZE];
		av_strerror(ret, errbuf, AV_ERROR_MAX_STRING_SIZE);
		*tcLog << "Cannot find stream info: " << errbuf << '\n';
		return;
	}
			
	Scan();
	
	Preview();
}

void MainFrame::btFOnButtonClick( wxCommandEvent& event ){
	Preview();
}

void MainFrame::btFFOnButtonClick( wxCommandEvent& event ){
	Seek(fc->pb->pos + 10*1024*1024, previewedPTS + wxTimeSpan(0,0,10));
	Preview();
}

void MainFrame::btFFFOnButtonClick( wxCommandEvent& event ){
	Seek(fc->pb->pos + 100*1024*1024, previewedPTS + wxTimeSpan(0,0,100));
	Preview();
}
void MainFrame::btROnButtonClick(wxCommandEvent& event)
{
	Seek(fc->pb->pos - 10*1024*1024, previewedPTS - wxTimeSpan(0,0,10));

	AVPacket pkt, lastpkt;
	pkt.data = lastpkt.data = NULL;
	pkt.size = lastpkt.size = 0;
	for (;;){
		if (NextPacket(previewedStream->index, &pkt, AV_PKT_FLAG_KEY) >= 0){
			if (PTStoWXTime(pkt.pts, previewedStream->time_base) < previewedPTS){
				if (lastpkt.size > 0)
					av_packet_unref(&lastpkt);
				lastpkt = pkt;
			}
			else if (PTStoWXTime(pkt.pts, previewedStream->time_base) == previewedPTS && lastpkt.size > 0){
				Seek(lastpkt.pos, PTStoWXTime(lastpkt.pts, previewedStream->time_base));
				Preview();
				break;
			}
			else{
				*tcLog << "Did not find any previous frames\n";
				break;
			}
		}
	}
	if (pkt.size > 0)
		av_packet_unref(&pkt);
	if (lastpkt.size > 0)
		av_packet_unref(&lastpkt);
}

void MainFrame::btRROnButtonClick(wxCommandEvent& event)
{
	Seek(fc->pb->pos - 10*1024*1024, previewedPTS - wxTimeSpan(0,0,10));
	Preview();
}

void MainFrame::btRRROnButtonClick(wxCommandEvent& event)
{
	Seek(fc->pb->pos - 100*1024*1024, previewedPTS - wxTimeSpan(0,0,100));
	Preview();
}

void MainFrame::OnSdpositionScrollChanged(wxScrollEvent& event)
{
	Seek(avio_size(fc->pb)*sdPosition->GetValue()/sdPosition->GetMax(), 
			previewedStream->start_time + previewedStream->duration*sdPosition->GetValue()/sdPosition->GetMax());
	Preview();
}


void MainFrame::btScanOnButtonClick(wxCommandEvent& event)
{
	if (!fc)
		return;
	
//	int64_t originalpos = fc->pb->pos;
	
	av_log_set_callback(&av_log_callback);

	Seek(0, 0);
	
	int64_t lastPTS[fc->nb_streams];
	int64_t lastpos[fc->nb_streams];
	wxTimeSpan start_time = PTStoWXTime(fc->start_time, AV_TIME_BASE_Q);
	for (unsigned int i = 0; i < fc->nb_streams; i++){
		lastPTS[i] = AV_NOPTS_VALUE;
		lastpos[i] = 0;
	}
	wxString str;
	wxNumberFormatter nf;
	
	AVPacket pkt;
	for (;;){
		av_init_packet(&pkt);
		int ret = av_read_frame(fc, &pkt);
		if (ret < 0){
			char errbuf[AV_ERROR_MAX_STRING_SIZE];
			av_strerror(ret, errbuf, AV_ERROR_MAX_STRING_SIZE);
			*tcLog << "Cannot read frame: " << errbuf << '\n';
			for (unsigned int i = 0; i < fc->nb_streams; i++){
				if (lastPTS[i] == (int64_t)AV_NOPTS_VALUE){
					str.Printf("Stream %d: not found\n", i);
					*tcLog << str;
				}
				else{
					AVStream *stream = fc->streams[i];
					str.Printf("Stream %d: Stopping scan at pos %s, PTS %s (~ %s)\n",
								i, nf.ToString(lastpos[i]), PTStoWXTime(lastPTS[i], stream->time_base).Format("%H:%M:%S.%l"), 
								(PTStoWXTime(lastPTS[i], stream->time_base) - start_time).Format("%H:%M:%S.%l"));
					*tcLog << str;
				}
			}
			break;
		}
		AVStream *stream = fc->streams[pkt.stream_index];
		if (pkt.pts != (int64_t)AV_NOPTS_VALUE && lastPTS[pkt.stream_index] == (int64_t)AV_NOPTS_VALUE){
			str.Printf("Stream %d: Starting scan at pos %s, PTS %s (~ %s)\n",
						pkt.stream_index, nf.ToString(pkt.pos), PTStoWXTime(pkt.pts, stream->time_base).Format("%H:%M:%S.%l"), 
						(PTStoWXTime(pkt.pts, stream->time_base) - start_time).Format("%H:%M:%S.%l"));
			*tcLog << str;
		}
		if (pkt.flags & AV_PKT_FLAG_CORRUPT){
			str.Printf("Stream %d: corrupt frame at pos %s, PTS %s (~ %s)\n",
						pkt.stream_index, nf.ToString(pkt.pos), PTStoWXTime(pkt.pts, stream->time_base).Format("%H:%M:%S.%l"), 
						(PTStoWXTime(pkt.pts, stream->time_base) - start_time).Format("%H:%M:%S.%l"));
			*tcLog << str;
		}
		
		if (errstr.Len() > 0){
			str.Printf("Stream %d at pos %s, PTS %s (~ %s): %s",
						pkt.stream_index, nf.ToString(pkt.pos), PTStoWXTime(pkt.pts, stream->time_base).Format("%H:%M:%S.%l"), 
						(PTStoWXTime(pkt.pts, stream->time_base) - start_time).Format("%H:%M:%S.%l"), errstr);
			*tcLog << str;
			errstr.Clear();
		}

		if (stream->codec->codec_type == AVMEDIA_TYPE_VIDEO && (pkt.flags & AV_PKT_FLAG_KEY)){
			sbStatus->SetStatusText("File position: " + nf.ToString(pkt.pos));
			if (pkt.pts != (int64_t)AV_NOPTS_VALUE){
				str.Printf("%s (~ %s)", PTStoWXTime(pkt.pts, stream->time_base).Format("%H:%M:%S.%l"),
										(PTStoWXTime(pkt.pts, stream->time_base) - start_time).Format("%H:%M:%S.%l"));
				sbStatus->SetStatusText(str, 1);
			}
			str.Printf("Progress: %.1f %%", (float)pkt.pos/avio_size(fc->pb)*100);
			sbStatus->SetStatusText(str, 2);
			sdPosition->SetValue(fc->pb->pos * sdPosition->GetMax() / avio_size(fc->pb));
			wxSafeYield(btScan, true);
		}

		if (pkt.pts != (int64_t)AV_NOPTS_VALUE)
			lastPTS[pkt.stream_index] = pkt.pts;
		if (pkt.pos > 0)
			lastpos[pkt.stream_index] = pkt.pos;

		av_packet_unref(&pkt);
	}
	
	av_packet_unref(&pkt);
	
	av_log_set_callback(&av_log_default_callback);	
		
//	av_seek_frame(fc, -1, originalpos, AVSEEK_FLAG_BYTE);
}

struct TCut{
	int64_t pos;
	wxTimeSpan time;
};

void MainFrame::btCutOnButtonClick(wxCommandEvent& event)
{
	for (unsigned int i = 0; i < cbCuts->GetCount(); i += 2){
		wxFileName path(wxStandardPaths::Get().GetExecutablePath());
		wxSetWorkingDirectory(path.GetPath());
		wxString exestr("ffmpeg");

		wxTimeSpan starttime = ((TCut*)cbCuts->GetClientData(i))->time;
		wxTimeSpan jumptime(starttime);
		jumptime.Subtract(wxTimeSpan(0, 0, 30));
		if (jumptime.IsPositive())
			exestr << jumptime.Format(" -ss %H:%M:%S.%l");
		else 
			jumptime = 0;

		exestr << " -i \"" << fpIn->GetFileName().GetFullPath() << "\"";
		for (unsigned int j = 0; j < clStreams->GetCount(); j++){
			if (clStreams->IsChecked(j)){
				int *streamindex = (int*)clStreams->GetClientData(j);
				exestr << " -map 0:" << *streamindex;
			}
		}
		exestr << " " << tcOptions->GetLineText(0) << " ";
		
		exestr << (starttime - jumptime).Format(" -ss %H:%M:%S.%l");
		if (cbCuts->GetCount() > i + 1)
			exestr << (((TCut*)cbCuts->GetClientData(i+1))->time - starttime).Format(" -t %H:%M:%S.%l");
		wxFileName out(fpOut->GetFileName());
		out.SetName(out.GetName() + ((TCut*)cbCuts->GetClientData(i))->time.Format("_%H%M%S%l"));
		exestr << " \"" << out.GetFullPath() << "\"";
		*tcLog << "Executing " << exestr << '\n';
		wxShell(exestr);
	}
}

void MainFrame::btAddCutOnButtonClick(wxCommandEvent& event)
{
	wxTimeSpan start_time = PTStoWXTime(fc->start_time, AV_TIME_BASE_Q);
	wxTimeSpan time(previewedPTS - start_time);
	TCut *cut = new TCut;
	cut->pos = previewedPos;
	cut->time = time;
	std::ostringstream cutstr;
	cutstr << std::setw(11) << previewedPos << std::setw(0) << " - " << time.Format("%H:%M:%S.%l");
	if (cbCuts->FindString(cutstr.str()) == wxNOT_FOUND)
		cbCuts->SetSelection(cbCuts->Append(cutstr.str(), cut));
}

void MainFrame::btRemoveCutOnButtonClick(wxCommandEvent& event)
{
	int i = cbCuts->GetSelection();
	delete (TCut*)cbCuts->GetClientData(i);
	cbCuts->Delete(i);
	cbCuts->SetSelection(i - 1);
}

void MainFrame::cbCutsOnCombobox(wxCommandEvent& event){
	TCut *cut = (TCut*)cbCuts->GetClientData(cbCuts->GetSelection());
	Seek(cut->pos, (int64_t)cut->time.GetMilliseconds().GetValue()*previewedStream->time_base.den/previewedStream->time_base.num/1000);
	Preview();
}

void MainFrame::sbStreamorderOnSpin( wxSpinEvent& event ){
	int i = clStreams->GetSelection();
	int dir = sbStreamorder->GetValue();
	if ((i != wxNOT_FOUND) && (((dir > 0) && (i > 0)) || ((dir <= 0) && ((unsigned int)i < clStreams->GetCount() - 1)))){
		int *streamindex = (int*)clStreams->GetClientData(i);
		wxString str = clStreams->GetString(i);
		clStreams->Delete(i);
		if (dir <= 0)
			clStreams->Insert(str, i + 1, streamindex);
		else
			clStreams->Insert(str, i - 1, streamindex);
	}
	sbStreamorder->SetValue(0);
}

void MainFrame::OnKeyDown(wxKeyEvent& event)
{
	wxCommandEvent ev(wxEVT_BUTTON);
	int key = event.GetKeyCode();
	int mod = event.GetModifiers();
	if (key == WXK_RIGHT){
		if (mod == wxMOD_NONE)
			btFOnButtonClick(ev);
		else if (mod == wxMOD_SHIFT)
			btFFOnButtonClick(ev);
		else if (mod == wxMOD_CONTROL)
			btFFFOnButtonClick(ev);
	}
	else if (key == WXK_LEFT){
		if (mod == wxMOD_NONE)
			btROnButtonClick(ev);
		else if (mod == wxMOD_SHIFT)
			btRROnButtonClick(ev);
		else if (mod == wxMOD_CONTROL)
			btRRROnButtonClick(ev);
	}
}
