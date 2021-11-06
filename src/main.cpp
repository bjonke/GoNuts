#include <ctime>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

SDL_Point BadgerPosition;
SDL_Point BadgerTwoPosition;
int TileSize = 50;
int FieldSize = 10;
SDL_Surface * GameOverScreen;
SDL_Texture * GameOverTexture;
SDL_Texture * BackgroundTexture;

#define WAV_PATH "./data/Morph.wav"
#define POSITIVE_OGG_PATH "./data/positive.ogg"
#define NEGATIVE_OGG_PATH "./data/negative.ogg"
#define MUS_PATH "./data/race-duel-short.wav"

// Our wave file
Mix_Chunk *wave = NULL;
Mix_Chunk *negative = NULL;
Mix_Chunk *positive = NULL;
// Our music file
Mix_Music *music = NULL;

void CheckBadgerPosition()
{
    if(BadgerPosition.x < 0)
        BadgerPosition.x = 0;
    if(BadgerPosition.y < 0)
        BadgerPosition.y = 0;
    if(BadgerPosition.x > TileSize*FieldSize-TileSize)
        BadgerPosition.x = TileSize*FieldSize-TileSize;
    if(BadgerPosition.y > TileSize*FieldSize-TileSize)
        BadgerPosition.y = TileSize*FieldSize-TileSize;

    if(BadgerTwoPosition.x < 0)
        BadgerTwoPosition.x = 0;
    if(BadgerTwoPosition.y < 0)
        BadgerTwoPosition.y = 0;
    if(BadgerTwoPosition.x > TileSize*FieldSize-TileSize)
        BadgerTwoPosition.x = TileSize*FieldSize-TileSize;
    if(BadgerTwoPosition.y > TileSize*FieldSize-TileSize)
        BadgerTwoPosition.y = TileSize*FieldSize-TileSize;
}

int AcornField[10][10];

