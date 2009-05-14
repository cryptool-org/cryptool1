/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

// Curvefit.h: interface for the CBezierfit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEFIT_H__8CC78BC2_CA92_11D3_949E_00104B6C2FFE__INCLUDED_)
#define AFX_CURVEFIT_H__8CC78BC2_CA92_11D3_949E_00104B6C2FFE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

void CalcBezier(const double *Rawdata, int n, double *Control);


#endif // !defined(AFX_CURVEFIT_H__8CC78BC2_CA92_11D3_949E_00104B6C2FFE__INCLUDED_)
