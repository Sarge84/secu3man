/* SECU-3  - An open source, free engine control unit
   Copyright (C) 2007 Alexey A. Shabelnikov. Ukraine, Gorlovka

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   contacts:
              http://secu-3.org
              email: shabelnikov@secu-3.org
*/

#pragma once

#include <memory>

class CFirmwareDataMediator;
class CRPMGridEditDlg;

class CFWRPMGridEditController
{
 typedef CRPMGridEditDlg VIEW;
 typedef CFirmwareDataMediator FWDM;

 public:
  CFWRPMGridEditController();
 ~CFWRPMGridEditController();

  void AttachFWDM(CFirmwareDataMediator* ip_fwdm);

  int Edit(void);

 private:
  void OnItemChange(size_t itemIndex, float value);
  void OnLoadDefVal(void);
  CFirmwareDataMediator* mp_fwdm;
  std::auto_ptr<CRPMGridEditDlg> mp_view;
};