bool GameOver()
{
    int GoodAcorns = 0;
	for(int Col = 0; Col < FieldSize; Col++)
	{
		for(int Row = 0; Row < FieldSize; Row++)
		{
            if(AcornField[Row][Col] == 0)
            {
                GoodAcorns++;
            }
            else
            {
            }
        }
    }

    if(GoodAcorns == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
};

SDL_Texture* testTexture;
SDL_Texture* LoadTexture( const std::string &str );
SDL_Renderer * renderer;

int main(int argc, char ** argv)
{
    BadgerPosition.x = 0;
    BadgerPosition.y = 0;

    BadgerTwoPosition.x = TileSize*FieldSize-TileSize;
    BadgerTwoPosition.y = 0;

    int Score = 0;
    int ScoreTwo = 0;

	for(int Col = 0; Col < FieldSize; Col++)
	{
	    for(int Row = 0; Row < FieldSize; Row++)
	    {
                 AcornField[Row][Col] = rand() % 4;
	    }
	}

    // variables

    bool quit = false;
    SDL_Event event;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        std::cout << "Failed to OpenAudio" << std::endl;
        return -1;
    }

    // Load our sound effect
    wave = Mix_LoadWAV(WAV_PATH);
    if (wave == NULL)
    {
        std::cout << "Failed loading wave" << std::endl;
        return -1;
    }

    // Load our sound effect
    positive = Mix_LoadWAV(POSITIVE_OGG_PATH);
    if (positive == NULL)
    {
        std::cout << "Failed loading positive wave" << std::endl;
        return -1;
    }

    // Load our sound effect
    negative = Mix_LoadWAV(NEGATIVE_OGG_PATH);
    if (negative == NULL)
    {
        std::cout << "loading negative failed" << std::endl;
        return -1;
    }

    // Load our music
    music = Mix_LoadMUS(MUS_PATH);
    if (music == NULL)
    {
        std::cout << "Failed loading music" << std::endl;
        return -1;
    }

    if ( Mix_PlayMusic( music, -1) == -1 )
    {
        std::cout << "Failed playing music" << std::endl;
        return -1;
    }

    SDL_Window * window = SDL_CreateWindow("GoNuts",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TileSize*FieldSize, TileSize*FieldSize, 0);

    SDL_Surface* surface = IMG_Load( "./data/atari.png" );

    // The icon is attached to the window pointer
    SDL_SetWindowIcon(window, surface);

    SDL_FreeSurface(surface);

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface * AcornsBMP = IMG_Load("./data/Acorns.png");//SDL_LoadBMP("Acorns.bmp");
    SDL_Texture * AcornsTexture = SDL_CreateTextureFromSurface(renderer, AcornsBMP);
    SDL_FreeSurface(AcornsBMP);

    SDL_Surface * BadAcornsBMP = IMG_Load("./data/BadAcorns.png");//SDL_LoadBMP("BadAcorns.bmp");
    SDL_Texture * BadAcornsTexture = SDL_CreateTextureFromSurface(renderer, BadAcornsBMP);
    SDL_FreeSurface(BadAcornsBMP);

    SDL_Surface * BadgerBMP = IMG_Load("./data/Badger.png");//SDL_LoadBMP("Badger.bmp");
    SDL_Texture * BadgerTexture = SDL_CreateTextureFromSurface(renderer, BadgerBMP);
    SDL_FreeSurface(BadgerBMP);

    SDL_Surface * BadgerTwoBMP = IMG_Load("./data/Badger.png");//SDL_LoadBMP("Badger.bmp");
    SDL_Texture * BadgerTwoTexture = SDL_CreateTextureFromSurface(renderer, BadgerTwoBMP);
    SDL_FreeSurface(BadgerTwoBMP);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // handle events
    std::string f_str;
    while (!quit)
    {
        quit = GameOver();
        f_str = "";
        f_str += "Badger One: ";
        f_str += std::to_string(Score);
        std::string e_str = std::to_string(ScoreTwo);
        f_str += " | Badger Two: ";
        f_str += e_str;
        SDL_SetWindowTitle(window, f_str.c_str());
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE: quit = true; break;
                case SDLK_LEFT:  BadgerPosition.x -= TileSize; std::cout << "LEFT" << std::endl; break;
                case SDLK_RIGHT: BadgerPosition.x += TileSize; std::cout << "RIGHT" << std::endl; break;
                case SDLK_UP:    BadgerPosition.y -= TileSize; std::cout << "UP" << std::endl; break;
                case SDLK_DOWN:  BadgerPosition.y += TileSize; std::cout << "DOWN" << std::endl; break;

                case SDLK_a: BadgerTwoPosition.x -= TileSize; std::cout << "LEFT" << std::endl; break;
                case SDLK_d: BadgerTwoPosition.x += TileSize; std::cout << "RIGHT" << std::endl; break;
                case SDLK_w: BadgerTwoPosition.y -= TileSize; std::cout << "UP" << std::endl; break;
                case SDLK_s: BadgerTwoPosition.y += TileSize; std::cout << "DOWN" << std::endl; break;
            } break;
        }

        CheckBadgerPosition();
        // Set render color to red ( background will be rendered in this color )
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderClear(renderer);

        SDL_Rect BackgroundRectangle = {0,0,TileSize*FieldSize,TileSize*FieldSize};
        BackgroundTexture = LoadTexture("./data/atari-abstract-clouds.jpg");
        SDL_SetTextureBlendMode( BackgroundTexture, SDL_BLENDMODE_BLEND );
        SDL_RenderCopy( renderer, BackgroundTexture, NULL, &BackgroundRectangle );

        // Set render color to blue ( rect will be rendered in this color )
        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

        //std::cout << "Badger Position: " << BadgerPosition.x << "," << BadgerPosition.y << std::endl;

        for(int Col = 0; Col < FieldSize; Col++)
        {
            for(int Row = 0; Row < FieldSize; Row++)
            {
                // Set render color to blue ( rect will be rendered in this color )
                SDL_SetRenderDrawColor( renderer, 0, 0, 255, 128 );
                // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
                SDL_Rect r;
                r.x = TileSize*Row;
                r.y = TileSize*Col;
                r.w = TileSize;
                r.h = TileSize;

                if( AcornField[Col][Row] == 0)
                {
                    SDL_SetTextureBlendMode( AcornsTexture, SDL_BLENDMODE_BLEND );
                    SDL_SetTextureAlphaMod( AcornsTexture, 255 );
                    SDL_RenderCopy(renderer, AcornsTexture, NULL, &r);

                    if((BadgerPosition.x/TileSize == Row) && (BadgerPosition.y/TileSize == Col))
                    {
                        Score++;
                        AcornField[Col][Row] = 3;
                        if ( Mix_PlayChannel(-1, positive, 0) == -1 )
                            return -1;
                    }
                    if((BadgerTwoPosition.x/TileSize == Row) && (BadgerTwoPosition.y/TileSize == Col))
                    {
                        ScoreTwo++;
                        AcornField[Col][Row] = 3;
                        if ( Mix_PlayChannel(-1, positive, 0) == -1 )
                            return -1;
                    }
                }
                else if( AcornField[Col][Row] == 1)
                {
                    SDL_RenderCopy(renderer, BadAcornsTexture, NULL, &r);

                    if((BadgerPosition.x/TileSize == Row) && (BadgerPosition.y/TileSize == Col))
                    {
                        Score--;
                        AcornField[Col][Row] = 3;
                        if ( Mix_PlayChannel(-1, negative, 0) == -1 )
                             return -1;
                    }
                    if((BadgerTwoPosition.x/TileSize == Row) && (BadgerTwoPosition.y/TileSize == Col))
                    {
                        ScoreTwo--;
                        AcornField[Col][Row] = 3;
                        if ( Mix_PlayChannel(-1, negative, 0) == -1 )
                            return -1;
                    }
                }
                else{}
            }
        }

        SDL_Rect r;
        r.x = BadgerPosition.x;
        r.y = BadgerPosition.y;
        r.w = TileSize;
        r.h = TileSize;

        SDL_Rect r2;
        r2.x = BadgerTwoPosition.x;
        r2.y = BadgerTwoPosition.y;
        r2.w = TileSize;
        r2.h = TileSize;

        SDL_RenderCopy(renderer, BadgerTexture, NULL, &r);
        SDL_RenderCopy(renderer, BadgerTwoTexture, NULL, &r2);

        SDL_RenderPresent(renderer);
    }

    // cleanup SDL

    SDL_DestroyTexture(AcornsTexture);
    SDL_DestroyTexture(BadAcornsTexture);
    SDL_DestroyTexture(BadgerTexture);
    SDL_DestroyTexture(BadgerTwoTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // clean up our resources
    Mix_FreeChunk(wave);
    Mix_FreeMusic(music);

    // quit SDL_mixer
    Mix_CloseAudio();

    SDL_Quit();
    return 0;
}

SDL_Texture* LoadTexture( const std::string &str )
{
    // Load image as SDL_Surface
    SDL_Surface* surface = IMG_Load( str.c_str() );

    // SDL_Surface is just the raw pixels
    // Convert it to a hardware-optimzed texture so we can render it

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Don't need the orignal texture, release the memory
    SDL_FreeSurface( surface );
    return texture;
};


