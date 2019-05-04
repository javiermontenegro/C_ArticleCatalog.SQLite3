#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 


int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("article.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }//End if

   /* Create SQL statement */
   sql = "CREATE TABLE users("  \
      "id INT PRIMARY KEY NOT NULL," \
      "username       CHAR(50) NOT NULL," \
      "password       CHAR(50) NOT NULL);" \
      "CREATE TABLE articles(" \
      "id INTEGER PRIMARY KEY AUTOINCREMENT," \
      "article_name      CHAR(50) NOT NULL," \
      "model             CHAR(50)," \
      "color             CHAR(50)," \
      "weight            CHAR(50)," \
      "dimensions        CHAR(50)," \
      "asin              CHAR(50)," \
      "stock             CHAR(50)," \
      "provider          CHAR(50)," \
      "description       CHAR(250));" \
      "INSERT INTO users (id,username,password) " \
      "VALUES (1, 'admin', '12345');";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, 0, NULL, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Setup database successfully\n");
   }//End if

   sqlite3_close(db);
   return 0;
}//End main