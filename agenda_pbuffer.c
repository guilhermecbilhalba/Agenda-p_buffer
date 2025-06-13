#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PESSOA ( 10 * sizeof( char ) + sizeof( int ) + 10 * sizeof( char ) )

int main() {
    void *pBuffer = malloc( 4 * sizeof( int ) + 10 + 10 ); 
    if ( !pBuffer ) return 1; 
    *( ( int * )pBuffer ) = 0;     // opcao
    *( ( int * )pBuffer + 1 ) = 0; // pessoas

    while ( 1 ) {
        printf( "\n==================== AGENDA ====================\n" );
        printf( "1 - Adicionar Pessoa\n2 - Remover Pessoa\n3 - Buscar Pessoa\n4 - Listar Todos\n5 - Sair\nOpcao: " );
        scanf( "%d", ( int * )pBuffer );
        getchar();

        if ( *( ( int * )pBuffer ) == 1 ) {
            // Adicionar pessoa
            printf( "Nome: " );
            *( ( int * )pBuffer + 2 ) = 0;
            while ( *( ( int * )pBuffer + 2 ) < 9 ) {
                *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) = getchar();
                if ( *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) == '\n' ) break;
                *( ( int * )pBuffer + 2 ) += 1;
            }
            *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) = '\0';

            printf( "Idade: " );
            scanf( "%d", ( int * )pBuffer + 3 );
            getchar();

            printf( "Email: " );
            *( ( int * )pBuffer + 2 ) = 0;
            while ( *( ( int * )pBuffer + 2 ) < 9 ) {
                *( ( char * )pBuffer + 4 * sizeof( int ) + 10 + *( ( int * )pBuffer + 2 ) ) = getchar();
                if ( *( ( char * )pBuffer + 4 * sizeof( int ) + 10 + *( ( int * )pBuffer + 2 ) ) == '\n' ) break;
                *( ( int * )pBuffer + 2 ) += 1;
            }
            *( ( char * )pBuffer + 4 * sizeof( int ) + 10 + *( ( int * )pBuffer + 2 ) ) = '\0';

        
            pBuffer = realloc( pBuffer, 4 * sizeof( int ) + 10 + 10 + ( *( ( int * )pBuffer + 1 ) + 1 ) * TAM_PESSOA );
            if ( !pBuffer ) return 1;

            void *dest = ( char * )pBuffer + 4 * sizeof( int ) + 10 + 10 + ( *( ( int * )pBuffer + 1 ) ) * TAM_PESSOA;
            strcpy( ( char * )dest, ( char * )pBuffer + 4 * sizeof( int ) ); 
            *( ( int * )( ( char * )dest + 10 ) ) = *( ( int * )pBuffer + 3 );   
            strcpy( ( char * )dest + 10 + sizeof( int ), ( char * )pBuffer + 4 * sizeof( int ) + 10 ); 

            *( ( int * )pBuffer + 1 ) += 1;
            printf( "Pessoa adicionada!\n" );
        } else if ( *( ( int * )pBuffer ) == 2 ) {
            // Remover pessoa
            printf( "Nome a remover: " );
            *( ( int * )pBuffer + 2 ) = 0;
            while ( *( ( int * )pBuffer + 2 ) < 9 ) {
                *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) = getchar();
                if ( *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) == '\n' ) break;
                *( ( int * )pBuffer + 2 ) += 1;
            }
            *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) = '\0';

            *( ( int * )pBuffer + 3 ) = 0; 
            for ( *( ( int * )pBuffer + 2 ) = 0; *( ( int * )pBuffer + 2 ) < *( ( int * )pBuffer + 1 ); ( *( ( int * )pBuffer + 2 ) )++ ) {
                void *pessoa = ( char * )pBuffer + 4 * sizeof( int ) + 10 + 10 + ( *( ( int * )pBuffer + 2 ) ) * TAM_PESSOA;
                if ( strcmp( ( char * )pessoa, ( char * )pBuffer + 4 * sizeof( int ) ) == 0 ) {
                    memmove( pessoa, ( char * )pessoa + TAM_PESSOA, ( ( *( ( int * )pBuffer + 1 ) - ( *( ( int * )pBuffer + 2 ) ) - 1 ) * TAM_PESSOA ) );
                    *( ( int * )pBuffer + 1 ) -= 1;
                    pBuffer = realloc( pBuffer, 4 * sizeof( int ) + 10 + 10 + ( *( ( int * )pBuffer + 1 ) ) * TAM_PESSOA );
                    printf( "Pessoa removida!\n" );
                    *( ( int * )pBuffer + 3 ) = 1; 
                    break;
                }
            }
            if ( !( *( ( int * )pBuffer + 3 ) ) ) printf( "Pessoa nao encontrada!\n" );
        } else if ( *( ( int * )pBuffer ) == 3 ) {
            // Buscar pessoa
            printf( "Nome a buscar: " );
            *( ( int * )pBuffer + 2 ) = 0;
            while ( *( ( int * )pBuffer + 2 ) < 9 ) {
                *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) = getchar();
                if ( *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) == '\n' ) break;
                *( ( int * )pBuffer + 2 ) += 1;
            }
            *( ( char * )pBuffer + 4 * sizeof( int ) + *( ( int * )pBuffer + 2 ) ) = '\0';

            *( ( int * )pBuffer + 3 ) = 0; // found = 0
            for ( *( ( int * )pBuffer + 2 ) = 0; *( ( int * )pBuffer + 2 ) < *( ( int * )pBuffer + 1 ); ( *( ( int * )pBuffer + 2 ) )++ ) {
                void *pessoa = ( char * )pBuffer + 4 * sizeof( int ) + 10 + 10 + ( *( ( int * )pBuffer + 2 ) ) * TAM_PESSOA;
                if ( strcmp( ( char * )pessoa, ( char * )pBuffer + 4 * sizeof( int ) ) == 0 ) {
                    printf( "Nome: %s\n", ( char * )pessoa );
                    printf( "Idade: %d\n", *( ( int * )( ( char * )pessoa + 10 ) ) );
                    printf( "Email: %s\n", ( char * )pessoa + 10 + sizeof( int ) );
                    *( ( int * )pBuffer + 3 ) = 1; // found = 1
                    break;
                }
            }
            if ( !( *( ( int * )pBuffer + 3 ) ) ) printf( "Pessoa nao encontrada!\n" );
        } else if ( *( ( int * )pBuffer ) == 4 ) {
            // Listar todos
            if ( *( ( int * )pBuffer + 1 ) == 0 ) {
                printf( "Agenda vazia!\n" );
            } else {
                for ( *( ( int * )pBuffer + 2 ) = 0; *( ( int * )pBuffer + 2 ) < *( ( int * )pBuffer + 1 ); ( *( ( int * )pBuffer + 2 ) )++ ) {
                    void *pessoa = ( char * )pBuffer + 4 * sizeof( int ) + 10 + 10 + ( *( ( int * )pBuffer + 2 ) ) * TAM_PESSOA;
                    printf( "Nome: %s | Idade: %d | Email: %s\n",
                        ( char * )pessoa,
                        *( ( int * )( ( char * )pessoa + 10 ) ),
                        ( char * )pessoa + 10 + sizeof( int ) );
                }
            }
        } else if ( *( ( int * )pBuffer ) == 5 ) {
            free( pBuffer );
            break;
        }
    }
    return 0;
}