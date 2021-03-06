/* SECU-3  - An open source, free engine control unit
   Copyright (C) 2007 Alexey A. Shabelnikov. Ukraine, Kiev

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

/** \file NumericConv.h
 * \author Alexey A. Shabelnikov
 */

#include <vector>
#include "iocore_api.h"
#include "types.h"

#ifndef _NUMERICCONV_
#define _NUMERICCONV_

class IOCORE_API CNumericConv
{
 public:
  inline static BYTE HTOD(BYTE h)
  {
   return ((h<0x3A)?h-'0':h-'A'+10);
  }

  inline static BYTE DTOH(BYTE d)
  {
   char hdig[] = "0123456789ABCDEF";
   return hdig[(d & 0x0F)];
  }

  static bool   HexArrayToBin(const BYTE* i_buf, BYTE* o_buf, const int size);
  static bool   Hex4ToBin(const BYTE i_hex_number,BYTE* o_byte);
  static bool   Hex8ToBin(const BYTE* i_hex_number,BYTE* o_byte);
  static bool   Hex8ToBin(const BYTE* i_hex_number,int* o_byte); //signed
  static bool   Hex16ToBin(const BYTE* i_hex_number,int* o_word,bool i_signed  = false);
  static bool   Hex32ToBin(const BYTE* i_hex_number,signed long *o_dword);
  static bool   Hex32ToBin(const BYTE* i_hex_number,unsigned long *o_dword);
  static bool   Hex24ToBin(const BYTE* i_hex_number,unsigned long *o_dword);

  static bool   BinToHexArray(const BYTE* i_buf, BYTE* o_buf, const int size);
  static bool   Bin4ToHex(const BYTE i_byte, std::vector<BYTE>& o_hex_number);
  static bool   Bin8ToHex(const BYTE i_byte, BYTE* o_hex_number);
  static bool   Bin8ToHex(const BYTE i_byte, std::vector<BYTE>& o_hex_number);
  static bool   Bin12ToHex(const int i_12bit, BYTE* o_hex_number);
  static bool   Bin16ToHex(const int i_word, BYTE* o_hex_number);
  static bool   Bin16ToHex(const int i_word, std::vector<BYTE>& o_hex_number);
  static bool   Bin32ToHex(const unsigned long i_dword, std::vector<BYTE>& o_hex_number);
  static bool   Bin32ToHex(const signed long i_dword, std::vector<BYTE>& o_hex_number);

  static BYTE   CheckSum_8_xor(const BYTE* i_buf,const int size);

 private:
  static bool CNumericConv::_Hex32ToBin(const BYTE* i_buf,DWORD* o_dword);
};

#endif //_NUMERICCONV_
