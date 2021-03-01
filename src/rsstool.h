/*
rsstool.h - RSStool reading, parsing and writing RSS (and ATOM) feeds

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
#ifndef RSSTOOL_H
#define RSSTOOL_H


typedef struct
{
  int version;  // rss? atom?

  time_t date;
  char url[RSSTOOL_MAXBUFSIZE];
  char title[RSSTOOL_MAXBUFSIZE];
  char desc[RSSTOOL_MAXBUFSIZE];

  char site[RSSTOOL_MAXBUFSIZE];
  char feed_url[RSSTOOL_MAXBUFSIZE];

//  int private;   // used by sort
} st_rsstool_item_t;


#if 0
typedef struct
{
  unsigned char md5[16];
} st_rsstool_itemhash_t;


typedef struct
{
  char fname[FILENAME_MAX];
  st_rsstool_itemhash_t *hash_old; // old items read from file
  st_rsstool_itemhash_t *hash_new; // new items to be written to file
  int old_count;
  int new_count;
} st_rsstool_olditems_t;
#endif


typedef struct
{
  int quiet;
  time_t start_time;
  char user_agent[MAXBUFSIZE];
  const char *optarg;

  int output;       // what kind of output
  FILE *output_file; // output pointer (default: stdout)
  char pipe_command[MAXBUFSIZE]; // name of command to pipe the output to,
                                 // empty string if --pipe not used
  int reverse;      // sort reverse before output
  int rss_version;  // version of RSS
  int ansisql_version; // which version of ANSI SQL output to use
  time_t since;     // no feed items older than since
  int fixdate;
  int csv_separator;

  int strip_html;
  int strip_desc;
  int strip_lf;
  int strip_whitespace;

//  char property[FILENAME_MAX];
  char template[FILENAME_MAX];
  char temp_file[FILENAME_MAX];
  FILE *input_file;
  FILE *log;
  int get_flags;

#if 0
  char new_only_dir[FILENAME_MAX]; // directory used to store lists of hashes
  st_rsstool_olditems_t old_urls;  // of old items, empty if not used
  st_rsstool_olditems_t old_titles;
#endif

  st_rsstool_item_t *item[RSSTOOL_MAXITEM];
  int item_count;
} st_rsstool_t;


extern st_rsstool_t rsstool;


#endif  // RSSTOOL_H
