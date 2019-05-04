/*! \file main.c
 *  \brief Definitions for main function.
 *
 */


#include <assert.h>
#include <termios.h>
#include <signal.h>
#include <errno.h>
#include <article.h>
   
typedef enum
{
    ADD=1,
    DISPLAY,
    FIND_BY_ARTICLENAME,
    EDIT,
    DELETE
} option_t;

struct termios saved_term;

static int login( void );
static void restore_terminal( void );
static void sigint_handler( int sig );

int main( int argc, char *argv[ ] )
{
    if( login( ) == 1 )
    {
        int option;

        do {
            printf( "\
            [1] Add new entry\n\
            [2] Display a list of all entries\n\
            [3] Find entries by article name\n\
            [4] Edit an entry\n\
            [5] Delete an entry\n\
            [0] Exit\n\
            --> " );
            scanf( "%d", &option );
            while( getchar( ) != '\n' );

            switch( option )
            {
                case ADD:
                {
                    article_t article;
                    unsigned int c;

                    printf("Please enter the article name: ");
                    scanf("%s", article.article_name);
        
                    printf("Please enter the model: ");
                    scanf("%s", article.model);

                    printf("Please enter the color: ");
                    scanf("%s", article.color);
        
                    printf("Please enter the weight: ");
                    scanf("%s", article.weight);

                    printf("Please enter the dimensions: ");
                    scanf("%s", article.dimensions);
        
                    printf("Please enter the asin: ");
                    scanf("%s", article.asin);

                    printf("Please enter the stock: ");
                    scanf("%s", article.stock);
        
                    printf("Please enter the provider: ");
                    scanf("%s", article.provider);

                    printf("Please enter the description: ");
                    scanf("%s", article.description);
        
                    if(!add_entry(db, &article)) 
                    {
                        perror ("Error on add entry\n");
                        printf( "Value of errno: %d\n", errno );           
                    }//End if
                    
                    c = display_entries(db);
                    if (c == 0)
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }
                    putc('\n', stdout);

                    } break;//End add case
                case DISPLAY:
                    {
                    unsigned int c; 

                    c = display_entries(db);
                    if (c == 0)
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }
                    putc('\n', stdout);

                    } break;//End display case
                case FIND_BY_ARTICLENAME:
                    {
                    char article_name[ MAXLENGTH ];
                    article_t article;
                    int next_option;
                    unsigned int c;

                    printf( "Enter article name: " );
                    scanf( "%[^\n]", article_name );
                    while( getchar( ) != '\n' );

                    c = find_entry(db, article_name);
                    if ( c == 0 )
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }//End if

                    do 
                    {
                        printf( "\
                        [1] Edit entry\n\
                        [2] Delete entry\n\
                        [0] Exit\n\
                        --> " );
                        scanf( "%d", &next_option );
                        while( getchar( ) != '\n' );

                        switch( next_option )
                        {
                         case 1:
                             {
                              int field_option;
                              unsigned int index;

                              do 
                              {
                               printf( "Enter index from list: " );
                               scanf( "%d", &index );
                              } while( getchar( ) != '\n' );

                              do 
                              {
                               printf( "\
                               What field to wish to edit?\n\
                               [1] Article name\n\
                               [2] Model\n\
                               [3] Color\n\
                               [4] Weight\n\
                               [5] Dimensions\n\
                               [6] Asin\n\
                               [7] Stock\n\
                               [8] Provider\n\
                               [9] Description\n\
                               [0] Exit\n\
                               --> " );
                               scanf( "%d", &field_option );
                               while( getchar( ) != '\n' );

                               switch( field_option )
                               {
                                case 1:
                                    {
                                     printf("Please enter the article name: ");
                                     scanf("%s", article.article_name);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit article name entry\n");
                                     }else{
                                         perror ("Error on edit article name entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 2:
                                    {
                                     printf("Please enter the model: ");
                                     scanf("%s", article.model);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit model entry\n");
                                     }else{
                                         perror ("Error on edit model entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 3:
                                    {
                                     printf("Please enter the color: ");
                                     scanf("%s", article.color);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit color entry\n");
                                     }else{
                                         perror ("Error on edit color entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 4:
                                    {
                                     printf("Please enter the weight: ");
                                     scanf("%s", article.weight);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit weight entry\n");
                                     }else{
                                         perror ("Error on edit weight entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 5:
                                    {
                                     printf("Please enter the dimensions: ");
                                     scanf("%s", article.dimensions);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit dimensions entry\n");
                                     }else{
                                         perror ("Error on edit dimensions entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 6:
                                    {
                                     printf("Please enter the asin: ");
                                     scanf("%s", article.asin);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit asin entry\n");
                                     }else{
                                         perror ("Error on edit asin entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 7:
                                    {
                                     printf("Please enter the stock: ");
                                     scanf("%s", article.stock);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit stock entry\n");
                                     }else{
                                         perror ("Error on edit stock entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 8:
                                    {
                                     printf("Please enter the provider: ");
                                     scanf("%s", article.provider);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit provider entry\n");
                                     }else{
                                         perror ("Error on edit provider entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 9:
                                    {
                                     printf("Please enter the description: ");
                                     scanf("%s", article.description);
                                                                
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit description entry\n");
                                     }else{
                                         perror ("Error on edit description entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;                                                
                                }//End switch

                                } while( field_option != 0 );

                             } break;
                         case 2:
                             {
                              unsigned int index;

                              do {
                                  printf( "Enter index from list: " );
                                  scanf( "%d", &index );
                              } while( getchar( ) != '\n' );

                              if (delete_entry( index )){
                                  printf( "Entry %d deleted successfully\n", index );
                              }else{
                                  perror ("Error on delete entry\n");
                                  printf( "Value of errno: %d\n", errno );           
                              }//End if
                              
                             } break;
                         }//End switch
                         
                         } while( next_option != 0 );                        
                    } break; /* end case find */
                case EDIT: 
                    {
                     article_t article;
                     int next_option;
                     unsigned int c;

                    c = display_entries(db);
                    if (c == 0)
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }//End if

                    do 
                    {
                        printf( "\
                        [1] Edit entry\n\
                        [2] Delete entry\n\
                        [0] Exit\n\
                        --> " );
                        scanf( "%d", &next_option );
                        while( getchar( ) != '\n' );

                        switch( next_option )
                        {
                         case 1:
                             {
                              int field_option;
                              unsigned int index;

                              do 
                              {
                               printf( "Enter index from list: " );
                               scanf( "%d", &index );
                              } while( getchar( ) != '\n' );

                              do 
                              {
                               printf( "\
                               What field to wish to edit?\n\
                               [1] Article name\n\
                               [2] Model\n\
                               [3] Color\n\
                               [4] Weight\n\
                               [5] Dimensions\n\
                               [6] Asin\n\
                               [7] Stock\n\
                               [8] Provider\n\
                               [9] Description\n\
                               [0] Exit\n\
                               --> " );
                               scanf( "%d", &field_option );
                               while( getchar( ) != '\n' );

                               switch( field_option )
                               {
                                case 1:
                                    {
                                     printf("Please enter the article name: ");
                                     scanf("%s", article.article_name);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit article name entry\n");
                                     }else{
                                         perror ("Error on edit article name entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 2:
                                    {
                                     printf("Please enter the model: ");
                                     scanf("%s", article.model);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit model entry\n");
                                     }else{
                                         perror ("Error on edit model entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 3:
                                    {
                                     printf("Please enter the color: ");
                                     scanf("%s", article.color);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit color entry\n");
                                     }else{
                                         perror ("Error on edit color entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 4:
                                    {
                                     printf("Please enter the weight: ");
                                     scanf("%s", article.weight);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit weight entry\n");
                                     }else{
                                         perror ("Error on edit weight entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 5:
                                    {
                                     printf("Please enter the dimensions: ");
                                     scanf("%s", article.dimensions);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit dimensions entry\n");
                                     }else{
                                         perror ("Error on edit dimensions entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 6:
                                    {
                                     printf("Please enter the asin: ");
                                     scanf("%s", article.asin);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit asin entry\n");
                                     }else{
                                         perror ("Error on edit asin entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 7:
                                    {
                                     printf("Please enter the stock: ");
                                     scanf("%s", article.stock);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit stock entry\n");
                                     }else{
                                         perror ("Error on edit stock entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 8:
                                    {
                                     printf("Please enter the provider: ");
                                     scanf("%s", article.provider);
                                                              
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit provider entry\n");
                                     }else{
                                         perror ("Error on edit provider entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 9:
                                    {
                                     printf("Please enter the description: ");
                                     scanf("%s", article.description);
                                                                
                                     if (edit_entry( index, field_option, &article )){
                                         printf("successfully edit description entry\n");
                                     }else{
                                         perror ("Error on edit description entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;                                                
                                }//End switch

                                } while( field_option != 0 );

                             } break;
                         case 2:
                             {
                              unsigned int index;

                              do {
                                  printf( "Enter index from list: " );
                                  scanf( "%d", &index );
                              } while( getchar( ) != '\n' );

                              if (delete_entry( index )){
                                  printf( "Entry %d deleted successfully\n", index );
                              }else{
                                  perror ("Error on delete entry\n");
                                  printf( "Value of errno: %d\n", errno );           
                              }///End if
                              
                             } break;
                         }//End switch
                         
                         } while( next_option != 0 ); 
                    } break; /* end case edit */
                case DELETE:
                    {
                    article_t article;  
                    unsigned int c;
                    unsigned int index;
                        
                    c = display_entries(db);
                    if (c == 0)
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }//End if

                    do {
                        printf( "Enter index from list: " );
                        scanf( "%d", &index );
                    } while( getchar( ) != '\n' );

                    if (delete_entry( index )){
                        printf( "Entry %d deleted successfully\n", index );
                    }else{
                        perror ("Error on delete entry\n");
                        printf( "Value of errno: %d\n", errno );           
                    }///End if
                        
                    } break; /* end case delete */
            }
        } while( option != 0 );

    }
    else 
    {
        printf( "Fail to login\n" );
    }//End if

    return 0;
}


int login( void )
{
    struct termios tmp_term;
    struct sigaction sa_sigint;
    char username[ MAXLENGTH ],
         password[ MAXLENGTH ];
         //scanned_line[ MAXLENGTH ],
         //scanned_username[ MAXLENGTH ],
         //scanned_password[ MAXLENGTH ];

    printf( "Enter username: " );
    scanf( "%s", username );

    if( tcgetattr( fileno( stdin ), &saved_term ) == -1 ) 
    {
        perror( "tcgetattr" );
        exit( EXIT_FAILURE );
    }//End if

    tmp_term = saved_term;

    memset( &sa_sigint, 0, sizeof( struct sigaction ) );
    sa_sigint.sa_handler = sigint_handler;
    sa_sigint.sa_flags = 0;

    if( sigaction( SIGINT, &sa_sigint, NULL ) < 0 )
    {
        perror( "sigaction" );
        exit( EXIT_FAILURE );
    }//End if

    tmp_term.c_lflag &= ~ECHO;
    if( tcsetattr( fileno( stdin ), TCSANOW, &tmp_term ) == -1 ) 
    {
        perror( "tcgetattr" );
        exit( EXIT_FAILURE );
    }//End if

    printf( "Enter password: " );
    scanf( "%s", password );

    restore_terminal( );

   return assert_credentials(db, username, password);
}//End login 


void restore_terminal( void )
{
    if( tcsetattr( fileno( stdin ), TCSANOW, &saved_term ) == -1 )
    {
        perror( "tcsetattr" );
        exit( EXIT_FAILURE );
    }//End if
}//End recatalog

void sigint_handler( int sig )
{
    if( SIGINT == sig )
   {
        restore_terminal( );
    }

    exit( EXIT_SUCCESS );
}// End sigint_handler

