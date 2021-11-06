#include "macros.h"
#include <stdio.h>
#include <time.h>

void InitLog( void )
{
	FILE *f;
	char t[256], d[256];

	f = fopen( "log.txt","w" );
	fprintf( f, "Log file started on %s at %s\r\n", _strdate( d ), _strtime( t ) );
	fclose( f );
	f = fopen( "memlog.txt","w" );
	fprintf( f, "Memory Alloc / Dealloc Log file started on %s at %s\r\n", _strdate( d ), _strtime( t ) );
	fclose( f );
}

void Log( char *fl, long ln, char *text )
{
	FILE *f;

	f = fopen( "log.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n", fl, ln, text );
		fclose( f );
	}
}

void MLog( char *fl, long ln, char *text )
{
	FILE *f;

	f = fopen( "memlog.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n", fl, ln, text );
		fclose( f );
	}
}

void MLog1( char *fl, long ln, char *text, char *txt1 )
{
	FILE *f;

	f = fopen( "memlog.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n\r", fl, ln, text );
		fprintf( f, "\t%s\n", txt1 );
		fclose( f );
	}
}

void Log1( char *fl, long ln, char *text, char *txt1 )
{
	FILE *f;

	f = fopen( "log.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n\r", fl, ln, text );
		fprintf( f, "\t%s\n", txt1 );
		fclose( f );
	}
}

void Log1n( char *fl, long ln, char *text, int txt1 )
{
	FILE *f;

	f = fopen( "log.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n", fl, ln, text );
		fprintf( f, "\t%d\n", txt1 );
		fclose( f );
	}
}

void Log2( char *fl, long ln, char *text, char *txt1, char *txt2 )
{
	FILE *f;

	f = fopen( "log.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n", fl, ln, text );
		fprintf( f, "\t%s\n", txt1 );
		fprintf( f, "\t%s\n", txt2 );
		fclose( f );
	}
}

void Log2n( char *fl, long ln, char *text, int txt1, int txt2 )
{
	FILE *f;

	f = fopen( "log.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n", fl, ln, text );
		fprintf( f, "\t%d\n", txt1 );
		fprintf( f, "\t%d\n", txt2 );
		fclose( f );
	}
}

void Log3( char *fl, long ln, char *text, char *txt1, char *txt2, char *txt3 )
{
	FILE *f;

	f = fopen( "log.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n", fl, ln, text );
		fprintf( f, "\t%s\n", txt1 );
		fprintf( f, "\t%s\n", txt2 );
		fprintf( f, "\t%s\n", txt3 );
		fclose( f );
	}
}

void Log3n( char *fl, long ln, char *text, int txt1, int txt2, int txt3 )
{
	FILE *f;

	f = fopen( "log.txt","a" );
	if( f != NULL )
	{
		fprintf( f, "%s,%d - %s\n", fl, ln, text );
		fprintf( f, "\t%d\n", txt1 );
		fprintf( f, "\t%d\n", txt2 );
		fprintf( f, "\t%d\n", txt3 );
		fclose( f );
	}
}
