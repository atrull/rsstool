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
#ifdef  HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef  USE_MYSQL
#include <mysql/mysql.h>
#include "sql.h"


extern int sql_malloc_array (st_sql_t *sql, int rows, int cols);
extern int sql_free_array (st_sql_t *sql);


st_sql_t *
sql_mysql_open (st_sql_t *sql,
                const char *host, int port,
                const char *user, const char *password,
                const char *db_name)
{
  mysql_init (&sql->db);
  mysql_options (&sql->db, MYSQL_READ_DEFAULT_GROUP, "random");

  if (!mysql_real_connect (&sql->db, host, user, password, db_name, port, NULL, 0))
    {
      fprintf (stderr, "ERROR: mysql_real_connect(): %s\n", mysql_error (&sql->db));
      return NULL;
    }

#if 1
  if (mysql_select_db (&sql->db, db_name))  // select the database we want to use
    {
      fprintf (stderr, "ERROR: mysql_select_db(): %s\n", mysql_error (&sql->db));
      return NULL;
    }
#endif

  return sql;
}


int
sql_mysql_close (st_sql_t *sql)
{
  if (sql->res)
    {
      mysql_free_result (sql->res);
      sql->res = NULL;
    }

  mysql_close (&sql->db);
  sql_free_array (sql);

  return 0;
}


const char ***
sql_mysql_read (st_sql_t *sql)
{
  int row = 0, col = 0;
  int rows = 0, cols = 0;

  if (!sql->res)
    return NULL;

  rows = mysql_num_rows (sql->res);
  cols = mysql_num_fields (sql->res);
  if (sql_malloc_array (sql, rows, cols))
    {
      mysql_free_result (sql->res);
      sql->res = NULL;
      return NULL;
    }

  // free and re-malloc the result array in st_sql_t
  sql_free_array (sql);
  if (sql_malloc_array (sql, rows, cols) != 0)
    {
      mysql_free_result (sql->res);
      sql->res = NULL;
      return NULL;
    }

  for (row = 0; row < rows; row++)
    if ((sql->row = mysql_fetch_row (sql->res)))
      for (col = 0; col < cols; col++)
        sql->array[row][col] = sql->row[col];

  return (const char ***) sql->array;
}


const char **
sql_mysql_getrow (st_sql_t *sql, int row)
{
  sql_mysql_read (sql);

  if (sql->array)
    if (mysql_num_rows (sql->res) > (unsigned int) row)
      return sql->array[row];

  return NULL;
}


int
sql_mysql_write (st_sql_t *sql, const char *sql_statement)
{
  if (mysql_real_query (&sql->db, sql_statement, strlen (sql_statement)))
    {
      fprintf (stderr, "ERROR: mysql_real_query(): %s\n", mysql_error (&sql->db));
      return -1;
    }

  sql->res = mysql_store_result (&sql->db);  // download result from server

  return 0;
}


#endif  // USE_MYSQL
