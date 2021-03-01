/*
google_news.c - Slashdot Google/News hack for RSStool

Copyright (c) 2007 NoisyB


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
#include "google_news.h"

//http://news.google.com/news/url?sa=T&ct=us/8-0&fd=R&url=...&cid=...
#define GOOGLE_NEWS_S "http://news.google.com/"
#define GOOGLE_NEWS_RSS_S GOOGLE_NEWS_S "news?ie=UTF-8&output=rss"
#define GOOGLE_NEWS_SEARCH_S "&q=%s"


int
google_news_get_rss (st_rsstool_t *rt, const char *search)
{
  st_rss_t *google = NULL;
  int count = 0;
  int i = 0;
  char buf[MAXBUFSIZE];
  const char *temp = NULL;

  strcpy (buf, GOOGLE_NEWS_RSS_S);
  if (search)
    sprintf (strchr (buf, 0), GOOGLE_NEWS_SEARCH_S, search);
  temp = net_http_get_to_temp (buf, rsstool.user_agent, rsstool.get_flags);
  if (!temp)
    {
      char log[MAXBUFSIZE];

      sprintf (log, "ERROR: failed to download %s\n", buf);
      rsstool_log (rt, log);
      return -1;
    }

//  if (rss_demux (p) != 0)
//    return -1;

  google = rss_open (temp);

  // delete temp file
  remove (temp);

  if (!google)
    return -1;

  count = rss_item_count (google);
  if (!count)
    return -1;

  // replace google redirect       
  for (i = 0; i < count; i++)
    {
      strcpy (buf, google->item[i].url);
      strtrim_s (buf, "&url=", "&cid=");

      rsstool_add_item_s (rt,
                          "Google/News",
                          GOOGLE_NEWS_S,
                          time (0),
                          buf,
                          google->item[i].title,
                          "");
    }

  return 0;
}
