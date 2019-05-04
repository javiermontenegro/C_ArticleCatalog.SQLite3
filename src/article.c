#include <article.h>

/*! \file article.c
 *  \brief Definitions for memory allocated entries.
 *
 *  Definition functions for data entries.
 */


bool add_entry(sqlite3* db, article_t* article)
{

   rc = sqlite3_open("article.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return false;
   }//End if

    sprintf(sql, "INSERT INTO articles (article_name, model, color, " \
            "weight, dimensions, asin, stock, provider, description) " \   
            "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
            article->article_name, article->model, article->color,
            article->weight, article->dimensions, article->asin, article->stock,
            article->provider, article->description);

   rc = sqlite3_exec(db, sql, 0, NULL, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      return false;
   }//End if

   sqlite3_close(db);
    return true;
}/* end add entry */


int display_entries(sqlite3* db)
{
   unsigned int c;

   int callback(void *data, int argc, char **argv, char **azColName){
     c = 0;
     for(int i = 0; i<argc; i++){
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
       c++; 
     }   
     printf("\n");   
     return 0;
   }

   rc = sqlite3_open("article.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return 0;
   }//End if

   rc = sqlite3_exec(db, "SELECT * FROM articles", callback, NULL, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      return 0;
   }//End if

   sqlite3_close(db);
   return c;
} /* end display entries */


bool delete_entry(const unsigned int index)
{
   rc = sqlite3_open("article.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return false;
   }//End if
    
   sprintf(sql, "DELETE FROM articles WHERE id = %d", index);
   rc = sqlite3_exec(db, sql, 0, NULL, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      return false;
   }//End if

   sqlite3_close(db);
   return true;
}/* end delete entry */

bool edit_entry(const unsigned int index, const unsigned int field_option, article_t* article){

    switch( field_option )
      {
        case 1:
          {
            sprintf(sql, "UPDATE articles SET article_name = '%s' WHERE id=%d", 
              article->article_name, index);
          } break;
        case 2:
          {
            sprintf(sql, "UPDATE articles SET model = '%s' WHERE id=%d", 
              article->model, index);
          } break;
        case 3:
          {
            sprintf(sql, "UPDATE articles SET color = '%s' WHERE id=%d", 
              article->color, index);
          } break;
        case 4:
          {
            sprintf(sql, "UPDATE articles SET weight = '%s' WHERE id=%d", 
              article->weight, index);
          } break;
        case 5:
          {
            sprintf(sql, "UPDATE articles SET dimensions = '%s' WHERE id=%d", 
              article->dimensions, index);
          } break;
        case 6:
          {
            sprintf(sql, "UPDATE articles SET asin = '%s' WHERE id=%d", 
              article->asin, index);
          } break; 
        case 7:
          {
            sprintf(sql, "UPDATE articles SET stock = '%s' WHERE id=%d", 
              article->stock, index);
          } break;
        case 8:
          {
            sprintf(sql, "UPDATE articles SET provider = '%s' WHERE id=%d", 
              article->provider, index);
          } break; 
        case 9:
          {
            sprintf(sql, "UPDATE articles SET description = '%s' WHERE id=%d", 
              article->description, index);
          } break;                                                         
   }//End switch 

   rc = sqlite3_open("article.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return false;
   }//End if

   rc = sqlite3_exec(db, sql, 0, NULL, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      return false;
   }//End if

   sqlite3_close(db);
    return true;
}/* end edit entry */


int find_entry(sqlite3* db, const char *article_name)
{
   unsigned int c;

   int callback(void *data, int argc, char **argv, char **azColName){
     c = 0;
     for(int i = 0; i<argc; i++){
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
       c++; 
     }   
     printf("\n");   
     return 0;
   }

   rc = sqlite3_open("article.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return 0;
   }//End if

   sprintf(sql, "SELECT * FROM articles WHERE article_name LIKE '%s'", article_name);

   rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      return 0;
   }//End if

   sqlite3_close(db);
    return c;
} /* end find entry */


int assert_credentials(sqlite3* db, const char *username, const char *password)
{
   unsigned int k;
   const char* data = "Verify login credentials\n";

   int callback(void *data, int argc, char **argv, char **azColName){
     
   fprintf(stderr, "%s: ", (const char*)data);
   k = (int) strtol(argv[0], NULL, 10);     
   
   return 0;
}

   rc = sqlite3_open("article.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }//End if

   sprintf(sql, "SELECT COUNT(*) AS resp FROM articles WHERE username LIKE '%s' AND password LIKE '%s'", username, password);

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }//End if
   sqlite3_close(db);

   return k;
}//End assert credentials

