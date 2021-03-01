/*
google.c - Google hack for RSStool

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
#include "google.h"


#define GOOGLE_MAX_RESULTS 2000
#define GOOGLE_URL_S "http://www.google.com"
#define GOOGLE_SEARCH_S GOOGLE_URL_S "/search?q=%s&num=100"
//#define GOOGLE_SEARCH_LANG_S "&lr=lang_%s"
#define GOOGLE_SEARCH_START_S "&start=%d&sa=N"


static FILE *fh = NULL;


#if 0
<!--m-->
<h2 class="r">
  <a href="http://www.oekotest.de/" class="l">www.oekotest.de (ho)</a>
</h2>
<table border="0" cellpadding="0" cellspacing="0">
  <tbody>
    <tr>
      <td class="j">
        <font size="-1">
          Verlag f<C3><BC>r <C3><B6>kologische Zeitschriften in Deutschland (<C3><96>ko-<b>Test</b>-Magazin, <C3><96>ko-Haus). Informiert <C3><BC>ber Produkte, Preise, Bestellm<C3><B6>glichkeiten, Archiv.<br>
          <span class="a">www.oeko<b>test</b>.de/ - 17. Apr. 2007 - </span>
          <nobr>
            <a class="fl" href="http://www.google.de/search?hl=de&amp;q=related:www.oekotest.de/"><C3><84>hnliche Seiten
            </a>
          </nobr>
        </font>
<!--n-->
#endif


static const char *
a_filter (const char *s)
{
  char title[MAXBUFSIZE];
  char link[MAXBUFSIZE];
  char desc[MAXBUFSIZE];
  const char *p = NULL;

  // a new item
  *title = *link = *desc = 0;

  // google links contain class="l"
  p = xml_tag_get_value (s, "class");
  if (!p)
    return "";

  if (stricmp (p, "l"))
    return "";

  p = xml_tag_get_value (s, "href");
  if (!p)
    return "";

  if (stristr (p, "http"))
    strncpy (link, p, MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;

  if (*title && *link && *desc)
    rsstool_add_item_s (&rsstool,
                        "Google",
                        "--google",
                        time (0),
                        link,
                        link,
                        "");

  return "";
}


st_tag_filter_t google_item_filter[] = {
  {
    "a",
    a_filter
  },
  {NULL, NULL}
};


int
google_hack (st_rsstool_t *rt, const char *search)
{
  (void) rt;
  st_net_t *n = NULL;
  char buf[MAXBUFSIZE];
  char search_esc[MAXBUFSIZE];
  int cf = 0;
  int count = 0;
  const char *temp = NULL;
//  FILE *fh = NULL;

  if (!search)
    return -1;

  if (!(n = net_init (0)))
    {
      fprintf (stderr, "ERROR: google_hack()/net_init() failed\n");
      return -1;
    }

  stresc (search_esc, search);

  for (count = 0; count < GOOGLE_MAX_RESULTS; count += 100)
    {
      if (net_open (n, GOOGLE_URL_S, 80) != 0)
        {
          fprintf (stderr, "ERROR: could not log on to %s\n", GOOGLE_URL_S);
          return -1;
        }

      sprintf (buf, GOOGLE_SEARCH_S, search_esc);
      if (count)
        sprintf (strchr (buf, 0), GOOGLE_SEARCH_START_S, count);

      rsstool_log (&rsstool, buf);      

      temp = net_http_get_to_temp (buf, rsstool.user_agent, rsstool.get_flags);
      if (!temp)
        {
          fprintf (stderr, "ERROR: failed to download %s\n", buf);
          continue;
        }

      if (!(fh = fopen (temp, "rb")))
        continue;

      while (fgets (buf, MAXBUFSIZE, fh))
        cf = xml_tag_filter (buf, google_item_filter, cf);

      fclose (fh);

      // remove temp file
      remove (temp);
    }

  return 0;
}


