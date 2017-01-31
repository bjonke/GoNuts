#include "CollisionObject.h"
#include <stdio.h>




// ---------------------------------------------------------------------------
// create() - create collision data from bitmap and hdc
// ---------------------------------------------------------------------------
void CollisionObject::create( HDC &hdc, HBITMAP &hbmp, COLORREF col )
{
	// Clear current collision data
	memset( m_cbits, 0, sizeof(int)*32 );

	
	// Get dimensions
	BITMAP bmp;
	GetObject( hbmp, sizeof(BITMAP), &bmp );
	m_width = bmp.bmWidth;
	m_height = bmp.bmHeight;

	int rx = 0, ry = 0;
	//int dx = 1 + ((m_width-1) >> 5);
	//int dy = 1 + ((m_height-1) >> 5);
	int dx = 2, dy = 2;

	int endX = min( m_width/dx, 32 );
	int endY = min( m_height/dy, 32 );

	
	// Create collision data, pixels -> bitmask
	for( int y = 0; y < endY; y++ )
	{
		for( int x = 0; x < endX; x++ )
		{
			int bitNr = 1 << (31-x);
	
			//if( GetPixel( hdc, rx, ry ) )	// inaccurate determination... fix
			if( getPreservedPixel( hdc, rx, ry, dx, dy, col ) )
				m_cbits[y] |= bitNr;	// add bit to mask

			rx += dx;
		}

		rx = 0;
		ry += dy;
	} 
}


// ---------------------------------------------------------------------------
// getPreservedPixel() - determine collidable pixel more accurately
// ---------------------------------------------------------------------------
bool CollisionObject::getPreservedPixel( HDC hdc, int xPos, int yPos, int dx, int dy, COLORREF col )
{
	int count = 0;

	for( int y = 0; y < dy; y++ )
		for( int x = 0; x < dx; x++ )
			if( col != GetPixel( hdc, x+xPos, y+yPos ) )	// is the pixel collideable?
				count++;

	if( count > ((dx-1)*(dy-1))/2 )	// if more than half of the subpixels are 
		return true;				// collideable, then this pixel is collidealble

	// No collision-pixel
	return false;
}



// ---------------------------------------------------------------------------
// drawCollisionData() - render collision data to DC (for debugging)
// ---------------------------------------------------------------------------
void CollisionObject::drawCollisionData( HDC hdc, int xPos, int yPos )
{
	for( int y = 0; y < 32; y++ )
		for( int x = 0; x < 32; x++ )
		{
			if( m_cbits[y] & (1 << (31-x)) )
				SetPixel( hdc, x+xPos, y+yPos, RGB(255,0,0) );
			else
				SetPixel( hdc, x+xPos, y+yPos, RGB(0,0,0) );
		}
}



// ---------------------------------------------------------------------------
// swap() - swap contents of two variables
// ---------------------------------------------------------------------------
template <class T>
void swap( T &a, T &b )
{
	T temp = a;
	a = b;
	b = temp;
}



// ---------------------------------------------------------------------------
// objectHasCollided() - check collision between two COBs
// ---------------------------------------------------------------------------
int objectHasCollided( CollisionObject *c1, int x1, int y1, 
					    CollisionObject *c2, int x2, int y2 )
{
	// Early-out.. check overlapping rectangles
	if( (x2 - x1) > c1->m_width  ) return 0;
	if( (y2 - y1) > c1->m_height ) return 0;
	if( (x1 - x2) > c2->m_width  ) return 0;
	if( (y1 - y2) > c2->m_height ) return 0;


	// Determine leftmost
	if( x2 < x1 )
	{
		swap( c1, c2 );
		swap( x1, x2 );
		swap( y1, y2 );
	}


	// Calc scale
	//int dx = 1 + ((m_width-1) >> 5);
	//int dy = 1 + ((m_height-1) >> 5);
	int dx = 2, dy = 2;
	
	// c1 is now leftmost, calc horizontal distance
	int hDist = (x2 - x1) / dx;



	
	// Determine topmost
/*	if( y2 > y1 )	// c1 is topmost?
	{
		int startRow = (y2 - y1) / dy;
		int endRow = 32 - startRow;
		
		for( int y = 0; y < endRow; y++ )
			if( (c1->m_cbits[y+startRow] << hDist) & c2->m_cbits[y] )
				return 2;	// pixelwise collision!
	}
	else	// c2 is topmost?
	{
		int startRow = (y1 - y2) / dy;
		int endRow = 32 - startRow;

		for( int y = 0; y < endRow; y++ )
			if( (c1->m_cbits[y] << hDist) & c2->m_cbits[y+startRow] )
				return 2;	// pixelwise collision!
	}*/




	// Possible collision
	// return 1;
	return 0;
}



