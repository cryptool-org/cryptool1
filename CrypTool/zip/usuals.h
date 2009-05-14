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

/* usuals.h - The usual typedefs, etc.
*/
#ifndef USUALS /* Assures no redefinitions of usual types...*/
#define USUALS

typedef unsigned char boolean;	/* values are TRUE or FALSE */
typedef unsigned char byte;	/* values are 0-255 */
typedef byte *byteptr;	/* pointer to byte */
typedef char *string;	/* pointer to ASCII character string */
typedef unsigned short word16;	/* values are 0-65535 */
#ifdef __alpha
typedef unsigned int word32;	/* values are 0-4294967295 */
#else
typedef unsigned long word32;	/* values are 0-4294967295 */
#endif

#ifndef TRUE
#define FALSE 0
#define TRUE (!FALSE)
#endif	/* if TRUE not already defined */

#ifndef min	/* if min macro not already defined */
#define min(a,b) (((a)<(b)) ? (a) : (b) )
#define max(a,b) (((a)>(b)) ? (a) : (b) )
#endif	/* if min macro not already defined */

/* void for use in pointers */
#ifndef NO_VOID_STAR
#define	VOID	void
#else
#define	VOID	char
#endif

	/* Zero-fill the byte buffer. */
#define fill0(buffer,count)	memset( buffer, 0, count )

	/* This macro is for burning sensitive data.  Many of the
	   file I/O routines use it for zapping buffers */
#define burn(x) fill0((VOID *)&(x),sizeof(x))

#define LANG(a) a

#endif	/* if USUALS not already defined */
