#pragma once



// ----------------------------------------------------------------------
// Anv�ndning:
// create() - skapar kollisionsobjekt fr�n en bitmap+DC. K�r den f�rst.
//            Skapa ett kollisionobjekt per bild du vill kunna testa.
//
// f�r att kolla om tv� objekt kolliderar, testa dom med funktionen
// objectHasCollided(). Den tar som parametrar tv� kollisionsobjekt, och
// deras respektive positioner.
//
// Se exempelkod f�r detaljer.
//
// ----------------------------------------------------------------------

class CollisionObject
{
	public:
		CollisionObject() : m_width(0), m_height(0) { memset( m_cbits, 0, sizeof(int)*32 ); }
		//CollisionObject( HDC &hdc, HBITMAP &hbmp, COLORREF col ) : m_width(0), m_height(0) { create( hdc, hbmp, col ); }
		~CollisionObject() {}


		//void create( HDC &hdc, HBITMAP &hbmp, COLORREF col );
		//void drawCollisionData( HDC hdc, int xPos, int yPos );	// for debugging...



	private:

		int m_cbits[32];
		int m_width, m_height;

		// For convinience
		friend int objectHasCollided(	CollisionObject *c1, int x1, int y1,
										CollisionObject *c2, int x2, int y2 );
		//bool getPreservedPixel( HDC hdc, int x, int y, int dx, int dy, COLORREF col );
};



// Global tester function...
int objectHasCollided( CollisionObject *c1, int cx1, int cy1,
					    CollisionObject *c2, int cx2, int cy2 );
