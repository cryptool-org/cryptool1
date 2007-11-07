/*-
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)pwd.h	5.13 (Berkeley) 5/28/91
 */

#ifndef _PWD_H_
#ifdef __cplusplus
extern "C" {
#endif
#define	_PWD_H_

#include <sys/types.h>

#ifdef _WIN32
	typedef int uid_t;
#endif

#ifndef _POSIX_SOURCE
#define	_PATH_PASSWD		"/etc/passwd"

#define	_PASSWORD_LEN		128	/* max length, not counting NULL */
#endif

struct passwd {
	char	*pw_name;		/* user name */
	char	*pw_passwd;		/* encrypted password */
	int	pw_uid;			/* user uid */
	int	pw_gid;			/* user gid */
	char	*pw_comment;		/* comment */
	char	*pw_gecos;		/* Honeywell login info */
	char	*pw_dir;		/* home directory */
	char	*pw_shell;		/* default shell */
};

struct passwd	*getpwuid (uid_t);

static struct passwd pw_passwd; /* password structure */
static FILE *passwd_fp;

static char logname[8];
static char password[1024];
static char gecos[1024];
static char dir[1024];
static char shell[1024];

struct passwd *
getpwuid (uid_t uid)
{
  FILE *fp;
  char buf[1024];

  if ((fp = fopen ("/etc/passwd", "r")) == NULL)
    {
      return NULL;
    }

  while (fgets (buf, sizeof (buf), fp))
    {
      sscanf (buf, "%[^:]:%[^:]:%d:%d:%[^:]:%[^:]:%s\n",
          logname, password, &pw_passwd.pw_uid,
             &pw_passwd.pw_gid, gecos,
          dir, shell);
      pw_passwd.pw_name = logname;
      pw_passwd.pw_passwd = password;
      pw_passwd.pw_comment = "";
      pw_passwd.pw_gecos = gecos;
      pw_passwd.pw_dir = dir;
      pw_passwd.pw_shell = shell;

      if (uid == pw_passwd.pw_uid)
    {
      fclose (fp);
      return &pw_passwd;
    }
    }
  fclose (fp);
  return NULL;
}

int
getuid ()
{
  /* One value is as good as another... */
  return 0;
}

struct passwd	*getpwnam (const char *);
int 		 getpwnam_r (const char *, struct passwd *,
			char *, size_t , struct passwd **);
int		 getpwuid_r (uid_t, struct passwd *, char *,
			size_t, struct passwd **);
#ifndef _POSIX_SOURCE
struct passwd	*getpwent (void);
void		 setpwent (void);
void		 endpwent (void);
#endif

#ifdef __cplusplus
}
#endif
#endif /* _PWD_H_ */
