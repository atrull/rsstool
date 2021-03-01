/*
youtube.c - YouTube hack for RSStool

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
#include "misc/string.h"
#include "misc/rss.h"
#include "misc/misc.h"
#include "rsstool_defines.h"
#include "rsstool.h"
#include "rsstool_misc.h"
#include "youtube.h"


//http://www.youtube.com/rss/global/recently_added.rss
//http://www.youtube.com/rss/tag/%s.rss
//&search_sort=video_date_uploaded
//http://youtube.com/watch?v=fCrFG9nMekk
#define YOUTUBE_URL_S "http://www.youtube.com"
#define YOUTUBE_DEFAULT_RSS_S "/rss/global/recently_added.rss"
#define YOUTUBE_SEARCH_RSS_S "/rss/tag/%s.rss"
#define YOUTUBE_HOOK "/player2.swf?"


static const char *
youtube_get_direct_url (const char *url_s)
{
  st_net_t *n = NULL;
  static char buf[MAXBUFSIZE];
  char *p = NULL;

  if (!(n = net_init (0)))
    {
      fprintf (stderr, "ERROR: youtube_get_direct_url()/net_init() failed\n");
      return url_s;
    }

  if (net_open (n, YOUTUBE_URL_S, 80) != 0)
    {
      fprintf (stderr, "ERROR: could not log on to %s\n", YOUTUBE_URL_S);
      return url_s;
    }

  strcpy (buf, url_s);
  p = strchr (buf, '?');
  if (!p)
    return url_s;

  strins (p, "watch");

  p = net_build_http_request (buf, rsstool.user_agent, 0, NET_METHOD_GET, 0);
  net_write (n, (char *) p, strlen (p));

  while (net_gets (n, buf, MAXBUFSIZE))
    if (strstr (buf, YOUTUBE_HOOK))
      {
        p = strchr (buf, '\n');
        if (p)
          *p = 0;

#ifdef  DEBUG  
        printf ("%s\n", buf);
#endif  
        strtrim_s (buf, YOUTUBE_HOOK, NULL);

        p = strchr (buf, '"');
        if (p)
          *p = 0;

        strins (buf, YOUTUBE_URL_S "/get_video?");

#ifdef  DEBUG
        printf ("%s\n", buf);
#endif
        break;
      }

  net_close (n);

  net_quit (n);

  return buf;
}


int
youtube_get_rss (st_rsstool_t *rt, const char *search)
{
  (void) rt;
  st_rss_t *youtube = NULL;
  int count = 0;
  int i = 0;
  char buf[MAXBUFSIZE];
  const char *p = NULL, *temp = NULL;

  strcpy (buf, YOUTUBE_URL_S);
  if (search)
    sprintf (strchr (buf, 0), YOUTUBE_SEARCH_RSS_S, search);
  else
    strcpy (strchr (buf, 0), YOUTUBE_DEFAULT_RSS_S);
  temp = net_http_get_to_temp (buf, rsstool.user_agent, rsstool.get_flags);
  if (!temp)
    {
      fprintf (stderr, "ERROR: failed to download %s\n", buf);
      return -1;
    }

//  if (rss_demux (temp) != 0)
//    return -1;

  youtube = rss_open (temp);

  // delete temp file
  remove (temp);

  if (!youtube)
    return -1;

  count = rss_item_count (youtube);
  if (!count)
    return -1;

  // replace youtube redirect       
  for (i = 0; i < count; i++)
    {
      p = youtube_get_direct_url (youtube->item[i].url);

#ifdef  DEBUG
      printf ("%s\n", p);
#endif

      if (!p)
        p = youtube->item[i].url;
      rsstool_add_item_s (&rsstool,
                          "YouTube",
                          YOUTUBE_URL_S,
                          time (0),
                          p,
                          youtube->item[i].title,
                          youtube->item[i].desc);
    }

  return 0;
}
