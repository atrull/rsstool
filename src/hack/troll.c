/*
troll.c - Slashdot trolls hack for RSStool

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
#include "misc/misc.h"
#include "misc/file.h"
#include "misc/xml.h"
#include "rsstool_defines.h"
#include "rsstool.h"
#include "rsstool_misc.h"
#include "troll.h"


#define TROLL_URL_S "http://slashdot.org"
#define TROLL_RSS_HOST_S "http://rss.slashdot.org"
#define TROLL_RSS_S "http://rss.slashdot.org/Slashdot/slashdot"

#define TROLL_REQ_OLDEST_FIRST_S "/comments.pl?threshold=-1&mode=flat&commentsort=0&startat=%d&sid=%s"
#define TROLL_REQ_NEWEST_FIRST_S "/comments.pl?threshold=-1&mode=flat&commentsort=1&startat=%d&sid=%s"

#define TROLL_ARTICLE_LINK_HOOK  "slashdot.org/article.pl?sid=%s"


// slashdot article layout
#if 0
<li id="tree_16991414" class="comment">
	<div id="comment_status_16991414" class="commentstatus">
	</div>
	<div id="comment_16991414">
		<div class="commentTop">
			<div class="title">
				<h4>
					<a name="16991414">Not a Frosty Piss</a>
				</h4>
				<span id="comment_score_16991414" class="score">
					(Score:-1, Offtopic)
				</span>
			</div>
			<div class="details">
				by Anonymous Coward 
				<span class="otherdetails">
					on Sunday November 26, @09:31AM (<a href="//slashdot.org/comments.pl?sid=208394&amp;cid=16991414">#16991414</a>)<small> </small>
				</span>
			</div>
		</div>
		<div class="commentBody">	
			<div id="comment_body_16991414">
				<br>I was too busy enjoying the snow to pour up a tall steaming mug of Frosty Piss. Sorry I didn't make it this time... I'll try better for the next story.<br>&nbsp;
			</div>
		</div>
		<div class="commentSub">
			[ <a href="//slashdot.org/comments.pl?sid=208394&amp;op=Reply&amp;threshold=-1&amp;commentsort=0&amp;mode=flat&amp;pid=16991414">Reply to This</a> ]
		</div>
	</div>
</li><li id="tree_18768961" class="comment">
        <div id="comment_status_18768961" class="commentstatus">
        </div>
        <div id="comment_18768961">
                <div class="commentTop">
                        <div class="title">
                                <h4>
                                        <a name="18768961">Twofo</a>
                                </h4>
                                <span id="comment_score_18768961" class="score">
                                        (Score:-1, Offtopic)
                                </span>
                        </div>
                        <div class="details">
                                by Anonymous Coward 
                                <span class="otherdetails" id="comment_otherdetails_18768961">                
                                        on Tuesday April 17, @12:48PM (<a href="//politics.slashdot.org/comments.pl?sid=231151&amp;cid=18768961">#18768961</a>)<small></small>
                                </span>
                        </div>
                </div>
                <div class="commentBody">        
                        <div id="comment_body_18768961">
                                <a href="http://www.twofo.co.uk/" title="twofo.co.uk" rel="nofollow">http://goatse.ch</a> [twofo.co.uk][goatse.ch]
                        </div>
                </div>
                <div class="commentSub" id="comment_sub_18768961">
                        [ <a href="//politics.slashdot.org/comments.pl?sid=231151&amp;op=Reply&amp;threshold=-1&amp;commentsort=0&amp;mode=thread&amp;pid=18768961">Reply to This</a> ]
                </div>
        </div>
</li>
#endif


static int troll_id = 0;
static char troll_article_url[MAXBUFSIZE];
//static char troll_article_title[MAXBUFSIZE];


static int
troll_parse_comment (const char *path)
{
  st_rss_t troll;
  char buf[MAXBUFSIZE];
  FILE *fh = NULL;
  char title[MAXBUFSIZE];
  char url[MAXBUFSIZE];
  char desc[MAXBUFSIZE];
  int end = 0;
  char *p = NULL;

  memset (&troll, 0, sizeof (st_rss_t));

  if (!(fh = fopen (path, "rb")))
    return -1;

  while (fgets (buf, MAXBUFSIZE, fh))
    if (stristr (buf, " class=\"commentTop\">"))
      {
        strcpy (title, buf);
        while (fgets (buf, MAXBUFSIZE, fh))
          {
            strcat (title, buf);
            title[4096] = 0;
     
            if (stristr (buf, " class=\"commentBody\">"))
              {
                strcpy (desc, buf);
                while (fgets (buf, MAXBUFSIZE, fh))
                  {
                    if (stristr (buf, " class=\"commentSub\" "))
                      { 
                        end = 1;
                        break;
                      }

                    strcat (desc, buf);
                    desc[4096] = 0;
                  }
              }

            if (end)
              break;
          }

        if (end)
          break;
      }
  fclose (fh);

  p = stristr (title, "<span class=\"otherdetails\"");
  if (p)
    {
      strcpy (buf, p);
      *p = 0;
    }

  // title
  strtriml (strtrimr (rsstool_strip_html (title)));
  strrep (title, "\n", "");
  strrep (title, "\t", " ");
  strrep (title, "    ", " ");
  strrep (title, "   ", " ");
  strrep (title, "  ", " ");

  // url
  strrep (buf, "\n", "");
  p = stristr (buf, "(<a href=\"//slashdot.org/comments.pl?sid=");
  if (p)
    {
      sprintf (url, "http:%s", p + strlen ("(<a href=\""));
      strrep (url, "&amp;", "&");
      p = stristr (url, "\">#");
      if (p)
        *p = 0;
    }

  // desc
  strtriml (strtrimr (rsstool_strip_html (desc)));
//  strrep (desc, "  ", " ");                                           
  sprintf (strchr (desc, 0), "<a href=\"%s\">Article</a>", troll_article_url);

#if 1
  sprintf (buf, "--troll=%d", troll_id);
  rsstool_add_item_s (&rsstool,
                      "Slashdot/Trolls",
                      buf,
                      time (0),
                      url,
                      title,
                      desc);
#else
  printf ("%s\n", title);
  printf ("%s\n", url);
  printf ("%s\n", desc);
  fflush (stdout);
#endif

  return 0; 
}


static const char *
troll_get_comment (const char *s)
{
  char buf[MAXBUFSIZE];
  char sid[MAXBUFSIZE];
  int startat = 0;
  char *p = NULL;
  const char *temp = NULL;
  char otemp[FILENAME_MAX];
  FILE *in = NULL;
  FILE *out = NULL;
  int comments = 0;
  int troll = 0;

  p = (char *) xml_tag_get_value (s, "rdf:about");

  if (!p)
    return "";

  strncpy (troll_article_url, p, MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;

  strncpy (sid, p, MAXBUFSIZE)[MAXBUFSIZE - 1] = 0;
  strtrim_s (sid, "sid=", "&amp;");

#ifdef  DEBUG
  printf ("%s\n", sid);
  fflush (stdout);
#endif

  while (comments > startat || !comments)
    {
      startat = comments;        // startat 0 or last comment
      sprintf (buf, TROLL_URL_S TROLL_REQ_OLDEST_FIRST_S, startat, sid);

#ifdef  DEBUG  
  printf ("%s ", buf);
  fflush (stdout);
#endif  

      temp = net_http_get_to_temp (buf, rsstool.user_agent, rsstool.get_flags);
      if (!temp)
        {
          char log[MAXBUFSIZE];

          sprintf (log, "ERROR: failed to download %s\n", buf);
          rsstool_log (&rsstool, log);
          return "";
        }

#ifdef  DEBUG   
  printf ("OK\n");
  fflush (stdout); 
#endif  

      if ((in = fopen (temp, "rb")))
        {
          while (fgets (buf, MAXBUFSIZE, in))
            if (stristr (buf, "class=\"commentstatus\">")) // start of comment
              {
                comments++;
    
                *otemp = 0;
                tmpnam3 (otemp, 0);
                if ((out = fopen (otemp, "wb")))
                  {
                    fputs ("<html>\n", out);
                    fputs (buf, out);
    
                    troll = 0;
                    while (fgets (buf, MAXBUFSIZE, in))
                      {
                        if (stristr (buf, "Flamebait)") ||
                            stristr (buf, "Troll)") ||
                            stristr (buf, "Offtopic)") ||
                            stristr (buf, "Overrated)") ||
                            stristr (buf, "(Score:-1"))
                          troll = 1;
    
                        if (stristr (buf, "</li>")) // end of comment
                          {
                            fputs ("</html>\n", out);
                            break;
                          }
    
                        fputs (buf, out);
                      }
    
                    fclose (out);
                    out = NULL;
    
                    if (troll)
                      troll_parse_comment (otemp);
        
                    remove (otemp);
                  }
              }
    
          fclose (in);
          remove (temp);
        }
    }

  return "";
}


st_tag_filter_t troll_tag_filter[] = {
  {
    "item",
    troll_get_comment
  },
  {NULL, NULL}
};


typedef struct
{
  const char *url;
  int id;
} st_troll_urls_t;


static st_troll_urls_t troll_urls[] = {
  {TROLL_RSS_S,                       1},  // Main
  {TROLL_RSS_S "Apple",            1<<1},
  {TROLL_RSS_S "AskSlashdot",      1<<2},
//  {TROLL_RSS_S "Backslash",        1<<3},
  {TROLL_RSS_S "BookReviews",      1<<4},
  {TROLL_RSS_S "Developers",       1<<5},
  {TROLL_RSS_S "Games",            1<<6},
  {TROLL_RSS_S "Hardware",         1<<7},
  {TROLL_RSS_S "Interviews",       1<<8},
  {TROLL_RSS_S "IT",               1<<9},
  {TROLL_RSS_S "Linux",            1<<10},
  {TROLL_RSS_S "Politics",         1<<11},
  {TROLL_RSS_S "Science",          1<<12},
  {TROLL_RSS_S "YourRightsOnline", 1<<13},
  {TROLL_RSS_S "BSD",              1<<14},
  {NULL, 0}
};


int
troll_get_rss (st_rsstool_t *rt, int flags)
{
  (void) rt;
  int i = 0;
  char buf[MAXBUFSIZE];
  const char *temp = NULL;
  int cf = 0;
  FILE *fh = NULL;

  if (!flags)
    flags = 0xffff; // default == all

  for (i = 0; troll_urls[i].id; i++)
    if ((troll_urls[i].id & flags) == troll_urls[i].id)
      {
        troll_id = troll_urls[i].id;
//#ifdef  DEBUG
        printf ("%s\n", troll_urls[i].url);
        fflush (stdout);
//#endif
        temp = net_http_get_to_temp (troll_urls[i].url, rsstool.user_agent, rsstool.get_flags);
        if (!temp)
          {
            fprintf (stderr, "ERROR: failed to download %s\n", troll_urls[i].url);
            continue;
          }

        if (!(fh = fopen (temp, "rb")))
          continue;

        cf = 0; // reset
        while (fgets (buf, MAXBUFSIZE, fh))
          cf = xml_tag_filter (buf, troll_tag_filter, cf);

        fclose (fh);

        // remove temp file
        remove (temp);
      }

  return 0;
}
