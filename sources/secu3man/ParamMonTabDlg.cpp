 /****************************************************************
 *       SECU-3  - An open source, free engine control unit
 *    Designed by Alexey A. Shabelnikov. Ukraine, Gorlovka 2007.
 *       Microprocessors systems - design & programming.
 *    contacts:
 *              http://secu-3.narod.ru
 *              ICQ: 405-791-931
 ****************************************************************/

#include "stdafx.h"
#include "resource.h"
#include "common/FastDelegate.h"
#include "ParamMonTabDlg.h"
#include "MIDesk/MIDeskDlg.h"
#include "MIDesk/RSDeskDlg.h"
#include "ParamDesk/ParamDeskDlg.h"
#include "ui-core/HotKeysToCmdRouter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace fastdelegate;

BEGIN_MESSAGE_MAP(CParamMonTabDlg, CDialog)
 ON_BN_CLICKED(IDC_PM_SHOW_RAW_SENSORS, OnPmShowRawSensors)
 ON_WM_CLOSE()
 ON_WM_DESTROY()
 ON_COMMAND(IDM_PM_MAXIMIZE_WINDOW, OnMaximizeWindow)	
 ON_COMMAND(IDM_PM_MINIMIZE_WINDOW, OnMinimizeWindow)	
END_MESSAGE_MAP()

CParamMonTabDlg::CParamMonTabDlg(CWnd* pParent /*=NULL*/)
: CTabDialog(CParamMonTabDlg::IDD, pParent)
, mp_MIDeskDlg(new CMIDeskDlg())
, mp_RSDeskDlg(new CRSDeskDlg())
, mp_ParamDeskDlg(new CParamDeskDlg())
, m_hot_keys_supplier(new CHotKeysToCmdRouter())
{
 //na
}

void CParamMonTabDlg::DoDataExchange(CDataExchange* pDX)
{
 CDialog::DoDataExchange(pDX);
 DDX_Control(pDX,IDC_PM_SHOW_RAW_SENSORS,m_raw_sensors_check);
}

LPCTSTR CParamMonTabDlg::GetDialogID(void) const
{
 return (LPCTSTR)IDD; 
}

/////////////////////////////////////////////////////////////////////////////
// CParamMonTabDlg message handlers

BOOL CParamMonTabDlg::OnInitDialog() 
{
 CDialog::OnInitDialog();
	
 mp_MIDeskDlg->Create(CMIDeskDlg::IDD, this);
 mp_MIDeskDlg->MoveWindow(280,0,427,312);
 mp_MIDeskDlg->ShowWindow(SW_SHOWNORMAL);
 mp_MIDeskDlg->Show(true);

 mp_RSDeskDlg->Create(CRSDeskDlg::IDD,this);
 mp_RSDeskDlg->MoveWindow(280,0,427,312);
 mp_RSDeskDlg->ShowWindow(SW_HIDE);
 mp_RSDeskDlg->Show(true);

 mp_ParamDeskDlg->Create(CParamDeskDlg::IDD,this);
 mp_ParamDeskDlg->SetTitle(MLL::LoadString(IDS_PM_EEPROM_PARAMETERS));
 mp_ParamDeskDlg->ShowWindow(SW_SHOWNORMAL);
 mp_ParamDeskDlg->Show(true);

 m_hot_keys_supplier->Init(this);
 _RegisterHotKeys();
	
 return TRUE;  // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CParamMonTabDlg::OnPmShowRawSensors() 
{//���������� ��������� ������� ��������	
 if (m_OnRawSensorsCheck)
  m_OnRawSensorsCheck();  
}

bool CParamMonTabDlg::GetRawSensorsCheckState(void)
{
 int check = m_raw_sensors_check.GetCheck();
 return (check==BST_CHECKED) ? true : false;
}

void CParamMonTabDlg::OnClose() 
{
 //CDialog::OnClose();
}

void CParamMonTabDlg::setOnRawSensorsCheck(EventHandler i_Function)
{
 m_OnRawSensorsCheck = i_Function;
}

void CParamMonTabDlg::OnDestroy() 
{
 CDialog::OnDestroy();  	
 m_hot_keys_supplier->Close();
}

void CParamMonTabDlg::OnMaximizeWindow()
{
 //int x_resolution = ::GetSystemMetrics(SM_CXFULLSCREEN);
 //int y_resolution = ::GetSystemMetrics(SM_CYFULLSCREEN);
}

void CParamMonTabDlg::OnMinimizeWindow()
{
}

void CParamMonTabDlg::_RegisterHotKeys(void)
{ //Ctrl + F = maximaze, Ctrl + M = minimaze
 m_hot_keys_supplier->RegisterCommand(IDM_PM_MAXIMIZE_WINDOW, 'F', MOD_CONTROL); 
 m_hot_keys_supplier->RegisterCommand(IDM_PM_MINIMIZE_WINDOW, 'M', MOD_CONTROL);
}
