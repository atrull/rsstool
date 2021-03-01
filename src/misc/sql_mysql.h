/*
  simple wrapper for ODBC or libmysql
  
  Copyright (c) 2006 Dirk
                            
                            
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef MISC_SQL_MYSQL_H
#define MISC_SQL_MYSQL_H
#ifdef  HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef  USE_MYSQL
#include <mysql/mysql.h>


/*
  sql_mysql_open()  open connection to db

  sql_mysql_close() close connection

  sql_mysql_query()  send query to db

  sql_mysql_gets()  read query result (ascii, lines)
*/
extern st_sql_t * sql_mysql_open (st_sql_t *sql,
                                  const char *host, int port,
                                  const char *user, const char *password,
                                  const char *db_name);

extern const char ***sql_mysql_read (st_sql_t *sql);
extern const char **sql_mysql_getrow (st_sql_t *sql, int row);
extern int sql_mysql_write (st_sql_t *sql, const char *sql_statement);

extern int sql_mysql_close (st_sql_t *sql);


#endif  // USE_MYSQL
#endif  // MISC_SQL_MYSQL_H
