#ifndef ARTICLE_H
#define ARTICLE_H

/*! \file article.h
 *  \brief Definitions for memory allocated entries.
 *
 *  The entry datatype supports the sage of attributes pertaining to
 *  entries from an article catalog, such as article name, model,
 *  weight and Description.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sqlite3.h>

#define MAXLENGTH   512

   sqlite3 *db;
   char *zErrMsg;
   int rc;
   char sql[MAXLENGTH];

/*! \typedef article_t
 *  \brief Type definition for article catalog entries.
 */
struct article
{
  char article_name  [MAXLENGTH];        
  char model         [MAXLENGTH]; 
  char color         [MAXLENGTH];         
  char weight        [MAXLENGTH];      
  char dimensions    [MAXLENGTH];   
  char asin          [MAXLENGTH]; 
  char stock         [MAXLENGTH]; 
  char provider      [MAXLENGTH]; 
  char description   [MAXLENGTH]; 
};
typedef struct article article_t;


/*! \fn bool add_entry(sqlite3* db, article_t* article)
 *  \brief Creates an entry.
 *  \return On success true.
 *  Otherwise false is returned and errno is set appropriately.
 */
extern bool add_entry(sqlite3* db, article_t* article);

/*! \fn  int display_entries(sqlite3* db)
 *  \brief Display entries.
 *  \return On success count of entries.
 *  Otherwise 0 is returned and errno is set appropriately.
 */
extern int display_entries(sqlite3* db);

/*! \fn bool delete_entry(const unsigned int index)
 *  \brief Delete an entry.
 *  \return On success true.
 *  Otherwise false is returned and errno is set appropriately.
 */
extern bool delete_entry(const unsigned int index);

/*! \fn bool edit_entry(const unsigned int index, const unsigned int field_option, article_t* article)
 *  \brief Edit an entry.
 *  \return On success true.
 *  Otherwise false is returned and errno is set appropriately.
 */
extern bool edit_entry(const unsigned int index, const unsigned int field_option, article_t* article);

/*! \fn  int find_entry(sqlite3* db, const char *article_name)
 *  \brief Find a entry.
 *  \return On success count of entries.
 *  Otherwise 0 is returned and errno is set appropriately.
 */
extern int find_entry(sqlite3* db, const char *article_name);

/*! \fn  int assert_credentials(sqlite3* db, const char *username, const char *password)
 *  \brief Find a entry.
 *  \return On success 1.
 *  Otherwise 0 is returned and errno is set appropriately.
 */
extern int assert_credentials(sqlite3* db, const char *username, const char *password);

#endif /* ARTICLE_H */
