//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#include "TextureManager.h"
#include <stdio.h>
#include <iostream>
using namespace std;

TextureManager* TextureManager::m_inst(0);

TextureManager* TextureManager::Inst()
{
	if(!m_inst)
		m_inst = new TextureManager();

	return m_inst;
}

TextureManager::TextureManager()
{
	// call this ONLY when linking with FreeImage as a static library
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif
}

//these should never be called
//TextureManager::TextureManager(const TextureManager& tm){}
//TextureManager& TextureManager::operator=(const TextureManager& tm){}

TextureManager::~TextureManager()
{
	// call this ONLY when linking with FreeImage as a static library
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif

	UnloadAllTextures();
	m_inst = 0;
}

bool TextureManager::LoadTexture(const char* filename, const unsigned int texID, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);

	//Identificador para la imagen de OpenGL
	// GLuint es un entero sin signo de 32 bits.
	GLuint gl_texID;

	//check the file signature and deduce its format
	//Comprueba la firma de la imagen y deduce de esta su formato.
	fif = FreeImage_GetFileType(filename, 0);


	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if(!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);

	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	cout << "La imagen mide " << width << " x " << height << endl;

    //Si no se hubieran cargado los datos o su tamaño correctamente saldríamos de la función
	//if this somehow one of these failed (they shouldn't), return failure
	if((bits == 0) || (width == 0) || (height == 0))
		return false;



	//if this texture ID is in use, unload the current texture
	if(m_texID.find(texID) != m_texID.end())
		glDeleteTextures(1, &(m_texID[texID]));

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);

    cout << "heeeo" << endl;

    GLenum    glError=glGetError();
    if(glError!=GL_NO_ERROR){
        cout << "Error tras glGenTextures: " << gluErrorString(glError) << endl;
    }
     cout << "gl_textID" << gl_texID << endl;


	//store the texture ID mapping
	m_texID[texID] = gl_texID;


	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);


    cout << "heeeo" << endl;
//       GLenum glError;
    glError=glGetError();
    if(glError!=GL_NO_ERROR){
        cout << "Error tras glGenTextures: " << gluErrorString(glError) << endl;
    }else{
    cout << "no error";}

    //Vamos a probar con una imagen diseñada por nosotros:
    //Una imagen de 10x10 necesita 100 píxeles que son a 3 byte por pixel 300 bytes.
    unsigned char imagen[100][3];

    for(int i=0; i<100; i++)
        for(int j=0; j<3; j++)
            imagen[i][j]=0; //Todo negro


    //Sacar todo de aquí... y probar sólo con la imagen pasada!!!

	//store the texture data for OpenGL use
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 10, 10, 0, GL_RGB, GL_UNSIGNED_BYTE, &imagen);

    glError=glGetError();
    if(glError!=GL_NO_ERROR){
        cout << GL_NO_ERROR ;
        cout << "Error tras glTexImage2D: "  << gluErrorString(glError) << endl;
        cout << "error crudo: " << glError << endl;
    }else{
    cout << "no error tras TexImage";}


	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	//return success
	return true;
}

bool TextureManager::UnloadTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, unload it's texture, and remove it from the map
	if(m_texID.find(texID) != m_texID.end())
	{
		glDeleteTextures(1, &(m_texID[texID]));
		m_texID.erase(texID);
	}
	//otherwise, unload failed
	else
	{
		result = false;
	}

	return result;
}

bool TextureManager::BindTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, bind it's texture as current
	if(m_texID.find(texID) != m_texID.end()){
		glBindTexture(GL_TEXTURE_2D, m_texID[texID]);

	//otherwise, binding failed
	}else
		result = false;

	return result;
}

void TextureManager::UnloadAllTextures()
{
	//start at the begginning of the texture map
	std::map<unsigned int, GLuint>::iterator i = m_texID.begin();

	//Unload the textures untill the end of the texture map is found
	while(i != m_texID.end())
		UnloadTexture(i->first);

	//clear the texture map
	m_texID.clear();
}
