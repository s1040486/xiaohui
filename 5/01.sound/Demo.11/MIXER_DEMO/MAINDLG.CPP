//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//
// If you wish to add new classes to this collection, feel free to do so.
// But please send me your code so that I can update the collection.
//
// Comments and bug reports: lpitre@sympatico.ca
//
//=============================================================================
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mixercontrols.h"
#include "MainDlg.h"
#include "MixerInfo.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : CMainDlg
//          
// Descr. : 
//          
// Arg    : CWnd* pParent /*=NULL*/ : 
//-----------------------------------------------------------------------------
CMainDlg::CMainDlg( CWnd* pParent /*=NULL*/ )
	: CDialog( CMainDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT( CMainDlg )
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}



//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : DoDataExchange
//          
// Descr. : 
//          
// Return : void
// Arg    : CDataExchange* pDX : 
//-----------------------------------------------------------------------------
void CMainDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP( CMainDlg )
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CMainDlg, CDialog )
	//{{AFX_MSG_MAP( CMainDlg )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND( ID_INFO, OnInfo )
	ON_COMMAND( ID_INFO_DLG, OnInfoDlg )
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE( ID_SPEAKERS, ID_VOICEIN, OnChangeDialog )
	ON_UPDATE_COMMAND_UI_RANGE( ID_SPEAKERS, ID_VOICEIN, OnUpdateMenu )
END_MESSAGE_MAP()


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnInitDialog
//          
// Descr. : 
//          
// Return : BOOL
//-----------------------------------------------------------------------------
BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
	SetIcon( m_hIcon, TRUE );		// Set big icon
	SetIcon( m_hIcon, FALSE );		// Set small icon

	wvDlg.Create( IDD_WAVEIN_DIALOG,  this );
	spDlg.Create( IDD_SPEAKER_DIALOG, this );
	//vcDlg.Create( IDD_WAVEIN_DIALOG,  this );
    vcDlg.Create(IDD_VOICE_DIALOG, this); 

	OnChangeDialog( ID_SPEAKERS );

	return TRUE;
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnPaint
//          
//  If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//          
// Return : void
//-----------------------------------------------------------------------------
void CMainDlg::OnPaint() 
{
	if ( IsIconic() )
	{
		CPaintDC dc( this ); // device context for painting

		SendMessage( WM_ICONERASEBKGND, ( WPARAM ) dc.GetSafeHdc(), 0 );

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics( SM_CXICON );
		int cyIcon = GetSystemMetrics( SM_CYICON );
		CRect rect;
		GetClientRect( &rect );
		int x = ( rect.Width() - cxIcon + 1 ) / 2;
		int y = ( rect.Height() - cyIcon + 1 ) / 2;

		// Draw the icon
		dc.DrawIcon( x, y, m_hIcon );
	}
	else
	{
		CDialog::OnPaint();
	}
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnQueryDragIcon
//          
// Descr. : 
//          
// Return : HCURSOR
//-----------------------------------------------------------------------------
HCURSOR CMainDlg::OnQueryDragIcon() 
{
	return ( HCURSOR ) m_hIcon;
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnChangeDialog
//          
// Descr. : Callback for a range of commands.
//          CMainDlg is an empty dialog resource. Instead, it owns and displays
//          child dialog boxes. This function performs switching between child
//          dialogs by hiding the current child dialog and showing the new
//          one. The main dialog then resizes to fit around the new child dialog.
//          
// Return : void
// Arg    : UINT nId : command id
//-----------------------------------------------------------------------------
void CMainDlg::OnChangeDialog( UINT nId )
{
	static UINT currentDlg = 0;
	CRect       childRect;

	if( nId == currentDlg )
		return;

	switch( nId )
	{
		case ID_SPEAKERS:
			vcDlg.ShowWindow( SW_HIDE );
			wvDlg.ShowWindow( SW_HIDE );
			spDlg.ShowWindow( SW_SHOW );
			spDlg.GetWindowRect( &childRect );
			break;

		case ID_WAVEIN:
			spDlg.ShowWindow( SW_HIDE );
			vcDlg.ShowWindow( SW_HIDE );
			wvDlg.ShowWindow( SW_SHOW );
			wvDlg.GetWindowRect( &childRect );
			break;

		case ID_VOICEIN:
			spDlg.ShowWindow( SW_HIDE );
			wvDlg.ShowWindow( SW_HIDE );
			vcDlg.ShowWindow( SW_SHOW );
			vcDlg.GetWindowRect( &childRect );
			break;
	}

	// resize the main window to fit the new child dialog

    //static int menuHeight = GetSystemMetrics( SM_CYMENU );
    //CalcWindowRect( &childRect );
    //SetWindowPos( &wndTop, 0, 0, childRect.Width(), childRect.Height() + menuHeight,
    //              SWP_NOMOVE|SWP_NOZORDER );
    
	::AdjustWindowRectEx(&childRect, GetStyle(), TRUE, GetExStyle());
    SetWindowPos(&wndTop, 0, 0, childRect.Width(), childRect.Height(), SWP_NOMOVE | SWP_NOZORDER); 

	currentDlg = nId;
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnInfo
//          
// Descr. : 
//          
// Return : void
//-----------------------------------------------------------------------------
void CMainDlg::OnInfo() 
{
	GetDevicesInfo( "mixerinfo.txt" );
	if( ( int )ShellExecute( GetSafeHwnd(), "open", "notepad.exe", "mixerinfo.txt", ".", SW_SHOW ) < 33 )
		MessageBox( "ShellExecute returned an error." );
	
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnInfoDlg
//          
// Descr. : 
//          
// Return : void
//-----------------------------------------------------------------------------
void CMainDlg::OnInfoDlg() 
{
	CInfoDlg  inDlg(this);

	inDlg.DoModal();
}

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
// Name   : OnUpdateMenu
//          
// Descr. : menu update callback for a range of command IDs
//          
// Return : void
// Arg    : CCmdUI* pCmdUI : 
//-----------------------------------------------------------------------------
void CMainDlg::OnUpdateMenu( CCmdUI* pCmdUI ) 
{		
	CMenu *menu = GetMenu();

	if( menu == NULL )
		return;

	switch( pCmdUI->m_nID )
	{
		case ID_SPEAKERS:
			TRACE( "  -- check ID_SPEAKERS.\n" );
			menu->CheckMenuItem( ID_SPEAKERS, MF_CHECKED   );
			menu->CheckMenuItem( ID_WAVEIN,   MF_UNCHECKED );
			menu->CheckMenuItem( ID_VOICEIN,  MF_UNCHECKED );
			break;

		case ID_WAVEIN:
			TRACE( "  -- check ID_WAVEIN.\n" );
			menu->CheckMenuItem( ID_SPEAKERS, MF_UNCHECKED );
			menu->CheckMenuItem( ID_WAVEIN,   MF_CHECKED   );
			menu->CheckMenuItem( ID_VOICEIN,  MF_UNCHECKED );
			break;

		case ID_VOICEIN:
            TRACE( "  -- check ID_VOICEIN.\n" );
			menu->CheckMenuItem( ID_SPEAKERS, MF_UNCHECKED );
			menu->CheckMenuItem( ID_WAVEIN,   MF_UNCHECKED );
			menu->CheckMenuItem( ID_VOICEIN,  MF_CHECKED   );
			break;
	}
}

