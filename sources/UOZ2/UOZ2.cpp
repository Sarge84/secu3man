/****************************************************************
 *               SECU-3  - engine control unit
 *    Designed by Aleksey Shabelnikov. Ukraine, Gorlovka 2007.
 *    STc - Microprocessors systems: design & programming
 *    contacts:
 *              shabelnikov-stc@mail.ru
 *              ICQ: 405-791-931
 ****************************************************************/

#include <vcl.h>
#include <windows.h>
#include "Unit1.h"
#include <mem.h>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <map>

#pragma hdrstop
extern "C"
{
  HWND  __declspec(dllexport)  __cdecl Chart3DCreate(float *original_function, float *modified_function,const int *x_axis_grid_values, int x_count_of_points, int z_count_of_points,float aai_min,float aai_max, LPCTSTR x_axis_title, LPCTSTR chart_title);
  void  __declspec(dllexport)  __cdecl Chart3DUpdate(HWND hWnd, float *original_function, float *modified_function);
  void  __declspec(dllexport)  __cdecl Chart3DSetOnChange(HWND hWnd, EventHandler i_pOnChange, void* i_param);
  void  __declspec(dllexport)  __cdecl Chart3DSetOnClose(HWND hWnd, EventHandler i_pOnClose, void* i_param);
}

std::map<HWND,TForm*> g_form_instances;

//---------------------------------------------------------------------------
bool RemoveInstanceByHWND(HWND hWnd)
{
 if (g_form_instances.find(hWnd)!= g_form_instances.end())
 {
  g_form_instances.erase(hWnd);
  return true;
 }
 return false;
}

//---------------------------------------------------------------------------
bool AddInstanceByHWND(HWND hWnd, TForm* i_pForm)
{
 if (g_form_instances.find(hWnd)!= g_form_instances.end())
 {
  return false; //why do you want to add redundant references?
 }
 g_form_instances[hWnd] = i_pForm;
 return true;
}

//---------------------------------------------------------------------------
TForm* GetInstanceByHWND(HWND hWnd)
{
 if (g_form_instances.find(hWnd)!= g_form_instances.end())
 {
  return g_form_instances[hWnd];
 }
 return NULL;
}

//---------------------------------------------------------------------------
#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
  return 1;
}

//---------------------------------------------------------------------------
// y = F(x,z)

//original_function � modified_function - ������ ���������� �������� ����������
//�������� �������
HWND __cdecl Chart3DCreate(float *original_function, float *modified_function,const int *x_axis_grid_values, int x_count_of_points, int z_count_of_points,float aai_min,float aai_max, LPCTSTR x_axis_title, LPCTSTR chart_title)
{
  TForm1 *pForm1 = new TForm1((TComponent *)NULL);
  pForm1->count_x    = x_count_of_points;
  pForm1->count_z    = z_count_of_points;
  pForm1->u_title    = chart_title;
  pForm1->modified_function = modified_function;
  pForm1->original_function = original_function;
  pForm1->x_title    = x_axis_title;
  pForm1->aai_min    = aai_min;
  pForm1->aai_max    = aai_max;
  memcpy(pForm1->u_slots,x_axis_grid_values,sizeof(int)*x_count_of_points);
  pForm1->Show();
  pForm1->DataPrepare();
  AddInstanceByHWND(pForm1->Handle,pForm1);
  return pForm1->Handle;
}

//---------------------------------------------------------------------------
void __cdecl Chart3DUpdate(HWND hWnd, float *original_function, float *modified_function)
{
 TForm1* pForm1 = static_cast<TForm1*>(GetInstanceByHWND(hWnd));
 if (NULL==pForm1)
   return;

 //������� ������ ��������, � ����� ����� ��������� �����
 for(int i = 0; i < pForm1->Chart1->SeriesList->Count; i++)
   for (;pForm1->Chart1->Series[i]->Count() > 0;)
     pForm1->Chart1->Series[i]->Delete(pForm1->Chart1->Series[i]->Count()-1);

  pForm1->original_function   = original_function;
  pForm1->modified_function   = modified_function;
  pForm1->DataPrepare();
}
//---------------------------------------------------------------------------
void __cdecl Chart3DSetOnChange(HWND hWnd, EventHandler i_pOnChange, void* i_param)
{
 TForm1* pForm1 = static_cast<TForm1*>(GetInstanceByHWND(hWnd));
 if (NULL==pForm1)
   return;
 pForm1->SetOnChange(i_pOnChange, i_param);
}

//---------------------------------------------------------------------------
void __cdecl Chart3DSetOnClose(HWND hWnd, EventHandler i_pOnClose, void* i_param)
{
 TForm1* pForm1 = static_cast<TForm1*>(GetInstanceByHWND(hWnd));
 if (NULL==pForm1)
   return;
 pForm1->SetOnClose(i_pOnClose,i_param);
}

//---------------------------------------------------------------------------

