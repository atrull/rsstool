/*
xxx.c - XXX hack for RSStool

Copyright (c) 2006 NoisyB


This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifdef  HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <time.h>
#include "misc/net.h"
#include "misc/xml.h"
#include "misc/string.h"
#include "misc/rss.h"
#include "misc/file.h"
#include "rsstool_defines.h"
#include "rsstool.h"
#include "rsstool_misc.h"
#include "xxx.h"


#define XXX1_URL_S "http://www.tommys-bookmarks.com"


typedef struct
{
  int flag;
  const char *url_s;
} st_xxx_url_t;


// TODO: zoo scat, elderly
static st_xxx_url_t urls[] =
{
  {2,   XXX1_URL_S "/amateurs.shtml"},
  {2,   XXX1_URL_S "/asians.shtml"},
  {2,   XXX1_URL_S "/babes.shtml"},
  {2,   XXX1_URL_S "/blacks.shtml"},
  {2,   XXX1_URL_S "/celebs.shtml"},
  {2,   XXX1_URL_S "/centerfolds.shtml"},
  {2,   XXX1_URL_S "/cumshots.shtml"},
  {2,   XXX1_URL_S "/fetish.shtml"},
  {2,   XXX1_URL_S "/premium.shtml"},
  {2,   XXX1_URL_S "/hardcore.shtml"},
//  {1|2, XXX1_URL_S "/interracial.shtml"},
  {2,   XXX1_URL_S "/latinas.shtml"},
  {2,   XXX1_URL_S "/lesbians.shtml"},
  {2,   XXX1_URL_S "/milf.shtml"},
  {2,   XXX1_URL_S "/pornstars.shtml"},
  {1,   XXX1_URL_S "/pmpegs.shtml"},
  {2,   XXX1_URL_S "/toons.shtml"},
  {2,   XXX1_URL_S "/teens.shtml"},
  {2,   XXX1_URL_S "/tits.shtml"},
  {2,   XXX1_URL_S "/transsexuals.shtml"},
  {2,   XXX1_URL_S "/uniform.shtml"},
  {2,   XXX1_URL_S "/voyeur.shtml"},
//  {1,   XXX1_URL_S "/movie.shtml"},
  {2,   XXX1_URL_S "/4women.shtml"},
#if 0
  {3,   "ppgirls.com"},
  {3,   "scatbitch.com"},
  {3,   "shitnasty.com"},
  {3,   "theshithole.com"},
  {3,   "www.potty.org"},
  {3,   "www.scat-post.com"},
  {3,   "www.scatbabes.com"},
  {3,   "www.scatflics.com"},
  {3,   "www.shitfreaks.com"},
  {3,   "www.shitxxx.com"},
#endif
  {0, NULL}
};
static int link = 0;
static char buffer[MAXBUFSIZE];


#if 0
static const char *
a_filter2 (const char *str)
{
  char buf[MAXBUFSIZE];
  char buf2[MAXBUFSIZE];
  char *p = NULL;
  const char *suffix = NULL;

  p = xml_tag_get_value (str, "href");

  strncpy (buf, p ? p : "", MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;

  suffix = get_suffix (buf);
  
  if (!stricmp (suffix, ".mpg") ||
      !stricmp (suffix, ".avi"))
    { 
      *buf2 = 0;
      if (strnicmp (buf, "http://", 7))
        {
          sprintf (buf2, "%s/%s", url.host, url.request);
          p = strrchr (buf2, '/');
          if (!p)
            p = strchr (buf2, 0);

          strcpy (p, "/");
        }
      strcat (buf2, buf);
      strrep (buf2 + 7, "//", "/");

#ifdef  DEBUG
      printf ("%s\n", buf2);
#endif

      rsstool_add_item_s (&rsstool,
                          "Porn",
                          "--xxx",
                          time (0),
                          buf2,
                          "test",
                          "test");
    }
    
  return "";
}


st_tag_filter_t xxx_item_filter2[] = {
  {
    "a",
    a_filter2
  },
  {NULL, NULL}
};
#endif


static int
get_xxx (const char *s)
{
#if 0
<P>
<A HREF="http://www.first-video.com/protect/series12/070/stacy-silver-internal-cumbustion-6-22.html">
Stacy Silver
</A> 
A juicy anal creampie after ass drilled, 4 vids
<IMG SRC="new.gif" WIDTH=42 HEIGHT=31>
</P>

<P>
<A HREF="http://www.socalcoedspage.com/fhg/sco/002/gall.php?4165">
Julia Bond Sex
</A>
4 movies of Julia in bed sucking cock and hit from behind on all fours
</P>
#endif


//  st_net_t *n = NULL;
  char buf[MAXBUFSIZE];
  char buf2[MAXBUFSIZE];
//  char *p = NULL;
  const char *u = NULL;
//  int cf = 0;

  u = xml_tag_get_value (s, "href");
  if (!u)
    return -1;

  strncpy (buf, buffer, MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;
  strtrim_s (buf, ">", NULL);
  strtrim_s (buf, ">", NULL);
  strtrim_s (buf, NULL, "<");
  strtrim_s (buf, NULL, "<");
  strtrim_s (buf, NULL, "<");
  strtrimr (strtriml (buf));

  strncpy (buf2, buffer, MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;
  strtrim_s (buf2, ">", NULL);
  strtrim_s (buf2, ">", NULL);
  strtrim_s (buf2, ">", NULL);
  strtrim_s (buf2, NULL, "<");
  strtrim_s (buf2, NULL, "<");
  strtrimr (strtriml (buf2));
  sprintf (strchr (buf, 0), " %s", buf2);

  rsstool_add_item_s (&rsstool,
                      "Porn",
                      "--xxx",
                      time (0),
                      u,
                      buf,
                      "");

#if 0
  if (!(n = net_init (0)))
    {
      fprintf (stderr, "ERROR: get_xxx()/net_init() failed\n");
      return -1;
    }

  strncpy (buf, u, MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;

  strurl (&url, buf);

  if (net_open (n, url.host, 80) != 0)
    {
      fprintf (stderr, "ERROR: could not log on to %s\n", url.host);
      return -1;
    }

  p = net_build_http_request (s, rsstool.user_agent, 0, NET_METHOD_GET, 0);
  net_write (n, (char *) p, strlen (p));

  while (net_gets (n, buf, MAXBUFSIZE))
    {
      p = strchr (buf, '\n');
      if (p)
        *p = 0;

      cf = xml_tag_filter (buf, xxx_item_filter2, cf);
    }

  net_quit (n);
#endif

  return 0;
}


static const char *
a_filter (const char *s)
{
  char buf[MAXBUFSIZE];

  if (link > 560)
    return "";

  strncpy (buf, s, MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;
//  urltrim (buf);

  if (link > 60)
    get_xxx (buf);

  link++;

  return "";
}


st_tag_filter_t xxx_item_filter[] = {
  {
    "a",
    a_filter
  },
  {NULL, NULL}
};


int
xxx_get_rss (st_rsstool_t *rt, int flag)
{
  (void) rt;
  int i = 0;
  st_net_t *n = NULL;
  char buf[MAXBUFSIZE];
  char *p = NULL;
  int cf = 0;

  if (!(n = net_init (0)))
    {
      fprintf (stderr, "ERROR: xxx_get_rss()/net_init() failed\n");
      return -1;
    }

  if (net_open (n, XXX1_URL_S, 80) != 0)
    {
      fprintf (stderr, "ERROR: could not log on to %s\n", XXX1_URL_S);
      return -1;
    }

  if (!flag)
    flag = 1; // default

  for (i = 0; urls[i].url_s; i++)
    if (urls[i].flag & flag)
      {
        link = 0;
        p = net_build_http_request (urls[i].url_s, rsstool.user_agent, 0, NET_METHOD_GET, 0);
        net_write (n, (char *) p, strlen (p));

        while (net_gets (n, buf, MAXBUFSIZE))
          {
            p = strchr (buf, '\n');
            if (p)
              *p = 0;

            strncpy (buffer, buf, MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;
            cf = xml_tag_filter (buf, xxx_item_filter, cf);
         }
      }

  net_close (n);

  net_quit (n);

  return 0;
}
